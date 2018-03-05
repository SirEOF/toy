
// SharkGuardDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SharkGuard.h"
#include "SharkGuardDlg.h"
#include "afxdialogex.h"
#include "stdio.h"
#include "afxwin.h"
#include <stdlib.h>
#include <strsafe.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSharkGuardDlg 对话框


#define WM_HIDE  WM_USER +1
CSharkGuardDlg::CSharkGuardDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSharkGuardDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CSharkGuardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
//	DDX_Control(pDX, IDC_HackAv, bOne);
	DDX_Control(pDX, IDC_HackAv, bOne);
	DDX_Control(pDX, IDC_LJClean, bTwo);
	DDX_Control(pDX, IDC_SoftMange, bThree);
	DDX_Control(pDX, IDC_VirsFuck, bFour);
	DDX_Control(pDX, IDC_SysServer, bFive);
	DDX_Control(pDX,IDC_NetMonitor,bSix);
	DDX_Control(pDX, IDC_SSDT, bSeven);
	DDX_Control(pDX, IDC_Exit, ei);
	DDX_Control(pDX, IDC_Min, mi);
	DDX_Control(pDX, IDC_Head, Top);
}

BEGIN_MESSAGE_MAP(CSharkGuardDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_NCHITTEST()
	ON_BN_CLICKED(IDC_HackAv, &CSharkGuardDlg::OnBnClickedHackav)
	ON_BN_CLICKED(IDC_Exit, &CSharkGuardDlg::OnBnClickedExit)
	ON_BN_CLICKED(IDC_Min, &CSharkGuardDlg::OnBnClickedMin)
	ON_BN_CLICKED(IDC_Head, &CSharkGuardDlg::OnBnClickedHead)
	ON_BN_CLICKED(IDC_LJClean, &CSharkGuardDlg::OnBnClickedLjclean)
	ON_BN_CLICKED(IDC_SoftMange, &CSharkGuardDlg::OnBnClickedSoftmange)
	ON_BN_CLICKED(IDC_VirsFuck, &CSharkGuardDlg::OnBnClickedVirsfuck)
	ON_BN_CLICKED(IDC_SysServer, &CSharkGuardDlg::OnBnClickedSysserver)
	ON_BN_CLICKED(IDC_NetMonitor, &CSharkGuardDlg::OnBnClickedNetmonitor)
	ON_BN_CLICKED(IDC_SSDT, &CSharkGuardDlg::OnBnClickedSsdt)
	ON_MESSAGE(WM_HIDE, &CSharkGuardDlg::Hide)
END_MESSAGE_MAP()


// CSharkGuardDlg 消息处理程序

BOOL CSharkGuardDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	//初始化

	CRect rt, rc;
	GetWindowRect(rt);
	//垃圾清理
	LjClear.Create(IDD_Dlg_LJClean, this);
	LjClear.MoveWindow(46, rc.top + 84, 832, 350);
	m_vecDlg.push_back(&LjClear);
	//软件管理
	SfMange.Create(IDD_Dlg_SoftMange, this);
	SfMange.MoveWindow(46, rc.top + 84, 832, 350);
	m_vecDlg.push_back(&SfMange);
	//系统服务
	Sys.Create(IDD_Dlg_SysServer, this);
	Sys.MoveWindow(46, rc.top + 84, 832, 350);
	m_vecDlg.push_back(&Sys);
	//网络监控
	Mitor.Create(IDD_Dlg_NetMonitor, this);
	Mitor.MoveWindow(46, rc.top + 84, 832, 350);
	m_vecDlg.push_back(&Mitor);
	//病毒查杀
	Av.Create(IDD_Dlg_HackAv, this);
	Av.MoveWindow(46, rc.top + 84, 832, 350);
	m_vecDlg.push_back(&Av);
	//主动防御
	defend.Create(IDD_SSDT, this);
	defend.MoveWindow(46, rc.top + 84, 832, 350);
	m_vecDlg.push_back(&defend);
	//爱德华~
	rock.Create(IDD_Rocket, GetDesktopWindow());
	rock.ShowWindow(SW_SHOW);
	rock.SetWindowPos(&wndTopMost, 1280, 690, 73, 78, 0);
	//Shell_NotifyIcon(NIM_DELETE, &Id);
	//rock.ShowWindow(SW_SHOW);
	//rock.MoveWindow(0, 0, 0, 0);
	//rock.ShowWindow(SW_HIDE);
	//ModifyStyle(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSharkGuardDlg::OnPaint()
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
		//**************************************
		// 给窗体添加背景
		//**************************************
		CPaintDC dc(this);

		CRect rc;
		GetClientRect(&rc);

		//设置主窗口背景色
		dc.FillSolidRect(rc, RGB(0, 151, 209));
		//首页图片
		CDC dcMem0;
		dcMem0.CreateCompatibleDC(&dc);
		CBitmap bmpBackground0;
		bmpBackground0.LoadBitmap(MainB);
		BITMAP bitmap0;
		bmpBackground0.GetBitmap(&bitmap0);
		CBitmap* pbmpPri0 = dcMem0.SelectObject(&bmpBackground0);
		dc.BitBlt(0, -10, 1000, 800, &dcMem0, 0, 0, SRCCOPY);
		CDialogEx::OnPaint();
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSharkGuardDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSharkGuardDlg::ShowWindowDlg(CDialogEx* phwnd)
{
	if (!phwnd)
	{
		return;
	}
	for (UINT i = 0; i < m_vecDlg.size(); i++)
	{
		if (phwnd == m_vecDlg[i])
		{
			m_vecDlg[i]->ShowWindow(SW_SHOW);
		}
		else
		{
			m_vecDlg[i]->ShowWindow(SW_HIDE);
		}
	}
}

LRESULT CSharkGuardDlg::OnNcHitTest(CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	return HTCAPTION;
	//return CDialogEx::OnNcHitTest(point);
}


void CSharkGuardDlg::OnBnClickedHackav()
{
	// TODO:  在此添加控件通知处理程序代码
	for (UINT i = 0; i < m_vecDlg.size(); i++)
	{
		m_vecDlg[i]->ShowWindow(SW_HIDE);
	}
	//MessageBox(L"ssssssssss");
}





void CSharkGuardDlg::OnBnClickedExit()
{
	SendMessage(WM_CLOSE, 0, 0);
}


void CSharkGuardDlg::OnBnClickedMin()
{
	m_nid.cbSize = sizeof(m_nid);											  // 结构的大小，必须在程序中给出
	m_nid.hWnd = m_hWnd;													 // 哪个窗口响应托盘消息
	m_nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;		    	//哪些参数有效
	m_nid.hIcon = m_hIcon;											     	 //显示在系统托盘上的Icon的句柄
	m_nid.uCallbackMessage = WM_HIDE;						 //使用该消息通知窗口
	StringCchCopy(m_nid.szTip, 128, L"暮光电脑管家 v1.0");

	Shell_NotifyIcon(NIM_ADD, &m_nid);    //添加托盘元素

	ShowWindow(SW_HIDE);
}


void CSharkGuardDlg::OnBnClickedHead()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CSharkGuardDlg::OnBnClickedLjclean()
{
	ShowWindowDlg(&LjClear);
}


void CSharkGuardDlg::OnBnClickedSoftmange()
{
	ShowWindowDlg(&SfMange);
}


void CSharkGuardDlg::OnBnClickedVirsfuck()
{
	ShowWindowDlg(&Av);
}


void CSharkGuardDlg::OnBnClickedSysserver()
{
	ShowWindowDlg(&Sys);
}


void CSharkGuardDlg::OnBnClickedNetmonitor()
{
	ShowWindowDlg(&Mitor);
}


void CSharkGuardDlg::OnBnClickedSsdt()
{
	ShowWindowDlg(&defend);
}

LRESULT CSharkGuardDlg::Hide(WPARAM wParam, LPARAM lParam)
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
		menuTray.LoadMenu(IDR_MENU5);
		CMenu * subMenu = menuTray.GetSubMenu(0);

		//TPM_RETURNCMD:    返回值为用户选择的菜单ID
		//TPM_RIGHTBUTTON:  能够使用右键来选择
		int id = subMenu->TrackPopupMenu(
			TPM_RETURNCMD | TPM_LEFTBUTTON | TPM_RIGHTBUTTON,
			point.x, point.y, this);
		CString caption;
		switch (id)
		{
		case ID_Show:	//主窗口显示
			Shell_NotifyIcon(NIM_DELETE, &m_nid);    //删除托盘元素
			ShowWindow(SW_SHOW);
			break;
		case ID_Exit://退出程序
			PostQuitMessage(0);
			break;
			
		case ID_Hide:   //隐藏程序
			Shell_NotifyIcon(NIM_DELETE, &m_nid);
			ShowWindow(SW_SHOW);
			MoveWindow(0, 0, 0, 0);
			ShowWindow(SW_HIDE);
			ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);
			break;
			
		case ID_About:
			// CString caption;
			MessageBox(L"HelloAgain！" + caption, L"CodeByIronMan", NULL);
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