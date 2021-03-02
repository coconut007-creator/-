// Customer.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BookSale.h"
#include "Customer.h"
#include "afxdialogex.h"
extern _ConnectionPtr m_pConnection;


// Customer �Ի���

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


// Customer ��Ϣ�������


void Customer::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	searchgrade();
	CDialogEx::OnOK();
}

void Customer::searchgrade()
{
	UpdateData(TRUE);
	if (MessageBox(TEXT("ȷʵҪ�ύ��?"),TEXT("��ʾ"),MB_YESNO|MB_ICONINFORMATION)==IDYES)
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
			   MessageBox(TEXT("�û�Ա�Ų����� ����������"));
		    }
				var=m_pUs->GetCollect("c_degree");
				if(var.vt!=NULL)
					c_grade=(LPCTSTR)_bstr_t(var);
				MessageBox(TEXT("�ɹ�"));
			}
			else{
				MessageBox(TEXT("������¼������ʧ��"));
			}
		}
		catch(_com_error *e){
			MessageBox(e->ErrorMessage());
		}
	}
}


void Customer::OnEnChangeEdit9()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void Customer::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}
