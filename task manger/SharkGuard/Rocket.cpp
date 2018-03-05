// Rocket.cpp : 实现文件
//

#include "stdafx.h"
#include "SharkGuard.h"
#include "Rocket.h"
#include "afxdialogex.h"
#include <tlhelp32.h>
#include <Psapi.h>


// Rocket 对话框

IMPLEMENT_DYNAMIC(Rocket, CDialogEx)

Rocket::Rocket(CWnd* pParent /*=NULL*/)
	: CDialogEx(Rocket::IDD, pParent)
{

}

Rocket::~Rocket()
{
}

void Rocket::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Rocket, CDialogEx)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// Rocket 消息处理程序

void Rocket::SetStyle()
{
	/*设置窗口风格*/
	SetWindowLong(m_hWnd, GWL_EXSTYLE, GetWindowLong(m_hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	/*设置窗口透明颜色*/
	SetLayeredWindowAttributes(RGB(255, 255, 255), 0, LWA_COLORKEY);
	/*加载bmp图片*/
	bmp.LoadBitmap(IDB_BITMAP40);										//正常时候的图片样子
	/*根据图片大小设置宽高*/
	BITMAP  bmpInfo;
	bmp.GetBitmap(&bmpInfo);

	MoveWindow(1200, 600, bmpInfo.bmWidth, bmpInfo.bmHeight);

}


void Rocket::Draw(CDC *dc)
{
	//打印图片到界面上,需要paint消息不停再画
	CDC  hMen;
	hMen.CreateCompatibleDC(dc);

	hMen.SelectObject(bmp);
	CRect rt;
	GetClientRect(rt);
	/*使用等比拷贝*/
	BITMAP bmpInfo;
	bmp.GetBitmap(&bmpInfo);
	dc->BitBlt(0, 0, rt.Width(), rt.Height(), &hMen, 0, 0, SRCCOPY);
}

BOOL Rocket::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


int Rocket::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetStyle();
	return 0;
}


void Rocket::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	Draw(&dc);
}


void Rocket::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CRect rt;
	GetWindowRect(rt);
	CRect old;
	GetWindowRect(old);
	while (rt.bottom > 0)
	{
		MoveWindow(rt, TRUE);
		rt.bottom--;
		rt.top--;
		Sleep(0.5);
	}
	MoveWindow(old);
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
	UpdateData(FALSE);
	CString m_SsFree;
	m_SsFree.Format(_T("内存清理完毕！本次清理 : %.2f MB"), preUsedMem - afterUsedMem);
	MessageBox(L"Declear  BingGo!\n" + m_SsFree, L"BingGo!", NULL);
	CDialogEx::OnLButtonDblClk(nFlags, point);
}


void Rocket::OnLButtonDown(UINT nFlags, CPoint point)
{
	SendMessage(WM_SYSCOMMAND, SC_MOVE | HTCAPTION, 0);
	CDialogEx::OnLButtonDown(nFlags, point);
}

void Rocket::ClearMemory()
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
			//尽可能多的将指定进程的页面从工作区移除
			EmptyWorkingSet(hProcess);
			CloseHandle(hProcess);
		}
		//获取下一个进程的信息  
		Status = Process32Next(hProcessSnap, &ProcessInfo);
	}
}