// PageThree.cpp : 实现文件
//

#include "stdafx.h"
#include "AAA.h"
#include "PageThree.h"
#include "afxdialogex.h"


// PageThree 对话框

IMPLEMENT_DYNAMIC(PageThree, CDialogEx)

PageThree::PageThree(CWnd* pParent /*=NULL*/)
	: CDialogEx(PageThree::IDD, pParent)
{
	m_IsUpDateSer = FALSE;
	m_UpDataTimes = 5;
	isInitEnd = false;
}

PageThree::~PageThree()
{
}

void PageThree::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LT3, servicer_List);
	
}


BEGIN_MESSAGE_MAP(PageThree, CDialogEx)
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_NOTIFY(NM_RCLICK, IDC_LT3, &PageThree::OnRclickList)
	ON_COMMAND(ID_HAHA_32846, &PageThree::qidong)
	ON_COMMAND(ID_HAHA_32845, &PageThree::tingzhi)
	ON_COMMAND(ID_HAHA_32847, &PageThree::shuaxin)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LT3, &PageThree::OnLvnItemchangedList3)
	
	ON_COMMAND(ID_StopS, &PageThree::OnStops)
END_MESSAGE_MAP()



// ServicerDlg 对话框






void PageThree::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (!isInitEnd)
	{
		return;
	}
	CRect rc;
	GetClientRect(&rc);
	rc.DeflateRect(10, 0, 0, 0);
	servicer_List.MoveWindow(rc, FALSE);
	// TODO: 在此处添加消息处理程序代码
}

// ServicerDlg 消息处理程序

BOOL PageThree::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//服务信息List初始化
	servicer_List.SetExtendedStyle(servicer_List.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);//可选中风格
	CString str[] = { _T(""), _T("名称"), _T("描述"), _T("状态"), _T("启动类型"), _T("服务类型") };
	servicer_List.InsertColumn(0, str[0], LVCFMT_LEFT, 2000);
	servicer_List.InsertColumn(1, str[1], LVCFMT_LEFT, 100);
	servicer_List.InsertColumn(2, str[2], LVCFMT_LEFT, 100);
	servicer_List.InsertColumn(3, str[3], LVCFMT_LEFT, 50);
	servicer_List.InsertColumn(4, str[4], LVCFMT_LEFT, 50);
	servicer_List.InsertColumn(5, str[5], LVCFMT_LEFT, 100);
	servicer_List.DeleteColumn(0);//删除第0列 用以文字居中

	//获取服务信息
	GetServiceInfo();
	isInitEnd = true;
	//更新服务信息间隔
	SetTimer(UPDATE_SERVICE_INFO, 1000, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
//************************************************************
// 函数名称:	GetServiceInfo
// 函数说明:	
// 返 回	值:	void
//************************************************************
void PageThree::GetServiceInfo()
{
	//1.打开远程计算机服务控制管理器
	servicer_List.DeleteAllItems();
	m_vecSerInfo.clear();
	SC_HANDLE hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	//2.第一次调用，获取需要的内存大小
	DWORD dwServiceNum = 0;
	DWORD dwSize = 0;
	EnumServicesStatus(
		hSCM,
		SERVICE_WIN32,
		SERVICE_STATE_ALL,	//所有服务状态
		NULL,				//缓冲区
		0,					//缓冲区大小
		&dwSize,			//需要的大小
		&dwServiceNum,		//缓冲区中的服务个数
		NULL);
	//3.申请需要的内存，第二次调用
	LPENUM_SERVICE_STATUS lpEnumService =
		(LPENUM_SERVICE_STATUS)LocalAlloc(LPTR, dwSize);
	//4.第二次枚举
	EnumServicesStatus(
		hSCM,
		SERVICE_WIN32,
		SERVICE_STATE_ALL,	//所有服务状态
		lpEnumService,		//缓冲区
		dwSize,				//缓冲区大小
		&dwSize,			//需要的大小
		&dwServiceNum,		//缓冲区中的服务个数
		NULL);
	//5.遍历信息
	SC_HANDLE hService = nullptr;
	for (DWORD i = 0; i < dwServiceNum; i++)
	{
		//获取基础信息
		//1.服务名称
		//2.服务描述
		//3.服务状态(根据得到的值手动输出字符串)
		//“已停止” “正在运行" "正在暂停"...
		m_vecSerInfo.push_back(lpEnumService[i]);

		//获取更多信息
		//1.打开服务
		hService = OpenService(hSCM,
			lpEnumService[i].lpServiceName, SERVICE_QUERY_CONFIG);
		// 2.第一次调用获取需要的缓冲区大小
		QueryServiceConfig(hService, NULL, 0, &dwSize);
		//分配内存
		LPQUERY_SERVICE_CONFIG pServiceConfig =
			(LPQUERY_SERVICE_CONFIG)LocalAlloc(LPTR, dwSize);
		//3.第二次调用,获取信息
		QueryServiceConfig(hService, pServiceConfig, dwSize, &dwSize);
		//获取服务信息完毕，开始插入List
		servicer_List.AddItem(i, 5,
			m_vecSerInfo[i].lpServiceName,
			m_vecSerInfo[i].lpDisplayName,
			m_vecSerInfo[i].ServiceStatus.dwCurrentState,
			pServiceConfig->dwStartType,
			m_vecSerInfo[i].ServiceStatus.dwServiceType);

		LocalFree(pServiceConfig);
	}
	LocalFree(lpEnumService);
	CloseServiceHandle(hSCM);
	CloseServiceHandle(hService);
}
//************************************************************
// 函数名称:	UpDataSerInfo
// 函数说明:	更新服务信息
// 返 回	值:	void
//************************************************************
void PageThree::UpDataSerInfo()
{
	//1.打开远程计算机服务控制管理器
	SC_HANDLE hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	//2.第一次调用，获取需要的内存大小
	DWORD dwServiceNum = 0;
	DWORD dwSize = 0;
	EnumServicesStatus(
		hSCM,
		SERVICE_WIN32,
		SERVICE_STATE_ALL,	//所有服务状态
		NULL,				//缓冲区
		0,					//缓冲区大小
		&dwSize,			//需要的大小
		&dwServiceNum,		//缓冲区中的服务个数
		NULL);
	//3.申请需要的内存，第二次调用
	LPENUM_SERVICE_STATUS lpEnumService =
		(LPENUM_SERVICE_STATUS)LocalAlloc(LPTR, dwSize);
	//4.第二次枚举
	EnumServicesStatus(
		hSCM,
		SERVICE_WIN32,
		SERVICE_STATE_ALL,	//所有服务状态
		lpEnumService,		//缓冲区
		dwSize,				//缓冲区大小
		&dwSize,			//需要的大小
		&dwServiceNum,		//缓冲区中的服务个数
		NULL);
	//5.遍历信息
	for (DWORD i = 0; i < dwServiceNum; i++)
	{
		//如果是要更新的服务
		if (!_tcscmp(lpEnumService[i].lpServiceName, m_ServiceName))
		{
			//更新list中该服务的状态信息
			switch (lpEnumService[i].ServiceStatus.dwCurrentState)
			{
			case SERVICE_STOPPED:
				servicer_List.SetItemText(m_SelectNum, 2, _T("已停止"));
				break;
			case SERVICE_STOP_PENDING:
				servicer_List.SetItemText(m_SelectNum, 2, _T("正在停止"));
				break;
			case SERVICE_START_PENDING:
				servicer_List.SetItemText(m_SelectNum, 2, _T("正在启动"));
				break;
			case SERVICE_RUNNING:
				servicer_List.SetItemText(m_SelectNum, 2, _T("正在运行"));
				break;
			case SERVICE_PAUSED:
				servicer_List.SetItemText(m_SelectNum, 2, _T("已暂停"));
				break;
			case SERVICE_PAUSE_PENDING:
				servicer_List.SetItemText(m_SelectNum, 2, _T("正在暂停"));
				break;
			case SERVICE_CONTINUE_PENDING:
				servicer_List.SetItemText(m_SelectNum, 2, _T("准备继续"));
				break;
			}
		}
	}
	LocalFree(lpEnumService);
	CloseServiceHandle(hSCM);
}

//************************************************************
// 函数名称:	OnTimer
// 函数说明:	更新服务频率
// 参	数:	UINT_PTR nIDEvent
// 返 回	值:	void
//************************************************************
void PageThree::OnTimer(UINT_PTR nIDEvent)
{
	if (UPDATE_SERVICE_INFO == nIDEvent&&m_UpDataTimes != 0 && m_IsUpDateSer)
	{
		UpDataSerInfo();
		if (m_UpDataTimes == 1)
		{
			m_IsUpDateSer = FALSE;
		}
		m_UpDataTimes--;
	}
	CDialogEx::OnTimer(nIDEvent);
}
//************************************************************
// 函数名称:	OnRclickList7
// 函数说明:	服务List右键响应函数
// 参	数:	NMHDR * pNMHDR
// 参	数:	LRESULT * pResult
// 返 回	值:	void
//************************************************************
void PageThree::OnRclickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	//防止在空白区点击弹出菜单  
	int n = pNMItemActivate->iItem;//选择了第几行
	if (n != -1)
	{
		//保存所选服务的 服务名
		m_ServiceName = servicer_List.GetItemText(n, 0);
		m_SelectNum = n;
		//下面的这段代码, 不单单适应于ListCtrl  
		CMenu menu, *pPopup;
		menu.LoadMenu(IDR_ServeR);
		pPopup = menu.GetSubMenu(0);
		CPoint myPoint;
		ClientToScreen(&myPoint);
		GetCursorPos(&myPoint);
		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);
	}
	*pResult = 0;
}

//************************************************************
// 函数名称:	qidong
// 函数说明:	启动服务
// 返 回	值:	void
//************************************************************
void PageThree::qidong()
{
	// TODO:  在此添加命令处理程序代码
	//启动服务
	SC_HANDLE hSCM = OpenSCManager(			//打开服务控制管理器
		NULL, NULL, SC_MANAGER_ALL_ACCESS);
	SC_HANDLE hService = OpenService(hSCM,	//打开服务
		m_ServiceName, SERVICE_START);
	StartService(hService, 0, 0);			//启动服务
	//更新信息
	UpDataSerInfo();
	m_IsUpDateSer = TRUE;
	m_UpDataTimes = 5;
	CloseServiceHandle(hSCM);
	CloseServiceHandle(hService);
}

//************************************************************
// 函数名称:	tingzhi
// 函数说明:	停止服务
// 返 回	值:	void
//************************************************************
void PageThree::tingzhi()
{
	// TODO:  在此添加命令处理程序代码
	//停止服务
	SC_HANDLE hSCM = OpenSCManager(			//打开服务控制管理器
		NULL, NULL, SC_MANAGER_ALL_ACCESS);
	SC_HANDLE hService = OpenService(hSCM,	//打开服务
		m_ServiceName, SERVICE_STOP);
	SERVICE_STATUS status;
	ControlService(hService,				//结束服务
		SERVICE_CONTROL_STOP,
		&status);
	//更新信息
	UpDataSerInfo();
	m_IsUpDateSer = TRUE;
	m_UpDataTimes = 5;
	CloseServiceHandle(hSCM);
	CloseServiceHandle(hService);
}

//************************************************************
// 函数名称:	shuaxin
// 函数说明:	刷新服务
// 返 回	值:	void
//************************************************************
void PageThree::shuaxin()
{
	// TODO:  在此添加命令处理程序代码
	GetServiceInfo();
}


void PageThree::OnLvnItemchangedList3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
}


//启动服务
void PageThree::OnStops()
{
	//qidong();
	// TODO:  在此添加命令处理程序代码
}
