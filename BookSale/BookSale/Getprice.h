#pragma once


// Getprice �Ի���

class Getprice : public CDialogEx
{
	DECLARE_DYNAMIC(Getprice)

public:
	Getprice(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Getprice();
	void updateprice();

// �Ի�������
	enum { IDD = IDD_Getprice };
	CString bid;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEdit9();
private:
	CString s_price;
};
