#pragma once


// Customer 对话框

class Customer : public CDialogEx
{
	DECLARE_DYNAMIC(Customer)

public:
	Customer(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Customer();
	void searchgrade();

// 对话框数据
	enum { IDD = IDD_CUSTOMER };
	CString c_grade; //获得顾客等级

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CString c_id;
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEdit9();
	afx_msg void OnBnClickedCancel();
};
