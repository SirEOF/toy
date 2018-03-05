// Defend.cpp : 实现文件
//

#include "stdafx.h"
#include "SharkGuard.h"
#include "Defend.h"
#include "afxdialogex.h"


// Defend 对话框
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


// Defend 消息处理程序


BOOL Defend::OnInitDialog()
{

	CDialogEx::OnInitDialog();
	M_Monlist.SetBkColor(RGB(0, 0, 0));
	M_Monlist.SetTextColor(RGB(255, 215, 0));
	M_Monlist.SetTextBkColor(RGB(0, 0, 0));
	M_Monlist.InsertColumn(0, _T("状态"), 0, 140);
	M_Monlist.InsertColumn(1, _T("文件动作"), 0, 200);
	M_Monlist.InsertColumn(2, _T("文件修改路径"), 0, 500);
	M_Monlist.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	CreateThread(NULL, 0, Monitor, this, 0, NULL);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void Defend::OnPaint()
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
	Defend *pThis = (Defend*)lpParameter;//本类的对象指针

	BYTE Buffer[1024] = { 0 };
	//参数
	FILE_NOTIFY_INFORMATION *in_out_notification = (FILE_NOTIFY_INFORMATION *)Buffer;//存储监控函数返回信息地址 
	DWORD in_out_BytesReturned = 1024;//存储监控函数返回信息的字节数 
	DWORD in_out_version = 0;//返回版本信息 
	FILE_NOTIFY_INFORMATION temp_notification = {};//备用的一个参数 

	//路径是空,默认C盘
	if (pThis->m_csDirPath == L"")
	{
		pThis->m_csDirPath = L"C:\\";
	}

	//创建一个目录句柄  
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
		::MessageBox(NULL, TEXT("打开目录错误!"), TEXT("文件监控"), 0);
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
		m_time = CTime::GetCurrentTime();             //获取当前时间日期  
		CString m_strDateTime = m_time.Format(_T("%Y-%m-%d %H:%M:%S"));   //格式化日期时间  


		if (GetLastError() == ERROR_INVALID_FUNCTION)
		{
			::MessageBox(NULL, TEXT("系统不支持!"), TEXT("文件监控"), 0);
		}
		else if (watch_state == 0)
		{
			::MessageBox(NULL, TEXT("监控失败!"), TEXT("文件监控"), 0);
		}
		else if (GetLastError() == ERROR_NOTIFY_ENUM_DIR)
		{
			::MessageBox(NULL, TEXT("内存溢出!"), TEXT("文件监控"), 0);
		}
		else
		{

			//文件路径  
			CString nFilePath(pThis->m_csDirPath);
			nFilePath += in_out_notification->FileName;

			/*nFilePath.Left(in_out_notification->FileNameLength / sizeof(WCHAR));*/

			//这里主要就是检测返回的信息，需要注意FILE_NOTIFY_INFORMATION结构体的定义，以便正确调用返回信息  
			CString nStr;

			if (in_out_notification->Action == FILE_ACTION_ADDED)
			{
		
				pThis->M_Monlist.InsertItem(pThis->M_Monlist.GetItemCount(), m_strDateTime);
				//状态
				pThis->M_Monlist.SetItemText(pThis->M_Monlist.GetItemCount() - 1, 1, L"新增文件");
				//名字
				pThis->M_Monlist.SetItemText(pThis->M_Monlist.GetItemCount() - 1, 2, nFilePath);
			}
			if (in_out_notification->Action == FILE_ACTION_REMOVED)
			{
				
				pThis->M_Monlist.InsertItem(pThis->M_Monlist.GetItemCount(), m_strDateTime);
				//状态
				pThis->M_Monlist.SetItemText(pThis->M_Monlist.GetItemCount() - 1, 1, L"删除文件");
				//名字
				pThis->M_Monlist.SetItemText(pThis->M_Monlist.GetItemCount() - 1, 2, nFilePath);
			}

			if (in_out_notification->Action == FILE_ACTION_MODIFIED)
			{
				
				pThis->M_Monlist.InsertItem(pThis->M_Monlist.GetItemCount(), m_strDateTime);
				//状态
				pThis->M_Monlist.SetItemText(pThis->M_Monlist.GetItemCount() - 1, 1, L"修改文件");
				//名字
				pThis->M_Monlist.SetItemText(pThis->M_Monlist.GetItemCount() - 1, 2, nFilePath);
			}

			//对于下面两种情况，Action本身也是文件名（可能是old_name也可能是new_name）  
			if (in_out_notification->Action == FILE_ACTION_RENAMED_OLD_NAME)
			{
				
				pThis->M_Monlist.InsertItem(pThis->M_Monlist.GetItemCount(), m_strDateTime);
				//状态
				pThis->M_Monlist.SetItemText(pThis->M_Monlist.GetItemCount() - 1, 1, L"重命名文件");
				//名字
				pThis->M_Monlist.SetItemText(pThis->M_Monlist.GetItemCount() - 1, 2, nFilePath);
			}
			if (in_out_notification->Action == FILE_ACTION_RENAMED_NEW_NAME)
			{
				
				pThis->M_Monlist.InsertItem(pThis->M_Monlist.GetItemCount(), m_strDateTime);
				//状态
				pThis->M_Monlist.SetItemText(pThis->M_Monlist.GetItemCount() - 1, 1, L"重命名");
				//名字
				pThis->M_Monlist.SetItemText(pThis->M_Monlist.GetItemCount() - 1, 2, nFilePath);

			}
			pThis->M_Monlist.SetItemState(pThis->M_Monlist.GetItemCount() - 1, LVIS_SELECTED, LVIS_SELECTED);//选择当前行
			pThis->M_Monlist.EnsureVisible(pThis->M_Monlist.GetItemCount() - 1, FALSE);//滚动到这里
		}
		Sleep(500);
	}
	CloseHandle(handle_directory);

}