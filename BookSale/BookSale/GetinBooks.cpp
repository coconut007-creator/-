// GetinBooks.cpp : 实现文件
//

#include "stdafx.h"
#include "BookSale.h"
#include "GetinBooks.h"
#include "afxdialogex.h"
extern _ConnectionPtr m_pConnection;

// CGetinBooks 对话框

IMPLEMENT_DYNAMIC(CGetinBooks, CDialogEx)

CGetinBooks::CGetinBooks(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGetinBooks::IDD, pParent)
	, b_amount(_T(""))
{

}

CGetinBooks::~CGetinBooks()
{
}

void CGetinBooks::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT9, b_amount);
}


BEGIN_MESSAGE_MAP(CGetinBooks, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CGetinBooks::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT9, &CGetinBooks::OnEnChangeEdit9)
END_MESSAGE_MAP()

void CGetinBooks::updatesell()
{
	UpdateData(TRUE);
	if (MessageBox(TEXT("确实要修改数据吗?"),TEXT("提示"),MB_YESNO|MB_ICONINFORMATION)==IDYES)
	{
		if(st==TEXT("1")){
		CString sql;
		sql.Format(TEXT("update sell set g_amount = %f where b_id= '%s'"),_ttof(amount)+_ttof(b_amount), bid);
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
		else{
			amount=b_amount;
		}
	}
	

}


// CGetinBooks 消息处理程序


void CGetinBooks::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	updatesell();
}


void CGetinBooks::OnEnChangeEdit9()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
