#pragma once


// BUYNUM 对话框

class BUYNUM : public CDialogEx
{
	DECLARE_DYNAMIC(BUYNUM)

public:
	BUYNUM(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~BUYNUM();
	void updatebuynum();
	BOOL insertintoAccount(CString strDate, float budget );

// 对话框数据
	enum { IDD = IDD_BUYNUM };
	CString inventory; //库存
	CString bid;
	CString date;
	CString degree;
	float price;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEdit9();
private:
	CString buynum;
public:
	afx_msg void OnBnClickedRadio1();
};
