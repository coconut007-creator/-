#pragma once


// Customer �Ի���

class Customer : public CDialogEx
{
	DECLARE_DYNAMIC(Customer)

public:
	Customer(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Customer();
	void searchgrade();

// �Ի�������
	enum { IDD = IDD_CUSTOMER };
	CString c_grade; //��ù˿͵ȼ�

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	CString c_id;
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEdit9();
	afx_msg void OnBnClickedCancel();
};
