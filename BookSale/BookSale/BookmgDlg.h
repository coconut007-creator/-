#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CBookmgDlg 对话框

class CBookmgDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBookmgDlg)

public:
	CBookmgDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBookmgDlg();

// 对话框数据
	enum { IDD = IDD_BOOKALREADYMANAGE };


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
private:
	CListCtrl bm_list;
	CString b_id;
	CString b_isbn;
	CString b_name;
	CString b_pub;
	CString b_wrt;
	CString b_price;
	CString b_num;
public:
	afx_msg void OnBnClickedButton3();
	//void Initbookmg();
	void searBooks();
	void insertbooks();
	void deletebooks();
	BOOL Querybookid(CString bid);

private:
//	bool b_check;
public:
//	BOOL m_check;
	afx_msg void OnBnClickedButton1();
private:
	CEdit b_idC;
	CEdit b_wrtC;
	CEdit b_isbnC;
	CEdit b_priceC;
	CEdit b_nameC;
	CEdit b_numC;
	CEdit b_pubC;
public:
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton2();
};
