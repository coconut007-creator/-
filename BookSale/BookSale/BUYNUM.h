#pragma once


// BUYNUM �Ի���

class BUYNUM : public CDialogEx
{
	DECLARE_DYNAMIC(BUYNUM)

public:
	BUYNUM(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~BUYNUM();
	void updatebuynum();
	BOOL insertintoAccount(CString strDate, float budget );

// �Ի�������
	enum { IDD = IDD_BUYNUM };
	CString inventory; //���
	CString bid;
	CString date;
	CString degree;
	float price;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
