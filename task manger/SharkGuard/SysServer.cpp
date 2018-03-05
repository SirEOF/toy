// SysServer.cpp : 实现文件
//

#include "stdafx.h"
#include "SharkGuard.h"
#include "SysServer.h"
#include "afxdialogex.h"


// SysServer 对话框

IMPLEMENT_DYNAMIC(SysServer, CDialogEx)

SysServer::SysServer(CWnd* pParent /*=NULL*/)
	: CDialogEx(SysServer::IDD, pParent)
{
	m_IsUpDateSer = FALSE;
	m_UpDataTimes = 5;
	m_Select = -1;
}

SysServer::~SysServer()
{
}

void SysServer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_Sever, MyFourthList);
	DDX_Control(pDX, IDC_LIST_QD, StartUp);
}


BEGIN_MESSAGE_MAP(SysServer, CDialogEx)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_COMMAND(ID_SeverStart, &SysServer::OnSeverstart)
	ON_COMMAND(ID_SeverStop, &SysServer::OnSeverstop)
	ON_COMMAND(ID_SeverFresh, &SysServer::OnSeverfresh)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_Sever, &SysServer::OnNMRClickListSever)
	ON_COMMAND(ID_AddQd, &SysServer::OnAddqd)
	ON_COMMAND(ID_BanQd, &SysServer::OnBanqd)
	ON_COMMAND(ID_FreshQd, &SysServer::OnFreshqd)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_QD, &SysServer::OnNMRClickListQd)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_QD, &SysServer::OnLvnItemchangedListQd)
END_MESSAGE_MAP()


// SysServer 消息处理程序


BOOL SysServer::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	MyFourthList.SetBkColor(RGB(0, 0, 0));
	MyFourthList.SetTextColor(RGB(255, 215, 0));
	MyFourthList.SetTextBkColor(RGB(0, 0, 0));
	MyFourthList.AddColumn(5,_T("服务名称"),_T("描述"),_T("状态"),_T("启动类型"),_T("服务类型"));
	MyFourthList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//获取服务信息
	GetServiceInfo();
	//更新服务信息间隔
	SetTimer(UPDATE_SERVICE_INFO, 1000, NULL);


	StartUp.AddColumn(3,_T("启动项目"),_T("命令"),_T("位置"));
	StartUp.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	GetBootInfo();
	StartUp.SetBkColor(RGB(0, 0, 0));
	StartUp.SetTextColor(RGB(255, 215, 0));
	StartUp.SetTextBkColor(RGB(0, 0, 0));
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void SysServer::OnPaint()
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
	bmpBackground0.LoadBitmap(IDB_BITMAP22);
	BITMAP bitmap0;
	bmpBackground0.GetBitmap(&bitmap0);
	CBitmap* pbmpPri0 = dcMem0.SelectObject(&bmpBackground0);
	dc.BitBlt(0, -10, 1000, 800, &dcMem0, 0, 0, SRCCOPY);
	CDialogEx::OnPaint();
	CDialogEx::OnPaint();
}

//获取服务信息
void SysServer::GetServiceInfo()
{
	//1.打开远程计算机服务控制管理器
	MyFourthList.DeleteAllItems();
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
		MyFourthList.AddItem(i, 5,
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

//更新服务频率
void SysServer::OnTimer(UINT_PTR nIDEvent)
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

//更新服务信息
void SysServer::UpDataSerInfo()
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
				MyFourthList.SetItemText(m_SelectNum, 2, _T("已停止"));
				break;
			case SERVICE_STOP_PENDING:
				MyFourthList.SetItemText(m_SelectNum, 2, _T("正在停止"));
				break;
			case SERVICE_START_PENDING:
				MyFourthList.SetItemText(m_SelectNum, 2, _T("正在启动"));
				break;
			case SERVICE_RUNNING:
				MyFourthList.SetItemText(m_SelectNum, 2, _T("正在运行"));
				break;
			case SERVICE_PAUSED:
				MyFourthList.SetItemText(m_SelectNum, 2, _T("已暂停"));
				break;
			case SERVICE_PAUSE_PENDING:
				MyFourthList.SetItemText(m_SelectNum, 2, _T("正在暂停"));
				break;
			case SERVICE_CONTINUE_PENDING:
				MyFourthList.SetItemText(m_SelectNum, 2, _T("准备继续"));
				break;
			}
		}
	}
	LocalFree(lpEnumService);
	CloseServiceHandle(hSCM);
}

void SysServer::OnSeverstart()
{
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

void SysServer::OnSeverstop()
{
	
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

void SysServer::OnSeverfresh()
{
	GetServiceInfo();
}

void SysServer::OnNMRClickListSever(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	//防止在空白区点击弹出菜单  
	int n = pNMItemActivate->iItem;//选择了第几行
	if (n != -1)
	{
		//保存所选服务的 服务名
		m_ServiceName = MyFourthList.GetItemText(n, 0);
		m_SelectNum = n;
		//下面的这段代码, 不单单适应于ListCtrl  
		CMenu menu, *pPopup;
		menu.LoadMenu(IDR_MENU2);
		pPopup = menu.GetSubMenu(0);
		CPoint myPoint;
		ClientToScreen(&myPoint);
		GetCursorPos(&myPoint);
		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);
	}
	*pResult = 0;
}

//************************************************************
// 函数名称:	GetBootInfo
// 返 回	值:	void
//************************************************************
void SysServer::GetBootInfo()
{
	StartUp.DeleteAllItems();
	m_vecBootInfo.clear();
	BOOTINFO stcBootInfo = { 0 };

	HKEY RootKey = NULL;						// 主键
	HKEY hkResult = NULL;						// 将要打开键的句柄 
	LONG lReturn;						// 记录读取注册表是否成功
	DWORD index = 0;
	TCHAR szKeyName[255] = { 0 };       // 注册表项名称
	DWORD dwKeyLen = 255;
	DWORD dwNameLen = 255;
	DWORD dwType = 0;
	CString buffer;
	LPCTSTR lpSubKey[2];				// 子键名称
	DWORD ListIndex = 0;

	lpSubKey[0] = _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");
	lpSubKey[1] = _T("SOFTWARE\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Run");

	for (DWORD i = 0; i < 2; i++)
	{
		if (i == 0)
			RootKey = HKEY_CURRENT_USER;
		if (i == 1)
			RootKey = HKEY_LOCAL_MACHINE;
		//打开lpSubkey
		lReturn = RegOpenKeyEx(RootKey, lpSubKey[i], 0,
			KEY_ALL_ACCESS, &hkResult);
		if (lReturn == ERROR_SUCCESS)
		{
			//如果打开成功，开始枚举其值
			while (ERROR_NO_MORE_ITEMS !=
				RegEnumValue(hkResult, index, stcBootInfo.szBootName, &dwKeyLen,
				0, NULL, NULL, NULL))
			{
				//获取每个值得数据 szKeyName为值得名称 buffer为值的数据
				RegQueryValueEx(hkResult, stcBootInfo.szBootName,
					0, &dwType, (LPBYTE)stcBootInfo.szBootOrder, &dwNameLen);
				//保存位置信息
				//主键信息
				stcBootInfo.szHKEY;
				if (i == 0)
					_tcscpy_s(stcBootInfo.szHKEY, _T("HKEY_CURRENT_USER"));
				if (i == 1)
					_tcscpy_s(stcBootInfo.szHKEY, _T("HKEY_LOCAL_MACHINE"));
				//删除时要用到的
				_tcscpy_s(stcBootInfo.szBootPos, lpSubKey[i]);
				//List中要显示的
				buffer.Empty();
				buffer = buffer + stcBootInfo.szHKEY + _T("\\") + stcBootInfo.szBootPos;
				_tcscpy_s(stcBootInfo.szBootPos_All, buffer);


				//添加到vector
				m_vecBootInfo.push_back(stcBootInfo);
				//插入List
				StartUp.AddItem(ListIndex++, 3,
					stcBootInfo.szBootName,
					stcBootInfo.szBootOrder,
					stcBootInfo.szBootPos_All);
				//
				index++;
				dwNameLen = 255;
				dwKeyLen = 255;
				memset(&stcBootInfo, 0, sizeof(BOOTINFO));
			}
			index = 0;
			RegCloseKey(hkResult);
		}
	}
}


void SysServer::OnAddqd()
{
	// TODO:  在此添加命令处理程序代码//打开文件代码
	TCHAR FilePathName[MAX_PATH] = { 0 };
	CString FileName;
	CFileDialog dlg(TRUE, //TRUE为OPEN对话框，FALSE为SAVE AS对话框
		NULL,
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		(LPCTSTR)_TEXT("All Files (*.*)|*.*||"),
		NULL);
	if (dlg.DoModal() == IDOK)
	{
		//文件名保存在了FilePathName里
		_tcscpy_s(FilePathName, dlg.GetPathName());
	}
	else
	{
		return;
	}
	//打开启动项Key
	HKEY hKey;
	LPCTSTR lpRun = _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");
	long lRet = RegOpenKeyEx(HKEY_CURRENT_USER, lpRun, 0, KEY_WRITE, &hKey);
	if (lRet == ERROR_SUCCESS)
	{
		//获取路径长度
		DWORD dwRet = _tcslen(FilePathName);

		//添加启动项信息
		FileName = dlg.GetFileTitle();
		int n = sizeof(TCHAR);
		lRet = RegSetValueEx(hKey, FileName, 0, REG_SZ,
			(BYTE *)FilePathName, dwRet*sizeof(TCHAR));

		//关闭注册表   
		RegCloseKey(hKey);
		if (lRet != ERROR_SUCCESS)
		{
			AfxMessageBox(_T("添加启动项失败!"));
		}
		else
		{
			AfxMessageBox(_T("添加启动项成功!"));
			GetBootInfo();
		}
	}
}


void SysServer::OnBanqd()
{
	if (m_Select == -1)
	{
		return;
	}
	HKEY RootKey = NULL;		//根键
	HKEY hKey;
	//确定要禁止的根键
	strTemp = m_vecBootInfo[m_Select].szHKEY;
	if (strTemp == _T("HKEY_CURRENT_USER"))
	{
		RootKey = HKEY_CURRENT_USER;
	}
	if (strTemp == _T("HKEY_LOCAL_MACHINE"))
	{
		RootKey = HKEY_LOCAL_MACHINE;
	}
	if (RootKey == NULL)
	{
		return;
	}
	//确定要禁止的Run子键路径
	LPCTSTR lpRun = m_vecBootInfo[m_Select].szBootPos;
	//打开启动项Key   
	long lRet = RegOpenKeyEx(RootKey, lpRun, 0, KEY_WRITE, &hKey);
	if (lRet == ERROR_SUCCESS)
	{
		//获取要禁止启动项的名字
		strTemp = m_vecBootInfo[m_Select].szBootName;
		//禁止此启动项 
		lRet = RegDeleteValue(hKey, strTemp);
		//关闭注册表   
		RegCloseKey(hKey);
		if (lRet != ERROR_SUCCESS)
		{
			AfxMessageBox(_T("禁止启动项成功！"));
		}
		else
		{
			AfxMessageBox(_T("禁止启动项成功！"));
			GetBootInfo();
		}
	}
}


void SysServer::OnFreshqd()
{
	GetBootInfo();
}


void SysServer::OnNMRClickListQd(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	//防止在空白区点击弹出菜单  
	int n = pNMItemActivate->iItem;//选择了第几行
	if (n != -1)
	{
		//保存所选软件的启动项
		m_Select = n;
		//下面的这段代码, 不单单适应于ListCtrl  
		CMenu menu, *pPopup;
		menu.LoadMenu(IDR_MENU3);
		pPopup = menu.GetSubMenu(0);
		CPoint myPoint;
		ClientToScreen(&myPoint);
		GetCursorPos(&myPoint);
		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);
	}
	*pResult = 0;
}


void SysServer::OnLvnItemchangedListQd(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
}
