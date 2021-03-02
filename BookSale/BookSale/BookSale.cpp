
// BookSale.cpp : 定义应用程序的类行为。
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


// CBookSaleApp 构造

CBookSaleApp::CBookSaleApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CBookSaleApp 对象

CBookSaleApp theApp;

CString user;
CString password;
CString deg;
_ConnectionPtr m_pConnection;

// CBookSaleApp 初始化

BOOL CBookSaleApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CoInitialize(NULL);
	ConnectDB();
	CBookSaleDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}



int CBookSaleApp::ExitInstance()
{
	// TODO: 在此添加专用代码和/或调用基类
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
	catch(_com_error e)///捕捉异常 
	{ 
		CString errormessage; 
		errormessage.Format(TEXT("连接数据库失败!\r\n错误信息:%s"),e.ErrorMessage()); 
		AfxMessageBox(errormessage);///显示错误信息 
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
