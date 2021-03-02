// Bookget.cpp : 实现文件
//

#include "stdafx.h"
#include "BookSale.h"
#include "Bookget.h"
#include "afxdialogex.h"
#include "GetinBooks.h"
extern _ConnectionPtr m_pConnection;
extern CString user;
extern CString password;
// CBookget 对话框

IMPLEMENT_DYNAMIC(CBookget, CDialogEx)

CBookget::CBookget(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBookget::IDD, pParent)
	, b_id(_T(""))
	, b_isbn(_T(""))
	, b_name(_T(""))
	, b_pub(_T(""))
	, g_price(_T(""))
	, g_amount(_T(""))
{

}

CBookget::~CBookget()
{
}

void CBookget::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, bm_list);
	DDX_Text(pDX, IDC_EDIT1, b_id);
	DDX_Text(pDX, IDC_EDIT12, b_isbn);
	DDX_Text(pDX, IDC_EDIT4, b_name);
	DDX_Text(pDX, IDC_EDIT8, b_pub);
	DDX_Control(pDX, IDC_COMBO5, b_state);
	//  DDX_Check(pDX, IDC_CHECK1, s_check);
	DDX_Text(pDX, IDC_EDIT9, g_price);
	DDX_Text(pDX, IDC_EDIT10, g_amount);
	DDX_Control(pDX, IDC_EDIT1, b_idC);
	DDX_Control(pDX, IDC_EDIT12, b_isbnC);
	DDX_Control(pDX, IDC_EDIT4, b_nameC);
	DDX_Control(pDX, IDC_EDIT8, b_pubC);
	DDX_Control(pDX, IDC_EDIT9, g_priceC);
	DDX_Control(pDX, IDC_EDIT10, g_amountC);
}


BEGIN_MESSAGE_MAP(CBookget, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CBookget::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CBookget::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CBookget::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CBookget::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON8, &CBookget::OnBnClickedButton8)
END_MESSAGE_MAP()


// CBookget 消息处理程序


void CBookget::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	searsell();
}

void CBookget::searsell()
{
	UpdateData(TRUE);
	_RecordsetPtr m_pBs;
	HRESULT hr;
	hr=m_pBs.CreateInstance(__uuidof(Recordset));
	CString b_st;
	b_state.GetWindowText(b_st);
	//可以输入书籍编号/ISBN/书名/状态/查询/
	CString strSQL;
	if(b_id.IsEmpty()&&b_isbn.IsEmpty()&&b_name.IsEmpty()&&b_st.IsEmpty())
		strSQL=TEXT("select books.b_id, b_name, ISBN, g_price, g_amount, s_t from sell inner join books on books.b_id=sell.b_id");
	else
		strSQL=TEXT("select books.b_id, b_name, ISBN, g_price, g_amount, s_t from sell inner join books on books.b_id=sell.b_id where");
	if(!b_id.IsEmpty()){
		strSQL.AppendFormat(TEXT(" books.b_id=\'%s\'"), b_id);
	}
	if(!b_isbn.IsEmpty()){
		if(!b_id.IsEmpty()){
			strSQL.AppendFormat(TEXT(" and books.ISBN=\'%s\'"), b_isbn);
		}
		else{
			strSQL.AppendFormat(TEXT(" books.ISBN=\'%s\'"), b_isbn);
		}
	}
	if(!b_name.IsEmpty()){
		if(!b_isbn.IsEmpty()||!b_id.IsEmpty()){
			strSQL.AppendFormat(TEXT(" and books.b_name=\'%s\'"), b_name);
		}
		else{
			strSQL.AppendFormat(TEXT(" books.b_name=\'%s\'"), b_name);
		}
	}
	if(!b_st.IsEmpty()){
		if(!b_isbn.IsEmpty()||!b_id.IsEmpty()||!b_name.IsEmpty()){
			strSQL.AppendFormat(TEXT(" and sell.s_t=\'%s\'"), b_st);
		}
		else{
			strSQL.AppendFormat(TEXT(" sell.s_t=\'%s\'"), b_st);
		}
	}
	try{
		hr=m_pBs->Open(_variant_t(strSQL),m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
		if(FAILED(hr)){
			return;
		}
		if(m_pBs->GetadoEof()){
			MessageBox(TEXT("结果为空"));
			return;
		}
		else{
			_variant_t var;
			CString strValue;
			int curItem=0;
			bm_list.DeleteAllItems();//把原来的删了
			while(!m_pBs->GetadoEof()){//EOF指示当前位置是否位于记录集的最后一个后
				var=m_pBs->GetCollect((long)0);//通过列号获取当前行第0列  接受_variant_t参数，有long转换的功能，所以转成long
				if(var.vt!=NULL)
					strValue=(LPCTSTR)_bstr_t(var);//把variant类型先转成bstr，再转CString
				bm_list.InsertItem(curItem, strValue);
				for(int i=1;i<6;i++){
					var=m_pBs->GetCollect((long)i);
					if(var.vt!=VT_NULL)
						strValue=(LPCTSTR)_bstr_t(var);
					else
						strValue=TEXT(" ");
					bm_list.SetItemText(curItem, i, strValue);//i为列号
				}
				m_pBs->MoveNext();//移到下一行
				curItem++;
			}
		}
	}
		catch(_com_error *e){
			MessageBox(e->ErrorMessage());
			return;
		}
	m_pBs->Close();
	m_pBs.Release();
}

CString CBookget::QueryBname( CString strValue )
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

CString CBookget::QueryBisbn( CString strValue)
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


int CBookget::Queryallsell( CString strV,int curItem , CString b_st)
{
	//通过b_id找sell
	CString strSQL;
	strSQL.Format(TEXT("select * from sell where b_id=\'%s\'"), strV);
	if(!b_st.IsEmpty())
		strSQL.AppendFormat(TEXT(" and s_t=\'%s\'"), b_st);

	_RecordsetPtr m_pAs;
	HRESULT hr;
	hr=m_pAs.CreateInstance(__uuidof(Recordset));
	if(FAILED(hr)){
		MessageBox(TEXT("创建记录集对象失败"));
		return -1;
	}
	try{
		hr=m_pAs->Open(_variant_t(strSQL),m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
		if(FAILED(hr)){
			return -1;
		}

		if(m_pAs->GetadoEof()){
			MessageBox(TEXT("结果为空"));
			return 0;
		}
		else{
			_variant_t var;
			CString strValue;
			bm_list.DeleteAllItems();//把原来的删了
			while(!m_pAs->GetadoEof()){//EOF指示当前位置是否位于记录集的最后一个后
				var=m_pAs->GetCollect((long)0);//通过列号获取当前行第0列  接受_variant_t参数，有long转换的功能，所以转成long
				if(var.vt!=NULL)
					strValue=(LPCTSTR)_bstr_t(var);//把variant类型先转成bstr，再转CString
				bm_list.InsertItem(curItem, strValue);
				//到books找
				bm_list.SetItemText(curItem, 1, QueryBname(strValue));//b_name
    			bm_list.SetItemText(curItem, 2, QueryBisbn(strValue));//isbn
				for(int i=1;i<4;i++){
					var=m_pAs->GetCollect((long)i);
					if(var.vt!=NULL)
						strValue=(LPCTSTR)_bstr_t(var);
					bm_list.SetItemText(curItem, i+2, strValue);//i为列号
				}
				m_pAs->MoveNext();//移到下一行
				curItem++;
			}
		}

	}
	catch(_com_error *e){
		MessageBox(e->ErrorMessage());
		return -1;
	}

	m_pAs->Close();
	m_pAs.Release();
	return curItem;
}


BOOL CBookget::updatesell( CString strbid, CString b_s ) 
{
	BOOL ret=FALSE;
	CString strSQL;
	strSQL.Format(TEXT("update sell set s_t=\'%s\' where b_id=\'%s\'"), b_s, strbid);
	_RecordsetPtr m_pAs;
	HRESULT hr;
	hr=m_pAs.CreateInstance(__uuidof(Recordset));
	if(FAILED(hr)){
		MessageBox(TEXT("创建记录集对象失败"));
	}
	try{
		hr=m_pAs->Open(_variant_t(strSQL),m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
		if(FAILED(hr)){
			return ret;
		}
		else ret=TRUE;
	}
	catch(_com_error *e){
		MessageBox(e->ErrorMessage());
	}
	return ret;
}

//付款
void CBookget::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);//得到日期
	CString strDate;
	CString strst;
	CString strprice;
	CString stramount;
	CString strbid;
	GetDlgItem(IDC_DATETIMEPICKER1)->GetWindowText(strDate);//获得付款日期

	int sel=bm_list.GetSelectionMark();
	if(sel<0){
		MessageBox(TEXT("请选择要付款的书"));
		return;
	}
	else{
		strst=bm_list.GetItemText(sel, 5);//选中行第5列
		strbid=bm_list.GetItemText(sel, 0);
		strprice=bm_list.GetItemText(sel, 3);
		stramount=bm_list.GetItemText(sel, 4);
	}
	float price=_ttof(strprice);
	float amount=_ttof(stramount);
	int st=_ttoi(strst);
	if(st!=1){
		MessageBox(TEXT("已付款"));
		return;
	}
	//插入account
	float budget=price*amount;
	BOOL bRet=insertintoAccount(strDate, budget);
	//改状态
	if(bRet==TRUE){
		CString b_s=TEXT("2");
		BOOL ret=updatesell(strbid, b_s);
		if(ret==TRUE){
			MessageBox(TEXT("付款成功"));
		}
	}
}

BOOL CBookget::insertintoAccount(CString strDate, float budget )
{
	BOOL ret=FALSE;
	_RecordsetPtr m_pRs;
	CString sta=TEXT("1");
	m_pRs.CreateInstance(__uuidof(Recordset));
	try{
		HRESULT hr=m_pRs->Open(TEXT("select * from account"), m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
		//先得到结果集全体，插入一条，写回
		if(SUCCEEDED(hr)){
			m_pRs->AddNew();
			m_pRs->PutCollect("a_date", _variant_t(strDate));
			m_pRs->PutCollect("budget", _variant_t(budget));
			m_pRs->PutCollect("u_id", _variant_t(user));
			m_pRs->PutCollect("a_type", _variant_t(sta));
			m_pRs->Update();//回写
			ret=TRUE;
		}

	}catch(_com_error *e){
		MessageBox(e->ErrorMessage());
	}
	m_pRs->Close();
	m_pRs=NULL;
	return ret;
}


void CBookget::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strst;
	CString strbid;

	int sel=bm_list.GetSelectionMark();
	if(sel<0){
		MessageBox(TEXT("请选择要退货的书"));
		return;
	}
	else{
		strst=bm_list.GetItemText(sel, 5);//选中行第5列
		strbid=bm_list.GetItemText(sel, 0);
	}
	int st=_ttoi(strst);
	if(st==2){
		MessageBox(TEXT("已付款"));
		return;
	}
	else if (st==3){
		MessageBox(TEXT("已退货"));
		return;
	}
	//改状态
		CString b_s=TEXT("3");
		BOOL ret=updatesell(strbid, b_s);
		if(ret==TRUE){
			MessageBox(TEXT("退货成功"));
		}
}

BOOL CBookget::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString str[] = { TEXT("书籍编号"),TEXT("书籍名称"), TEXT("ISBN"),TEXT("进货价格"), TEXT("购买数量"),TEXT("状态") };
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
	strSQL=TEXT("select * from sell");
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


void CBookget::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	POSITION pos = bm_list.GetFirstSelectedItemPosition();
	int j = bm_list.GetNextSelectedItem(pos);
	CString b_st=TEXT("1");
	if (j!=-1){
		CString bu_id;
		bu_id = bm_list.GetItemText(bm_list.GetSelectionMark(),0);
		CString bu_amount;
		bu_amount = bm_list.GetItemText(bm_list.GetSelectionMark(),4);
		CString bst;
		bst = bm_list.GetItemText(bm_list.GetSelectionMark(),5);
		CGetinBooks dlg;
		dlg.bid=bu_id;
		dlg.amount=bu_amount;
		dlg.st=bst;
		dlg.DoModal();
		if(bst==TEXT("1")){
			return;
		}
		else{
			b_id=bu_id;
			g_price=bm_list.GetItemText(bm_list.GetSelectionMark(),3);
			g_amount=dlg.amount;
		}
		
	}
	
	if(!Querybid(b_id))
	{
		_RecordsetPtr m_pUs;
		m_pUs.CreateInstance(__uuidof(Recordset));
		HRESULT hr;
		try{
			hr=m_pUs->Open(TEXT("select * from books"), m_pConnection.GetInterfacePtr(), adOpenKeyset, adLockOptimistic, adCmdText);
			if(SUCCEEDED(hr)){
			m_pUs->AddNew();
				if(!b_id.IsEmpty())
					m_pUs->PutCollect("b_id", _variant_t(b_id));
				else {
					MessageBox(TEXT("书籍编号不为空"));
					return;
				}
				if(!b_isbn.IsEmpty())
					m_pUs->PutCollect("ISBN", _variant_t(b_isbn));
				if(!b_name.IsEmpty())
					m_pUs->PutCollect("b_name", _variant_t(b_name));
				m_pUs->PutCollect("publisher", _variant_t(b_pub));
				m_pUs->PutCollect("s_amount", _variant_t(g_amount));
				m_pUs->Update();//回写
		}
	}catch(_com_error *e){
		MessageBox(e->ErrorMessage());
	}

	MessageBox(TEXT("添加成功!"));
	m_pUs->Close();
	m_pUs=NULL;
		}


	_RecordsetPtr m_pBs;
	m_pBs.CreateInstance(__uuidof(Recordset));
	HRESULT hrr;
	try{
		hrr=m_pBs->Open(TEXT("select * from sell"), m_pConnection.GetInterfacePtr(), adOpenKeyset, adLockOptimistic, adCmdText);
		//先得到结果集全体，插入一条，写回
		if(SUCCEEDED(hrr)){
			m_pBs->AddNew();
				if(!b_id.IsEmpty())
					m_pBs->PutCollect("b_id", _variant_t(b_id));
				else {
					MessageBox(TEXT("书籍编号不为空"));
					return;
				}
				if(!g_price.IsEmpty())
					m_pBs->PutCollect("g_price", _variant_t(g_price));
				else{
					MessageBox(TEXT("进货价格不为空"));
					return;
				}
				if(!g_amount.IsEmpty())
					m_pBs->PutCollect("g_amount", _variant_t(g_amount));
				else{
					MessageBox(TEXT("进货数量不为空"));
					return;
				}
				m_pBs->PutCollect("s_t", _variant_t(b_st));
				m_pBs->Update();//回写
		}
	}catch(_com_error *e){
		MessageBox(e->ErrorMessage());
	}

	MessageBox(TEXT("添加成功!"));
	m_pBs->Close();
	m_pBs=NULL;
}


BOOL CBookget::Querybid( CString bid )
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
			return TRUE;
		}
	}
	catch(_com_error *e){
		MessageBox(e->ErrorMessage());
		return FALSE;
	}
	m_pUs->Close();
	m_pUs.Release();
	return FALSE;
}


void CBookget::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	b_state.SetCurSel(0);
	b_idC.SetWindowText(TEXT(""));
	b_isbnC.SetWindowText(TEXT(""));
	b_nameC.SetWindowText(TEXT(""));
	b_pubC.SetWindowText(TEXT(""));
	g_amountC.SetWindowText(TEXT(""));
	g_priceC.SetWindowText(TEXT(""));
}
