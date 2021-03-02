#pragma once


// Getprice 对话框

class Getprice : public CDialogEx
{
	DECLARE_DYNAMIC(Getprice)

public:
	Getprice(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Getprice();
	void updateprice();

// 对话框数据
	enum { IDD = IDD_Getprice };
	CString bid;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEdit9();
private:
	CString s_price;
};
