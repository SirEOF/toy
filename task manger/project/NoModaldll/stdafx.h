// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ
// Windows ͷ�ļ�: 
#include <windows.h>

#define  NO_MODULE_MARK 0x2012aaae
extern HANDLE g_hMutex;
extern TCHAR dllModuleName[MAX_PATH];
extern char exeModuleName[MAX_PATH];
#define _CRT_SECURE_NO_WARNINGS
// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
