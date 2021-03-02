
// BookSale.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "BookSale.h"
#include "BookSaleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBookSaleApp

BEGIN_MESSAGE_MAP(CBookSaleApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CBookSaleApp ����

CBookSaleApp::CBookSaleApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CBookSaleApp ����

CBookSaleApp theApp;

CString user;
CString password;
CString deg;
_ConnectionPtr m_pConnection;

// CBookSaleApp ��ʼ��

BOOL CBookSaleApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CoInitialize(NULL);
	ConnectDB();
	CBookSaleDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}



int CBookSaleApp::ExitInstance()
{
	// TODO: �ڴ����ר�ô����/����û���
	CloseDB();
	CoUninitialize();
	return CWinApp::ExitInstance();
}

BOOL CBookSaleApp::ConnectDB()
{
	m_pConnection.CreateInstance(__uuidof(Connection));
	try{
		
		m_pConnection->ConnectionString = "Provider=SQLOLEDB.1;Password=songsjl123;Persist Security Info=True;User ID=sa;Initial Catalog=Booksale;Data Source=(local);";
		//pConn->ConnectionString = "Provider=SQLOLEDB.1; User ID=sa; Password=12345678; Initial Catalog=Stock; Data Source=.;";
		m_pConnection->Open(m_pConnection->ConnectionString,"","",adConnectUnspecified);
	}
	catch(_com_error e)///��׽�쳣 
	{ 
		CString errormessage; 
		errormessage.Format(TEXT("�������ݿ�ʧ��!\r\n������Ϣ:%s"),e.ErrorMessage()); 
		AfxMessageBox(errormessage);///��ʾ������Ϣ 
		return FALSE;
	} 
	return TRUE;

	//HRESULT hr;
	//try{
	//	hr=m_pConnection.CreateInstance(__uuidof(Connection));
	//	if(SUCCEEDED(hr)){
	//		//_bstr_t connectStr=_T("Provider=SQLNCLI10;Server=192.168.64.134;Database=Booksale;Uid=sa;Pwd=zunaiJKS");
	//		_bstr_t connectStr=_T("Provider=SQLOLEDB.1;Password=zunaiJKS;Persist Security Info=True;User ID=sa;Initial Catalog=Booksale;Data Source=(local);");
	//		m_pConnection->ConnectionTimeout=20;
	//		hr=m_pConnection->Open(connectStr, _T(""), _T(""), adConnectUnspecified);
	//		if(FAILED(hr)){
	//			MessageBox(TEXT("fail"));
	//			return FALSE;
	//		}
	//	}
	//	else{
	//		MessageBox(TEXT("Cfail"));
	//		return FALSE;
	//	}

	//}
	//catch(_com_error &e)
	//{
	//	_bstr_t bstrSource(e.Source());
	//	_bstr_t bstrDescription(e.Description());
	//	MessageBox(bstrDescription, bstrSource);
	//	return FALSE;
	//}
	//if(m_pConnection && m_pConnection->State==adStateOpen){
	//	m_pConnection->Close();
	//	return TRUE;
	//}



}

void CBookSaleApp::CloseDB()
{
	m_pConnection->Close();
	m_pConnection.Release();

}
