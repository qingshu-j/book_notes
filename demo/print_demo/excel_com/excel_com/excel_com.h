
// excel_com.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cexcel_comApp: 
// �йش����ʵ�֣������ excel_com.cpp
//

class Cexcel_comApp : public CWinApp
{
public:
	Cexcel_comApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cexcel_comApp theApp;