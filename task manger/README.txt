Windows Process Analysis Tools (windows�����������)


��Ҫ����:�鿴����,�߳�,ģ��,���ڴ�,����,�����߳�,�����߳�,ж��ģ��,CPUʹ����,�ڴ�ʹ����,����pe�ļ�����,֧�ֲ鿴�����,������,�ض�λ��,��Դ��,TLS��,�ӳټ��ص�..

���ӹ���:dllע��(win32/x64)����ģ��Pe����ע�룬R3;inlineHookʵ�ֽ������أ����÷��������ʵ�ִ���ע��

��������:MD5����,һ�����ش���,���̹���,��ɾ�û�,�ڴ�����,��������,�ȵ����ĵĹ��ܶ�д�����ˡ�

�漰��֪ʶ��MFC���,Windows���ı��,C++,ע���hook��

��Ŀ�����ο� ��ЩС���� �ܾ�ǰд��һ����Ŀ ������ߺ���


��������:
(�������ز�����R3 ��Hook ZwQuerySystemInformation �������,������������������,Proexp,Promon,һ����̹�������ȡ���̵�һ�������ײ���õ����������,����Ҫ�Ȱ�DLL
ע�뵽�����������,Ȼ����dll����ʵ��inlineHook ���api ��ǰ����ֽ�����dll���Լ���NewZwQuerySystemInformation�ĺ�����,��Ҫ���صĽ��̴ӵ���������ȥ,�����ʵĶ�����..  ���������ο����򹤳̺���ԭ��,����Ҫ��һ�������ؽ����ǽ��̲��������������ʾ,��������hook�������������ZwQuerySystemInformation ����,��Ϊ���еĲ��Ի�����Win7 x32�����������������Ҳ��32λ��,���Ը÷�����Win7 x64 ��ʮ��λ�������������Ч,��Ϊ���ǵĺ���������ջ��ʽ��ͬ,Ҫд���߸��ֽڵ�������࡭.

Demo:

DWORD dwOldProtect, dwAddress;
BYTE pBuf[5] = { 0xE9, 0, };
PBYTE pByte;

// ��ȡZwQuerySystemInformation��ַ
pfnOrg = (FARPROC)GetProcAddress(GetModuleHandleA(szDllName), szFuncName);
pByte = (PBYTE)pfnOrg;

// �жϵ�һ���ֽ��Ƿ��ѱ��޸�
if (pByte[0] == 0xE9)
return FALSE;

// �޸��ڴ����� ǰ������ֽ�Ϊ��д
VirtualProtect((LPVOID)pfnOrg, 5, PAGE_EXECUTE_READWRITE, &dwOldProtect);

// �����޸�֮ǰ������ֽ�
memcpy(pOrgBytes, pfnOrg, 5);

// JMP �ĵ�ַ

dwAddress = (DWORD)pfnNew �C (DWORD)pfnOrg �C 5;
memcpy(&pBuf[1], &dwAddress, 4);

// �޸�����ֽ�
memcpy(pfnOrg, pBuf, 5);

// �ָ��ڴ�����
VirtualProtect((LPVOID)pfnOrg, 5, dwOldProtect, &dwOldProtect);

return TRUE;
}

BOOL unhook_by_code(LPCSTR szDllName, LPCSTR szFuncName, PBYTE pOrgBytes)
{
FARPROC pFunc;
DWORD dwOldProtect;
PBYTE pByte;
// ��ȡapi��ַ
pFunc = GetProcAddress(GetModuleHandleA(szDllName), szFuncName);
pByte = (PBYTE)pFunc;
//�ж��Ƿ�ҹ�
if (pByte[0] != 0xE9)
return FALSE;
// �޸��ڴ�����
VirtualProtect((LPVOID)pFunc, 5, PAGE_EXECUTE_READWRITE, &dwOldProtect);

// ж������
memcpy(pFunc, pOrgBytes, 5);

// ��ԭ�ڴ�����
VirtualProtect((LPVOID)pFunc, 5, dwOldProtect, &dwOldProtect);
return TRUE;
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
extern ��C�� {
#endif
__declspec(dllexport) void SetProcName(LPCTSTR szProcName)
{
_tcscpy_s(g_szProcName, szProcName);
}
#ifdef __cplusplus
}
#endif

Dllע��:

�ҵĳ�����Win32λ��,����ֻ��ע��Win32�ĳ���,��ͨ����Win32����Win64�ĳ���,FindWindow,�õ����ھ��Ȼ������Ϣ,Win64���������˴�������,���ú󼴿�����,����ע��ķ���,���һƪ��ѩ��ģ�����ע��DLL�Ҽ򵥵�˵���ҵ����,Ҳ�������ƪ�������½��Ͱ�..

�������µ�ַ:http://bbs.pediy.com/showthread.php?p=1243996

Nomal Dll Inject Demo:

//����һ�����̻�����  ��ֹ��ģ��DLL���ע��
BOOL IsMutexExist(char* pstrMutex)
{
BOOL bRet = FALSE;
HANDLE hMutex = NULL;

hMutex = CreateMutexA(NULL, TRUE, pstrMutex);
if ( hMutex )
{
if ( GetLastError() == ERROR_ALREADY_EXISTS )
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

//����LoadPE.cpp��ĺ��������д���PE���أ���DLL����������ڴ������������ִ����ں���
void LaunchNoModule()
{
LaunchDll(dllModuleName,NO_MODULE_MARK);
}
unsigned int  __stdcall NoModuleThread(void* lpParameter)
{
while (TRUE)
{
Sleep(1000);
OutputDebugString(��helloAgain~��);
}

return TRUE;
}
//����LoadPE.cpp��ĺ��������д���PE���أ���DLL����������ڴ������������ִ����ں���
void NoModuleEntryCall(HMODULE hModule, DWORD ul_reason_for_call, char* pstrModuleName)
{
char szMutexName[MAX_PATH];
wsprintf(szMutexName,��HelloAgain~%d��,GetCurrentProcessId());
g_hMutex = CreateMutex(NULL, TRUE, szMutexName);

char szLog[MAX_PATH] = {0};
wsprintf(szLog,��NoModuleEntryCall Module Start:%p��,hModule);
OutputDebugString(szLog);
//����Ϊ����Dll���ܴ���

CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)NoModuleThread,NULL,NULL,NULL);

}

BOOL ChooseSub(HMODULE hModule, DWORD ul_reason_for_call, char* pstrModuleName)
{
BOOL bRet = FALSE;
GetModuleFileNameA(NULL, exeModuleName, MAX_PATH);
if ( ul_reason_for_call == NO_MODULE_MARK )
strcpy(dllModuleName, pstrModuleName);
else
GetModuleFileName(hModule, dllModuleName, MAX_PATH);

if ( ul_reason_for_call == NO_MODULE_MARK )
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

//ul_reason_for_call����NO_MODULE_MARKʱ��DllMain�Ѿ�������������ڴ�������
//DllMain����ֵ�Ǹ��ܹؼ��ĵط���ƽ��дDLLMain��ʱ�򲻻�ע�⣬����ֱ�ӷ���TRUE��û��ȥ��עFALSE�����
//ul_reason_for_call����DLL_PROCESS_ATTACHʱ,DllMain����FALSE��ʹDLL����ж��
//������һ���ٽ��PE���м��أ��Ϳ���ʵ����ģ��ע����
//��Ȼ��������DLL������ɳ����ڲ����أ�Ҳ������ģ�����ʽ���ڵ�
BOOL APIENTRY DllMain( HMODULE hModule,
DWORD  ul_reason_for_call,
LPVOID lpReserved
)
{
BOOL  bRet = FALSE;
if ( ul_reason_for_call == DLL_PROCESS_ATTACH || ul_reason_for_call == NO_MODULE_MARK )
{
char szMutexName[MAX_PATH];
wsprintf(szMutexName,��yanshier2013nomoduleinject%d��,GetCurrentProcessId());
if ( IsMutexExist(szMutexName))
return FALSE;

bRet = ChooseSub(hModule, ul_reason_for_call, (char *)lpReserved);
}
else
{
if ( ul_reason_for_call ==  DLL_PROCESS_DETACH)
{
ReleaseMutex(g_hMutex);
CloseHandle(g_hMutex);
bRet = TRUE;
}
}
return bRet;
}
�������ؿ�������Pe���ع���
BOOL PELoader(char *lpStaticPEBuff, PVOID& pExecuMem)
{
long lPESignOffset = *(long *)(lpStaticPEBuff + 0x3c);
IMAGE_NT_HEADERS *pINH = (IMAGE_NT_HEADERS *)(lpStaticPEBuff + lPESignOffset);

long lImageSize = pINH->OptionalHeader.SizeOfImage;
char *lpDynPEBuff = (char *)VirtualAlloc(NULL,lImageSize,MEM_COMMIT,PAGE_EXECUTE_READWRITE);
//����һ��SizeOfImage���ڴ�
if(lpDynPEBuff == NULL)
{
return FALSE;
}
memset(lpDynPEBuff, 0, lImageSize);

long lSectionNum = pINH->FileHeader.NumberOfSections;

IMAGE_SECTION_HEADER *pISH = (IMAGE_SECTION_HEADER *)((char *)pINH + sizeof(IMAGE_NT_HEADERS));

memcpy(lpDynPEBuff, lpStaticPEBuff, pISH->VirtualAddress);

long lFileAlignMask = pINH->OptionalHeader.FileAlignment �C 1;
long lSectionAlignMask = pINH->OptionalHeader.SectionAlignment �C 1;
//���ڱ���,�ض�λIAT
for(int nIndex = 0; nIndex < lSectionNum; nIndex++, pISH++)
{
memcpy(lpDynPEBuff + pISH->VirtualAddress, lpStaticPEBuff + pISH->PointerToRawData, pISH->SizeOfRawData);
}

if(pINH->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size > 0)
{
IMAGE_IMPORT_DESCRIPTOR *pIID = (IMAGE_IMPORT_DESCRIPTOR *)(lpDynPEBuff + \
pINH->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
//
for(; pIID->Name != NULL; pIID++)
{
IMAGE_THUNK_DATA *pITD = (IMAGE_THUNK_DATA *)(lpDynPEBuff + pIID->FirstThunk);

char* pLoadName = lpDynPEBuff + pIID->Name;
HINSTANCE hInstance = LoadLibrary(pLoadName);
if(hInstance == NULL)
{
//Free������ڴ�,Ȼ��Ȼ��ִ������ĺ��� ��ul_reason_for_call ��ǳ�NO_MODULE_MARK
VirtualFree(lpDynPEBuff,lImageSize,MEM_DECOMMIT);
return FALSE;
}

for(; pITD->u1.Ordinal != 0; pITD++)
{
FARPROC fpFun;
if(pITD->u1.Ordinal & IMAGE_ORDINAL_FLAG32)
{
fpFun = GetProcAddress(hInstance, (LPCSTR)(pITD->u1.Ordinal & 0x0000ffff));
}
else
{
IMAGE_IMPORT_BY_NAME * pIIBN = (IMAGE_IMPORT_BY_NAME *)(lpDynPEBuff + pITD->u1.Ordinal);
fpFun = GetProcAddress(hInstance, (LPCSTR)pIIBN->Name);
}

if(fpFun == NULL)
{
delete lpDynPEBuff;
return false;
}

pITD->u1.Ordinal = (long)fpFun;
}
}
}

��·��ž���:��һ�ν���DllMain ʵ��PE����,��PE����ǰ����һ���ڴ���Լ�Copy��ȥ,Ȼ���ͷŵ�ǰ��dll,������һ������ ����ֵ��No_Modal_Mark���Ȼ��;���No_Modal_Mark��������������ǿ��ڴ����������ˡ�

===============================================================================
����ע��: 

���������,��Դ�����Ϻܶ�������һ��������õ�..   Ȼ��������ļ�д���Զ�̴���ע����������ݰ�

�˺���ֻ��Ҫ��������ע����̵�PID�������뻹��Ҫ�Լ�ȥ�ֶ���λ������ַ,�Ͼ�����shellcode,�����÷������ϴ���ע��������һ���ġ�

void CAsmInJectDlg::InjectBin(DWORD pid)
{
if (!AdjustPr())
{
MessageBox(����Ȩʧ�ܡ�);
return;
}
HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_CREATE_THREAD | PROCESS_VM_OPERATION | PROCESS_VM_WRITE, FALSE, pid);
if (!hProcess)
{
MessageBox(��OpenProcessʧ�ܡ�);
return;
}
//LPVOID pParam = VirtualAllocEx(hProcess, NULL, 4, MEM_COMMIT, PAGE_READWRITE);
LPVOID pAddr = VirtualAllocEx(hProcess, NULL, 4096, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
if (!pAddr)
{
MessageBox(��VirtualAllocExʧ�ܡ�);
return;
}

CString tmp, str;
tmp.Format(�����ٵ������ַ:%08X��, pAddr);
OutputDebugString(tmp);

char error[256] = { 0 };
int count = m_Asm.GetLineCount();
BYTE buf[4096] = { 0 };
int j = 0;
int m = 0;

for (int i = 0; i < count; i++)
{
char cmd[256] = { 0 };
int len = m_Asm.GetLine(i, cmd, 256);
if (len == 0) continue;
cmd[len] = ��\0��;
t_asmmodel t_asm;
j = m_asm.Assemble(cmd, (DWORD)pAddr + j, &t_asm, 0, 4, error);
if (j <= 0)
{
tmp.Format(��error=\��%s\����, error);
OutputDebugString(tmp);
}
for (int k = 0; k<j; k++)
{
buf[m] = (BYTE)t_asm.code[k];        //���ֽڽ���opcodeת��
tmp.Format(��%02X��, buf[m]);
str = str + tmp;
m = m + 1;
}
OutputDebugString(str);
str = ����;
}

buf[m] = 0x0c2;//ret 4
buf[m + 1] = 0x04;
buf[m + 2] = 0x00;
if (!WriteProcessMemory(hProcess, pAddr, buf, 4096, NULL))
{
MessageBox(���ڴ�д��ʧ�ܡ�);
return;
}
DWORD dwThreadID;
DWORD dwParam = 0;
HANDLE hRemoteThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)pAddr, NULL, 0, &dwThreadID);
if (!hRemoteThread)
{
MessageBox(��Զ���̴߳���ʧ�ܡ�);
return;
}
CloseHandle(hRemoteThread);
CloseHandle(hProcess);

}


