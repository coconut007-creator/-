// GetinBooks.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BookSale.h"
#include "GetinBooks.h"
#include "afxdialogex.h"
extern _ConnectionPtr m_pConnection;

// CGetinBooks �Ի���

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
	if (MessageBox(TEXT("ȷʵҪ�޸�������?"),TEXT("��ʾ"),MB_YESNO|MB_ICONINFORMATION)==IDYES)
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

				MessageBox(TEXT("�޸ĳɹ�"));
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


// CGetinBooks ��Ϣ�������


void CGetinBooks::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	updatesell();
}


void CGetinBooks::OnEnChangeEdit9()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
