
// BookSale.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CBookSaleApp:
// �йش����ʵ�֣������ BookSale.cpp
//

class CBookSaleApp : public CWinApp
{
public:
	CBookSaleApp();

// ��д
public:
	virtual BOOL InitInstance();
	BOOL ConnectDB();
	void CloseDB();

// ʵ��

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};


extern CBookSaleApp theApp;