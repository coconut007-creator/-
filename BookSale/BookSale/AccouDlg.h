#pragma once
#include "afxcmn.h"
#include "afxdtctl.h"
#include "afxwin.h"


// CAccouDlg 对话框

class CAccouDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAccouDlg)

public:
	CAccouDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAccouDlg();

// 对话框数据
	enum { IDD = IDD_ACCOUNT };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
private:
	CListCtrl am_list;
public:
	afx_msg void OnBnClickedButton1();
	void searAcc();
private:
	bool a_check;
public:
	CDateTimeCtrl a_datafrom;
private:
	CDateTimeCtrl a_datato;
	CString a_name;
	CComboBox a_type;
public:
	afx_msg void OnDtnDatetimechangeDatetimepicker2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnCbnSelchangeCombo2();
};
