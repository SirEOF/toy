Windows Process Analysis Tools (windows程序分析工具)


主要功能:查看进程,线程,模块,堆内存,窗口,挂起线程,结束线程,卸载模块,CPU使用率,内存使用率,附加pe文件解析,支持查看导入表,导出表,重定位表,资源表,TLS表,延迟加载等..

附加功能:dll注入(win32/x64)，无模块Pe加载注入，R3;inlineHook实现进程隐藏，内置反汇编引擎实现代码注入

其他功能:MD5计算,一键隐藏窗口,托盘管理,增删用户,内存清理,窗口重置,等等无聊的功能都写里面了…

涉及的知识【MFC编程,Windows核心编程,C++,注入和hook】

项目仅供参考 有些小功能 很久前写的一个项目 当个玩具好啦


进程隐藏:
(进程隐藏采用了R3 层Hook ZwQuerySystemInformation 这个函数,这个函数是任务管理器,Proexp,Promon,一类进程管理所获取进程的一个函数底层调用的是这个函数,我们要先把DLL
注入到任务管理器中,然后在dll里面实现inlineHook 这个api 改前五个字节跳到dll中自己的NewZwQuerySystemInformation的函数中,把要隐藏的进程从单链表中剔去,不新鲜的东西咯..  详情代码请参考逆向工程核心原理,含有要提一点想隐藏进程是进程不在任务管理器显示,所以我们hook的是任务管理器ZwQuerySystemInformation 函数,因为书中的测试环境是Win7 x32所以他的任务管理器也是32位的,所以该方法对Win7 x64 六十四位的任务管理器无效,因为他们的函数参数入栈方式不同,要写段七个字节的内联汇编….

Demo:

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

dwAddress = (DWORD)pfnNew – (DWORD)pfnOrg – 5;
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
extern “C” {
#endif
__declspec(dllexport) void SetProcName(LPCTSTR szProcName)
{
_tcscpy_s(g_szProcName, szProcName);
}
#ifdef __cplusplus
}
#endif

Dll注入:

我的程序是Win32位的,所以只能注入Win32的程序,我通过在Win32唤起Win64的程序,FindWindow,得到窗口句柄然后发送消息,Win64程序我用了窗口隐藏,调用后即可销毁,这是注入的方法,借鉴一篇看雪无模块加载注入DLL我简单的说下我的理解,也算对他那篇文章做下解释吧..

它的文章地址:http://bbs.pediy.com/showthread.php?p=1243996

Nomal Dll Inject Demo:

//创建一个进程互斥量  防止无模块DLL多次注入
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

//调用LoadPE.cpp里的函数，自行处理PE加载，把DLL在新申请的内存加载起来，并执行入口函数
void LaunchNoModule()
{
LaunchDll(dllModuleName,NO_MODULE_MARK);
}
unsigned int  __stdcall NoModuleThread(void* lpParameter)
{
while (TRUE)
{
Sleep(1000);
OutputDebugString(“helloAgain~”);
}

return TRUE;
}
//调用LoadPE.cpp里的函数，自行处理PE加载，把DLL在新申请的内存加载起来，并执行入口函数
void NoModuleEntryCall(HMODULE hModule, DWORD ul_reason_for_call, char* pstrModuleName)
{
char szMutexName[MAX_PATH];
wsprintf(szMutexName,”HelloAgain~%d”,GetCurrentProcessId());
g_hMutex = CreateMutex(NULL, TRUE, szMutexName);

char szLog[MAX_PATH] = {0};
wsprintf(szLog,”NoModuleEntryCall Module Start:%p”,hModule);
OutputDebugString(szLog);
//下面为正常Dll功能代码

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

//ul_reason_for_call等于NO_MODULE_MARK时，DllMain已经是在新申请的内存中运行
//DllMain返回值是个很关键的地方，平常写DLLMain的时候不会注意，都是直接返回TRUE，没有去关注FALSE的情况
//ul_reason_for_call等于DLL_PROCESS_ATTACH时,DllMain返回FALSE会使DLL自行卸载
//利用这一点再结合PE自行加载，就可以实现无模块注入了
//当然，这样的DLL，如果由程序内部加载，也是以无模块的形式存在的
BOOL APIENTRY DllMain( HMODULE hModule,
DWORD  ul_reason_for_call,
LPVOID lpReserved
)
{
BOOL  bRet = FALSE;
if ( ul_reason_for_call == DLL_PROCESS_ATTACH || ul_reason_for_call == NO_MODULE_MARK )
{
char szMutexName[MAX_PATH];
wsprintf(szMutexName,”yanshier2013nomoduleinject%d”,GetCurrentProcessId());
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
下面着重看下它的Pe加载过程
BOOL PELoader(char *lpStaticPEBuff, PVOID& pExecuMem)
{
long lPESignOffset = *(long *)(lpStaticPEBuff + 0x3c);
IMAGE_NT_HEADERS *pINH = (IMAGE_NT_HEADERS *)(lpStaticPEBuff + lPESignOffset);

long lImageSize = pINH->OptionalHeader.SizeOfImage;
char *lpDynPEBuff = (char *)VirtualAlloc(NULL,lImageSize,MEM_COMMIT,PAGE_EXECUTE_READWRITE);
//申请一块SizeOfImage的内存
if(lpDynPEBuff == NULL)
{
return FALSE;
}
memset(lpDynPEBuff, 0, lImageSize);

long lSectionNum = pINH->FileHeader.NumberOfSections;

IMAGE_SECTION_HEADER *pISH = (IMAGE_SECTION_HEADER *)((char *)pINH + sizeof(IMAGE_NT_HEADERS));

memcpy(lpDynPEBuff, lpStaticPEBuff, pISH->VirtualAddress);

long lFileAlignMask = pINH->OptionalHeader.FileAlignment – 1;
long lSectionAlignMask = pINH->OptionalHeader.SectionAlignment – 1;
//按节表拷贝,重定位IAT
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
//Free掉这块内存,然后然后执行下面的函数 将ul_reason_for_call 标记成NO_MODULE_MARK
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

套路大概就是:第一次进入DllMain 实现PE加载,在PE加载前申请一块内存把自己Copy进去,然后释放当前的dll,进入下一个函数 返回值用No_Modal_Mark标记然后就举着No_Modal_Mark的牌子用申请的那块内存来搞事情了…

===============================================================================
代码注入: 

反汇编引擎,开源的网上很多我下了一个做外挂用的..   然后解释下文件写入和远程代码注入这里的内容吧

此函数只需要传进来被注入进程的PID，汇编代码还是要自己去手动定位函数基址,毕竟不是shellcode,其他用法和网上代码注入器都是一样的。

void CAsmInJectDlg::InjectBin(DWORD pid)
{
if (!AdjustPr())
{
MessageBox(“提权失败”);
return;
}
HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_CREATE_THREAD | PROCESS_VM_OPERATION | PROCESS_VM_WRITE, FALSE, pid);
if (!hProcess)
{
MessageBox(“OpenProcess失败”);
return;
}
//LPVOID pParam = VirtualAllocEx(hProcess, NULL, 4, MEM_COMMIT, PAGE_READWRITE);
LPVOID pAddr = VirtualAllocEx(hProcess, NULL, 4096, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
if (!pAddr)
{
MessageBox(“VirtualAllocEx失败”);
return;
}

CString tmp, str;
tmp.Format(“开辟的虚拟地址:%08X”, pAddr);
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
cmd[len] = ‘\0’;
t_asmmodel t_asm;
j = m_asm.Assemble(cmd, (DWORD)pAddr + j, &t_asm, 0, 4, error);
if (j <= 0)
{
tmp.Format(“error=\”%s\””, error);
OutputDebugString(tmp);
}
for (int k = 0; k<j; k++)
{
buf[m] = (BYTE)t_asm.code[k];        //按字节进行opcode转换
tmp.Format(“%02X”, buf[m]);
str = str + tmp;
m = m + 1;
}
OutputDebugString(str);
str = “”;
}

buf[m] = 0x0c2;//ret 4
buf[m + 1] = 0x04;
buf[m + 2] = 0x00;
if (!WriteProcessMemory(hProcess, pAddr, buf, 4096, NULL))
{
MessageBox(“内存写入失败”);
return;
}
DWORD dwThreadID;
DWORD dwParam = 0;
HANDLE hRemoteThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)pAddr, NULL, 0, &dwThreadID);
if (!hRemoteThread)
{
MessageBox(“远程线程创建失败”);
return;
}
CloseHandle(hRemoteThread);
CloseHandle(hProcess);

}


