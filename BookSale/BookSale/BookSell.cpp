// BookSell.cpp : 实现文件
//

#include "stdafx.h"
#include "BookSale.h"
#include "BookSell.h"
#include "afxdialogex.h"
#include "Getprice.h"
#include "BUYNUM.h"

extern _ConnectionPtr m_pConnection;
extern CString user;
extern CString password;

// CBookSell 对话框

IMPLEMENT_DYNAMIC(CBookSell, CDialogEx)

CBookSell::CBookSell(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBookSell::IDD, pParent)
	, b_id(_T(""))
	, b_isbn(_T(""))
	, b_name(_T(""))
	, b_pub(_T(""))
	, g_price(_T(""))
	, g_amount(_T(""))
{

}

CBookSell::~CBookSell()
{
}


void CBookSell::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, bm_list);
}

BEGIN_MESSAGE_MAP(CBookSell, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CBookSell::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CBookSell::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CBookSell::OnBnClickedButton3)
END_MESSAGE_MAP()

BOOL CBookSell::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString str[] = { TEXT("书籍编号"),TEXT("书籍名称"),TEXT("ISBN"), TEXT("零售价"), TEXT("库存数量"),TEXT("状态") };
	for (int i = 0; i < 6; i++) {
		//设置表头：索引，内容，对齐方式，列宽
		bm_list.InsertColumn(i, str[i],LVCFMT_LEFT,90);
	}
	bm_list.SetExtendedStyle(bm_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	_RecordsetPtr m_pAs;
	HRESULT hr;
	hr=m_pAs.CreateInstance(__uuidof(Recordset));
	if(FAILED(hr)){
		MessageBox(TEXT("创建记录集对象失败"));
		return FALSE;
	}
	CString strSQL;
	strSQL=TEXT("select b_id, b_name, ISBN, s_price, s_amount from books");
	try{
		hr=m_pAs->Open(_variant_t(strSQL),m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
		if(FAILED(hr)){
			return FALSE;
		}

		if(m_pAs->GetadoEof()){
			MessageBox(TEXT("结果为空"));///????
			return TRUE;
		}
		else{
			_variant_t var;
			CString strValue;
			int curItem=0;

			bm_list.DeleteAllItems();//把原来的删了
			while(!m_pAs->GetadoEof()){//EOF指示当前位置是否位于记录集的最后一个后
				var=m_pAs->GetCollect((long)0);//通过列号获取当前行第0列  接受_variant_t参数，有long转换的功能，所以转成long
				if(var.vt!=NULL)
					strValue=(LPCTSTR)_bstr_t(var);//把variant类型先转成bstr，再转CString
				bm_list.InsertItem(curItem, strValue);
				////到books找
				//bm_list.SetItemText(curItem, 1, QueryBname(strValue));//b_name
				bm_list.SetItemText(curItem, 5, QueryBstate(strValue));//state在sell中
				for(int i=1;i<5;i++){
					var=m_pAs->GetCollect((long)i);
					if(var.vt!=VT_NULL)
						strValue=(LPCTSTR)_bstr_t(var);
					else
						strValue=TEXT(" ");
					bm_list.SetItemText(curItem, i, strValue);//i为列号
				}
				m_pAs->MoveNext();//移到下一行
				curItem++;
			}
		}

	}
	catch(_com_error *e){
		MessageBox(e->ErrorMessage());
		return FALSE;
	}

	m_pAs->Close();
	m_pAs.Release();
	return TRUE;

}

CString CBookSell::QueryBstate( CString strValue )
{
	CString strSQL;
	CString strst;
	strSQL.Format(TEXT("select s_t from sell where b_id=\'%s\'"), strValue);
	_RecordsetPtr m_pAs;
	HRESULT hr;
	hr=m_pAs.CreateInstance(__uuidof(Recordset));
	if(FAILED(hr)){
		MessageBox(TEXT("创建记录集对象失败"));
		return _T("");
	}
	try{
		hr=m_pAs->Open(_variant_t(strSQL),m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
		if(FAILED(hr)){
			return _T("");
		}
		if(m_pAs->GetadoEof()){
			//MessageBox(TEXT("结果为空"));
			return _T("");
		}
		else{
			_variant_t var;
			var=m_pAs->GetCollect((long)0);//通过列号获取当前行第0列  接受_variant_t参数，有long转换的功能，所以转成long
			if(var.vt!=VT_NULL)
				strst=(LPCTSTR)_bstr_t(var);
			else
				strst=TEXT(" ");
		}
	}
	catch(_com_error *e){
		MessageBox(e->ErrorMessage());
		return _T("");
	}
	m_pAs->Close();
	m_pAs.Release();
	return strst;

}

void CBookSell::OnBnClickedButton1()
{
	QueryAOG();
}

BOOL CBookSell::QueryAOG()
{
	UpdateData(TRUE);
	CString strDate;
	GetDlgItem(IDC_DATETIMEPICKER1)->GetWindowText(strDate);//获得查询时日期
	
	_RecordsetPtr m_pAs;
	HRESULT hr;
	hr=m_pAs.CreateInstance(__uuidof(Recordset));
	if(FAILED(hr)){
		MessageBox(TEXT("创建记录集对象失败"));
		return FALSE;
	}
	CString strSQL=TEXT("select b_id, g_price, g_amount, s_t from sell where s_t=\'2\'");
	strSQL.AppendFormat(TEXT(" and g_price*g_amount in (select budget from account where a_date<=\'%s\')"),strDate);
	try{
		hr=m_pAs->Open(_variant_t(strSQL),m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
		if(FAILED(hr)){
			return FALSE;
		}

		if(m_pAs->GetadoEof()){
			MessageBox(TEXT("结果为空"));
			return TRUE;
		}
		else{
			_variant_t var;
			CString strValue;
			int curItem=0;

			bm_list.DeleteAllItems();//把原来的删了
			while(!m_pAs->GetadoEof()){//EOF指示当前位置是否位于记录集的最后一个后
				var=m_pAs->GetCollect((long)0);//通过列号获取当前行第0列  接受_variant_t参数，有long转换的功能，所以转成long
				if(var.vt!=NULL)
					strValue=(LPCTSTR)_bstr_t(var);//把variant类型先转成bstr，再转CString
				bm_list.InsertItem(curItem, strValue);
				//到books找
				bm_list.SetItemText(curItem, 2, QueryBname(strValue));//b_name
				bm_list.SetItemText(curItem, 1, QueryBisbn(strValue));//isbn
				for(int i=1;i<4;i++){
					var=m_pAs->GetCollect((long)i);
					if(var.vt!=VT_NULL)
						strValue=(LPCTSTR)_bstr_t(var);
					else
						strValue=TEXT(" ");
					bm_list.SetItemText(curItem, i+2, strValue);//i为列号
				}
				m_pAs->MoveNext();//移到下一行
				curItem++;
			}

		}

	}
	catch(_com_error *e){
		MessageBox(e->ErrorMessage());
		return FALSE;
	}

	m_pAs->Close();
	m_pAs.Release();
	return TRUE;
}

CString CBookSell::QueryBisbn( CString strValue)
{
	CString strSQL;
	CString strisbn;
	strSQL.Format(TEXT("select ISBN from books where b_id=\'%s\'"), strValue);
	_RecordsetPtr m_pAs;
	HRESULT hr;
	hr=m_pAs.CreateInstance(__uuidof(Recordset));
	if(FAILED(hr)){
		MessageBox(TEXT("创建记录集对象失败"));
		return _T("");
	}
	try{
		hr=m_pAs->Open((_variant_t)strSQL,m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
		if(FAILED(hr)){
			return _T("");
		}
		if(m_pAs->GetadoEof()){
			MessageBox(TEXT("结果为空"));
			return _T("");
		}
		else{
			_variant_t var;
			var=m_pAs->GetCollect((long)0);//通过列号获取当前行第0列  接受_variant_t参数，有long转换的功能，所以转成long
			if(var.vt!=VT_NULL)
				strisbn=(LPCTSTR)_bstr_t(var);
			else
				strisbn=TEXT(" ");
			}
	}
	catch(_com_error *e){
		MessageBox(e->ErrorMessage());
		return _T("");
	}
	m_pAs->Close();
	m_pAs.Release();
	return strisbn;
}

CString CBookSell::QueryBname( CString strValue )
{
	CString strSQL;
	CString strname;
	strSQL.Format(TEXT("select b_name from books where b_id=\'%s\'"), strValue);
	_RecordsetPtr m_pAs;
	HRESULT hr;
	hr=m_pAs.CreateInstance(__uuidof(Recordset));
	if(FAILED(hr)){
		MessageBox(TEXT("创建记录集对象失败"));
		return _T("");
	}
	try{
		hr=m_pAs->Open((_variant_t)strSQL,m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
		if(FAILED(hr)){
			return _T("");
		}
		if(m_pAs->GetadoEof()){
			MessageBox(TEXT("结果为空"));
			return _T("");
		}
		else{
			_variant_t var;
			var=m_pAs->GetCollect((long)0);
			if(var.vt!=VT_NULL)
				strname=(LPCTSTR)_bstr_t(var);
			else
				strname=TEXT(" ");
		}
	}
	catch(_com_error *e){
		MessageBox(e->ErrorMessage());
		return _T("");
	}
	m_pAs->Close();
	m_pAs.Release();
	return strname;
}

float CBookSell::QuerySprice( CString strValue )
{
	CString strSQL;
	float strprice;
	strSQL.Format(TEXT("select s_price from books where b_id=\'%s\'"), strValue);
	_RecordsetPtr m_pAs;
	HRESULT hr;
	hr=m_pAs.CreateInstance(__uuidof(Recordset));
	if(FAILED(hr)){
		MessageBox(TEXT("创建记录集对象失败"));
		return 0;
	}
	try{
		hr=m_pAs->Open((_variant_t)strSQL,m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
		if(FAILED(hr)){
			return 0;
		}
		if(m_pAs->GetadoEof()){
			MessageBox(TEXT("结果为空"));
			return 0;
		}
		else{
			_variant_t var;
			var=m_pAs->GetCollect((long)0);
			if(var.vt!=VT_NULL)
				strprice=(_variant_t)_bstr_t(var);
			else
				strprice=0;
		}
	}
	catch(_com_error *e){
		MessageBox(e->ErrorMessage());
		return 0;
	}
	m_pAs->Close();
	m_pAs.Release();
	return strprice;
}

void CBookSell::OnBnClickedButton2()
{
	UpdateData(TRUE);
	CString strst;
	CString strbid;
	CString strisbn;
	CString strname;
	CString stramount;
	int sel=bm_list.GetSelectionMark();

	if(sel<0){
		MessageBox(TEXT("请选择要添加的书"));
		return;
	}
	else{
		strst=bm_list.GetItemText(sel, 5);//选中行第5列
		stramount=bm_list.GetItemText(sel, 4);
		strisbn=bm_list.GetItemText(sel, 2);
		strname=bm_list.GetItemText(sel, 1);
		strbid=bm_list.GetItemText(sel, 0);
	}
	int st=_ttoi(strst);
	if(st==1){
		MessageBox(TEXT("尚未付款"));
		return;
	}
	//加入库存
	_RecordsetPtr m_pRs;
	BOOL ret=FALSE;
	m_pRs.CreateInstance(__uuidof(Recordset));
	try{
		HRESULT hr=m_pRs->Open(TEXT("select b_id,ISBN,b_name,s_amount from books"), m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
		//先得到结果集全体，插入一条，写回
		if(SUCCEEDED(hr)&!QueryBisbn(strisbn)){
			m_pRs->AddNew();
			m_pRs->PutCollect("b_id", _variant_t(strbid));
			m_pRs->PutCollect("ISBN", _variant_t(strisbn));
			m_pRs->PutCollect("b_name", _variant_t(strname));
			m_pRs->PutCollect("s_amount", _variant_t(stramount));
			m_pRs->Update();//回写
			ret=TRUE;
		}

	}catch(_com_error *e){
		MessageBox(e->ErrorMessage());
	}

	POSITION pos = bm_list.GetFirstSelectedItemPosition();
	int j = bm_list.GetNextSelectedItem(pos);
	if (j!=-1){
		CString bu_id;
		bu_id = bm_list.GetItemText(sel,0);
		Getprice dlg;
		dlg.bid=bu_id;
		dlg.DoModal();
	}

	if(ret==TRUE){
		MessageBox(TEXT("添加成功"));
	}

	m_pRs->Close();
	m_pRs=NULL;
}

BOOL CBookSell::Querybookid(CString bid)
{
	_RecordsetPtr m_pUs;
	HRESULT hr;
	hr=m_pUs.CreateInstance(__uuidof(Recordset));
	if(FAILED(hr)){
		MessageBox(TEXT("创建记录集对象失败"));
		return FALSE;
	}
	CString sql;
	CString strValue;
	sql.Format(TEXT("select * from books where b_id = \'%s\'"),bid);
	hr=m_pUs->Open(_variant_t(sql),m_pConnection.GetInterfacePtr(),adOpenKeyset,adLockOptimistic,adCmdText);
	if(FAILED(hr)){
		return FALSE;
	}
	try{
		if (m_pUs->RecordCount>0)
		{
			return FALSE;
		}
	}
	catch(_com_error *e){
		MessageBox(e->ErrorMessage());
		return FALSE;
	}
	m_pUs->Close();
	m_pUs.Release();
	return TRUE;
}


// CBookSell 消息处理程序


void CBookSell::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString strst;
	BOOL ret=FALSE;
	int sel=bm_list.GetSelectionMark();

	if(sel<0){
		MessageBox(TEXT("请选择要购买的书"));
		return;
	}
	else{
		strst=bm_list.GetItemText(sel, 5);//选中行第5列
	}
	int st=_ttoi(strst);
	if(st==1){
		MessageBox(TEXT("尚未到货"));
		return;
	}
	else{
		CString bu_id;
		CString inventory;
		CString date;
		float price;
		GetDlgItem(IDC_DATETIMEPICKER1)->GetWindowText(date);

		bu_id = bm_list.GetItemText(sel,0);
		inventory = bm_list.GetItemText(sel,4);
		price=QuerySprice(bu_id);
		BUYNUM dlg;
		dlg.date=date;
		dlg.bid=bu_id;
		dlg.inventory=inventory;
		dlg.price=price;
		dlg.DoModal();
		ret=TRUE;
	}

	if(ret==TRUE){
		MessageBox(TEXT("购买成功"));
	}
}
