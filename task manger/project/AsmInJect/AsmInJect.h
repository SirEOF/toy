
// AsmInJect.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CAsmInJectApp: 
// �йش����ʵ�֣������ AsmInJect.cpp
//

class CAsmInJectApp : public CWinApp
{
public:
	CAsmInJectApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CAsmInJectApp theApp;