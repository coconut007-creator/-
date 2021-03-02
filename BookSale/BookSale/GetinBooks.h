#pragma once


// CGetinBooks 对话框

class CGetinBooks : public CDialogEx
{
	DECLARE_DYNAMIC(CGetinBooks)

public:
	CGetinBooks(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGetinBooks();
	void updatesell();
// 对话框数据
	enum { IDD = IDD_BOOKGETIN };
	CString st;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CString bid;
	CString amount;
private:
	CString b_amount;
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeEdit9();
};
