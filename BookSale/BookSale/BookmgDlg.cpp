// BookmgDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BookSale.h"
#include "BookmgDlg.h"
#include "afxdialogex.h"
#include "UpdateBooks.h"
extern _ConnectionPtr m_pConnection;
// CBookmgDlg 对话框

IMPLEMENT_DYNAMIC(CBookmgDlg, CDialogEx)

CBookmgDlg::CBookmgDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBookmgDlg::IDD, pParent)
	, b_id(_T(""))
	, b_isbn(_T(""))
	, b_name(_T(""))
	, b_pub(_T(""))
	, b_wrt(_T(""))
	, b_price(_T(""))
	, b_num(_T(""))
{

}

CBookmgDlg::~CBookmgDlg()
{
}

void CBookmgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, bm_list);
	DDX_Text(pDX, IDC_EDIT5, b_id);
	DDX_Text(pDX, IDC_EDIT1, b_isbn);
	DDX_Text(pDX, IDC_EDIT4, b_name);
	DDX_Text(pDX, IDC_EDIT8, b_pub);
	DDX_Text(pDX, IDC_EDIT9, b_wrt);
	DDX_Text(pDX, IDC_EDIT10, b_price);
	DDX_Text(pDX, IDC_EDIT11, b_num);
	//  DDX_Check(pDX, IDC_CHECK1, m_check);
	DDX_Control(pDX, IDC_EDIT5, b_idC);
	DDX_Control(pDX, IDC_EDIT9, b_wrtC);
	DDX_Control(pDX, IDC_EDIT1, b_isbnC);
	DDX_Control(pDX, IDC_EDIT10, b_priceC);
	DDX_Control(pDX, IDC_EDIT4, b_nameC);
	DDX_Control(pDX, IDC_EDIT11, b_numC);
	DDX_Control(pDX, IDC_EDIT8, b_pubC);
}


BEGIN_MESSAGE_MAP(CBookmgDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON3, &CBookmgDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, &CBookmgDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON6, &CBookmgDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON4, &CBookmgDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON2, &CBookmgDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CBookmgDlg 消息处理程序


void CBookmgDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	searBooks();
}

void CBookmgDlg::searBooks()
{
	UpdateData(TRUE);
	_RecordsetPtr m_pBs;
	m_pBs.CreateInstance(__uuidof(Recordset));

	//可以输入书籍编号/ISBN/书名/作者/出版社查询/一个都没有
	CString strSQL;
	
	if(b_id.IsEmpty()&&b_isbn.IsEmpty()&&b_name.IsEmpty()&&b_wrt.IsEmpty()&&b_pub.IsEmpty()){
		strSQL=TEXT("select * from books");
	}
	else{
		strSQL=TEXT("select * from books where");
	if(!b_id.IsEmpty()){
		strSQL.AppendFormat(TEXT(" b_id=\'%s\'"), b_id);
	}
	if(!b_isbn.IsEmpty()){
		if(!b_id.IsEmpty()){
			strSQL.AppendFormat(TEXT(" and ISBN=\'%s\'"), b_isbn);
		}
		else{
			strSQL.AppendFormat(TEXT(" ISBN=\'%s\'"), b_isbn);
		}
	}

	if(!b_name.IsEmpty()){
		if(!b_id.IsEmpty()||!b_isbn.IsEmpty()){
			strSQL.AppendFormat(TEXT(" and b_name=\'%s\'"), b_name);
		}
		else{
			strSQL.AppendFormat(TEXT(" b_name=\'%s\'"), b_name);
		}
	}

	if(!b_wrt.IsEmpty()){
		if(!b_id.IsEmpty()||!b_isbn.IsEmpty()||!b_name.IsEmpty()){
			strSQL.AppendFormat(TEXT(" and author=\'%s\'"), b_wrt);
		}
		else{
			strSQL.AppendFormat(TEXT(" author=\'%s\'"), b_wrt);
		}
	}

	if(!b_pub.IsEmpty()){
		if(!b_id.IsEmpty()||!b_isbn.IsEmpty()||!b_name.IsEmpty()||!b_wrt.IsEmpty()){
			strSQL.AppendFormat(TEXT(" and publisher=\'%s\'"), b_pub);
		}
		else{
			strSQL.AppendFormat(TEXT(" publisher=\'%s\'"), b_pub);
		}
	}
}
	//SQL建好了

	try{
		HRESULT hr=m_pBs->Open((_variant_t)strSQL,m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
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
				for(int i=1;i<7;i++){
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

BOOL CBookmgDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString str[] = { TEXT("书籍编号"),TEXT("ISBN"), TEXT("书名"),TEXT("作者"),TEXT("出版社"), TEXT("零售价"),TEXT("库存数量") };
	for (int i = 0; i < 7; i++) {
		//设置表头：索引，内容，对齐方式，列宽
		bm_list.InsertColumn(i, str[i],LVCFMT_LEFT,100);
	}
	bm_list.SetExtendedStyle(bm_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	_RecordsetPtr m_pBs;
	HRESULT hr;
	hr=m_pBs.CreateInstance(__uuidof(Recordset));
	if(FAILED(hr)){
		MessageBox(TEXT("创建记录集对象失败"));
		return FALSE;
	}
	CString strSQL;
	strSQL=TEXT("select * from books");
	try{
		hr=m_pBs->Open(_variant_t(strSQL),m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
		if(FAILED(hr)){
			return FALSE;
		}

		if(m_pBs->GetadoEof()){
			MessageBox(TEXT("结果为空"));
			return TRUE;
		}
		else{
			_variant_t var;
			CString strValue;
			int curItem=0;

			bm_list.DeleteAllItems();//把原来的删了
			while(!m_pBs->GetadoEof()){//EOF指示当前位置是否位于记录集的最后一个后
				var=m_pBs->GetCollect((long)0);//通过列号获取当前行第0列  接受_variant_t参数，有long转换的功能，所以转成long
				if(var.vt!=VT_NULL)
					strValue=(LPCTSTR)_bstr_t(var);
				else
					strValue=TEXT(" ");
				bm_list.InsertItem(curItem, strValue);
				for(int i=1;i<7;i++){
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
		return FALSE;
	}
	m_pBs->Close();
	m_pBs.Release();
	return TRUE;
}

void CBookmgDlg::insertbooks()
{
	UpdateData(TRUE);
	_RecordsetPtr m_pUs;
	m_pUs.CreateInstance(__uuidof(Recordset));
	if(!Querybookid(b_id)){
		MessageBox(TEXT("书籍编号重复!"));
		return;
	}
	try{
		HRESULT hr=m_pUs->Open(TEXT("select * from books"), m_pConnection.GetInterfacePtr(), adOpenKeyset, adLockOptimistic, adCmdText);
		//先得到结果集全体，插入一条，写回
		if(SUCCEEDED(hr)){
			m_pUs->AddNew();
			if(!b_id.IsEmpty())
				m_pUs->PutCollect("b_id", _variant_t(b_id));
			else MessageBox(TEXT("书籍编号不为空"));
			if(!b_isbn.IsEmpty())
				m_pUs->PutCollect("ISBN", _variant_t(b_isbn));
			if(!b_wrt.IsEmpty())
				m_pUs->PutCollect("author", _variant_t(b_wrt));
			if(!b_name.IsEmpty())
				m_pUs->PutCollect("b_name", _variant_t(b_name));
			if(!b_pub.IsEmpty())
				m_pUs->PutCollect("publisher", _variant_t(b_pub));
			if(!b_price.IsEmpty()){
				m_pUs->PutCollect("s_price", _ttof(b_price));
			}
			if(!b_num.IsEmpty())
				m_pUs->PutCollect("s_amount", _ttof(b_num));
			m_pUs->Update();//回写
		}
	}catch(_com_error *e){
		MessageBox(e->ErrorMessage());
	}

	
	MessageBox(TEXT("添加书籍成功!"));
	m_pUs->Close();
	m_pUs=NULL;
}


void CBookmgDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	insertbooks();
}


void CBookmgDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	b_idC.SetWindowText(TEXT(""));
	b_isbnC.SetWindowText(TEXT(""));
	b_nameC.SetWindowText(TEXT(""));
	b_wrtC.SetWindowText(TEXT(""));
	b_pubC.SetWindowText(TEXT(""));
	b_priceC.SetWindowText(TEXT(""));
	b_numC.SetWindowText(TEXT(""));
}


void CBookmgDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	deletebooks();
}

void CBookmgDlg::deletebooks()
{
	if (bm_list.GetSelectionMark()!=-1)
	{
		if (MessageBox(TEXT("确实要删除数据吗?"),TEXT("提示"),MB_YESNO|MB_ICONINFORMATION)==IDYES)
		{
			int i = bm_list.GetSelectionMark();
			CString bid = bm_list.GetItemText(i,0);
			CString sql;
			sql.Format(TEXT("delete books where b_id= \'%s\'"),bid);
			_RecordsetPtr m_pUs;
			m_pUs.CreateInstance(__uuidof(Recordset));
			try
			{
				HRESULT hr=m_pUs->Open((_variant_t)sql, m_pConnection.GetInterfacePtr(), adOpenKeyset, adLockOptimistic, adCmdText);
				if(SUCCEEDED(hr)){

					MessageBox(TEXT("删除成功"));
				}

			}
			catch(_com_error *e){
				MessageBox(e->ErrorMessage());
			}
		}
	}
	else
		MessageBox(TEXT("请选择要删除的信息"));
}


void CBookmgDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	if (bm_list.GetSelectionMark()!=-1)
	{
		CString bu_id;
		bu_id = bm_list.GetItemText(bm_list.GetSelectionMark(),0);
		CUpdateBooks dlg;
		dlg.bid=bu_id;
		dlg.DoModal();
	}
	else
		MessageBox(TEXT("请选择要修改的信息"));
}

BOOL CBookmgDlg::Querybookid(CString bid)
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

