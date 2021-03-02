// UpdateBooks.cpp : 实现文件
//

#include "stdafx.h"
#include "BookSale.h"
#include "UpdateBooks.h"
#include "afxdialogex.h"

extern _ConnectionPtr m_pConnection;
// CUpdateBooks 对话框

IMPLEMENT_DYNAMIC(CUpdateBooks, CDialogEx)

CUpdateBooks::CUpdateBooks(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUpdateBooks::IDD, pParent)
	, b_isbn(_T(""))
	, b_wrt(_T(""))
	, b_name(_T(""))
	, b_price(_T(""))
	, b_pub(_T(""))
	, b_num(_T(""))
{

}

CUpdateBooks::~CUpdateBooks()
{
}

void CUpdateBooks::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, b_isbn);
	DDX_Text(pDX, IDC_EDIT9, b_wrt);
	DDX_Text(pDX, IDC_EDIT4, b_name);
	DDX_Text(pDX, IDC_EDIT10, b_price);
	DDX_Text(pDX, IDC_EDIT8, b_pub);
	DDX_Text(pDX, IDC_EDIT11, b_num);
}


BEGIN_MESSAGE_MAP(CUpdateBooks, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CUpdateBooks::OnBnClickedButton1)
END_MESSAGE_MAP()

void CUpdateBooks::updatebooks()
{
	UpdateData(TRUE);
	if (MessageBox(TEXT("确实要修改数据吗?"),TEXT("提示"),MB_YESNO|MB_ICONINFORMATION)==IDYES)
	{
		CString sql;
		sql.Format(TEXT("update books set ISBN = '%s',b_name = '%s',author = '%s',publisher = '%s',s_price = %f,s_amount = %f where b_id= '%s'"),b_isbn,b_name,b_wrt,b_pub ,_ttof(b_price),_ttof(b_num), bid);
		_RecordsetPtr m_pUs;
		m_pUs.CreateInstance(__uuidof(Recordset));
		try
		{
			HRESULT hr=m_pUs->Open((_variant_t)sql, m_pConnection.GetInterfacePtr(), adOpenKeyset, adLockOptimistic, adCmdText);
			if(SUCCEEDED(hr)){

				MessageBox(TEXT("修改成功"));
			}

		}
		catch(_com_error *e){
			MessageBox(e->ErrorMessage());
		}
	}


}


// CUpdateBooks 消息处理程序


void CUpdateBooks::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	updatebooks();
}
