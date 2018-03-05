// SysServer.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SharkGuard.h"
#include "SysServer.h"
#include "afxdialogex.h"


// SysServer �Ի���

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


// SysServer ��Ϣ�������


BOOL SysServer::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	MyFourthList.SetBkColor(RGB(0, 0, 0));
	MyFourthList.SetTextColor(RGB(255, 215, 0));
	MyFourthList.SetTextBkColor(RGB(0, 0, 0));
	MyFourthList.AddColumn(5,_T("��������"),_T("����"),_T("״̬"),_T("��������"),_T("��������"));
	MyFourthList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//��ȡ������Ϣ
	GetServiceInfo();
	//���·�����Ϣ���
	SetTimer(UPDATE_SERVICE_INFO, 1000, NULL);


	StartUp.AddColumn(3,_T("������Ŀ"),_T("����"),_T("λ��"));
	StartUp.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	GetBootInfo();
	StartUp.SetBkColor(RGB(0, 0, 0));
	StartUp.SetTextColor(RGB(255, 215, 0));
	StartUp.SetTextBkColor(RGB(0, 0, 0));
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void SysServer::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect rc;
	GetClientRect(&rc);

	//���������ڱ���ɫ
	dc.FillSolidRect(rc, RGB(0, 151, 209));
	//��ҳͼƬ
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

//��ȡ������Ϣ
void SysServer::GetServiceInfo()
{
	//1.��Զ�̼����������ƹ�����
	MyFourthList.DeleteAllItems();
	m_vecSerInfo.clear();
	SC_HANDLE hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	//2.��һ�ε��ã���ȡ��Ҫ���ڴ��С
	DWORD dwServiceNum = 0;
	DWORD dwSize = 0;
	EnumServicesStatus(
		hSCM,
		SERVICE_WIN32,
		SERVICE_STATE_ALL,	//���з���״̬
		NULL,				//������
		0,					//��������С
		&dwSize,			//��Ҫ�Ĵ�С
		&dwServiceNum,		//�������еķ������
		NULL);
	//3.������Ҫ���ڴ棬�ڶ��ε���
	LPENUM_SERVICE_STATUS lpEnumService =
		(LPENUM_SERVICE_STATUS)LocalAlloc(LPTR, dwSize);
	//4.�ڶ���ö��
	EnumServicesStatus(
		hSCM,
		SERVICE_WIN32,
		SERVICE_STATE_ALL,	//���з���״̬
		lpEnumService,		//������
		dwSize,				//��������С
		&dwSize,			//��Ҫ�Ĵ�С
		&dwServiceNum,		//�������еķ������
		NULL);
	//5.������Ϣ
	SC_HANDLE hService = nullptr;
	for (DWORD i = 0; i < dwServiceNum; i++)
	{
		//��ȡ������Ϣ
		//1.��������
		//2.��������
		//3.����״̬(���ݵõ���ֵ�ֶ�����ַ���)
		//����ֹͣ�� ����������" "������ͣ"...
		m_vecSerInfo.push_back(lpEnumService[i]);

		//��ȡ������Ϣ
		//1.�򿪷���
		hService = OpenService(hSCM,
			lpEnumService[i].lpServiceName, SERVICE_QUERY_CONFIG);
		// 2.��һ�ε��û�ȡ��Ҫ�Ļ�������С
		QueryServiceConfig(hService, NULL, 0, &dwSize);
		//�����ڴ�
		LPQUERY_SERVICE_CONFIG pServiceConfig =
			(LPQUERY_SERVICE_CONFIG)LocalAlloc(LPTR, dwSize);
		//3.�ڶ��ε���,��ȡ��Ϣ
		QueryServiceConfig(hService, pServiceConfig, dwSize, &dwSize);
		//��ȡ������Ϣ��ϣ���ʼ����List
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

//���·���Ƶ��
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

//���·�����Ϣ
void SysServer::UpDataSerInfo()
{
	//1.��Զ�̼����������ƹ�����
	SC_HANDLE hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	//2.��һ�ε��ã���ȡ��Ҫ���ڴ��С
	DWORD dwServiceNum = 0;
	DWORD dwSize = 0;
	EnumServicesStatus(
		hSCM,
		SERVICE_WIN32,
		SERVICE_STATE_ALL,	//���з���״̬
		NULL,				//������
		0,					//��������С
		&dwSize,			//��Ҫ�Ĵ�С
		&dwServiceNum,		//�������еķ������
		NULL);
	//3.������Ҫ���ڴ棬�ڶ��ε���
	LPENUM_SERVICE_STATUS lpEnumService =
		(LPENUM_SERVICE_STATUS)LocalAlloc(LPTR, dwSize);
	//4.�ڶ���ö��
	EnumServicesStatus(
		hSCM,
		SERVICE_WIN32,
		SERVICE_STATE_ALL,	//���з���״̬
		lpEnumService,		//������
		dwSize,				//��������С
		&dwSize,			//��Ҫ�Ĵ�С
		&dwServiceNum,		//�������еķ������
		NULL);
	//5.������Ϣ
	for (DWORD i = 0; i < dwServiceNum; i++)
	{
		//�����Ҫ���µķ���
		if (!_tcscmp(lpEnumService[i].lpServiceName, m_ServiceName))
		{
			//����list�и÷����״̬��Ϣ
			switch (lpEnumService[i].ServiceStatus.dwCurrentState)
			{
			case SERVICE_STOPPED:
				MyFourthList.SetItemText(m_SelectNum, 2, _T("��ֹͣ"));
				break;
			case SERVICE_STOP_PENDING:
				MyFourthList.SetItemText(m_SelectNum, 2, _T("����ֹͣ"));
				break;
			case SERVICE_START_PENDING:
				MyFourthList.SetItemText(m_SelectNum, 2, _T("��������"));
				break;
			case SERVICE_RUNNING:
				MyFourthList.SetItemText(m_SelectNum, 2, _T("��������"));
				break;
			case SERVICE_PAUSED:
				MyFourthList.SetItemText(m_SelectNum, 2, _T("����ͣ"));
				break;
			case SERVICE_PAUSE_PENDING:
				MyFourthList.SetItemText(m_SelectNum, 2, _T("������ͣ"));
				break;
			case SERVICE_CONTINUE_PENDING:
				MyFourthList.SetItemText(m_SelectNum, 2, _T("׼������"));
				break;
			}
		}
	}
	LocalFree(lpEnumService);
	CloseServiceHandle(hSCM);
}

void SysServer::OnSeverstart()
{
		//��������
		SC_HANDLE hSCM = OpenSCManager(			//�򿪷�����ƹ�����
			NULL, NULL, SC_MANAGER_ALL_ACCESS);
		SC_HANDLE hService = OpenService(hSCM,	//�򿪷���
			m_ServiceName, SERVICE_START);
		StartService(hService, 0, 0);			//��������
		//������Ϣ
		UpDataSerInfo();
		m_IsUpDateSer = TRUE;
		m_UpDataTimes = 5;
		CloseServiceHandle(hSCM);
		CloseServiceHandle(hService);
}

void SysServer::OnSeverstop()
{
	
				SC_HANDLE hSCM = OpenSCManager(			//�򿪷�����ƹ�����
				NULL, NULL, SC_MANAGER_ALL_ACCESS);
			SC_HANDLE hService = OpenService(hSCM,	//�򿪷���
				m_ServiceName, SERVICE_STOP);
			SERVICE_STATUS status;
			ControlService(hService,				//��������
				SERVICE_CONTROL_STOP,
				&status);
			//������Ϣ
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//��ֹ�ڿհ�����������˵�  
	int n = pNMItemActivate->iItem;//ѡ���˵ڼ���
	if (n != -1)
	{
		//������ѡ����� ������
		m_ServiceName = MyFourthList.GetItemText(n, 0);
		m_SelectNum = n;
		//�������δ���, ��������Ӧ��ListCtrl  
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
// ��������:	GetBootInfo
// �� ��	ֵ:	void
//************************************************************
void SysServer::GetBootInfo()
{
	StartUp.DeleteAllItems();
	m_vecBootInfo.clear();
	BOOTINFO stcBootInfo = { 0 };

	HKEY RootKey = NULL;						// ����
	HKEY hkResult = NULL;						// ��Ҫ�򿪼��ľ�� 
	LONG lReturn;						// ��¼��ȡע����Ƿ�ɹ�
	DWORD index = 0;
	TCHAR szKeyName[255] = { 0 };       // ע���������
	DWORD dwKeyLen = 255;
	DWORD dwNameLen = 255;
	DWORD dwType = 0;
	CString buffer;
	LPCTSTR lpSubKey[2];				// �Ӽ�����
	DWORD ListIndex = 0;

	lpSubKey[0] = _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");
	lpSubKey[1] = _T("SOFTWARE\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Run");

	for (DWORD i = 0; i < 2; i++)
	{
		if (i == 0)
			RootKey = HKEY_CURRENT_USER;
		if (i == 1)
			RootKey = HKEY_LOCAL_MACHINE;
		//��lpSubkey
		lReturn = RegOpenKeyEx(RootKey, lpSubKey[i], 0,
			KEY_ALL_ACCESS, &hkResult);
		if (lReturn == ERROR_SUCCESS)
		{
			//����򿪳ɹ�����ʼö����ֵ
			while (ERROR_NO_MORE_ITEMS !=
				RegEnumValue(hkResult, index, stcBootInfo.szBootName, &dwKeyLen,
				0, NULL, NULL, NULL))
			{
				//��ȡÿ��ֵ������ szKeyNameΪֵ������ bufferΪֵ������
				RegQueryValueEx(hkResult, stcBootInfo.szBootName,
					0, &dwType, (LPBYTE)stcBootInfo.szBootOrder, &dwNameLen);
				//����λ����Ϣ
				//������Ϣ
				stcBootInfo.szHKEY;
				if (i == 0)
					_tcscpy_s(stcBootInfo.szHKEY, _T("HKEY_CURRENT_USER"));
				if (i == 1)
					_tcscpy_s(stcBootInfo.szHKEY, _T("HKEY_LOCAL_MACHINE"));
				//ɾ��ʱҪ�õ���
				_tcscpy_s(stcBootInfo.szBootPos, lpSubKey[i]);
				//List��Ҫ��ʾ��
				buffer.Empty();
				buffer = buffer + stcBootInfo.szHKEY + _T("\\") + stcBootInfo.szBootPos;
				_tcscpy_s(stcBootInfo.szBootPos_All, buffer);


				//��ӵ�vector
				m_vecBootInfo.push_back(stcBootInfo);
				//����List
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
	// TODO:  �ڴ���������������//���ļ�����
	TCHAR FilePathName[MAX_PATH] = { 0 };
	CString FileName;
	CFileDialog dlg(TRUE, //TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���
		NULL,
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		(LPCTSTR)_TEXT("All Files (*.*)|*.*||"),
		NULL);
	if (dlg.DoModal() == IDOK)
	{
		//�ļ�����������FilePathName��
		_tcscpy_s(FilePathName, dlg.GetPathName());
	}
	else
	{
		return;
	}
	//��������Key
	HKEY hKey;
	LPCTSTR lpRun = _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");
	long lRet = RegOpenKeyEx(HKEY_CURRENT_USER, lpRun, 0, KEY_WRITE, &hKey);
	if (lRet == ERROR_SUCCESS)
	{
		//��ȡ·������
		DWORD dwRet = _tcslen(FilePathName);

		//�����������Ϣ
		FileName = dlg.GetFileTitle();
		int n = sizeof(TCHAR);
		lRet = RegSetValueEx(hKey, FileName, 0, REG_SZ,
			(BYTE *)FilePathName, dwRet*sizeof(TCHAR));

		//�ر�ע���   
		RegCloseKey(hKey);
		if (lRet != ERROR_SUCCESS)
		{
			AfxMessageBox(_T("���������ʧ��!"));
		}
		else
		{
			AfxMessageBox(_T("���������ɹ�!"));
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
	HKEY RootKey = NULL;		//����
	HKEY hKey;
	//ȷ��Ҫ��ֹ�ĸ���
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
	//ȷ��Ҫ��ֹ��Run�Ӽ�·��
	LPCTSTR lpRun = m_vecBootInfo[m_Select].szBootPos;
	//��������Key   
	long lRet = RegOpenKeyEx(RootKey, lpRun, 0, KEY_WRITE, &hKey);
	if (lRet == ERROR_SUCCESS)
	{
		//��ȡҪ��ֹ�����������
		strTemp = m_vecBootInfo[m_Select].szBootName;
		//��ֹ�������� 
		lRet = RegDeleteValue(hKey, strTemp);
		//�ر�ע���   
		RegCloseKey(hKey);
		if (lRet != ERROR_SUCCESS)
		{
			AfxMessageBox(_T("��ֹ������ɹ���"));
		}
		else
		{
			AfxMessageBox(_T("��ֹ������ɹ���"));
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//��ֹ�ڿհ�����������˵�  
	int n = pNMItemActivate->iItem;//ѡ���˵ڼ���
	if (n != -1)
	{
		//������ѡ�����������
		m_Select = n;
		//�������δ���, ��������Ӧ��ListCtrl  
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}
