// PageFour.cpp : 实现文件
//
#include "windows.h"
#include "stdafx.h"
#include "AAA.h"
#include "AAADlg.h"
#include "PageFour.h"
#include "afxdialogex.h"
#include <string.h>
#include "shellapi.h"
#include "resource.h"
#include <TlHelp32.h>
#include <psapi.h>
#define SystemBasicInformation 0 
#define SystemPerformanceInformation 2 
#define SystemTimeInformation 3
#define _CRT_SECURE_NO_WARNINGS

#define Li2Double(x) ((double)((x).HighPart) * 4.294967296E9 + (double)((x).LowPart))
const int KB_DIV = 1024;
const int MB_DIV = 1024 * 1024;
CCPUUseRate cpuUseRate;
CRITICAL_SECTION g_cs;


typedef struct
{
	DWORD dwUnknown1;
	ULONG uKeMaximumIncrement;
	ULONG uPageSize;
	ULONG uMmNumberOfPhysicalPages;
	ULONG uMmLowestPhysicalPage;
	ULONG uMmHighestPhysicalPage;
	ULONG uAllocationGranularity;
	PVOID pLowestUserAddress;
	PVOID pMmHighestUserAddress;
	ULONG uKeActiveProcessors;
	BYTE bKeNumberProcessors;
	BYTE bUnknown2;
	WORD wUnknown3;
} SYSTEM_BASIC_INFORMATION;

typedef struct
{
	LARGE_INTEGER liIdleTime; //系统空闲时间
	DWORD dwSpare[76];
} SYSTEM_PERFORMANCE_INFORMATION;

typedef struct
{
	LARGE_INTEGER liKeBootTime;
	LARGE_INTEGER liKeSystemTime;
	LARGE_INTEGER liExpTimeZoneBias;
	ULONG uCurrentTimeZoneId;
	DWORD dwReserved;
} SYSTEM_TIME_INFORMATION;

typedef LONG(WINAPI *PROCNTQSI)(UINT, PVOID, ULONG, PULONG);

PROCNTQSI NtQuerySystemInformation;
#define WM_MY_REPAINT (WM_USER +100)
double dbIdleTime = 0;
CWnd* pWnd = NULL;
int a_dbIdleTime[210];
double memSize = 0;
int a_memSize[210];
int memTotal = 0;
int memAvail = 0;
int g_num = 0;
// myCapab dialog


UINT getCpuInfo(double &dbIdleTime, LARGE_INTEGER &liOldIdleTime, LARGE_INTEGER &liOldSystemTime)
{
	SYSTEM_PERFORMANCE_INFORMATION SysPerfInfo;
	SYSTEM_TIME_INFORMATION SysTimeInfo;
	SYSTEM_BASIC_INFORMATION SysBaseInfo;
	double dbSystemTime;
	LONG status;

	NtQuerySystemInformation = (PROCNTQSI)GetProcAddress(GetModuleHandle(L"ntdll"), "NtQuerySystemInformation");

	if (!NtQuerySystemInformation)
		return 1;

	// get number of processors in the system 
	status = NtQuerySystemInformation(SystemBasicInformation, &SysBaseInfo, sizeof(SysBaseInfo), NULL);
	if (status != NO_ERROR)
		return 2;
	// get new system time 
	status = NtQuerySystemInformation(SystemTimeInformation, &SysTimeInfo, sizeof(SysTimeInfo), 0);
	if (status !=NO_ERROR)
		return 3;

	// get new CPU's idle time 
	status = NtQuerySystemInformation(SystemPerformanceInformation, &SysPerfInfo, sizeof(SysPerfInfo), NULL);
	if (status !=NO_ERROR)
		return 4;

	// if it's a first call - skip it 
	if (liOldIdleTime.QuadPart != 0)
	{
		// CurrentValue = NewValue - OldValue 
		dbIdleTime = Li2Double(SysPerfInfo.liIdleTime) - Li2Double(liOldIdleTime); //空闲时间
		dbSystemTime = Li2Double(SysTimeInfo.liKeSystemTime) - Li2Double(liOldSystemTime); //总时间

		// CurrentCpuIdle = IdleTime / SystemTime 
		dbIdleTime = dbIdleTime / dbSystemTime;

		// CurrentCpuUsage% = 100 - (CurrentCpuIdle * 100) / NumberOfProcessors 
		dbIdleTime = 100.0 - dbIdleTime * 100.0 /
			(double)SysBaseInfo.bKeNumberProcessors + 0.5;

	}

	// store new CPU's idle and system time 
	liOldIdleTime = SysPerfInfo.liIdleTime;
	liOldSystemTime = SysTimeInfo.liKeSystemTime;

	// 等待一秒
	return 0;
}

UINT MyThreadFunction(LPVOID)
{

	LARGE_INTEGER liOldIdleTime = { 0, 0 };
	LARGE_INTEGER liOldSystemTime = { 0, 0 };
	MEMORYSTATUS memory;
	while (1)
	{
		EnterCriticalSection(&g_cs);
		getCpuInfo(dbIdleTime, liOldIdleTime, liOldSystemTime);
#if 1
		//MEMORYSTATUSEX statex;
		memory.dwLength = sizeof(MEMORYSTATUS);
		::GlobalMemoryStatus(&memory);
		memSize = memory.dwMemoryLoad;
		memAvail = memory.dwAvailPhys;
		memTotal = memory.dwTotalPhys;
		a_memSize[g_num] = memSize;
		a_dbIdleTime[g_num] = dbIdleTime;
		pWnd->SendMessage(WM_MY_REPAINT);

		if (g_num < 210)
		{
			g_num++;

		}
		else
		{
			for (int i = 0; i < 210; i++)
			{
				//a_memSize[i] = a_memSize[i + 1];
			}
			g_num--;
		}
		LeaveCriticalSection(&g_cs);

#endif

		Sleep(1000);
	}

	return 0;
}

IMPLEMENT_DYNAMIC(PageFour, CDialogEx)

PageFour::PageFour(CWnd* pParent /*=NULL*/)
	: CDialogEx(PageFour::IDD, pParent)

	, m_SsFree(_T(""))
{

}

PageFour::~PageFour()
{
}

void PageFour::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_AddressMem, M_AddMem);
	DDX_Control(pDX, IDC_KeYongMem, S_AddFreeMem);
	DDX_Text(pDX, IDC_FreeTotal, m_SsFree);
	DDX_Control(pDX, IDC_FreeTotal, FuckDog);
}


BEGIN_MESSAGE_MAP(PageFour, CDialogEx)
	ON_MESSAGE(WM_MY_REPAINT, OnRePaint)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_ZYJSQ, &PageFour::OnBnClickedZyjsq)
	ON_BN_CLICKED(IDC_WULINEICUN, &PageFour::OnBnClickedWulineicun)
	ON_STN_CLICKED(IDC_AddressMem, &PageFour::OnStnClickedAddressmem)
	ON_STN_CLICKED(IDC_FreeAddress, &PageFour::OnStnClickedFreeaddress)
	ON_STN_CLICKED(IDC_WuliMem, &PageFour::OnStnClickedWulimem)
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CleanMemry, &PageFour::OnBnClickedCleanmemry)
END_MESSAGE_MAP()



// PageFour 消息处理程序

BOOL PageFour::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	

	// TODO:  在此添加额外的初始化
	InitializeCriticalSection(&g_cs);

	pWnd = CWnd::FromHandle(m_hWnd);
	AfxBeginThread(MyThreadFunction, NULL, 0);




	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void PageFour::RefreshControl(UINT uCtlID)
{
	CRect    rc;
	GetDlgItem(uCtlID)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	InvalidateRect(rc);
}

LRESULT PageFour::OnRePaint(WPARAM wParam, LPARAM lParam)
{

	MEMORYSTATUSEX memStatusEx;
	memStatusEx.dwLength = sizeof(memStatusEx);
	GlobalMemoryStatusEx(&memStatusEx);

	TCHAR StrMem[128];
	swprintf_s(StrMem, 128, L"物理内存:         %I64d MB", memStatusEx.ullTotalPhys / MB_DIV);
	GetDlgItem(IDC_AddressMem)->SetWindowText(StrMem);
	RefreshControl(IDC_AddressMem);
	
	TCHAR StrMemAvi[128];
	swprintf_s(StrMemAvi, 128, L"可用物理内存: %d MB", memStatusEx.ullAvailPhys / KB_DIV/1024);
	GetDlgItem(IDC_KeYongMem)->SetWindowText(StrMemAvi);
	RefreshControl(IDC_KeYongMem);

	TCHAR StrMeVir[128];
	swprintf_s(StrMeVir, 128, L"虚拟内存:         %I64d MB", memStatusEx.ullTotalVirtual / MB_DIV);
	GetDlgItem(IDC_VirAddTol)->SetWindowText(StrMeVir);
	RefreshControl(IDC_VirAddTol);

	cpuUseRate.Initialize();
	SetTimer(1, 1000, NULL);

	TCHAR StrMeVirFree[128];
	swprintf_s(StrMeVirFree, 128, L"可用虚拟内存: %I64d MB", memStatusEx.ullTotalVirtual / MB_DIV);
	GetDlgItem(IDC_FreeAddress)->SetWindowText(StrMeVirFree);
	RefreshControl(IDC_FreeAddress);

	
	TCHAR SysMem[128];
	swprintf_s(SysMem, 128, L"当前内存使用率:         %d%%\n", memStatusEx.dwMemoryLoad);
	GetDlgItem(IDC_SysMem)->SetWindowText(SysMem);
	RefreshControl(IDC_SysMem);

	TCHAR SysFileTol[128];
	swprintf_s(SysFileTol, 128, L"系统文件总量:     %I64d MB\n", memStatusEx.ullTotalPageFile / MB_DIV);
	GetDlgItem(IDC_SysTol)->SetWindowText(SysFileTol);
	RefreshControl(IDC_SysTol);

	TCHAR SysFileFree[128];
	swprintf_s(SysFileFree, 128, L"当前空闲文件:     %I64d   MB\n", memStatusEx.ullAvailPageFile / MB_DIV);
	GetDlgItem(IDC_SysMemFree)->SetWindowTextW(SysFileFree);
	RefreshControl(IDC_SysMemFree);
	

	return 0;
	
}

void PageFour::OnPaint()
{
	
	/*******************************************************************************************************
	/**************************************** HDC 设备创建 ************************************************
	*******************************************************************************************************/
	
	
	
	
	
	
	
	
	
	//------------------------------------------------------------CPUHDC----------------------------------------
	CPaintDC dc(this); // device context for painting
	CRect rect;
	GetClientRect(&rect);
	CDC dcMem;
	CBitmap bmp;
	dcMem.CreateCompatibleDC(&dc);
	bmp.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	dcMem.SelectObject(&bmp);
	//创建环境画刷  初始化指定画刷的颜色为黑色
	CBrush brush;									
	brush.CreateSolidBrush(RGB(0, 0, 0));
	//创建五种颜色的画笔 
	CPen pen, pen1, pen2, pen3, pen5;						//画笔
	pen1.CreatePen(PS_SOLID, 1, RGB(0, 120, 0)); /*Red*/
	pen2.CreatePen(PS_SOLID, 1, RGB(250, 0, 0));/*Red*/
	pen3.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));/*Black*/
	pen5.CreatePen(PS_SOLID, 1, RGB(0, 250, 0));
	//创建DrawText的显示方式画笔   引用字体结构对象
	HFONT   hf;											//字体
	LOGFONT logFont;
	logFont.lfHeight = 15;
	logFont.lfWidth = 0;
	logFont.lfEscapement = 0;
	logFont.lfOrientation = 0;
	logFont.lfWeight = FW_NORMAL;
	logFont.lfItalic = 0;
	logFont.lfUnderline = 0;
	logFont.lfStrikeOut = 0;
	logFont.lfCharSet = ANSI_CHARSET;
	logFont.lfOutPrecision = OUT_DEFAULT_PRECIS;
	logFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	logFont.lfQuality = PROOF_QUALITY;
	logFont.lfPitchAndFamily = VARIABLE_PITCH | FF_ROMAN;
	//strcpy_s((char*)logFont.lfFaceName, "Times New Roman");
	hf = CreateFontIndirect(&logFont);

	dcMem.FillSolidRect(rect, RGB(236, 233, 216)); //填充指定矩形
	dcMem.SetBkMode(TRANSPARENT);
	dcMem.SelectObject(brush);

	/*******************************************************************************************************
	/******************************************  CPU相关 ***************************************************
	*******************************************************************************************************/
	dcMem.Rectangle(CRect(21, 10, 96, 100));
	for (int i = 38; i <= 78; i++)            //控制宽度打印
	{
		for (int j = 10; j < 80; j++)        //控制长度打印
		{
			if ((j - 8) % 3 != 0)
			{
				if ((j - 6) % 3 == 0)
				{
					if (i % 2 == 0)
					{
						//if( i != 70)
						dcMem.SetPixel(CPoint(i, j), RGB(0, 150, 0));
					}
				}
				else
				{
					if ((i) % 2 != 0)
					{
						//if( i != 71 )
						dcMem.SetPixel(CPoint(i, j), RGB(0, 150, 0));
					}
				}
			}
		}
	}
/*************************************************************************************/

	dcMem.SelectObject(&pen5);
	for (int i = 0; i < (int)dbIdleTime + 2; i++)
	{
		if ((80 - i - 8) % 3 != 0)
		{
			dcMem.MoveTo(38, 80 - i);
			dcMem.LineTo(79, 80 - i);
		}

	}
	dcMem.SelectObject(&pen3);
	dcMem.MoveTo(58, 10);
	dcMem.LineTo(58, 134);/******************************/
	dcMem.SelectObject(hf);
	dcMem.SetBkMode(TRANSPARENT);
	dcMem.SetTextColor(RGB(0, 255, 0));
	//****************************************************CPU进度文本显示
	CString str;
	str.Format(L"%d", (int)dbIdleTime);
	str += "%";
	dcMem.DrawText(str, CRect(45, 80, 75, 100), 1);   
	/*************************************背景黑色矩形*/

	dcMem.Rectangle(CRect(120, 10, 330, 100));
	dcMem.SelectObject(pen1);

	/*↓↓↓↓↓↓↓↓↓↓========设置黑色矩形背景绿色线条======== ↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓*/
	for (int i = 10; i <= 100; i += 12)
	{
		dcMem.MoveTo(120, i);
		dcMem.LineTo(330, i);
	}
	for (int i = 120; i <= 330; i += 12)
	{
		dcMem.MoveTo(i, 10);
		dcMem.LineTo(i, 100);
	}
	/*↑↑↑↑↑↑↑↑↑↑========设置黑色矩形背景绿色线条======== ↑↑↑↑↑↑↑↑↑↑↑↑*/
	
	
	dcMem.SelectObject(pen5);     //放置画刷
	dcMem.MoveTo(328, 50);          //设置cpu曲线的DrawText的其起始坐标
	for (int j = 0; j < g_num; j++)
	{
		dcMem.LineTo(328 - j, 50 - a_dbIdleTime[j]);
	}

	/*******************************************************************************************************
	/******************************************  内存相关***************************************************
	*******************************************************************************************************/
	
	dcMem.Rectangle(CRect(21, 120, 98, 210));
	for (int i = 38; i <= 78; i++)
	{
		for (int j = 127; j < 195; j++)
		{
			if ((j - 8) % 3 != 0)
			{
				if ((j - 6) % 3 == 0)
				{
					if (i % 2 == 0)
					{
						//if( i != 70)
						dcMem.SetPixel(CPoint(i, j), RGB(0, 150, 0));
					}
				}
				else
				{
					if ((i) % 2 != 0)
					{
						//if( i != 71 )
						dcMem.SetPixel(CPoint(i, j), RGB(0, 150, 0));
					}
				}
			}
		}
	}
	dcMem.SelectObject(&pen5);
	for (int i = 0; i < (int)memSize + 2; i++)
	{
		if (i % 3 != 0)
		{
			dcMem.MoveTo(38, 195 - i);
			dcMem.LineTo(79, 195 - i);
		}

	}
	dcMem.SelectObject(&pen3);
	dcMem.MoveTo(58, 150);
	dcMem.LineTo(58, 200);
	dcMem.SelectObject(hf);
	dcMem.SetBkMode(TRANSPARENT);
	dcMem.SetTextColor(RGB(0, 255, 0));
	str.Format(L"%d", (int)memSize);
	str += "%";
	dcMem.DrawText(str, CRect(45, 195, 75, 210), 1);

     /***************设置内存的图形化曲线矩形背景*/

	dcMem.Rectangle(CRect(122, 120, 330, 210));       
	dcMem.SelectObject(pen1);

	/*↓↓↓↓↓↓↓↓↓↓========设置黑色矩形背景绿色线条======== ↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓*/
	
	for (int i = 120; i <= 210; i += 12)
	{
		dcMem.MoveTo(122, i);
		dcMem.LineTo(330, i);
	}
	for (int i = 122; i <= 330; i += 12)
	{
		dcMem.MoveTo(i, 120);
		dcMem.LineTo(i, 210);
	}

	/*↑↑↑↑↑↑↑↑↑↑========设置黑色矩形背景绿色线条======== ↑↑↑↑↑↑↑↑↑↑↑↑*/
	dcMem.SelectObject(pen5);      //设置画笔
	dcMem.MoveTo(328, 200);		//设置内存的DrawText的起始位置
	for (int j = 0; j < g_num; j++)
	{
		dcMem.LineTo(328 - j, 200 - a_memSize[j]);
	}
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0, SRCCOPY);
	bmp.DeleteObject();
	dcMem.DeleteDC();
	
}


void PageFour::OnBnClickedZyjsq()
{
	ShellExecute(NULL, L"open", L"C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs\\Accessories\\System Tools\\Resource Monitor.lnk", NULL, NULL, SW_SHOWNORMAL);

	// TODO:  在此添加控件通知处理程序代码
}


void PageFour::OnBnClickedWulineicun()
{
	// TODO:  在此添加控件通知处理程序代码
}


void PageFour::OnStnClickedAddressmem()
{
	// TODO:  在此添加控件通知处理程序代码
}


void PageFour::OnStnClickedFreeaddress()
{
	// TODO:  在此添加控件通知处理程序代码
}


void PageFour::OnStnClickedWulimem()
{
	// TODO:  在此添加控件通知处理程序代码
}


HBRUSH PageFour::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	if (nCtlColor == CTLCOLOR_STATIC)

	{
		pDC->SetTextColor(RGB(0, 0, 0)); //字体颜色
		pDC->SetBkMode(TRANSPARENT);// 背景透明
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
	}
	
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void PageFour::OnTimer(UINT_PTR nIDEvent)
{
	TCHAR StrCpu[128];
	swprintf_s(StrCpu, 128, L"CPU使用率:                %4d%%", cpuUseRate.GetCPUUseRate());
	GetDlgItem(IDC_CpuUs)->SetWindowText(StrCpu);
	RefreshControl(IDC_CpuUs);

	CDialogEx::OnTimer(nIDEvent);
}


void PageFour::OnBnClickedCleanmemry()
{
			TCHAR sSs[128];
			swprintf_s(sSs, 128, L"正在清理内存,请稍等·········");
			GetDlgItem(IDC_FreeTotal)->SetWindowText(sSs);
		
			UpdateData(FALSE);
			//获取清理前的内存信息
			MEMORYSTATUSEX memStatus = { sizeof(MEMORYSTATUSEX) };
			GlobalMemoryStatusEx(&memStatus);
			DOUBLE preUsedMem = (DOUBLE)(memStatus.ullTotalPhys - memStatus.ullAvailPhys) / 1024 / 1024;
			//开始清理内存
			ClearMemory();
			//获取清理后的内存信息
			GlobalMemoryStatusEx(&memStatus);
			DOUBLE afterUsedMem = (DOUBLE)(memStatus.ullTotalPhys - memStatus.ullAvailPhys) / 1024 / 1024;
			//输出清理信息
			
			RefreshControl(IDC_FreeTotal);
			UpdateData(FALSE);
			m_SsFree.Format(_T("内存清理完毕！本次清理 : %.2f MB"), preUsedMem - afterUsedMem);
			//Sleep(10000);
			//GetDlgItem(IDC_FreeTotal)->ShowWindow(SW_HIDE);
				/*
			TCHAR aAa[128];
			swprintf_s(aAa, 128, L"");
			GetDlgItem(IDC_FreeTotal)->SetWindowText(aAa);
			UpdateData(FALSE);
			*/
}

void PageFour::ClearMemory()
{
			HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
			if (hProcessSnap == INVALID_HANDLE_VALUE)
			{
				return;
			}

			PROCESSENTRY32 ProcessInfo;
			ProcessInfo.dwSize = sizeof(ProcessInfo);
			int count = 0;

			//获取系统中第一个进程的信息  
			BOOL Status = Process32First(hProcessSnap, &ProcessInfo);
			while (Status)
			{
				HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, TRUE,
					ProcessInfo.th32ProcessID);
				if (hProcess)
				{
					//设置进程工作区大小
					SetProcessWorkingSetSize(hProcess, -1, -1);
					
					EmptyWorkingSet(hProcess);
					CloseHandle(hProcess);
				}
				//获取下一个进程的信息  
				Status = Process32Next(hProcessSnap, &ProcessInfo);
			}
}
