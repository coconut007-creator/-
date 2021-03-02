// Customer.cpp : 实现文件
//

#include "stdafx.h"
#include "BookSale.h"
#include "Customer.h"
#include "afxdialogex.h"
extern _ConnectionPtr m_pConnection;


// Customer 对话框

IMPLEMENT_DYNAMIC(Customer, CDialogEx)

Customer::Customer(CWnd* pParent /*=NULL*/)
	: CDialogEx(Customer::IDD, pParent)
	,c_id(_T(""))
{

}

Customer::~Customer()
{
}

void Customer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT9, c_id);
}


BEGIN_MESSAGE_MAP(Customer, CDialogEx)
	ON_BN_CLICKED(IDOK, &Customer::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT9, &Customer::OnEnChangeEdit9)
	ON_BN_CLICKED(IDCANCEL, &Customer::OnBnClickedCancel)
END_MESSAGE_MAP()


// Customer 消息处理程序


void Customer::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	searchgrade();
	CDialogEx::OnOK();
}

void Customer::searchgrade()
{
	UpdateData(TRUE);
	if (MessageBox(TEXT("确实要提交吗?"),TEXT("提示"),MB_YESNO|MB_ICONINFORMATION)==IDYES)
	{
		CString sql;
		sql.Format(TEXT("select c_degree from customer where c_id= \'%s\'"),c_id);
		_RecordsetPtr m_pUs;
		m_pUs.CreateInstance(__uuidof(Recordset));

		try
		{
			_variant_t var;
			HRESULT hr=m_pUs->Open((_variant_t)sql, m_pConnection.GetInterfacePtr(), adOpenKeyset, adLockOptimistic, adCmdText);
			if(SUCCEEDED(hr)){
			if(m_pUs->GetadoEof()){
			   MessageBox(TEXT("该会员号不存在 请重新输入"));
		    }
				var=m_pUs->GetCollect("c_degree");
				if(var.vt!=NULL)
					c_grade=(LPCTSTR)_bstr_t(var);
				MessageBox(TEXT("成功"));
			}
			else{
				MessageBox(TEXT("创建记录集对象失败"));
			}
		}
		catch(_com_error *e){
			MessageBox(e->ErrorMessage());
		}
	}
}


void Customer::OnEnChangeEdit9()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void Customer::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
