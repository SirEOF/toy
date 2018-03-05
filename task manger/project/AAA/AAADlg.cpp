
// AAADlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AAA.h"
#include "AAADlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "windows.h"
#include "shellapi.h"
#include "PageOne.h"
#include "stdio.h"
#include "afxwin.h"
#include <stdlib.h>
#include <strsafe.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_TUOPAN WM_USER +1
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()





CAAADlg::CAAADlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAAADlg::IDD, pParent)
	, m_IsWindowHide(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	m_IsWindowHide = false;
}

void CAAADlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB, m_tab);
	DDX_Control(pDX, IDC_SendMes, m_SendMes);
}

BEGIN_MESSAGE_MAP(CAAADlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_QUERYDRAGICON()
//	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, &CAAADlg::OnTcnSelchangeTab)
ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, &CAAADlg::OnTcnSelchangeTab)
//ON_BN_CLICKED(IDC_EndProcess, &CAAADlg::OnClickedEndprocess)
ON_BN_CLICKED(IDC_D2endProcess, &CAAADlg::OnClickedD2endprocess)
ON_BN_CLICKED(IDC_P3Server, &CAAADlg::OnBnClickedP3server)
ON_BN_CLICKED(IDC_EndProcess, &CAAADlg::OnClickedEndprocess)
ON_COMMAND(ID_32771, &CAAADlg::OnTopMenuStart)
ON_COMMAND(ID_32772, &CAAADlg::OnExitTaskManger)
ON_COMMAND(ID_32788, &CAAADlg::On32788)
ON_COMMAND(ID_32782, &CAAADlg::OnWideSpread)
ON_COMMAND(ID_32783, &CAAADlg::OnListSpread)
ON_COMMAND(ID_32784, &CAAADlg::OnSetMin)
ON_COMMAND(ID_32785, &CAAADlg::OnSetMax)
ON_COMMAND(ID_32786, &CAAADlg::OnCengD)
ON_COMMAND(ID_32787, &CAAADlg::OnForeSet)
ON_COMMAND(ID_32776, &CAAADlg::OnFreshRightOnce)
ON_BN_CLICKED(IDC_NewTask, &CAAADlg::OnBnClickedNewServer)
ON_BN_CLICKED(IDC_TurnTo, &CAAADlg::OnBnClickedTurnto)
ON_BN_CLICKED(IDC_LogOut, &CAAADlg::OnBnClickedLogout)
ON_BN_CLICKED(IDC_ZhuXiao, &CAAADlg::OnBnClickedZhuxiao)
ON_BN_CLICKED(IDC_SendMes, &CAAADlg::OnBnClickedSendmes)
ON_COMMAND(ID_SysRise, &CAAADlg::OnSysrise)
ON_COMMAND(ID_ViewWindow, &CAAADlg::OnViewwindow)
ON_WM_CLOSE()
ON_WM_HOTKEY()
ON_MESSAGE(WM_TUOPAN, &CAAADlg::OnTuoPan)
END_MESSAGE_MAP()



CCPUUseRate gCpuUseRate;


// CAAADlg 消息处理程序

BOOL CAAADlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	::RegisterHotKey(this->GetSafeHwnd(), 0xa001, MOD_WIN | MOD_ALT, 'Z');
	InitStaus();
	TabInsert();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CAAADlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	
	CTime t1;
	t1 = CTime::GetCurrentTime();
	m_Status.SetPaneText(2, t1.Format("当前时间: %H:%M:%S"));
	//SetTimer(1, 1000, NULL);


	WCHAR  Buffer[128];
	memset(Buffer,0,128*sizeof(WCHAR));
	swprintf_s(Buffer, 128, L"CPU使用率:%4d%%", gCpuUseRate.GetCPUUseRate());
	m_Status.SetPaneText(0, Buffer);


	MEMORYSTATUSEX memStatusEx;
	memStatusEx.dwLength = sizeof(memStatusEx);
	GlobalMemoryStatusEx(&memStatusEx);
	WCHAR Cuffer[128];
	swprintf_s(Cuffer, 128, L"物理内存:%d%%", memStatusEx.dwMemoryLoad);
	m_Status.SetPaneText(1,Cuffer);
	
	UpdateData(FALSE);
	CDialogEx::OnTimer(nIDEvent);
	
}


void CAAADlg::InitStaus()
{
	m_Status.Create(this);
	UINT nID[3] = { 2000, 2001, 2002 };
	m_Status.SetIndicators(nID, 3);
	CControlBarInfo c;

	m_Status.SetPaneInfo(0, 2000, SBPS_STRETCH, 100);
	m_Status.SetPaneInfo(1, 2001, SBPS_STRETCH, 100);
	m_Status.SetPaneInfo(2, 2002, SBPS_STRETCH, 100);
	
	RECT rect;
	GetClientRect(&rect);
	m_Status.MoveWindow(0, rect.bottom - 17, rect.right, 20, true);
	

	gCpuUseRate.Initialize();
	 SetTimer(1, 1000, NULL);


	
}

void CAAADlg::TabInsert()
{


	((CButton*)GetDlgItem(IDC_SendMes))->EnableWindow(FALSE);
	//InitMenu();
	m_tab.InsertItem(0, _T("应用程序"));
	m_tab.InsertItem(1, _T("进程"));
	m_tab.InsertItem(2, _T("服务"));
	m_tab.InsertItem(3, _T("性能"));
	m_tab.InsertItem(4, _T("PE解析"));
	m_tab.InsertItem(5, _T("用户"));

	m_L1.Create(MAKEINTRESOURCE(IDD_P1), &m_tab);
	m_L2.Create(MAKEINTRESOURCE(IDD_P2), &m_tab);
	m_L3.Create(MAKEINTRESOURCE(IDD_P3), &m_tab);
	m_L4.Create(MAKEINTRESOURCE(IDD_P4), &m_tab);
	m_L5.Create(MAKEINTRESOURCE(IDD_P5), &m_tab);
	m_L6.Create(MAKEINTRESOURCE(IDD_P6), &m_tab);
	//m_L3.Create(MAKEINTRESOURCE(IDD_P3), &m_tab);
	//m_L4.Create(MAKEINTRESOURCE(IDD_P4), &m_tab);
	//m_L5.Create(MAKEINTRESOURCE(IDD_P5), &m_tab);

	CRect r1, r4;
	m_tab.GetClientRect(r1);
	m_tab.GetClientRect(r4);
	r1.top += 30;
	r1.left += 8;
	r1.right -= 12;
	r1.bottom -= 42;
	m_L1.ShowWindow(SW_SHOW);
	r4.top += 23;
	r4.left += 2;
	r4.right -= 3;
	r4.bottom -= 3;

	m_L1.MoveWindow(r1);
	m_L2.MoveWindow(r1);
	m_L3.MoveWindow(r1);
	m_L4.MoveWindow(r4);
	m_L5.MoveWindow(r4);
	m_L6.MoveWindow(r1);
	///////////////////////////////////////////////////////////////////////////////

}

void CAAADlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAAADlg::OnPaint()
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
HCURSOR CAAADlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CAAADlg::OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	switch (m_tab.GetCurSel())
	{
	case 0:
		((CButton *)GetDlgItem(IDC_EndProcess))->ShowWindow(TRUE);
		((CButton *)GetDlgItem(IDC_TurnTo))->ShowWindow(TRUE);
		((CButton *)GetDlgItem(IDC_NewTask))->ShowWindow(TRUE);
		((CButton *)GetDlgItem(IDC_D2endProcess))->ShowWindow(false);
		((CButton *)GetDlgItem(IDC_P3Server))->ShowWindow(false);
		((CButton *)GetDlgItem(IDC_LogOut))->ShowWindow(false);
		((CButton *)GetDlgItem(IDC_ZhuXiao))->ShowWindow(false);
		((CButton *)GetDlgItem(IDC_SendMes))->ShowWindow(false);
		
		m_L1.ShowWindow(TRUE);
		m_L2.ShowWindow(FALSE);
		m_L3.ShowWindow(FALSE);
		m_L4.ShowWindow(SW_HIDE);
		m_L5.ShowWindow(SW_HIDE);
		m_L6.ShowWindow(SW_HIDE);
		//m_L4.ShowWindow(SW_HIDE);
		//m_L5.ShowWindow(SW_HIDE);
	
		
		break;
		
	case 1:
		((CButton *)GetDlgItem(IDC_EndProcess))->ShowWindow(false);
		((CButton *)GetDlgItem(IDC_TurnTo))->ShowWindow(false);
		((CButton *)GetDlgItem(IDC_NewTask))->ShowWindow(false);
		((CButton *)GetDlgItem(IDC_D2endProcess))->ShowWindow(TRUE);
		((CButton *)GetDlgItem(IDC_P3Server))->ShowWindow(false);
		((CButton *)GetDlgItem(IDC_LogOut))->ShowWindow(false);
		((CButton *)GetDlgItem(IDC_ZhuXiao))->ShowWindow(false);
		((CButton *)GetDlgItem(IDC_SendMes))->ShowWindow(false);
		
		
		m_L1.ShowWindow(FALSE);
		m_L2.ShowWindow(TRUE);
		m_L3.ShowWindow(FALSE);
		m_L4.ShowWindow(SW_HIDE);
		m_L5.ShowWindow(SW_HIDE);
		m_L6.ShowWindow(SW_HIDE);
		//m_L4.ShowWindow(SW_HIDE);
		//m_L5.ShowWindow(SW_HIDE);
		break;
		
	case 2:
	((CButton *)GetDlgItem(IDC_EndProcess))->ShowWindow(false);
	((CButton *)GetDlgItem(IDC_TurnTo))->ShowWindow(false);
	((CButton *)GetDlgItem(IDC_NewTask))->ShowWindow(false);
	((CButton *)GetDlgItem(IDC_D2endProcess))->ShowWindow(false);
	((CButton *)GetDlgItem(IDC_P3Server))->ShowWindow(TRUE);
	((CButton *)GetDlgItem(IDC_LogOut))->ShowWindow(false);
	((CButton *)GetDlgItem(IDC_ZhuXiao))->ShowWindow(false);
	((CButton *)GetDlgItem(IDC_SendMes))->ShowWindow(false);
	
	m_L1.ShowWindow(SW_HIDE);
		m_L2.ShowWindow(SW_HIDE);
		m_L3.ShowWindow(SW_SHOW);
		m_L4.ShowWindow(SW_HIDE);
		m_L5.ShowWindow(SW_HIDE);
		m_L6.ShowWindow(SW_HIDE);
		//m_L5.ShowWindow(SW_HIDE);
	break;
	
	case 3:
		((CButton *)GetDlgItem(IDC_EndProcess))->ShowWindow(false);
		((CButton *)GetDlgItem(IDC_TurnTo))->ShowWindow(false);
		((CButton *)GetDlgItem(IDC_NewTask))->ShowWindow(false);
		((CButton *)GetDlgItem(IDC_D2endProcess))->ShowWindow(false);
		((CButton *)GetDlgItem(IDC_P3Server))->ShowWindow(false);
		((CButton *)GetDlgItem(IDC_LogOut))->ShowWindow(false);
		((CButton *)GetDlgItem(IDC_ZhuXiao))->ShowWindow(false);
		((CButton *)GetDlgItem(IDC_SendMes))->ShowWindow(false);
		
		m_L1.ShowWindow(SW_HIDE);
		m_L2.ShowWindow(SW_HIDE);
		m_L3.ShowWindow(SW_HIDE);
		m_L4.ShowWindow(SW_SHOW);
		m_L5.ShowWindow(SW_HIDE);
		m_L6.ShowWindow(SW_HIDE);
		break;
		
	case 4:
		((CButton *)GetDlgItem(IDC_EndProcess))->ShowWindow(false);
		((CButton *)GetDlgItem(IDC_TurnTo))->ShowWindow(false);
		((CButton *)GetDlgItem(IDC_NewTask))->ShowWindow(false);
		((CButton *)GetDlgItem(IDC_D2endProcess))->ShowWindow(false);
		((CButton *)GetDlgItem(IDC_P3Server))->ShowWindow(false);
		((CButton *)GetDlgItem(IDC_LogOut))->ShowWindow(false);
		((CButton *)GetDlgItem(IDC_ZhuXiao))->ShowWindow(false);
		((CButton *)GetDlgItem(IDC_SendMes))->ShowWindow(false);
		
		m_L1.ShowWindow(SW_HIDE);
		m_L2.ShowWindow(SW_HIDE);
		m_L3.ShowWindow(SW_HIDE);
		m_L4.ShowWindow(SW_HIDE);
		m_L5.ShowWindow(SW_SHOW);
		m_L6.ShowWindow(SW_HIDE);
		break;
	case 5:
		((CButton *)GetDlgItem(IDC_EndProcess))->ShowWindow(false);
		((CButton *)GetDlgItem(IDC_TurnTo))->ShowWindow(false);
		((CButton *)GetDlgItem(IDC_NewTask))->ShowWindow(false);
		((CButton *)GetDlgItem(IDC_D2endProcess))->ShowWindow(false);
		((CButton *)GetDlgItem(IDC_P3Server))->ShowWindow(false);
		((CButton *)GetDlgItem(IDC_LogOut))->ShowWindow(TRUE);
		((CButton *)GetDlgItem(IDC_ZhuXiao))->ShowWindow(TRUE);
		((CButton *)GetDlgItem(IDC_SendMes))->ShowWindow(TRUE);
		
		m_L1.ShowWindow(SW_HIDE);
		m_L2.ShowWindow(SW_HIDE);
		m_L3.ShowWindow(SW_HIDE);
		m_L4.ShowWindow(SW_HIDE);
		m_L5.ShowWindow(SW_HIDE);
		m_L6.ShowWindow(SW_SHOW);

	}
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
}

//void CAAADlg::OnClickedEndprocess()
//{
//	
//	
//	MessageBox(L"sssssssss");
//	// TODO:  在此添加控件通知处理程序代码
//}

void CAAADlg::OnBnClickedP3server()
{
	
	ShellExecute(NULL,L"open",L"C:\\Windows\\system32\\services.msc",NULL,NULL,SW_SHOWNORMAL);
	//WinExec("Notepad.exe", SW_SHOW);
	// TODO:  在此添加控件通知处理程序代码
}


void CAAADlg::OnClickedD2endprocess()
{

	POSITION pos = m_L2.m_L2.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		CString str;
		int nItem = m_L2.m_L2.GetNextSelectedItem(pos);
		str = m_L2.m_L2.GetItemText(nItem, 1);
		char _char[100] = { 0 };
		WideCharToMultiByte(CP_ACP, NULL, str, -1, _char, 100, NULL, NULL);
		DWORD pid = (DWORD)atoi(_char);
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
		TerminateProcess(hProcess, 0);
		CloseHandle(hProcess);
		m_L2.Refreshlist();
	}
	//MessageBox(L"DL2");
	// TODO:  在此添加控件通知处理程序代码
}
/*
void AAADlg::initStatusBar()
{
	//创建状态栏
	m_StatusBar.Create(this);
	//设置分割窗格

	UINT array[3] = { 50001, 50002, IDS_INDICATOR_TIME };
	m_StatusBar.SetIndicators(array, 3);
	m_StatusBar.SetPaneInfo(0, 50001, NULL, 370);
	m_StatusBar.SetPaneInfo(1, 50001, NULL, 100);
	m_StatusBar.SetPaneInfo(2, IDS_INDICATOR_TIME, SBPS_STRETCH, 0);
	CTime t1;
	t1 = CTime::GetCurrentTime();
	m_StatusBar.SetPaneText(2, t1.Format("%H:%M:%S"));
	//设置窗格的文本
	m_StatusBar.SetPaneText(0, L"");
	m_StatusBar.SetPaneText(1, L" ");
	RepositionBars(
		AFX_IDW_CONTROLBAR_FIRST,
		AFX_IDW_CONTROLBAR_LAST,
		IDS_INDICATOR_TIME);
	SetTimer(1, 1000, NULL);
}

*/


void CAAADlg::OnClickedEndprocess()
{


	int i = m_L1.m_L1.GetSelectionMark();
	CString caption = m_L1.m_L1.GetItemText(i, 0);
	if (MessageBox(L"确定要关闭?" + caption, L"提示", MB_YESNO) == IDYES)
	{
		CWnd* pWnd = CWnd::FindWindowW(NULL, caption);
		if (pWnd != INVALID_HANDLE_VALUE)
		{
			pWnd->SendMessage(WM_CLOSE, 0);
			m_L2.Refreshlist();
		
		}
	}
	
	
}


void CAAADlg::OnTopMenuStart()
{

	ShellExecute(NULL, L"open", L"C:\\Users\\Administrator\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Accessories\\Run.lnk", NULL, NULL, SW_SHOWNORMAL);
	// TODO:  在此添加命令处理程序代码
}


void CAAADlg::OnExitTaskManger()
{
	AfxGetMainWnd()->SendMessage(WM_CLOSE);
	// TODO:  在此添加命令处理程序代码
}


void CAAADlg::On32788()
{
	CString caption;
	MessageBox(L"Made By IronMan\n\tQ~398104927" + caption, L"helloAgain", NULL);
	// TODO:  在此添加命令处理程序代码
}


void CAAADlg::OnWideSpread()
{
	TileWindows(NULL, MDITILE_HORIZONTAL, NULL, NULL, NULL);
	// TODO:  在此添加命令处理程序代码
}


void CAAADlg::OnListSpread()
{
	TileWindows(NULL, MDITILE_VERTICAL, NULL, NULL, NULL);
	// TODO:  在此添加命令处理程序代码
}


void CAAADlg::OnSetMin()
{
	::SendMessage(this->m_hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
	// TODO:  在此添加命令处理程序代码
}


void CAAADlg::OnSetMax()
{
	
	::SendMessage(this->m_hWnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
	// TODO:  在此添加命令处理程序代码
}


void CAAADlg::OnCengD()
{
	TileWindows(NULL, MDITILE_HORIZONTAL, NULL, NULL, NULL);
	// TODO:  在此添加命令处理程序代码
}


void CAAADlg::OnForeSet()
{
	CascadeWindows(NULL, NULL, NULL, NULL, NULL);
	// TODO:  在此添加命令处理程序代码
}


void CAAADlg::OnFreshRightOnce()
{
	
	// TODO:  在此添加命令处理程序代码
}


void CAAADlg::OnBnClickedNewServer()
{
	ShellExecute(NULL, L"open", L"C:\\Users\\Administrator\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Accessories\\Run.lnk", NULL, NULL, SW_SHOWNORMAL);
	// TODO:  在此添加控件通知处理程序代码
}


void CAAADlg::OnBnClickedTurnto()
{
	::SendMessage(this->m_hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
	// TODO:  在此添加控件通知处理程序代码
}


void CAAADlg::OnBnClickedLogout()
{
	LockWorkStation();
}


void CAAADlg::OnBnClickedZhuxiao()
{
	ExitWindowsEx(EWX_LOGOFF, EWX_FORCE);
	// TODO:  在此添加控件通知处理程序代码
}


void CAAADlg::OnBnClickedSendmes()
{
      
}





void CAAADlg::OnSysrise()
{
	// TODO:  在此添加命令处理程序代码
	::ShowWindow(m_hWnd, SW_HIDE);
	// 2. 获取当前程序路径
	WCHAR szApplication[MAX_PATH] = { 0 };
	DWORD cchLength = _countof(szApplication);
	QueryFullProcessImageName(GetCurrentProcess(), 0,
		szApplication, &cchLength);
	// 3. 以管理员权限重新打开进程
	SHELLEXECUTEINFO sei = { sizeof(SHELLEXECUTEINFO) };
	sei.lpVerb = L"runas";      // 请求提升权限
	sei.lpFile = szApplication; // 可执行文件路径
	sei.lpParameters = NULL;          // 不需要参数
	sei.nShow = SW_SHOWNORMAL; // 正常显示窗口
	if (ShellExecuteEx(&sei))
		exit(0);
	else
		::ShowWindow(m_hWnd, SW_SHOWNORMAL);

}


void CAAADlg::OnViewwindow()
{
	// TODO:  在此添加命令处理程序代码
	DlgView A;
	A.DoModal();

}


void CAAADlg::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (MessageBox(L"                 是否开启托盘？", L"托盘", MB_YESNO) == IDYES)
	{
		//设置结构体    
		m_nid.cbSize = sizeof(m_nid);											  // 结构的大小，必须在程序中给出
		m_nid.hWnd = m_hWnd;													 // 哪个窗口响应托盘消息
		m_nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;		    	//哪些参数有效
		m_nid.hIcon = m_hIcon;											     	 //显示在系统托盘上的Icon的句柄
		m_nid.uCallbackMessage = WM_TUOPAN;						 //使用该消息通知窗口
		StringCchCopy(m_nid.szTip, 128, L"寒江独钓");

		Shell_NotifyIcon(NIM_ADD, &m_nid);    //添加托盘元素

		ShowWindow(SW_HIDE);
	}
	else
	{
		PostQuitMessage(0);
	}
	//CDialogEx::OnClose();
}


LRESULT CAAADlg::OnTuoPan(WPARAM wParam, LPARAM lParam)
{
	UINT nMsg = (UINT)lParam;
	switch (nMsg)
	{
	case WM_LBUTTONDOWN:  //左键单击
		ShowWindow(SW_SHOW);
		break;
	case WM_RBUTTONDOWN: //右键单击
	{
						 //实现右键菜单
						 CPoint point;
						 GetCursorPos(&point);  //得到鼠标的坐标(基于窗口)
						 CMenu menuTray;
						 menuTray.LoadMenu(IDR_TuoPan);
						 CMenu * subMenu = menuTray.GetSubMenu(0);

						 //TPM_RETURNCMD:    返回值为用户选择的菜单ID
						 //TPM_RIGHTBUTTON:  能够使用右键来选择
						 int id = subMenu->TrackPopupMenu(
							 TPM_RETURNCMD | TPM_LEFTBUTTON | TPM_RIGHTBUTTON,
							 point.x, point.y, this);
						 CString caption;
						 switch (id)
						 {
						 case ID_LOWBEE_MainDlg:	//主窗口显示
							 Shell_NotifyIcon(NIM_DELETE, &m_nid);    //删除托盘元素
							 ShowWindow(SW_SHOW);
							 break;
						 case ID_LOWBEE_QuitPro://退出程序
							 PostQuitMessage(0);
							 break;
						 case ID_LOWBEE_HidePro:   //隐藏程序
							 Shell_NotifyIcon(NIM_DELETE, &m_nid);  
							 ShowWindow(SW_SHOW);
							 MoveWindow(0, 0, 0, 0);
							 ShowWindow(SW_HIDE);
							 ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);

							 break;
						 case ID_LOWBEE_About:
							// CString caption;
							 MessageBox(L"HelloAgain！"+caption,L"CodeByIronMan",NULL);
							 break;
						 default:
							 break;
						 }
	}  break;
	default:
		break;
	}

	return 0;
}

void CAAADlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (nHotKeyId == 0xa001)
	{
		//隐藏窗口
		if (m_IsWindowHide == true)
		{
			ShowWindow(SW_SHOW);
			m_IsWindowHide = false;
		}
		else
		{
			ShowWindow(SW_HIDE);
			m_IsWindowHide = true;
		}
	}
	CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);
}
