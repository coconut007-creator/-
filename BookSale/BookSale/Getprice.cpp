// Getprice.cpp : 实现文件
//

#include "stdafx.h"
#include "BookSale.h"
#include "Getprice.h"
#include "afxdialogex.h"
extern _ConnectionPtr m_pConnection;


// Getprice 对话框

IMPLEMENT_DYNAMIC(Getprice, CDialogEx)

Getprice::Getprice(CWnd* pParent /*=NULL*/)
	: CDialogEx(Getprice::IDD, pParent)
	,s_price(_T(""))
{

}

Getprice::~Getprice()
{
}

void Getprice::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT9, s_price);
}


BEGIN_MESSAGE_MAP(Getprice, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &Getprice::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &Getprice::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT9, &Getprice::OnEnChangeEdit9)
END_MESSAGE_MAP()


// Getprice 消息处理程序


void Getprice::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void Getprice::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	updateprice();
	CDialogEx::OnOK();
}


void Getprice::OnEnChangeEdit9()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void Getprice::updateprice()
{
	UpdateData(TRUE);
	if (MessageBox(TEXT("确实要修改数据吗?"),TEXT("提示"),MB_YESNO|MB_ICONINFORMATION)==IDYES)
	{
		CString sql;
		sql.Format(TEXT("update books set s_price  = %f where b_id= '%s'"),_ttof(s_price), bid);
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
