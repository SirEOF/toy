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
	//�ܹ���̬����Ӷ���
	void AddColumn(DWORD dwCount, ...)
	{
		va_list vl;
		va_start(vl, dwCount);
		//����
		TCHAR* pName = va_arg(vl, TCHAR*);
		InsertColumn(0, pName, 0, 200);
		//����
		pName = va_arg(vl, TCHAR*);
		InsertColumn(1, pName, 0, 370);
		//״̬
		pName = va_arg(vl, TCHAR*);
		InsertColumn(2, pName, 0, 80);
		//��������
		pName = va_arg(vl, TCHAR*);
		InsertColumn(3, pName, 0, 80);
		//��������
		pName = va_arg(vl, TCHAR*);
		InsertColumn(4, pName, 0, 100);
		va_end(vl);
	}
	//�ܹ���̬���һ���е�����
	void AddItem(int n, DWORD dwCount, ...)
	{
		va_list vl;
		va_start(vl, dwCount);
		//����
		TCHAR* pName = va_arg(vl, TCHAR*);
		InsertItem(n, pName);
		//����
		pName = va_arg(vl, TCHAR*);
		SetItemText(n, 1, pName);
		//״̬
		DWORD dwCurrentState = va_arg(vl, DWORD);
		switch (dwCurrentState)
		{
		case SERVICE_STOPPED:
			SetItemText(n, 2, _T("��ֹͣ"));
			break;
		case SERVICE_STOP_PENDING:
			SetItemText(n, 2, _T("����ֹͣ"));
			break;
		case SERVICE_START_PENDING:
			SetItemText(n, 2, _T("��������"));
			break;
		case SERVICE_RUNNING:
			SetItemText(n, 2, _T("��������"));
			break;
		case SERVICE_PAUSED:
			SetItemText(n, 2, _T("����ͣ"));
			break;
		case SERVICE_PAUSE_PENDING:
			SetItemText(n, 2, _T("������ͣ"));
			break;
		case SERVICE_CONTINUE_PENDING:
			SetItemText(n, 2, _T("׼������"));
			break;
		}
		//��������
		DWORD dwStartType = va_arg(vl, DWORD);
		switch (dwStartType)
		{
		case SERVICE_AUTO_START:
			SetItemText(n, 3, _T("�Զ�"));
			break;
		case SERVICE_BOOT_START:
			SetItemText(n, 3, _T("SERVICE_BOOT_START"));
			break;
		case SERVICE_DEMAND_START:
			SetItemText(n, 3, _T("�ֶ�"));
			break;
		case SERVICE_DISABLED:
			SetItemText(n, 3, _T("����"));
			break;
		case SERVICE_SYSTEM_START:
			SetItemText(n, 3, _T("SERVICE_SYSTEM_START"));
			break;
		}
		//��������
		DWORD dwServiceType = va_arg(vl, DWORD);
		switch (dwServiceType)
		{
		case SERVICE_FILE_SYSTEM_DRIVER:
			SetItemText(n, 4, _T("�ļ�ϵͳ��������"));
			break;
		case SERVICE_KERNEL_DRIVER:
			SetItemText(n, 4, _T("��������"));
			break;
		case SERVICE_WIN32_OWN_PROCESS:
			SetItemText(n, 4, _T("�������̷���"));
			break;
		case SERVICE_WIN32_SHARE_PROCESS:
			SetItemText(n, 4, _T("������̷���"));
			break;
		}
		va_end(vl);
	}
};


