#pragma once


// CUpdateBooks �Ի���

class CUpdateBooks : public CDialogEx
{
	DECLARE_DYNAMIC(CUpdateBooks)

public:
	CUpdateBooks(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUpdateBooks();
	void updatebooks();
	CString bid;
// �Ի�������
	enum { IDD = IDD_UPDATEBOOKS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
