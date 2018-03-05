
// x64toolDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "x64tool.h"
#include "x64toolDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_CONTROLPRINT WM_USER+1001
#define  PATH  L"C:\\x64.dll"
//#define PATH L"C:\\Users\\Administrator\\Desktop\\okokok\\x64\\Debug\\TestDll.dll"



Cx64toolDlg::Cx64toolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cx64toolDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cx64toolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Cx64toolDlg, CDialogEx)
	ON_MESSAGE(WM_CONTROLPRINT, OnControlPrint)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// Cx64toolDlg ��Ϣ�������

LRESULT Cx64toolDlg::OnControlPrint(WPARAM wParam, LPARAM lParam)
{
	int n;
	n = (int)lParam;
	GetProcessId(n);
	DestroyWindow();

	return 1;
}

void Cx64toolDlg::GetProcessId(int a)
{
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, a);
	LPVOID lpAddress = VirtualAllocEx(hProcess, NULL, 1024, MEM_COMMIT, PAGE_READWRITE);
	WriteProcessMemory(hProcess, lpAddress, (LPVOID)PATH, (wcslen(PATH) + 1) * 2, 0);
	HANDLE hThread = CreateRemoteThread(hProcess, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibraryW, lpAddress, NULL, NULL);
	if (hThread)
	{
		::MessageBox(0, L"ע��ɹ�", L"Bingo", 0);

		CloseHandle(hProcess);
		CloseHandle(hThread);

	}

}

BOOL Cx64toolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	MoveWindow(0, 0, 0, 0);
	ShowWindow(SW_HIDE);
	ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Cx64toolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR Cx64toolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

