// AccouDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BookSale.h"
#include "AccouDlg.h"
#include "afxdialogex.h"
extern _ConnectionPtr m_pConnection;

// CAccouDlg 对话框

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
//	CString str[] = { TEXT("日期"),TEXT("收支"), TEXT("操作人"),TEXT("类型") };
//	for (int i = 0; i < 4; i++) {
//		//设置表头：索引，内容，对齐方式，列宽
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
//		MessageBox(TEXT("创建记录集对象失败"));
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
//		MessageBox(TEXT("结果为空"));
//		return;
//	}
//	else{
//		_variant_t var;
//		CString strValue;
//		int curItem=0;
//
//		am_list.DeleteAllItems();//把原来的删了
//		try{
//			while(!m_pAs->GetadoEof()){//EOF指示当前位置是否位于记录集的最后一个后
//
//				var=m_pAs->GetCollect((long)0);//通过列号获取当前行第0列  接受_variant_t参数，有long转换的功能，所以转成long
//				if(var.vt!=NULL)
//					strValue=(LPCTSTR)_bstr_t(var);//把variant类型先转成bstr，再转CString
//				am_list.InsertItem(curItem, strValue);
//				for(int i=1;i<4;i++){
//					var=m_pAs->GetCollect((long)i);
//					if(var.vt!=NULL)
//						strValue=(LPCTSTR)_bstr_t(var);
//					am_list.SetItemText(curItem, i, strValue);//i为列号
//				}//数字？
//				m_pAs->MoveNext();//移到下一行
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


// CAccouDlg 消息处理程序


void CAccouDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
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
		MessageBox(TEXT("创建记录集对象失败"));
		return;
	}
	
	CString strSQL=TEXT("select * from account where");
	//检测日期范围对不对
		CTime timeFrom, timeTo;
		a_datafrom.GetTime(timeFrom);
		a_datato.GetTime(timeTo);

		a_datafrom.GetWindowText(strDatefrom);
		a_datato.GetWindowText(strDateto);

		if(timeFrom.GetMonth()>timeTo.GetMonth()){
			MessageBox(TEXT("日期设置错误"));
			return;
		}else if(timeFrom.GetMonth()==timeTo.GetMonth()){
			if(timeFrom.GetDay()>timeTo.GetDay()){
				MessageBox(TEXT("日期设置错误"));
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
		MessageBox(TEXT("请输入信息"));
		return;
	}
	//SQL建好了

	try{
		hr=m_pAs->Open((_variant_t)strSQL,m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
		if(FAILED(hr)){
			MessageBox(TEXT("创建记录集对象失败"));
			return;
		}

	if(m_pAs->GetadoEof()){
		MessageBox(TEXT("结果为空"));
		return;
	}
	else{
		_variant_t var;
		CString strValue;
		int curItem=0;

		am_list.DeleteAllItems();//把原来的删了
		try{
			while(!m_pAs->GetadoEof()){//EOF指示当前位置是否位于记录集的最后一个后

				var=m_pAs->GetCollect((long)0);//通过列号获取当前行第0列  接受_variant_t参数，有long转换的功能，所以转成long
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
					am_list.SetItemText(curItem, i, strValue);//i为列号
				}
				m_pAs->MoveNext();//移到下一行
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
	CString str[] = { TEXT("日期"),TEXT("收支"), TEXT("操作人"),TEXT("类型") };
	for (int i = 0; i < 4; i++) {
		//设置表头：索引，内容，对齐方式，列宽
		am_list.InsertColumn(i, str[i],LVCFMT_LEFT,90);
	}
	am_list.SetExtendedStyle(am_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	CString strSQL;
	strSQL=TEXT("select * from account");

	_RecordsetPtr m_pAs;
	HRESULT hr;
	hr=m_pAs.CreateInstance(__uuidof(Recordset));
	if(FAILED(hr)){
		MessageBox(TEXT("创建记录集对象失败"));
		return FALSE;
	}
	try{
		hr=m_pAs->Open((_variant_t)strSQL,m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
		if(FAILED(hr)){
			return FALSE;
		}
		if(m_pAs->GetadoEof()){
			MessageBox(TEXT("account结果为空"));
			return TRUE;
		}
		else{
			_variant_t var;
			CString strValue;
			int curItem=0;

			am_list.DeleteAllItems();//把原来的删了
			while(!m_pAs->GetadoEof()){//EOF指示当前位置是否位于记录集的最后一个后
				var=m_pAs->GetCollect((long)0);//通过列号获取当前行第0列  接受_variant_t参数，有long转换的功能，所以转成long
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
					am_list.SetItemText(curItem, i, strValue);//i为列号
				}
				m_pAs->MoveNext();//移到下一行
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
	// TODO: 在此添加控件通知处理程序代码
}
