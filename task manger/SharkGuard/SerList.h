#pragma once
#include <winsvc.h>


// MyFourList

class MyFourList : public CListCtrl
{
	DECLARE_DYNAMIC(MyFourList)

public:
	MyFourList();
	virtual ~MyFourList();

protected:
	DECLARE_MESSAGE_MAP()
public:
	//能够动态的添加多列
	void AddColumn(DWORD dwCount, ...)
	{
		va_list vl;
		va_start(vl, dwCount);
		//名称
		TCHAR* pName = va_arg(vl, TCHAR*);
		InsertColumn(0, pName, 0, 200);
		//描述
		pName = va_arg(vl, TCHAR*);
		InsertColumn(1, pName, 0, 370);
		//状态
		pName = va_arg(vl, TCHAR*);
		InsertColumn(2, pName, 0, 80);
		//启动类型
		pName = va_arg(vl, TCHAR*);
		InsertColumn(3, pName, 0, 80);
		//服务类型
		pName = va_arg(vl, TCHAR*);
		InsertColumn(4, pName, 0, 100);
		va_end(vl);
	}
	//能够动态添加一整行的内容
	void AddItem(int n, DWORD dwCount, ...)
	{
		va_list vl;
		va_start(vl, dwCount);
		//名称
		TCHAR* pName = va_arg(vl, TCHAR*);
		InsertItem(n, pName);
		//描述
		pName = va_arg(vl, TCHAR*);
		SetItemText(n, 1, pName);
		//状态
		DWORD dwCurrentState = va_arg(vl, DWORD);
		switch (dwCurrentState)
		{
		case SERVICE_STOPPED:
			SetItemText(n, 2, _T("已停止"));
			break;
		case SERVICE_STOP_PENDING:
			SetItemText(n, 2, _T("正在停止"));
			break;
		case SERVICE_START_PENDING:
			SetItemText(n, 2, _T("正在启动"));
			break;
		case SERVICE_RUNNING:
			SetItemText(n, 2, _T("正在运行"));
			break;
		case SERVICE_PAUSED:
			SetItemText(n, 2, _T("已暂停"));
			break;
		case SERVICE_PAUSE_PENDING:
			SetItemText(n, 2, _T("正在暂停"));
			break;
		case SERVICE_CONTINUE_PENDING:
			SetItemText(n, 2, _T("准备继续"));
			break;
		}
		//启动类型
		DWORD dwStartType = va_arg(vl, DWORD);
		switch (dwStartType)
		{
		case SERVICE_AUTO_START:
			SetItemText(n, 3, _T("自动"));
			break;
		case SERVICE_BOOT_START:
			SetItemText(n, 3, _T("SERVICE_BOOT_START"));
			break;
		case SERVICE_DEMAND_START:
			SetItemText(n, 3, _T("手动"));
			break;
		case SERVICE_DISABLED:
			SetItemText(n, 3, _T("禁用"));
			break;
		case SERVICE_SYSTEM_START:
			SetItemText(n, 3, _T("SERVICE_SYSTEM_START"));
			break;
		}
		//服务类型
		DWORD dwServiceType = va_arg(vl, DWORD);
		switch (dwServiceType)
		{
		case SERVICE_FILE_SYSTEM_DRIVER:
			SetItemText(n, 4, _T("文件系统驱动服务"));
			break;
		case SERVICE_KERNEL_DRIVER:
			SetItemText(n, 4, _T("驱动服务"));
			break;
		case SERVICE_WIN32_OWN_PROCESS:
			SetItemText(n, 4, _T("独立进程服务"));
			break;
		case SERVICE_WIN32_SHARE_PROCESS:
			SetItemText(n, 4, _T("共享进程服务"));
			break;
		}
		va_end(vl);
	}
};


