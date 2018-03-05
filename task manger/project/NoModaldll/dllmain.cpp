// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include "MemoryLoad.h"



//创建一个进程互斥量  防止无模块DLL多次注入
BOOL IsMutexExist(char* pstrMutex)
{
	BOOL bRet = FALSE;
	HANDLE hMutex = NULL;

	hMutex = CreateMutexA(NULL, TRUE, pstrMutex);
	if (hMutex)
	{
		if (GetLastError() == ERROR_ALREADY_EXISTS)
			bRet = TRUE;
		ReleaseMutex(hMutex);
		CloseHandle(hMutex);
	}
	else
	{
		bRet = TRUE;
	}
	return bRet;

}

//调用LoadPE.cpp里的函数，自行处理PE加载，把DLL在新申请的内存加载起来，并执行入口函数
void LaunchNoModule()
{
	LaunchDll((char*)dllModuleName, NO_MODULE_MARK);
}
unsigned int  __stdcall NoModuleThread(void* lpParameter)
{
	while (TRUE)
	{
		Sleep(1000);
		OutputDebugString(L"Test by 2333333333333333333333333333333333333333333333");
	}

	return TRUE;
}
//调用LoadPE.cpp里的函数，自行处理PE加载，把DLL在新申请的内存加载起来，并执行入口函数
void NoModuleEntryCall(HMODULE hModule, DWORD ul_reason_for_call, char* pstrModuleName)
{
	TCHAR szMutexName[MAX_PATH];
	wsprintf(szMutexName, L"Test 15pb bingo! %d", GetCurrentProcessId());
	g_hMutex = CreateMutex(NULL, TRUE, szMutexName);

	TCHAR szLog[MAX_PATH] = { 0 };
	wsprintf(szLog, L"NoModuleEntryCall Module Start:%p", hModule);
	OutputDebugString(szLog);
	//下面为正常Dll功能代码


	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)NoModuleThread, NULL, NULL, NULL);


}

BOOL ChooseSub(HMODULE hModule, DWORD ul_reason_for_call, char* pstrModuleName)
{
	BOOL bRet = FALSE;
	GetModuleFileNameA(NULL, exeModuleName, MAX_PATH);
	if (ul_reason_for_call == NO_MODULE_MARK)
		//	strcpy((char*)dllModuleName,pstrModuleName);
		int a = 1;
	else
		GetModuleFileName(hModule, dllModuleName, MAX_PATH);

	if (ul_reason_for_call == NO_MODULE_MARK)
	{
		NoModuleEntryCall(hModule, DLL_PROCESS_ATTACH, 0);
		bRet = TRUE;
	}
	else
	{
		LaunchNoModule();
		bRet = FALSE;
	}
	return bRet;


}




BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	BOOL  bRet = FALSE;
	if (ul_reason_for_call == DLL_PROCESS_ATTACH || ul_reason_for_call == NO_MODULE_MARK)
	{
		TCHAR szMutexName[MAX_PATH];
		wsprintf(szMutexName, L"yanshier2013nomoduleinject%d", GetCurrentProcessId());
		if (IsMutexExist((char*)szMutexName))
			return FALSE;

		bRet = ChooseSub(hModule, ul_reason_for_call, (char *)lpReserved);
	}
	else
	{
		if (ul_reason_for_call == DLL_PROCESS_DETACH)
		{
			ReleaseMutex(g_hMutex);
			CloseHandle(g_hMutex);
			bRet = TRUE;
		}
	}
	return bRet;
}

