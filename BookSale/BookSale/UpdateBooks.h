#pragma once


// CUpdateBooks 对话框

class CUpdateBooks : public CDialogEx
{
	DECLARE_DYNAMIC(CUpdateBooks)

public:
	CUpdateBooks(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUpdateBooks();
	void updatebooks();
	CString bid;
// 对话框数据
	enum { IDD = IDD_UPDATEBOOKS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CString b_isbn;
	CString b_wrt;
	CString b_name;
	CString b_price;
	CString b_pub;
	CString b_num;
public:
	afx_msg void OnBnClickedButton1();
};
