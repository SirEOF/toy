
// x64tool.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cx64toolApp: 
// �йش����ʵ�֣������ x64tool.cpp
//

class Cx64toolApp : public CWinApp
{
public:
	Cx64toolApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cx64toolApp theApp;