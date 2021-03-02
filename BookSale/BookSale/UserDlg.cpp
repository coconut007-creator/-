// UserDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BookSale.h"
#include "UserDlg.h"
#include "afxdialogex.h"
#include<atlconv.h>
extern CString user;
extern CString password;
extern CString deg;
extern _ConnectionPtr m_pConnection;
// CUserDlg �Ի���

IMPLEMENT_DYNAMIC(CUserDlg, CDialogEx)

CUserDlg::CUserDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUserDlg::IDD, pParent)
	, u_id(_T(""))
	, u_pwd(_T(""))
	, u_wid(_T(""))
	, u_name(_T(""))
	, u_age(_T(""))
{

}

CUserDlg::~CUserDlg()
{
}

void CUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Text(pDX, IDC_EDIT1, u_id);
	DDX_Text(pDX, IDC_EDIT4, u_pwd);
	DDX_Control(pDX, IDC_COMBO1, u_deg);
	DDX_Text(pDX, IDC_EDIT5, u_wid);
	DDX_Text(pDX, IDC_EDIT7, u_name);
	DDX_Control(pDX, IDC_COMBO2, u_gen);
	DDX_Text(pDX, IDC_EDIT6, u_age);
	//  DDX_Check(pDX, IDC_CHECK1, u_check);
	DDX_Control(pDX, IDC_EDIT4, u_pwdC);
	DDX_Control(pDX, IDC_EDIT5, u_widC);
	DDX_Control(pDX, IDC_EDIT7, u_nameC);
	DDX_Control(pDX, IDC_EDIT6, u_ageC);
	DDX_Control(pDX, IDC_EDIT1, u_idC);
}


BEGIN_MESSAGE_MAP(CUserDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CUserDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CUserDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CUserDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CUserDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CUserDlg ��Ϣ�������


void CUserDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int d=_ttoi(deg);
	if(d!=1){
		MessageBox(TEXT("û��Ȩ��"));
		return;
	}
	insertusers();

}
BOOL CUserDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//�������ݰ����Լ�����Ҫд
	CString str[] = { TEXT("�û���"),TEXT("����"), TEXT("����"),TEXT("����"),TEXT("�Ա�"), TEXT("����"),TEXT("�ȼ�") };
	for (int i = 0; i < 7; i++) {
		//���ñ�ͷ�����������ݣ����뷽ʽ���п�
		m_list.InsertColumn(i, str[i],LVCFMT_LEFT,90);
	}
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	_RecordsetPtr m_pUs;
	HRESULT hr;
	hr=m_pUs.CreateInstance(__uuidof(Recordset));
	if(FAILED(hr)){
		MessageBox(TEXT("������¼������ʧ��"));
		return FALSE;
	}
	CString sql;
	CString strValue;
	sql.Format(TEXT("select * from users where u_id = \'%s\' and pwd = (SELECT sys.fn_sqlvarbasetostr(HashBytes(\'MD5\',\'%s\')))"),user,password);
	try{
		hr=m_pUs->Open(_variant_t(sql),m_pConnection.GetInterfacePtr(),adOpenKeyset,adLockOptimistic,adCmdText);
		if(FAILED(hr)){
			return FALSE;
		}
		m_list.InsertItem(0, user);
		m_list.SetItemText(0, 1, password);
		strValue=m_pUs->GetCollect("name").bstrVal;
		m_list.SetItemText(0, 2, strValue);
		strValue=m_pUs->GetCollect("w_id").bstrVal;
		m_list.SetItemText(0, 3, strValue);
		strValue=m_pUs->GetCollect("gender").bstrVal;
		m_list.SetItemText(0, 4, strValue);
		strValue=m_pUs->GetCollect("age").bstrVal;
		m_list.SetItemText(0, 5, strValue);
		strValue=m_pUs->GetCollect("degree").bstrVal;
		m_list.SetItemText(0, 6, strValue);
		//Ĭ����ʾ�Լ���
	}
	catch(_com_error *e){
		MessageBox(e->ErrorMessage());
		return FALSE;
	}
	m_pUs->Close();
	m_pUs.Release();
	return TRUE;
}

void CUserDlg::searUsers()
{
	UpdateData(TRUE);
	_RecordsetPtr m_pUs;
	m_pUs.CreateInstance(__uuidof(Recordset));
	CString strdeg;
	CString strgen;
	u_deg.GetWindowText(strdeg);
	u_gen.GetWindowText(strgen);

	//���������û���/����/����/�ȼ���ѯ/һ����û��
	CString strSQL;
	//if(!u_check){//һ����û��
	//	strSQL=TEXT("select * from users");
	//}
	//else{
	//	strSQL=TEXT("select * from users where");
	//}
	if(u_id.IsEmpty()&&u_name.IsEmpty()&&u_wid.IsEmpty()&&strdeg.IsEmpty()&&strgen.IsEmpty()){
		strSQL=TEXT("select * from users");
	}
	else{
		strSQL=TEXT("select * from users where");
	if(!u_id.IsEmpty()){
		strSQL.AppendFormat(TEXT(" u_id=\'%s\'"), u_id);
	}
	if(!u_name.IsEmpty()){
		if(!u_id.IsEmpty()){
			strSQL.AppendFormat(TEXT(" and name=\'%s\'"), u_name);
		}
		else{
			strSQL.AppendFormat(TEXT(" name=\'%s\'"), u_name);
		}
	}
	if(!u_wid.IsEmpty()){
		if(!u_name.IsEmpty()||!u_id.IsEmpty()){
			strSQL.AppendFormat(TEXT(" and w_id=\'%s\'"), u_wid);
		}
		else{
			strSQL.AppendFormat(TEXT(" w_id=\'%s\'"), u_wid);
		}
	}
	if(!strdeg.IsEmpty()){
		if(!u_name.IsEmpty()||!u_id.IsEmpty()||!u_wid.IsEmpty()){
			strSQL.AppendFormat(TEXT(" and degree=\'%s\'"), strdeg);
		}
		else{
			strSQL.AppendFormat(TEXT(" degree=\'%s\'"), strdeg);
		}
	}
	if(!strgen.IsEmpty()){
		if(!u_name.IsEmpty()||!u_id.IsEmpty()||!u_wid.IsEmpty()||!strdeg.IsEmpty()){
			strSQL.AppendFormat(TEXT(" and gender=\'%s\'"), strgen);
		}
		else{
			strSQL.AppendFormat(TEXT(" gender=\'%s\'"), strgen);
		}
	}
}
	//SQL������

	try{
		HRESULT hr=m_pUs->Open(_variant_t(strSQL),m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
		if(FAILED(hr)){
			return;
		}

		if(m_pUs->GetadoEof()){
			MessageBox(TEXT("���Ϊ��"));
			return;
		}
		else{
			_variant_t var;
			CString strValue;
			int curItem=0;

			m_list.DeleteAllItems();//��ԭ����ɾ��
				while(!m_pUs->GetadoEof()){//EOFָʾ��ǰλ���Ƿ�λ�ڼ�¼�������һ����
					var=m_pUs->GetCollect((long)0);//ͨ���кŻ�ȡ��ǰ�е�0��  ����_variant_t��������longת���Ĺ��ܣ�����ת��long
					if(var.vt!=NULL)
						strValue=(LPCTSTR)_bstr_t(var);//��variant������ת��bstr����תCString
					m_list.InsertItem(curItem, strValue);
					for(int i=1;i<7;i++){
						var=m_pUs->GetCollect((long)i);//ͨ����������ȡ
						if(var.vt!=VT_NULL)
							strValue=(LPCTSTR)_bstr_t(var);
						else
							strValue=TEXT(" ");
						m_list.SetItemText(curItem, i, strValue);//1Ϊ�к�
					}
					m_pUs->MoveNext();//�Ƶ���һ��
					curItem++;
				}
			}
	}
	catch(_com_error *e){
		MessageBox(e->ErrorMessage());
		return;
	}

	m_pUs->Close();
	m_pUs.Release();
}


void CUserDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int d=_ttoi(deg);
	if(d!=1){
		MessageBox(TEXT("û��Ȩ��"));
		return;
	}
	//���������û���/����/������ѯ
	searUsers();
	return;
}

void CUserDlg::insertusers()
{
	//BOOL ret=FALSE;
	UpdateData(TRUE);
	CString strdeg;
	CString strgen;
	u_deg.GetWindowText(strdeg);
	u_gen.GetWindowText(strgen);
	_RecordsetPtr m_pUs;
	m_pUs.CreateInstance(__uuidof(Recordset));
	if(!Queryuserid(u_id)){
		MessageBox(TEXT("�û����ظ�!"));
		return;
	}
	try{
		HRESULT hr=m_pUs->Open(TEXT("select * from users"), m_pConnection.GetInterfacePtr(), adOpenKeyset, adLockOptimistic, adCmdText);
		//�ȵõ������ȫ�壬����һ����д��
		if(SUCCEEDED(hr)){
			m_pUs->AddNew();
			if(!u_id.IsEmpty())
				m_pUs->PutCollect("u_id", _variant_t(u_id));
			else MessageBox(TEXT("�û�����Ϊ��"));
			if(!u_pwd.IsEmpty())
			{
				_RecordsetPtr m_pAs;
	            m_pAs.CreateInstance(__uuidof(Recordset));
				CString sql;
				sql.Format(TEXT("select sys.fn_sqlvarbasetostr(HashBytes(\'MD5\',\'%s\'))"),u_pwd);
				HRESULT hr1=m_pAs->Open(_variant_t(sql), m_pConnection.GetInterfacePtr(), adOpenKeyset, adLockOptimistic, adCmdText);
				_variant_t var;
				var=m_pAs->GetCollect((long)0);//ͨ���кŻ�ȡ��ǰ�е�0��  ����_variant_t��������longת���Ĺ��ܣ�����ת��long
				if(var.vt!=NULL)
					u_pwd=(LPCTSTR)_bstr_t(var);//��variant������ת��bstr����תCString
				m_pUs->PutCollect("pwd", _variant_t(u_pwd));
			}
			else MessageBox(TEXT("���벻Ϊ��"));
			if(!u_name.IsEmpty())
				m_pUs->PutCollect("name", _variant_t(u_name));
			if(!u_wid.IsEmpty())
				m_pUs->PutCollect("w_id", _variant_t(u_wid));
			if(!strgen.IsEmpty())
				m_pUs->PutCollect("gender", _variant_t(strgen));
			if(!u_age.IsEmpty())
				m_pUs->PutCollect("age", _variant_t(u_age));
			if(!strdeg.IsEmpty())
				m_pUs->PutCollect("degree", _variant_t(strdeg));
			else MessageBox(TEXT("�ȼ���Ϊ��"));
			m_pUs->Update();//��д
		}

		
	}catch(_com_error *e){
		MessageBox(e->ErrorMessage());
	}

	

	MessageBox(TEXT("����û��ɹ�!"));
	m_pUs->Close();
	m_pUs=NULL;
}

void CUserDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	u_deg.SetCurSel(0);
	u_gen.SetCurSel(0);
	u_idC.SetWindowText(TEXT(""));
	u_pwdC.SetWindowText(TEXT(""));
	u_nameC.SetWindowText(TEXT(""));
	u_widC.SetWindowText(TEXT(""));
	u_ageC.SetWindowText(TEXT(""));
}


void CUserDlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	deleteusers();
}

void CUserDlg::deleteusers()
{
	if (m_list.GetSelectionMark()!=-1)
	{
		if (MessageBox(TEXT("ȷʵҪɾ��������?"),TEXT("��ʾ"),MB_YESNO|MB_ICONINFORMATION)==IDYES)
		{
			int i = m_list.GetSelectionMark();
			CString uid = m_list.GetItemText(i,0);
			CString sql;
			sql.Format(TEXT("delete users where u_id= \'%s\'"),uid);
			_RecordsetPtr m_pUs;
			m_pUs.CreateInstance(__uuidof(Recordset));
			try
			{
				HRESULT hr=m_pUs->Open((_variant_t)sql, m_pConnection.GetInterfacePtr(), adOpenKeyset, adLockOptimistic, adCmdText);
				if(SUCCEEDED(hr)){

					MessageBox(TEXT("ɾ���ɹ�"));
				}
					
			}
			catch(_com_error *e){
				MessageBox(e->ErrorMessage());
			}
		}
	}
	else
		MessageBox(TEXT("��ѡ��Ҫɾ������Ϣ"));
}

BOOL CUserDlg::Queryuserid(CString uid)
{
	_RecordsetPtr m_pUs;
	HRESULT hr;
	hr=m_pUs.CreateInstance(__uuidof(Recordset));
	if(FAILED(hr)){
		MessageBox(TEXT("������¼������ʧ��"));
		return FALSE;
	}
	CString sql;
	CString strValue;
	sql.Format(TEXT("select * from users where u_id = \'%s\'"),uid);
	hr=m_pUs->Open(_variant_t(sql),m_pConnection.GetInterfacePtr(),adOpenKeyset,adLockOptimistic,adCmdText);
	if(FAILED(hr)){
		return FALSE;
	}
	try{
		if (m_pUs->RecordCount>0)
		{
			return FALSE;
		}
	}
	catch(_com_error *e){
		MessageBox(e->ErrorMessage());
		return FALSE;
	}
	m_pUs->Close();
	m_pUs.Release();
	return TRUE;
}
