
// BasketballTiming.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CBasketballTimingApp:
// �йش����ʵ�֣������ BasketballTiming.cpp
//

class CBasketballTimingApp : public CWinApp
{
public:
	CBasketballTimingApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CBasketballTimingApp theApp;