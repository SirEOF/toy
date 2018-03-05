// NetMonitor.cpp : 实现文件
//

#include "stdafx.h"
#include "SharkGuard.h"
#include "NetMonitor.h"
#include "afxdialogex.h"
#include <stdio.h>

NetMonitor *g_trform;
//更新速度
#define g_TIME_STEP_HIGH   200   //0.5秒
#define g_TIME_STEP_NORMAL 1500  //1.5秒
#define g_TIME_STEP_SLOW   5000  //5.0秒
#define g_TIME_STEP_SLEEP   24*60*60*1000  //1天

unsigned int  g_TIME_STEP = g_TIME_STEP_NORMAL; //更新速度 5秒默认

RECT g_Traffic_From_Rect;
RECT g_TFR_ALL;
RECT g_TFR_IN;
RECT g_TFR_OUT;

int g_Cur_Draw_State = 0;//当前绘图状态 0：原始 1:all 2:in 3:out

void TrafficchangeDrawState();



//IMPLEMENT_DYNAMIC(NetMonitor, CDialogEx)

NetMonitor::NetMonitor(CWnd* pParent /*=NULL*/)
	: CDialogEx(NetMonitor::IDD, pParent)
{
	SelectedInterface = 0;
}

/*
NetMonitor::~NetMonitor()
{
}
*/

void NetMonitor::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_OUT, m_btnOutgoing);
	DDX_Control(pDX, IDC_BUTTON_IN, m_btnIncoming);
	DDX_Control(pDX, IDC_BUTTON_ALL, m_btnTotalTraffic);
}


BEGIN_MESSAGE_MAP(NetMonitor, CDialogEx)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_RBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON_IN, &NetMonitor::OnBnClickedButtonIn)
	ON_STN_CLICKED(IDC_STATIC_IN, &NetMonitor::OnStnClickedStaticIn)
	ON_WM_CTLCOLOR()
	ON_STN_CLICKED(IDC_STATIC_OUT, &NetMonitor::OnStnClickedStaticOut)
END_MESSAGE_MAP()

void NetMonitor::RefreshControl(UINT uCtlID)
{
	CRect    rc;
	GetDlgItem(uCtlID)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	InvalidateRect(rc);
}

void NetMonitor::draw()
{
	double traffic;

	traffic = m_Traffic.GetTraffic(SelectedInterface);//单位数据量		
	mDaraAll.AddData(traffic, g_TIME_STEP);//存储的是网络速度
	traffic = m_TrafficIn.GetTraffic(SelectedInterface);//单位数据量		
	mDaraIn.AddData(traffic, g_TIME_STEP);//存储的是网络速度
	traffic = m_TrafficOut.GetTraffic(SelectedInterface);//单位数据量		
	mDaraOut.AddData(traffic, g_TIME_STEP);//存储的是网络速度


	double delta1;
	TCHAR str[128];

	DWORD  totaltraffic = m_Traffic.GetInterfaceTotalTraffic(SelectedInterface);
	delta1 = mDaraAll.GetTrafficTotal();
	swprintf_s(str, 128, L"当前网卡总流量:%.2fMB", totaltraffic / (1024 * 1024.0));
	//		SetDlgItemText(IDC_STATIC_CARD,str);//IDC_STATIC_OUT

	if (0 == g_Cur_Draw_State)
	{
		__int64 mTotalTime;
		delta1 = mDaraAll.GetTrafficTotal();
		mTotalTime = mDaraAll.GetTotalTime();
		swprintf_s(str, 128 ,L"网络总流量:%.2fMB   平均数据流量: %.2f KB/sec", delta1 / (1024 * 1024.0), (double)(delta1 * (1000.0 / (double)mTotalTime)) / 1024.0);
		SetDlgItemText(IDC_STATIC_ALL, str);//IDC_STATIC_OUT
		RefreshControl(IDC_STATIC_ALL);

		delta1 = mDaraIn.GetTrafficTotal();
		mTotalTime = mDaraIn.GetTotalTime();
		swprintf_s(str,128,L"网络输入总流量:%.2fMB   平均数据流量: %.2f KB/sec", delta1 / (1024 * 1024.0), (double)(delta1 * (1000.0 / (double)mTotalTime)) / 1024.0);
		SetDlgItemText(IDC_STATIC_IN, str);//IDC_STATIC_OUT
		RefreshControl(IDC_STATIC_IN);

		delta1 = mDaraOut.GetTrafficTotal();
		mTotalTime = mDaraOut.GetTotalTime();
		swprintf_s(str,128,L"网络输出总流量:%.2fMB   平均数据流量: %.2f KB/sec", delta1 / (1024 * 1024.0), (double)(delta1 * (1000.0 / (double)mTotalTime)) / 1024.0);
		SetDlgItemText(IDC_STATIC_OUT, str);//IDC_STATIC_OUT
		RefreshControl(IDC_STATIC_OUT);
	}
	/*
	else
	{
	SetDlgItemText(IDC_STATIC_ALL,"");//IDC_STATIC_OUT
	SetDlgItemText(IDC_STATIC_IN,"");//IDC_STATIC_OUT
	SetDlgItemText(IDC_STATIC_OUT,"");//IDC_STATIC_OUT
	}*/

	if ((0 == g_Cur_Draw_State) || (1 == g_Cur_Draw_State))
		m_btnTotalTraffic.gostep(&mDaraAll);
	if ((0 == g_Cur_Draw_State) || (2 == g_Cur_Draw_State))
		m_btnIncoming.gostep(&mDaraIn);
	if ((0 == g_Cur_Draw_State) || (3 == g_Cur_Draw_State))
		m_btnOutgoing.gostep(&mDaraOut);
}



BOOL NetMonitor::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_Traffic.SetTrafficType(Traffic_AllTraffic);
	m_TrafficIn.SetTrafficType(Traffic_IncomingTraffic);;
	m_TrafficOut.SetTrafficType(Traffic_OutGoingTraffic);;

	this->GetClientRect(&g_Traffic_From_Rect);
	this->m_btnTotalTraffic.GetWindowRect(&g_TFR_ALL);//GetClientRect
	this->m_btnOutgoing.GetWindowRect(&g_TFR_OUT);
	this->m_btnIncoming.GetWindowRect(&g_TFR_IN);

	g_Cur_Draw_State = 0;//setState
	this->m_btnTotalTraffic.setState(1);
	this->m_btnOutgoing.setState(3);
	this->m_btnIncoming.setState(2);

	g_trform = this;
	SetTimer(1, g_TIME_STEP, 0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void TrafficchangeDrawState()
{
	//int g_Cur_Draw_State;
	//当前绘图状态 0：原始 1:all 2:in 3:out
	if (0 == g_Cur_Draw_State)
	{
		g_trform->m_btnTotalTraffic.MoveWindow(g_TFR_ALL.left, g_TFR_ALL.top - 22, g_TFR_ALL.right - g_TFR_ALL.left, g_TFR_ALL.bottom - g_TFR_ALL.top, true);
		g_trform->m_btnOutgoing.MoveWindow(g_TFR_OUT.left, g_TFR_OUT.top - 22, g_TFR_OUT.right - g_TFR_OUT.left, g_TFR_OUT.bottom - g_TFR_OUT.top, true);
		g_trform->m_btnIncoming.MoveWindow(g_TFR_IN.left, g_TFR_IN.top - 22, g_TFR_IN.right - g_TFR_IN.left, g_TFR_IN.bottom - g_TFR_IN.top, true);

		g_trform->m_btnTotalTraffic.ShowWindow(true);
		g_trform->m_btnOutgoing.ShowWindow(true);
		g_trform->m_btnIncoming.ShowWindow(true);
		(CStatic*)(g_trform->GetDlgItem(IDC_STATIC_ALL))->ShowWindow(true);
		(CStatic*)(g_trform->GetDlgItem(IDC_STATIC_OUT))->ShowWindow(true);
		(CStatic*)(g_trform->GetDlgItem(IDC_STATIC_IN))->ShowWindow(true);

	}
	else
	{
		(CStatic*)(g_trform->GetDlgItem(IDC_STATIC_OUT))->ShowWindow(SW_HIDE);
		(CStatic*)(g_trform->GetDlgItem(IDC_STATIC_IN))->ShowWindow(SW_HIDE);
		(CStatic*)(g_trform->GetDlgItem(IDC_STATIC_ALL))->ShowWindow(SW_HIDE);

	}

	if (1 == g_Cur_Draw_State)
	{
		g_trform->m_btnTotalTraffic.ShowWindow(true);
		g_trform->m_btnTotalTraffic.MoveWindow(g_Traffic_From_Rect.left, g_Traffic_From_Rect.top, g_Traffic_From_Rect.right - g_Traffic_From_Rect.left, g_Traffic_From_Rect.bottom - g_Traffic_From_Rect.top, true);
		g_trform->m_btnIncoming.ShowWindow(false);
		g_trform->m_btnOutgoing.ShowWindow(false);
	}
	else if (2 == g_Cur_Draw_State)
	{
		g_trform->m_btnIncoming.ShowWindow(true);
		g_trform->m_btnIncoming.MoveWindow(g_Traffic_From_Rect.left, g_Traffic_From_Rect.top, g_Traffic_From_Rect.right - g_Traffic_From_Rect.left, g_Traffic_From_Rect.bottom - g_Traffic_From_Rect.top, true);
		g_trform->m_btnTotalTraffic.ShowWindow(false);
		g_trform->m_btnOutgoing.ShowWindow(false);
	}
	else if (3 == g_Cur_Draw_State)
	{
		g_trform->m_btnOutgoing.ShowWindow(true);
		g_trform->m_btnOutgoing.MoveWindow(g_Traffic_From_Rect.left, g_Traffic_From_Rect.top, g_Traffic_From_Rect.right - g_Traffic_From_Rect.left, g_Traffic_From_Rect.bottom - g_Traffic_From_Rect.top, true);
		g_trform->m_btnTotalTraffic.ShowWindow(false);
		g_trform->m_btnIncoming.ShowWindow(false);
	}
	g_trform->draw();
}

void NetMonitor::OnPaint()
{
		
		CPaintDC dc(this); // device context for painting
		CRect rc;
		GetClientRect(&rc);

		//设置主窗口背景色
		dc.FillSolidRect(rc, RGB(0, 151, 209));
		//首页图片
		CDC dcMem0;
		dcMem0.CreateCompatibleDC(&dc);
		CBitmap bmpBackground0;
		bmpBackground0.LoadBitmap(IDB_BITMAP45);
		BITMAP bitmap0;
		bmpBackground0.GetBitmap(&bitmap0);
		CBitmap* pbmpPri0 = dcMem0.SelectObject(&bmpBackground0);
		dc.BitBlt(0, -10, 1000, 800, &dcMem0, 0, 0, SRCCOPY);
		CDialogEx::OnPaint();
		CDialogEx::OnPaint();
	
}

void NetMonitor::OnTimer(UINT nIDEvent)
{
	draw();
}

void NetMonitor::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	HMENU hMenu, hPopup, hPopup2;
	long retId = 0;
	POINT pt;

	hMenu = CreatePopupMenu();
	if (hMenu)
	{
		//  If the menu was created, add the item text
		CString tmp;

		tmp.Format(L"重新记数");
		AppendMenu(hMenu, MF_STRING, 1001, tmp);

		hPopup = CreatePopupMenu();			  //  Create a new popup menu
		if (hPopup)
		{
			switch (g_TIME_STEP)
			{
			case g_TIME_STEP_HIGH:
				AppendMenu(hPopup, MF_STRING, 1002, L"*高");
				AppendMenu(hPopup, MF_STRING, 1003, L" 正常");
				AppendMenu(hPopup, MF_STRING, 1004, L" 低");
				AppendMenu(hPopup, MF_STRING, 1005, L" 暂停");
				break;
			case g_TIME_STEP_NORMAL:
				AppendMenu(hPopup, MF_STRING, 1002, L" 高");
				AppendMenu(hPopup, MF_STRING, 1003, L"*正常");
				AppendMenu(hPopup, MF_STRING, 1004, L" 低");
				AppendMenu(hPopup, MF_STRING, 1005, L" 暂停");
				break;
			case g_TIME_STEP_SLOW:
				AppendMenu(hPopup, MF_STRING, 1002, L" 高");
				AppendMenu(hPopup, MF_STRING, 1003, L" 正常");
				AppendMenu(hPopup, MF_STRING, 1004, L"*低");
				AppendMenu(hPopup, MF_STRING, 1005, L" 暂停");
				break;
			default:
				AppendMenu(hPopup, MF_STRING, 1002, L" 高");
				AppendMenu(hPopup, MF_STRING, 1003, L" 正常");
				AppendMenu(hPopup, MF_STRING, 1004, L" 低");
				AppendMenu(hPopup, MF_STRING, 1005, L"*暂停");
				break;
			}

			AppendMenu(hMenu, MF_POPUP, (UINT)hPopup, L"更新速度");
		}

		hPopup2 = CreatePopupMenu();			  //  Create a new popup menu
		if (hPopup2)
		{
			int CARDID = 1050;
			int cnt;
			for (cnt = 0; cnt <= m_Traffic.GetNetworkInterfacesCount(); cnt++, CARDID++)
			{
				CString tmp2;
				m_Traffic.GetNetworkInterfaceName(&tmp2, cnt);
				CString tmp1;
				tmp1.Format(L"MS TCP Loopback interface");
				if (0 != tmp2.Compare(tmp1))
				{
					if (cnt == SelectedInterface)
						tmp2.Insert(0, L"*");
					else
						tmp2.Insert(0,L" ");
					AppendMenu(hPopup2, MF_STRING, CARDID, tmp2);
				}
			}

			AppendMenu(hMenu, MF_POPUP, (UINT)hPopup2, L"网卡");
		}
	}


	GetCursorPos(&pt);
	//显示菜单
	retId = TrackPopupMenu(hMenu, TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_RETURNCMD, pt.x, pt.y, 0, this->m_hWnd, NULL);  //  start the menu
	DestroyMenu(hMenu);

	switch (retId)
	{
	case 1001:
		mDaraAll.Clear();
		mDaraIn.Clear();
		mDaraOut.Clear();
		break;
	case 1002:
		g_TIME_STEP = g_TIME_STEP_HIGH;
		SetTimer(1, g_TIME_STEP, 0);
		break;
	case 1003:
		g_TIME_STEP = g_TIME_STEP_NORMAL;
		SetTimer(1, g_TIME_STEP, 0);
		break;
	case 1004:
		g_TIME_STEP = g_TIME_STEP_SLOW;
		SetTimer(1, g_TIME_STEP, 0);
		break;
	case 1005:
		g_TIME_STEP = g_TIME_STEP_SLEEP;
		SetTimer(1, g_TIME_STEP, 0);
		break;
	default:
	{
			  if (retId >= 1050)
			  {
				  int mt = retId - 1050;
				  if (mt >= 0 && mt <= m_Traffic.GetNetworkInterfacesCount())
					  SelectedInterface = mt;
			  }
	}
		break;
	}

	CDialog::OnRButtonDown(nFlags, point);
}


void NetMonitor::OnBnClickedButtonIn()
{
	// TODO:  在此添加控件通知处理程序代码
}


void NetMonitor::OnStnClickedStaticIn()
{
	// TODO:  在此添加控件通知处理程序代码
}


HBRUSH NetMonitor::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	UINT id = pWnd->GetDlgCtrlID();
	if (id == IDC_STATIC_IN || id == IDC_STATIC_OUT || id == IDC_STATIC_ALL)
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255, 0, 0));  //蓝色
		CRect rc;
		pWnd->GetWindowRect(&rc);
		ScreenToClient(&rc);

		CDC* dc = GetDC();

		pDC->BitBlt(0, 0, rc.Width(), rc.Height(), dc, rc.left, rc.top, SRCCOPY);	//把父窗口背景图片先画到按钮上

		ReleaseDC(dc);

		hbr = (HBRUSH) ::GetStockObject(NULL_BRUSH);
	}
	return hbr;
}


void NetMonitor::OnStnClickedStaticOut()
{
	// TODO:  在此添加控件通知处理程序代码
}
