#pragma once


// CGetinBooks �Ի���

class CGetinBooks : public CDialogEx
{
	DECLARE_DYNAMIC(CGetinBooks)

public:
	CGetinBooks(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGetinBooks();
	void updatesell();
// �Ի�������
	enum { IDD = IDD_BOOKGETIN };
	CString st;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
