
// BookSaleDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BookSale.h"
#include "BookSaleDlg.h"
#include "afxdialogex.h"

#include "LoginDlg.h"
#include "UserDlg.h"
#include "BookmgDlg.h"
#include "AccouDlg.h"
#include "Bookget.h"
#include "BookSell.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern _ConnectionPtr m_pConnection;
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CBookSaleDlg 对话框




CBookSaleDlg::CBookSaleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBookSaleDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBookSaleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC, m_pic);
}

BEGIN_MESSAGE_MAP(CBookSaleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON1, &CBookSaleDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CBookSaleDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CBookSaleDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &CBookSaleDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON4, &CBookSaleDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CBookSaleDlg 消息处理程序

BOOL CBookSaleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//picture
	m_pic.ModifyStyle(15,SS_BITMAP|SS_CENTERIMAGE);//修改风格：位图居中显示
	#define HBMP(filepath,width,height)(HBITMAP)LoadImage(AfxGetInstanceHandle(),filepath,IMAGE_BITMAP,width,height,LR_LOADFROMFILE|LR_CREATEDIBSECTION)
	
	CRect rect;
	m_pic.GetWindowRect(rect);
	m_pic.SetBitmap(HBMP(TEXT("./pic.bmp"), rect.Width(), rect.Height()));

	CLoginDlg dlg;
	dlg.DoModal();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CBookSaleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CBookSaleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CBookSaleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CBookSaleDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	CDialogEx::OnClose();
}


void CBookSaleDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CUserDlg ulg;
	
	ulg.DoModal();
}


void CBookSaleDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CBookmgDlg dlg;
	dlg.DoModal();
}


void CBookSaleDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	CAccouDlg alg;
	alg.DoModal();

}


void CBookSaleDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	CBookget dlg;
	dlg.DoModal();
}


void CBookSaleDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	CBookSell blg;
	blg.DoModal();
}
