
// x64toolDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "x64tool.h"
#include "x64toolDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_CONTROLPRINT WM_USER+1001
#define  PATH  L"C:\\x64.dll"
//#define PATH L"C:\\Users\\Administrator\\Desktop\\okokok\\x64\\Debug\\TestDll.dll"



Cx64toolDlg::Cx64toolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cx64toolDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cx64toolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Cx64toolDlg, CDialogEx)
	ON_MESSAGE(WM_CONTROLPRINT, OnControlPrint)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// Cx64toolDlg 消息处理程序

LRESULT Cx64toolDlg::OnControlPrint(WPARAM wParam, LPARAM lParam)
{
	int n;
	n = (int)lParam;
	GetProcessId(n);
	DestroyWindow();

	return 1;
}

void Cx64toolDlg::GetProcessId(int a)
{
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, a);
	LPVOID lpAddress = VirtualAllocEx(hProcess, NULL, 1024, MEM_COMMIT, PAGE_READWRITE);
	WriteProcessMemory(hProcess, lpAddress, (LPVOID)PATH, (wcslen(PATH) + 1) * 2, 0);
	HANDLE hThread = CreateRemoteThread(hProcess, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibraryW, lpAddress, NULL, NULL);
	if (hThread)
	{
		::MessageBox(0, L"注入成功", L"Bingo", 0);

		CloseHandle(hProcess);
		CloseHandle(hThread);

	}

}

BOOL Cx64toolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	MoveWindow(0, 0, 0, 0);
	ShowWindow(SW_HIDE);
	ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Cx64toolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Cx64toolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

