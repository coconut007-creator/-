#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CBookSell 对话框

class CBookSell : public CDialogEx
{
	DECLARE_DYNAMIC(CBookSell)

public:
	CBookSell(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBookSell();
	CString QueryBstate(CString strValue);
	afx_msg void OnBnClickedButton1(); //查询到货
	afx_msg void OnBnClickedButton2(); //添加新书
	//afx_msg void OnBnClickedButton3(); //书籍购买
	BOOL QueryAOG();
	CString QueryBisbn( CString strValue);
	CString QueryBname( CString strValue);
	float QuerySprice( CString strValue);
	BOOL Querybookid(CString bid);
// 对话框数据
	enum { IDD = IDD_CHECKDAESK };

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
	CComboBox b_state;
	CString g_price;
	CString g_amount;
public:
	afx_msg void OnBnClickedButton3();
};
