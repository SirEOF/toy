// PageTwo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AAA.h"
#include "PageTwo.h"

#include "afxdialogex.h"
#include "resource.h"
#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <afxmsg_.h>
#include <locale.h>
#include <Psapi.h>
#include "ModelPro.h"
#include "ItemPro2Dlg.h"

#define WM_CONTROLPRINT WM_USER+1001
#define WM_HEAPget WM_USER+1002
#define WM_ASMPROID WM_USER+3

/*
#include "WarnDlg.h"
#include "MoudleDlg.h"
#include "ProcessHide.h"
*/
// PageTwo �Ի���
#pragma comment (lib,"Psapi.lib")
extern TCHAR g_szProcName[MAX_PATH];//������
extern  BYTE g_pOrgBytes[5];//HOOKԭ����

//ȫ�ֱ���
TCHAR SZPath[MAX_PATH];
TCHAR PSZPath[MAX_PATH];
HANDLE HPrs;
static PQWORD hnnd;
IMPLEMENT_DYNAMIC(PageTwo, CDialogEx)
UINT HideInject(LPVOID);


PageTwo::PageTwo(CWnd* pParent /*=NULL*/)
	: CDialogEx(PageTwo::IDD, pParent)
	
{
	pFlag = false;
}

PageTwo::~PageTwo()
{
}

void PageTwo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LT2, m_L2);
	ShowList();
}


BEGIN_MESSAGE_MAP(PageTwo, CDialogEx)
	//ON_NOTIFY(NM_RCLICK, IDC_PROCESS_LIST, &ProcessDlg::OnRclickProcessList)
	ON_COMMAND(ID__KillPro, &PageTwo::KillPro)		  //��������
	ON_COMMAND(ID_OpenPos, &PageTwo::Openpos)		  //���ļ�λ��
	ON_COMMAND(ID_RePro, &PageTwo::RePro)			  //�ָ�����
	ON_COMMAND(ID_ReFreshList, &PageTwo::Refreshlist)   //ˢ�½���
	ON_COMMAND(ID_ViewModel, &PageTwo::Viewmodel)	  //�鿴ģ��
	ON_COMMAND(ID_ItemPro, &PageTwo::ViewProcess)	//�鿴�߳�
	ON_COMMAND(ID_PickPro,&PageTwo::OnPickpro)      //�������
	ON_COMMAND(ID_DllInject,&PageTwo::OnDllinJect)  //DLLע��
	ON_MESSAGE(WM_CONTROLPRINT, &PageTwo::SendProcessID)//�Զ�����Ϣ
	ON_MESSAGE(WM_HEAPget,&PageTwo::SendProHeap)  //�Զ�����Ϣ
//	ON_MESSAGE(WM_HEAPget, &PageTwo::SendProHeap)

	ON_NOTIFY(NM_RCLICK, IDC_LT2, &PageTwo::OnNMRClickLt2)
	ON_COMMAND(ID_PickPro, &PageTwo::OnPickpro)
	ON_COMMAND(ID_Injectshellcode, &PageTwo::OnInjectshellcode)
	ON_COMMAND(ID_SHISHI, &PageTwo::OnShishi)
	ON_COMMAND(ID_HighStd, &PageTwo::OnHighstd)
	ON_COMMAND(ID_Std, &PageTwo::OnStd)
	ON_COMMAND(ID_BelowStd, &PageTwo::OnBelowstd)
	ON_COMMAND(ID_Low, &PageTwo::OnLow)
	ON_COMMAND(ID_High, &PageTwo::OnHigh)
	ON_COMMAND(ID_ViewHeap, &PageTwo::OnViewheap)

	ON_NOTIFY(NM_RCLICK, IDC_ItemProD, &PageTwo::OnNMRClickItemprod)

	ON_COMMAND(ID_32798, &PageTwo::OnHideProcess)
END_MESSAGE_MAP()


void PageTwo::OnNMRClickItemprod(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���������������

	int a = 0;
}

//��������
void PageTwo::KillPro()
{
	POSITION pos = m_L2.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		CString str;
		int nItem = m_L2.GetNextSelectedItem(pos);
		str = m_L2.GetItemText(nItem, 1);
		char _char[100] = { 0 };
		WideCharToMultiByte(CP_ACP, NULL, str, -1, _char, 100, NULL, NULL);
		DWORD pid = (DWORD)atoi(_char);
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
		TerminateProcess(hProcess, 0);
		CloseHandle(hProcess);
		Refreshlist();
	}
	// TODO:  �ڴ���������������
}

//�鿴ģ��
void PageTwo::Viewmodel()
{
	//MessageBox(L"11111111");
	// TODO:  �ڴ���������������
	
	ModelPro MoudleDLG;
	MoudleDLG.m_dwPID = m_PID;

	MoudleDLG.DoModal();
	
}

//�鿴�߳�
void PageTwo::ViewProcess()
{
#if 0
	ThreadTool ThreadDLG;
	
	ThreadDLG.m_currPid = m_PID;
	ThreadDLG.DoModal();
#endif

	CItemPro2Dlg dlg;
	dlg.m_FuckPid = m_PID;
	dlg.DoModal();
	
}

//�鿴�ѷֲ�
void PageTwo::OnViewheap()
{
	sViewHeap HeapDlg;
	HeapDlg.m_HeapId = m_PID;
	HeapDlg.DoModal();





	/*
	int i = m_L2.GetSelectionMark();//���ѡ ���е��б�

	//CString s = m_L2.GetItemText(i, 0);
	int processID = _ttoi(m_L2.GetItemText(i, 0));
	sViewHeap DlgHeap;
	//DlgHeap.DoModal();
	//DlgHeap.ShowWindow(TRUE);

	HWND hWnd = ::FindWindow(NULL, _T("�ѷֲ��鿴��"));
	if (hWnd)
	{
		LPARAM a = processID;
		::SendMessage(hWnd, WM_HEAPget, NULL, processID);
		//SendMessage(hWnd, WM_CONTROLPRINT, NULL, b);
	}
	DlgHeap.DoModal();
	
	hhnd = new QWORD;
	*hhnd = processID;
	
	*/

}


//���ļ�λ��
POSITION pos;
void PageTwo::Openpos()
{
		// TODO:  �ڴ���������������
	pos = m_L2.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		CString strParam, str;
		int nItem = m_L2.GetNextSelectedItem(pos);
		str = m_L2.GetItemText(nItem, 4);
		strParam.Format(_T("/select,%s"), str);
		ShellExecute(0, _T("open"), _T("Explorer.exe"), strParam, 0, SW_NORMAL);
	}
	
	
}

//�ָ�����
void PageTwo::RePro()
{
	POSITION pos = m_L2.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		CString str;
		int nItem = m_L2.GetNextSelectedItem(pos);
		str = m_L2.GetItemText(nItem, 1);
		char _char[100] = { 0 };
		WideCharToMultiByte(CP_ACP, NULL, str, -1, _char, 100, NULL, NULL);
		DWORD pid = (DWORD)atoi(_char);
		HANDLE hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, pid);
		THREADENTRY32 te32 = { sizeof(te32) };
		int nCount = 0;
		if (hThreadSnap != INVALID_HANDLE_VALUE)
		{
			if (!Thread32First(hThreadSnap, &te32))
				CloseHandle(hThreadSnap);
			do
			{
				if (te32.th32OwnerProcessID == pid)
				{
					HANDLE hthread = OpenThread(THREAD_ALL_ACCESS, FALSE, te32.th32ThreadID);
					ResumeThread(hthread);
				}
			} while (Thread32Next(hThreadSnap, &te32));
		}
		Refreshlist();
	}
	// TODO:  �ڴ���������������
}

//ˢ���б�
void PageTwo::Refreshlist()
{
	// TODO:  �ڴ���������������
	m_L2.SetRedraw(FALSE);
	UpdateData(TRUE);
	m_L2.DeleteAllItems();
	UpdateData(FALSE);
	m_L2.SetRedraw(TRUE);
	m_L2.Invalidate();
	m_L2.UpdateWindow();
	// TODO:  �ڴ���������������
}

//����Ŀ¼��ȡ
BOOL PageTwo::GetProcessPath(DWORD dwPID)
{
	if (!PSZPath)
	{
		return FALSE;
	}
	PSZPath[0] = '\0';
	HPrs = OpenProcess(PROCESS_QUERY_INFORMATION, 0, dwPID);
	if (!HPrs)
		return FALSE;
	if (!GetProcessImageFileName(HPrs, SZPath, MAX_PATH))
	{
		CloseHandle(HPrs);
		return FALSE;
	}
	if (!BDTPath(SZPath, PSZPath))
	{
		CloseHandle(HPrs);
		return FALSE;
	}
	/*CloseHandle(HPrs);*/
	Path = PSZPath;
	return TRUE;
}

HANDLE         HSnap;
PROCESSENTRY32 pe;

//List�ؼ�����ʾ
void PageTwo::ShowList()
{

	CString Dat = {};
	if (!pFlag)
	{
		m_L2.SetExtendedStyle(m_L2.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
		CString str[] = { _T(""), _T("ӳ������"), _T("PID"), _T("�߳���"), _T("���ȼ�"), _T("ƽ̨"), _T("ӳ���ļ�λ��") };
		m_L2.InsertColumn(0, str[0], LVCFMT_LEFT, 1000);
		m_L2.InsertColumn(1, str[1], LVCFMT_LEFT, 100);
		m_L2.InsertColumn(2, str[2], LVCFMT_LEFT,50 );
		m_L2.InsertColumn(3, str[3], LVCFMT_LEFT, 50);
		m_L2.InsertColumn(4, str[4], LVCFMT_LEFT, 50);
		m_L2.InsertColumn(5, str[5], LVCFMT_LEFT, 50);
		m_L2.InsertColumn(6, str[6], LVCFMT_LEFT, 100);
		m_L2.DeleteColumn(0);
		pFlag = TRUE;
	}
	//��ʼ���������б�
	setlocale(LC_ALL, "chs");
	HSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	pe = { sizeof(pe) };
	BOOL bPrcs = Process32First(HSnap, &pe);
	int Num = 0;
	if (bPrcs)
	{
		do
		{
			m_L2.InsertItem(Num, _T(""));
			m_L2.SetItemText(Num, 0, pe.szExeFile);
			Dat.Format(L"%d", pe.th32ProcessID);
			m_L2.SetItemText(Num, 1, Dat);
			Dat.Format(L"%d", pe.cntThreads);
			m_L2.SetItemText(Num, 2, Dat);
			Dat.Format(L"%d", pe.pcPriClassBase);
			m_L2.SetItemText(Num, 3, Dat);
			GetProcessPath(pe.th32ProcessID);
			m_L2.SetItemText(Num, 5, Path);

			BOOL a;
			HANDLE hP = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pe.th32ProcessID);
			IsWow64Process(hP, &a);
			if (hP == NULL)
				m_L2.SetItemText(Num, 4, L"δ֪");
			else if (a == 0)
				m_L2.SetItemText(Num, 4, L"x64");
			else if (a == 1)
				m_L2.SetItemText(Num, 4, L"Win32");
			
			Num++;
		} while (Process32Next(HSnap, &pe));
	}
	CloseHandle(HSnap);
	HSnap = NULL;
}

//����Ŀ¼����
BOOL PageTwo::BDTPath(LPTSTR BDPath, LPTSTR BTPath)
{
	TCHAR           szDriveStr[500];
	TCHAR           szDrive[3];
	TCHAR           szDevName[100];
	INT             cchDevName;
	INT             i;
	//������  
	if (!BDPath || !BTPath)
		return FALSE;
	//��ȡ���ش����ַ���  
	if (GetLogicalDriveStrings(sizeof(szDriveStr), szDriveStr))
	{
		for (i = 0; szDriveStr[i]; i += 4)
		{
			if (!lstrcmpi(&(szDriveStr[i]), _T("A:\\")) || !lstrcmpi(&(szDriveStr[i]), _T("B:\\")))
				continue;
			szDrive[0] = szDriveStr[i];
			szDrive[1] = szDriveStr[i + 1];
			szDrive[2] = '\0';
			if (!QueryDosDevice(szDrive, szDevName, 100))//��ѯ Dos �豸��  
				return FALSE;
			cchDevName = lstrlen(szDevName);
			if (_tcsnicmp(BDPath, szDevName, cchDevName) == 0)//����  
			{
				lstrcpy(BTPath, szDrive);//����������  
				lstrcat(BTPath, BDPath + cchDevName);//����·��  
				return TRUE;
			}
		}
	}
	lstrcpy(BTPath, BDPath);
	return FALSE;
}

//List�ؼ�������һ���Ϣ
void PageTwo::OnNMRClickLt2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	CString str = m_L2.GetItemText(pNMItemActivate->iItem, 1);
	_stscanf_s(str, L"%d", &m_PID);
	ProcessName = m_L2.GetItemText(pNMItemActivate->iItem, 0);
	CMenu Menu;
	VERIFY(Menu.LoadMenu(IDR_ProcessMenu));
	CMenu* pPopup = Menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);
	CPoint point;
	GetCursorPos(&point);
	pPopup->TrackPopupMenu(TPM_LEFTBUTTON | TPM_RIGHTBUTTON, point.x, point.y, this);
	*pResult = 0;
	*pResult = 0;
}

//�����߳�
void PageTwo::OnPickpro()
{
	// TODO:  �ڴ���������������
	POSITION pos = m_L2.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		CString str;
		int nItem = m_L2.GetNextSelectedItem(pos);
		str = m_L2.GetItemText(nItem, 1);
		char _char[100] = { 0 };
		WideCharToMultiByte(CP_ACP, NULL, str, -1, _char, 100, NULL, NULL);
		DWORD pid = (DWORD)atoi(_char);
		HANDLE hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, pid);
		THREADENTRY32 te32 = { sizeof(te32) };
		int nCount = 0;
		if (hThreadSnap != INVALID_HANDLE_VALUE)
		{
			if (!Thread32First(hThreadSnap, &te32))
				CloseHandle(hThreadSnap);
			do
			{
				if (te32.th32OwnerProcessID == pid)
				{
					HANDLE hthread = OpenThread(THREAD_ALL_ACCESS, FALSE, te32.th32ThreadID);
					SuspendThread(hthread);
				}
			} while (Thread32Next(hThreadSnap, &te32));
		}
	//	Refreshlist();
	}
	// TODO:  �ڴ���������������
}

//���ý������ȼ�
void PageTwo::SetProcessPriority(int PriorityFlag)
{
	HANDLE hProcessHandle;
	POSITION pos = m_L2.GetFirstSelectedItemPosition();
	int nItem = m_L2.GetNextSelectedItem(pos);
	//	int j = m_VecProList[m_VecProList.size()-(nItem+1)].th32ProcessID;
	hProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, m_PID);
	

	switch (PriorityFlag)
	{      
	case 1:
		SetPriorityClass(hProcessHandle, REALTIME_PRIORITY_CLASS);//ʵʱ		
		Refreshlist();
		break;
	case 2:
		SetPriorityClass(hProcessHandle, HIGH_PRIORITY_CLASS);//��
		Refreshlist();
		break;
	case 3:
		SetPriorityClass(hProcessHandle, ABOVE_NORMAL_PRIORITY_CLASS);//���ڱ�׼
		Refreshlist();
		break;
	case 4:
		SetPriorityClass(hProcessHandle, NORMAL_PRIORITY_CLASS);//��׼
		Refreshlist();
		break;
	case 5:
		SetPriorityClass(hProcessHandle, BELOW_NORMAL_PRIORITY_CLASS);//���ڱ�׼
		Refreshlist();
		break;
	case 6:
		SetPriorityClass(hProcessHandle, IDLE_PRIORITY_CLASS);//��
		Refreshlist();
		break;
	default:
		break;
	}
}

LRESULT PageTwo::SendProcessID(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT PageTwo::SendProHeap(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

DWORD a;
UINT DlliNjeCT(LPVOID)
{
	SIZE_T  Count = 0;
	//�򿪽���
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, a);
	//�ڱ��˵��߳��д���һ���ڴ� д200��ô���
	LPVOID pMen = VirtualAllocEx(hProcess, NULL, 200, MEM_COMMIT, PAGE_READWRITE);
	//���ǿ������ڴ���д������
	//WriteProcessMemory(hProcess, pMen, L"C:\\Win32.dll", (wcslen(L"C:\\Win32.dll") + 1) * 2, &Count);
	WriteProcessMemory(hProcess, pMen, L"C:\\Users\\Administrator\\Desktop\\okokok\\Debug\\TestDll.dll", (wcslen(L"C:\\Users\\Administrator\\Desktop\\okokok\\Debug\\TestDll.dll") + 1) * 2, &Count);
	//�򿪶Է�����ʹ���̵߳Ļص����� ֱ�ӵ����Լ���DLL
	HANDLE hThread = CreateRemoteThread(
		hProcess, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibraryW, pMen, NULL, NULL);
	if (hThread)
	{
		MessageBox(0,L"ע��ɹ�",L"Congratulation",0);
	}
	WaitForSingleObject(hThread, -1);
	CloseHandle(hProcess);
	CloseHandle(hThread);

	return 0;
}

DWORD b;
UINT X64Inject(LPVOID)
{
	/*
		CHAR TEMP[200] = { 0 };
		CString TEMP1;
		TEMP1.Format(L"C:\\Users\\Administrator\\Desktop\\�޸���\\x64\\Debug\\x64InjectT00l.exe  %d", b);
		WideCharToMultiByte(CP_ACP, NULL, TEMP1, -1, TEMP,_countof(TEMP), NULL, FALSE);
		system(TEMP);
		*/
		//ShellExecute(NULL, L"open", L"C:\\Users\\Administrator\\Documents\\Visual Studio 2013\\Projects\\MFCApplication1\\x64\\Debug\\MFCApplication1.exe", NULL, NULL, SW_SHOWNORMAL);
		
		WinExec("C:\\Users\\Administrator\\Desktop\\okokok\\x64\\Debug\\x64tool.exe", SW_HIDE);
		//ShellExecute(NULL, L"open", L"C:\\Users\\Administrator\\Documents\\Visual Studio 2013\\Projects\\MFCApplication1\\x64\\Debug\\MFCApplication1.exe", NULL, NULL, SW_SHOWNORMAL);

	// ��ȡ���մ��ھ��
	HWND hWnd = FindWindow(NULL, _T("x64tool"));
	if (hWnd == NULL)
	{
		MessageBox(0, L"���ܳ���û��������", L"Error", 0);
		
	}
	//������Ϣ
	LPARAM lPram = b;
	SendMessage(hWnd, WM_CONTROLPRINT, NULL, b);
	


	
	//::PostMessage(hx64Dlg, WM_CONTROLPRINT, 0, 0);
		return 0;
}

void PageTwo::OnDllinJect()
{
	
	int i = m_L2.GetSelectionMark();			//���ѡ ���е��б�
	if (m_L2.GetItemText(i, 4) == L"Win32")
	{
		a = _ttoi(m_L2.GetItemText(i, 1));
		AfxBeginThread(DlliNjeCT, 0, 0);
	}
	else if (m_L2.GetItemText(i, 4) == L"x64")
	{
		b = _ttoi(m_L2.GetItemText(i, 1));
		AfxBeginThread(X64Inject, 0, 0);
	}
	else
	{
		MessageBox(L"δ֪�ĳ���");
	}
}

void PageTwo::OnInjectshellcode()
{

	DWORD c;
	int i = m_L2.GetSelectionMark();
	c = _ttoi(m_L2.GetItemText(i,1));
	
	WinExec("C:\\Users\\Administrator\\Desktop\\okokok\\Debug\\AsmInJect.exe", SW_HIDE);
	HWND hWND = ::FindWindow(NULL,_T("AsmInJect"));
	if (hWND == NULL)
	{
		MessageBox(L"���ܳ���û��������");
	}
	LPARAM lpRam = c;
	::SendMessage(hWND,WM_ASMPROID,NULL,c);

}

//ʵʱ
void PageTwo::OnShishi()
{
	// TODO:  �ڴ���������������
	SetProcessPriority(1);

}

//���ڱ�׼
void PageTwo::OnHighstd()
{
	// TODO:  �ڴ���������������
	SetProcessPriority(3);
}

//��׼
void PageTwo::OnStd()
{
	// TODO:  �ڴ���������������
	SetProcessPriority(4);
}

//���ڱ�׼
void PageTwo::OnBelowstd()
{
	// TODO:  �ڴ���������������
	SetProcessPriority(5);
}

//��
void PageTwo::OnLow()
{
	// TODO:  �ڴ���������������
	SetProcessPriority(6);
}

//��            
void PageTwo::OnHigh()  
{
	// TODO:  �ڴ���������������
	SetProcessPriority(2);
}

//���ؽ���
DWORD D = 0;
TCHAR szDllPath[260] = L"D:\\HideDll.dll";
void PageTwo::OnHideProcess()
{
	typedef void(*PFN_SetProcName)(LPCTSTR szProcName);
	
	HMODULE                 hLib = NULL;
	PFN_SetProcName         SetProcName = NULL;
	hLib = LoadLibraryW(szDllPath);
	SetProcName = (PFN_SetProcName)GetProcAddress(hLib, "SetProcName");
	

	HWND taskMang = ::FindWindow(NULL,_T("Windows ���������"));
	
	GetWindowThreadProcessId(taskMang, &D);

 	int i = m_L2.GetSelectionMark();

	
	CString ProName = m_L2.GetItemText(i, 0);
	SetProcName(ProName);

	AfxBeginThread(HideInject, 0, 0);
	

}

CRITICAL_SECTION g_cs1;
UINT HideInject(LPVOID)
{
	HANDLE                 hProcess, hThread;
	LPVOID                  pRemoteBuf;
	DWORD                   dwBufSize = (DWORD)(_tcslen(szDllPath) + 1) * sizeof(TCHAR);
	LPTHREAD_START_ROUTINE  pThreadProc;

	
	EnterCriticalSection(&g_cs1);

	if (!(hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, D)))
	{
		TCHAR Str[20] = L"";
		swprintf_s(Str, L"�򿪽���ʧ�� %d", D);
		MessageBox(0, Str, Str, 0);
	}

	LeaveCriticalSection(&g_cs1);

	pRemoteBuf = VirtualAllocEx(hProcess, NULL, dwBufSize,
		MEM_COMMIT, PAGE_READWRITE);

	WriteProcessMemory(hProcess, pRemoteBuf,
		(LPVOID)szDllPath, dwBufSize, NULL);

	pThreadProc = (LPTHREAD_START_ROUTINE)
		GetProcAddress(GetModuleHandle(L"kernel32.dll"),
		"LoadLibraryW");
	hThread = CreateRemoteThread(hProcess, NULL, 0,
		pThreadProc, pRemoteBuf, 0, NULL);
	WaitForSingleObject(hThread, INFINITE);

	VirtualFreeEx(hProcess, pRemoteBuf, dwBufSize, MEM_RELEASE);

	CloseHandle(hThread);
	CloseHandle(hProcess);
	return 0;
}

BOOL PageTwo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitializeCriticalSection(&g_cs1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
