// PageThree.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AAA.h"
#include "PageThree.h"
#include "afxdialogex.h"


// PageThree �Ի���

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



// ServicerDlg �Ի���






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
	// TODO: �ڴ˴������Ϣ����������
}

// ServicerDlg ��Ϣ�������

BOOL PageThree::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//������ϢList��ʼ��
	servicer_List.SetExtendedStyle(servicer_List.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);//��ѡ�з��
	CString str[] = { _T(""), _T("����"), _T("����"), _T("״̬"), _T("��������"), _T("��������") };
	servicer_List.InsertColumn(0, str[0], LVCFMT_LEFT, 2000);
	servicer_List.InsertColumn(1, str[1], LVCFMT_LEFT, 100);
	servicer_List.InsertColumn(2, str[2], LVCFMT_LEFT, 100);
	servicer_List.InsertColumn(3, str[3], LVCFMT_LEFT, 50);
	servicer_List.InsertColumn(4, str[4], LVCFMT_LEFT, 50);
	servicer_List.InsertColumn(5, str[5], LVCFMT_LEFT, 100);
	servicer_List.DeleteColumn(0);//ɾ����0�� �������־���

	//��ȡ������Ϣ
	GetServiceInfo();
	isInitEnd = true;
	//���·�����Ϣ���
	SetTimer(UPDATE_SERVICE_INFO, 1000, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
//************************************************************
// ��������:	GetServiceInfo
// ����˵��:	
// �� ��	ֵ:	void
//************************************************************
void PageThree::GetServiceInfo()
{
	//1.��Զ�̼����������ƹ�����
	servicer_List.DeleteAllItems();
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
// ��������:	UpDataSerInfo
// ����˵��:	���·�����Ϣ
// �� ��	ֵ:	void
//************************************************************
void PageThree::UpDataSerInfo()
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
				servicer_List.SetItemText(m_SelectNum, 2, _T("��ֹͣ"));
				break;
			case SERVICE_STOP_PENDING:
				servicer_List.SetItemText(m_SelectNum, 2, _T("����ֹͣ"));
				break;
			case SERVICE_START_PENDING:
				servicer_List.SetItemText(m_SelectNum, 2, _T("��������"));
				break;
			case SERVICE_RUNNING:
				servicer_List.SetItemText(m_SelectNum, 2, _T("��������"));
				break;
			case SERVICE_PAUSED:
				servicer_List.SetItemText(m_SelectNum, 2, _T("����ͣ"));
				break;
			case SERVICE_PAUSE_PENDING:
				servicer_List.SetItemText(m_SelectNum, 2, _T("������ͣ"));
				break;
			case SERVICE_CONTINUE_PENDING:
				servicer_List.SetItemText(m_SelectNum, 2, _T("׼������"));
				break;
			}
		}
	}
	LocalFree(lpEnumService);
	CloseServiceHandle(hSCM);
}

//************************************************************
// ��������:	OnTimer
// ����˵��:	���·���Ƶ��
// ��	��:	UINT_PTR nIDEvent
// �� ��	ֵ:	void
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
// ��������:	OnRclickList7
// ����˵��:	����List�Ҽ���Ӧ����
// ��	��:	NMHDR * pNMHDR
// ��	��:	LRESULT * pResult
// �� ��	ֵ:	void
//************************************************************
void PageThree::OnRclickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	//��ֹ�ڿհ�����������˵�  
	int n = pNMItemActivate->iItem;//ѡ���˵ڼ���
	if (n != -1)
	{
		//������ѡ����� ������
		m_ServiceName = servicer_List.GetItemText(n, 0);
		m_SelectNum = n;
		//�������δ���, ��������Ӧ��ListCtrl  
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
// ��������:	qidong
// ����˵��:	��������
// �� ��	ֵ:	void
//************************************************************
void PageThree::qidong()
{
	// TODO:  �ڴ���������������
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

//************************************************************
// ��������:	tingzhi
// ����˵��:	ֹͣ����
// �� ��	ֵ:	void
//************************************************************
void PageThree::tingzhi()
{
	// TODO:  �ڴ���������������
	//ֹͣ����
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

//************************************************************
// ��������:	shuaxin
// ����˵��:	ˢ�·���
// �� ��	ֵ:	void
//************************************************************
void PageThree::shuaxin()
{
	// TODO:  �ڴ���������������
	GetServiceInfo();
}


void PageThree::OnLvnItemchangedList3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


//��������
void PageThree::OnStops()
{
	//qidong();
	// TODO:  �ڴ���������������
}
