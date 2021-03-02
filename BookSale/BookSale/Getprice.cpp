// Getprice.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BookSale.h"
#include "Getprice.h"
#include "afxdialogex.h"
extern _ConnectionPtr m_pConnection;


// Getprice �Ի���

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


// Getprice ��Ϣ�������


void Getprice::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void Getprice::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	updateprice();
	CDialogEx::OnOK();
}


void Getprice::OnEnChangeEdit9()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

void Getprice::updateprice()
{
	UpdateData(TRUE);
	if (MessageBox(TEXT("ȷʵҪ�޸�������?"),TEXT("��ʾ"),MB_YESNO|MB_ICONINFORMATION)==IDYES)
	{
		CString sql;
		sql.Format(TEXT("update books set s_price  = %f where b_id= '%s'"),_ttof(s_price), bid);
		_RecordsetPtr m_pUs;
		m_pUs.CreateInstance(__uuidof(Recordset));

		try
		{
			HRESULT hr=m_pUs->Open((_variant_t)sql, m_pConnection.GetInterfacePtr(), adOpenKeyset, adLockOptimistic, adCmdText);
			if(SUCCEEDED(hr)){

				MessageBox(TEXT("�޸ĳɹ�"));
			}

		}
		catch(_com_error *e){
			MessageBox(e->ErrorMessage());
		}
	}
}
