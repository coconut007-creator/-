// LoginDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BookSale.h"
#include "LoginDlg.h"
#include "afxdialogex.h"

extern _ConnectionPtr m_pConnection;

extern CString user;
extern CString password;
extern CString deg;
// CLoginDlg �Ի���

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


// CLoginDlg ��Ϣ�������


void CLoginDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_use.IsEmpty() || m_pwd.IsEmpty())
	{
		MessageBox(TEXT("�û����ƻ����벻��Ϊ��"));
		return;
	}

	//_RecordsetPtr pRst(__uuidof(Recordset));
	_RecordsetPtr pRst;
	//_CommandPtr pCmd(__uuidof(Command));
	HRESULT hr;
	hr=pRst.CreateInstance(__uuidof(Recordset));
	if(FAILED(hr)){
		MessageBox(TEXT("������¼������ʧ��"));
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
		str.Format(TEXT("��½�ɹ����ȼ�Ϊ\'%s\'"), deg);
		MessageBox(str);
		CDialogEx::OnOK();
	}
	else
	{
		MessageBox(TEXT("�û��������벻��ȷ"));
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	exit(0);

}


void CLoginDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//CDialogEx::OnClose();
	exit(0);
}
