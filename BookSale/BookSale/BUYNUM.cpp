// BUYNUM.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BookSale.h"
#include "BUYNUM.h"
#include "afxdialogex.h"
#include "Customer.h"
extern _ConnectionPtr m_pConnection;
extern CString user;
extern CString password;


// BUYNUM �Ի���

IMPLEMENT_DYNAMIC(BUYNUM, CDialogEx)

BUYNUM::BUYNUM(CWnd* pParent /*=NULL*/)
	: CDialogEx(BUYNUM::IDD, pParent)
	,buynum(_T(""))
{

}

BUYNUM::~BUYNUM()
{
}

void BUYNUM::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT9, buynum);
}


BEGIN_MESSAGE_MAP(BUYNUM, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &BUYNUM::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &BUYNUM::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT9, &BUYNUM::OnEnChangeEdit9)
	ON_BN_CLICKED(IDC_RADIO1, &BUYNUM::OnBnClickedRadio1)
END_MESSAGE_MAP()


// BUYNUM ��Ϣ�������


void BUYNUM::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void BUYNUM::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	updatebuynum();
	CDialogEx::OnOK();
}

void BUYNUM::updatebuynum()
{
	UpdateData(TRUE);
	if (MessageBox(TEXT("ȷʵҪ�޸�������?"),TEXT("��ʾ"),MB_YESNO|MB_ICONINFORMATION)==IDYES)
	{
		CString sql;
		sql.Format(TEXT("update books set s_amount  = %f where b_id= \'%s\'"),_ttof(inventory)-_ttof(buynum), bid);
		_RecordsetPtr m_pUs;
		m_pUs.CreateInstance(__uuidof(Recordset));

		try
		{
			HRESULT hr=m_pUs->Open((_variant_t)sql, m_pConnection.GetInterfacePtr(), adOpenKeyset, adLockOptimistic, adCmdText);
			if(SUCCEEDED(hr)){

				MessageBox(TEXT("����ɹ�"));
			}

		}
		catch(_com_error *e){
			MessageBox(e->ErrorMessage());
		}
		if(degree.IsEmpty()) degree="1";
		float budget=_ttof(buynum);
		budget=budget*price;
		int grade=_ttoi(degree);
		if(grade==2) budget*=0.8;
		else if(grade==3) budget*=0.6;
		insertintoAccount(date,budget);
	}
}

BOOL BUYNUM::insertintoAccount(CString strDate, float budget )
{
	BOOL ret=FALSE;
	_RecordsetPtr m_pRs;
	CString sta=TEXT("2");
	m_pRs.CreateInstance(__uuidof(Recordset));
	try{
		HRESULT hr=m_pRs->Open(TEXT("select * from account"), m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
		//�ȵõ������ȫ�壬����һ����д��
		if(SUCCEEDED(hr)){
			m_pRs->AddNew();
			m_pRs->PutCollect("a_date", _variant_t(strDate));
			m_pRs->PutCollect("budget", _variant_t(budget));
			m_pRs->PutCollect("u_id", _variant_t(user));
			m_pRs->PutCollect("a_type", _variant_t(sta));
			m_pRs->Update();//��д
			ret=TRUE;
		}

	}catch(_com_error *e){
		MessageBox(e->ErrorMessage());
	}
	m_pRs->Close();
	m_pRs=NULL;
	return ret;
}

void BUYNUM::OnEnChangeEdit9()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void BUYNUM::OnBnClickedRadio1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	degree="1"; //���ó�ʼ�ȵ�
	UpdateData(TRUE);
	Customer dlg;
	dlg.c_grade=degree;
	dlg.DoModal();
	degree=dlg.c_grade;
}
