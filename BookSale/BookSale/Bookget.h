#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CBookget 对话框

class CBookget : public CDialogEx
{
	DECLARE_DYNAMIC(CBookget)

public:
	CBookget(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBookget();
// 对话框数据
	enum { IDD = IDD_BOOKSGETINOUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
private:
	CListCtrl bm_list;
public:
	afx_msg void OnBnClickedButton1();
	void searsell();
	CString QueryBname(CString strValue);
	CString QueryBisbn(CString strValue);
	BOOL Querybid(CString bid);
    int Queryallsell(CString strValue,int curItem, CString b_st);

private:
//	bool s_check;
	CString b_id;
	CString b_isbn;
	CString b_name;
	CString b_pub;
	CComboBox b_state;
public:
	afx_msg void OnBnClickedButton2();
	BOOL insertintoAccount( CString strDate,  float budget );
	BOOL updatesell( CString strbid, CString b_s );
	afx_msg void OnBnClickedButton3();
private:
//	BOOL s_check;
public:
	afx_msg void OnBnClickedButton4();
private:
	CString g_price;
	CString g_amount;
public:
	afx_msg void OnBnClickedButton8();
private:
	CEdit b_idC;
	CEdit b_isbnC;
	CEdit b_nameC;
	CEdit b_pubC;
	CEdit g_priceC;
	CEdit g_amountC;
};
