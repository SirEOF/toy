// Defend.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SharkGuard.h"
#include "Defend.h"
#include "afxdialogex.h"


// Defend �Ի���
DWORD WINAPI  Monitor(LPVOID lpParameter);
IMPLEMENT_DYNAMIC(Defend, CDialogEx)

Defend::Defend(CWnd* pParent /*=NULL*/)
	: CDialogEx(Defend::IDD, pParent)
{

}

Defend::~Defend()
{
}

void Defend::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_FlieMonitor, M_Monlist);
}


BEGIN_MESSAGE_MAP(Defend, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// Defend ��Ϣ�������


BOOL Defend::OnInitDialog()
{

	CDialogEx::OnInitDialog();
	M_Monlist.SetBkColor(RGB(0, 0, 0));
	M_Monlist.SetTextColor(RGB(255, 215, 0));
	M_Monlist.SetTextBkColor(RGB(0, 0, 0));
	M_Monlist.InsertColumn(0, _T("״̬"), 0, 140);
	M_Monlist.InsertColumn(1, _T("�ļ�����"), 0, 200);
	M_Monlist.InsertColumn(2, _T("�ļ��޸�·��"), 0, 500);
	M_Monlist.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	CreateThread(NULL, 0, Monitor, this, 0, NULL);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void Defend::OnPaint()
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
	bmpBackground0.LoadBitmap(IDB_BITMAP46);
	BITMAP bitmap0;
	bmpBackground0.GetBitmap(&bitmap0);
	CBitmap* pbmpPri0 = dcMem0.SelectObject(&bmpBackground0);
	dc.BitBlt(0, -10, 1000, 800, &dcMem0, 0, 0, SRCCOPY);
	CDialogEx::OnPaint();
	CDialogEx::OnPaint();
}

DWORD WINAPI  Monitor(LPVOID lpParameter)
{
	Defend *pThis = (Defend*)lpParameter;//����Ķ���ָ��

	BYTE Buffer[1024] = { 0 };
	//����
	FILE_NOTIFY_INFORMATION *in_out_notification = (FILE_NOTIFY_INFORMATION *)Buffer;//�洢��غ���������Ϣ��ַ 
	DWORD in_out_BytesReturned = 1024;//�洢��غ���������Ϣ���ֽ��� 
	DWORD in_out_version = 0;//���ذ汾��Ϣ 
	FILE_NOTIFY_INFORMATION temp_notification = {};//���õ�һ������ 

	//·���ǿ�,Ĭ��C��
	if (pThis->m_csDirPath == L"")
	{
		pThis->m_csDirPath = L"C:\\";
	}

	//����һ��Ŀ¼���  
	HANDLE handle_directory = CreateFile(pThis->m_csDirPath,
		FILE_LIST_DIRECTORY,
		FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
		NULL,
		OPEN_EXISTING,
		FILE_FLAG_BACKUP_SEMANTICS,
		NULL);
	if (handle_directory == INVALID_HANDLE_VALUE)
	{
		DWORD ERROR_DIR = GetLastError();
		::MessageBox(NULL, TEXT("��Ŀ¼����!"), TEXT("�ļ����"), 0);
	}

	BOOL watch_state;


	while (TRUE)
	{
		::ZeroMemory(Buffer, sizeof(Buffer));

		watch_state = ReadDirectoryChangesW(handle_directory,
			(LPVOID)&Buffer,
			sizeof(Buffer),
			TRUE,
			FILE_NOTIFY_CHANGE_FILE_NAME |
			FILE_NOTIFY_CHANGE_DIR_NAME |
			FILE_NOTIFY_CHANGE_LAST_WRITE,
			&in_out_BytesReturned,
			NULL,
			NULL);

		CTime m_time;
		m_time = CTime::GetCurrentTime();             //��ȡ��ǰʱ������  
		CString m_strDateTime = m_time.Format(_T("%Y-%m-%d %H:%M:%S"));   //��ʽ������ʱ��  


		if (GetLastError() == ERROR_INVALID_FUNCTION)
		{
			::MessageBox(NULL, TEXT("ϵͳ��֧��!"), TEXT("�ļ����"), 0);
		}
		else if (watch_state == 0)
		{
			::MessageBox(NULL, TEXT("���ʧ��!"), TEXT("�ļ����"), 0);
		}
		else if (GetLastError() == ERROR_NOTIFY_ENUM_DIR)
		{
			::MessageBox(NULL, TEXT("�ڴ����!"), TEXT("�ļ����"), 0);
		}
		else
		{

			//�ļ�·��  
			CString nFilePath(pThis->m_csDirPath);
			nFilePath += in_out_notification->FileName;

			/*nFilePath.Left(in_out_notification->FileNameLength / sizeof(WCHAR));*/

			//������Ҫ���Ǽ�ⷵ�ص���Ϣ����Ҫע��FILE_NOTIFY_INFORMATION�ṹ��Ķ��壬�Ա���ȷ���÷�����Ϣ  
			CString nStr;

			if (in_out_notification->Action == FILE_ACTION_ADDED)
			{
		
				pThis->M_Monlist.InsertItem(pThis->M_Monlist.GetItemCount(), m_strDateTime);
				//״̬
				pThis->M_Monlist.SetItemText(pThis->M_Monlist.GetItemCount() - 1, 1, L"�����ļ�");
				//����
				pThis->M_Monlist.SetItemText(pThis->M_Monlist.GetItemCount() - 1, 2, nFilePath);
			}
			if (in_out_notification->Action == FILE_ACTION_REMOVED)
			{
				
				pThis->M_Monlist.InsertItem(pThis->M_Monlist.GetItemCount(), m_strDateTime);
				//״̬
				pThis->M_Monlist.SetItemText(pThis->M_Monlist.GetItemCount() - 1, 1, L"ɾ���ļ�");
				//����
				pThis->M_Monlist.SetItemText(pThis->M_Monlist.GetItemCount() - 1, 2, nFilePath);
			}

			if (in_out_notification->Action == FILE_ACTION_MODIFIED)
			{
				
				pThis->M_Monlist.InsertItem(pThis->M_Monlist.GetItemCount(), m_strDateTime);
				//״̬
				pThis->M_Monlist.SetItemText(pThis->M_Monlist.GetItemCount() - 1, 1, L"�޸��ļ�");
				//����
				pThis->M_Monlist.SetItemText(pThis->M_Monlist.GetItemCount() - 1, 2, nFilePath);
			}

			//�����������������Action����Ҳ���ļ�����������old_nameҲ������new_name��  
			if (in_out_notification->Action == FILE_ACTION_RENAMED_OLD_NAME)
			{
				
				pThis->M_Monlist.InsertItem(pThis->M_Monlist.GetItemCount(), m_strDateTime);
				//״̬
				pThis->M_Monlist.SetItemText(pThis->M_Monlist.GetItemCount() - 1, 1, L"�������ļ�");
				//����
				pThis->M_Monlist.SetItemText(pThis->M_Monlist.GetItemCount() - 1, 2, nFilePath);
			}
			if (in_out_notification->Action == FILE_ACTION_RENAMED_NEW_NAME)
			{
				
				pThis->M_Monlist.InsertItem(pThis->M_Monlist.GetItemCount(), m_strDateTime);
				//״̬
				pThis->M_Monlist.SetItemText(pThis->M_Monlist.GetItemCount() - 1, 1, L"������");
				//����
				pThis->M_Monlist.SetItemText(pThis->M_Monlist.GetItemCount() - 1, 2, nFilePath);

			}
			pThis->M_Monlist.SetItemState(pThis->M_Monlist.GetItemCount() - 1, LVIS_SELECTED, LVIS_SELECTED);//ѡ��ǰ��
			pThis->M_Monlist.EnsureVisible(pThis->M_Monlist.GetItemCount() - 1, FALSE);//����������
		}
		Sleep(500);
	}
	CloseHandle(handle_directory);

}