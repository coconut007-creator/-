#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CBookSell �Ի���

class CBookSell : public CDialogEx
{
	DECLARE_DYNAMIC(CBookSell)

public:
	CBookSell(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBookSell();
	CString QueryBstate(CString strValue);
	afx_msg void OnBnClickedButton1(); //��ѯ����
	afx_msg void OnBnClickedButton2(); //�������
	//afx_msg void OnBnClickedButton3(); //�鼮����
	BOOL QueryAOG();
	CString QueryBisbn( CString strValue);
	CString QueryBname( CString strValue);
	float QuerySprice( CString strValue);
	BOOL Querybookid(CString bid);
// �Ի�������
	enum { IDD = IDD_CHECKDAESK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
private:
	CListCtrl bm_list;
	CString b_id;
	CString b_isbn;
	CString b_name;
	CString b_pub;
	CString b_wrt;
	CComboBox b_state;
	CString g_price;
	CString g_amount;
public:
	afx_msg void OnBnClickedButton3();
};
