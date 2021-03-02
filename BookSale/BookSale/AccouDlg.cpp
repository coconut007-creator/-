// AccouDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BookSale.h"
#include "AccouDlg.h"
#include "afxdialogex.h"
extern _ConnectionPtr m_pConnection;

// CAccouDlg �Ի���

IMPLEMENT_DYNAMIC(CAccouDlg, CDialogEx)

CAccouDlg::CAccouDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAccouDlg::IDD, pParent)
	, a_name(_T(""))
{

}

CAccouDlg::~CAccouDlg()
{
}

void CAccouDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, am_list);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, a_datafrom);
	DDX_Control(pDX, IDC_DATETIMEPICKER3, a_datato);
	DDX_Text(pDX, IDC_EDIT1, a_name);
	DDX_Control(pDX, IDC_COMBO2, a_type);
}


BEGIN_MESSAGE_MAP(CAccouDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CAccouDlg::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CAccouDlg::OnCbnSelchangeCombo2)
END_MESSAGE_MAP()

//void CAccouDlg::InitAccount()
//{
//
//	CString str[] = { TEXT("����"),TEXT("��֧"), TEXT("������"),TEXT("����") };
//	for (int i = 0; i < 4; i++) {
//		//���ñ�ͷ�����������ݣ����뷽ʽ���п�
//		am_list.InsertColumn(i, str[i],LVCFMT_LEFT,50);
//	}
//	am_list.SetExtendedStyle(am_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
//	CString strSQL;
//	strSQL=TEXT("select * from account");
//
//	_RecordsetPtr m_pAs;
//	HRESULT hr;
//	hr=m_pAs.CreateInstance(__uuidof(Recordset));
//	if(FAILED(hr)){
//		MessageBox(TEXT("������¼������ʧ��"));
//		return;
//	}
//	try{
//		hr=m_pAs->Open((_variant_t)strSQL,m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
//		if(FAILED(hr)){
//			return;
//		}
//	}
//	catch(_com_error *e){
//		MessageBox(e->ErrorMessage());
//		return;
//	}
//
//	if(m_pAs->GetadoEof()){
//		MessageBox(TEXT("���Ϊ��"));
//		return;
//	}
//	else{
//		_variant_t var;
//		CString strValue;
//		int curItem=0;
//
//		am_list.DeleteAllItems();//��ԭ����ɾ��
//		try{
//			while(!m_pAs->GetadoEof()){//EOFָʾ��ǰλ���Ƿ�λ�ڼ�¼�������һ����
//
//				var=m_pAs->GetCollect((long)0);//ͨ���кŻ�ȡ��ǰ�е�0��  ����_variant_t��������longת���Ĺ��ܣ�����ת��long
//				if(var.vt!=NULL)
//					strValue=(LPCTSTR)_bstr_t(var);//��variant������ת��bstr����תCString
//				am_list.InsertItem(curItem, strValue);
//				for(int i=1;i<4;i++){
//					var=m_pAs->GetCollect((long)i);
//					if(var.vt!=NULL)
//						strValue=(LPCTSTR)_bstr_t(var);
//					am_list.SetItemText(curItem, i, strValue);//iΪ�к�
//				}//���֣�
//				m_pAs->MoveNext();//�Ƶ���һ��
//				curItem++;
//			}
//		}
//		catch(_com_error* e){
//			MessageBox(e->ErrorMessage());
//			return;
//		}
//	}
//	m_pAs->Close();
//	m_pAs=NULL;
//}


// CAccouDlg ��Ϣ�������


void CAccouDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	searAcc();
}

void CAccouDlg::searAcc()
{
	UpdateData(TRUE);
	CString strDatefrom;
	CString strDateto;
	CString strtype;

	_RecordsetPtr m_pAs;
	HRESULT hr;
	hr=m_pAs.CreateInstance(__uuidof(Recordset));
	if(FAILED(hr)){
		MessageBox(TEXT("������¼������ʧ��"));
		return;
	}
	
	CString strSQL=TEXT("select * from account where");
	//������ڷ�Χ�Բ���
		CTime timeFrom, timeTo;
		a_datafrom.GetTime(timeFrom);
		a_datato.GetTime(timeTo);

		a_datafrom.GetWindowText(strDatefrom);
		a_datato.GetWindowText(strDateto);

		if(timeFrom.GetMonth()>timeTo.GetMonth()){
			MessageBox(TEXT("�������ô���"));
			return;
		}else if(timeFrom.GetMonth()==timeTo.GetMonth()){
			if(timeFrom.GetDay()>timeTo.GetDay()){
				MessageBox(TEXT("�������ô���"));
				return;
			}
		}
		strSQL.AppendFormat(TEXT(" a_date>=\'%s\' and a_date<=\'%s\'"), strDatefrom, strDateto);

	if(!a_name.IsEmpty()){
		strSQL.AppendFormat(TEXT(" and u_id=\'%s\'"), a_name);
	}

	a_type.GetWindowText(strtype);
	if(!strtype.IsEmpty()){
		strSQL.AppendFormat(TEXT(" and a_type=\'%s\'"), strtype);
	}

	if(a_name.IsEmpty()&&strtype.IsEmpty()){
		MessageBox(TEXT("��������Ϣ"));
		return;
	}
	//SQL������

	try{
		hr=m_pAs->Open((_variant_t)strSQL,m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
		if(FAILED(hr)){
			MessageBox(TEXT("������¼������ʧ��"));
			return;
		}

	if(m_pAs->GetadoEof()){
		MessageBox(TEXT("���Ϊ��"));
		return;
	}
	else{
		_variant_t var;
		CString strValue;
		int curItem=0;

		am_list.DeleteAllItems();//��ԭ����ɾ��
		try{
			while(!m_pAs->GetadoEof()){//EOFָʾ��ǰλ���Ƿ�λ�ڼ�¼�������һ����

				var=m_pAs->GetCollect((long)0);//ͨ���кŻ�ȡ��ǰ�е�0��  ����_variant_t��������longת���Ĺ��ܣ�����ת��long
				if(var.vt!=NULL)
					strValue=(LPCTSTR)_bstr_t(var);
				else
					strValue=TEXT(" ");
				am_list.InsertItem(curItem, strValue);
				for(int i=1;i<4;i++){
					var=m_pAs->GetCollect((long)i);
					if(var.vt!=VT_NULL)
						strValue=(LPCTSTR)_bstr_t(var);
					else
						strValue=TEXT(" ");
					am_list.SetItemText(curItem, i, strValue);//iΪ�к�
				}
				m_pAs->MoveNext();//�Ƶ���һ��
				curItem++;
			}
		}
		catch(_com_error* e){
			MessageBox(e->ErrorMessage());
			return;
		}
	}
	}catch(_com_error *e){
		MessageBox(e->ErrorMessage());
		return;
	}

	m_pAs->Close();
	m_pAs.Release();

}

BOOL CAccouDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString str[] = { TEXT("����"),TEXT("��֧"), TEXT("������"),TEXT("����") };
	for (int i = 0; i < 4; i++) {
		//���ñ�ͷ�����������ݣ����뷽ʽ���п�
		am_list.InsertColumn(i, str[i],LVCFMT_LEFT,90);
	}
	am_list.SetExtendedStyle(am_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	CString strSQL;
	strSQL=TEXT("select * from account");

	_RecordsetPtr m_pAs;
	HRESULT hr;
	hr=m_pAs.CreateInstance(__uuidof(Recordset));
	if(FAILED(hr)){
		MessageBox(TEXT("������¼������ʧ��"));
		return FALSE;
	}
	try{
		hr=m_pAs->Open((_variant_t)strSQL,m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
		if(FAILED(hr)){
			return FALSE;
		}
		if(m_pAs->GetadoEof()){
			MessageBox(TEXT("account���Ϊ��"));
			return TRUE;
		}
		else{
			_variant_t var;
			CString strValue;
			int curItem=0;

			am_list.DeleteAllItems();//��ԭ����ɾ��
			while(!m_pAs->GetadoEof()){//EOFָʾ��ǰλ���Ƿ�λ�ڼ�¼�������һ����
				var=m_pAs->GetCollect((long)0);//ͨ���кŻ�ȡ��ǰ�е�0��  ����_variant_t��������longת���Ĺ��ܣ�����ת��long
				if(var.vt!=VT_NULL)
					strValue=(LPCTSTR)_bstr_t(var);
				else
					strValue=TEXT(" ");
				am_list.InsertItem(curItem, strValue);
				for(int i=1;i<4;i++){
					var=m_pAs->GetCollect((long)i);
					if(var.vt!=VT_NULL)
						strValue=(LPCTSTR)_bstr_t(var);
					else
						strValue=TEXT(" ");
					am_list.SetItemText(curItem, i, strValue);//iΪ�к�
				}
				m_pAs->MoveNext();//�Ƶ���һ��
				curItem++;
			}
		}

	}
	catch(_com_error *e){
		MessageBox(e->ErrorMessage());
		return FALSE;
	}

	m_pAs->Close();
	m_pAs.Release();
	return TRUE;
}




void CAccouDlg::OnCbnSelchangeCombo2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
