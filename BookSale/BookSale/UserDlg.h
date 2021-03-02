#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CUserDlg 对话框

class CUserDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUserDlg)

public:
	CUserDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUserDlg();

// 对话框数据
	enum { IDD = IDD_USERMANAGE };
	//void InitUsers();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	
	DECLARE_MESSAGE_MAP()
private:
	CListCtrl m_list;
	
	CString u_id;
	CString u_pwd;
	CComboBox u_deg;
	CString u_wid;
private:
	CString u_name;
	CComboBox u_gen;
	CString u_age;
public:
	afx_msg void OnBnClickedButton1();
	void searUsers();
	 void insertusers();
	 void deleteusers();
	 BOOL Queryuserid(CString uid);
private:
//	bool u_check;
public:
	afx_msg void OnBnClickedButton3();
private:
//	BOOL u_check;
	CEdit u_pwdC;
	CEdit u_widC;
	CEdit u_nameC;
	CEdit u_ageC;
	CEdit u_idC;
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
};
