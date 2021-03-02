// LoginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BookSale.h"
#include "LoginDlg.h"
#include "afxdialogex.h"

extern _ConnectionPtr m_pConnection;

extern CString user;
extern CString password;
extern CString deg;
// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLoginDlg::IDD, pParent)
	, m_use(_T(""))
	, m_pwd(_T(""))
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, m_use);
	DDX_Text(pDX, IDC_EDIT2, m_pwd);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CLoginDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CLoginDlg::OnBnClickedButton2)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序


void CLoginDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_use.IsEmpty() || m_pwd.IsEmpty())
	{
		MessageBox(TEXT("用户名称或密码不能为空"));
		return;
	}

	//_RecordsetPtr pRst(__uuidof(Recordset));
	_RecordsetPtr pRst;
	//_CommandPtr pCmd(__uuidof(Command));
	HRESULT hr;
	hr=pRst.CreateInstance(__uuidof(Recordset));
	if(FAILED(hr)){
		MessageBox(TEXT("创建记录集对象失败"));
		return;
	}
	//pCmd->put_ActiveConnection(_variant_t((IDispatch*)pConn));
	CString sql;

	sql.Format(TEXT("select * from users where u_id = \'%s\' and pwd = (SELECT sys.fn_sqlvarbasetostr(HashBytes(\'MD5\',\'%s\')))"),m_use,m_pwd);
	
	hr=pRst->Open(_variant_t(sql),m_pConnection.GetInterfacePtr(),adOpenKeyset,adLockOptimistic,adCmdText);
	if(FAILED(hr)){
		return;
	}
	try{
	if (pRst->RecordCount>0)
	{
		user=m_use;
		password=m_pwd;
		deg=pRst->GetCollect("degree").bstrVal;
		CString str;
		str.Format(TEXT("登陆成功，等级为\'%s\'"), deg);
		MessageBox(str);
		CDialogEx::OnOK();
	}
	else
	{
		MessageBox(TEXT("用户名或密码不正确"));
		return;
	}
	}
	catch(_com_error *e){
		MessageBox(e->ErrorMessage());
		return;
	}
	pRst->Close();
	pRst.Release();
}


void CLoginDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);

}


void CLoginDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//CDialogEx::OnClose();
	exit(0);
}
