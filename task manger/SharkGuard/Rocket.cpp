// Rocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SharkGuard.h"
#include "Rocket.h"
#include "afxdialogex.h"
#include <tlhelp32.h>
#include <Psapi.h>


// Rocket �Ի���

IMPLEMENT_DYNAMIC(Rocket, CDialogEx)

Rocket::Rocket(CWnd* pParent /*=NULL*/)
	: CDialogEx(Rocket::IDD, pParent)
{

}

Rocket::~Rocket()
{
}

void Rocket::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Rocket, CDialogEx)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// Rocket ��Ϣ�������

void Rocket::SetStyle()
{
	/*���ô��ڷ��*/
	SetWindowLong(m_hWnd, GWL_EXSTYLE, GetWindowLong(m_hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	/*���ô���͸����ɫ*/
	SetLayeredWindowAttributes(RGB(255, 255, 255), 0, LWA_COLORKEY);
	/*����bmpͼƬ*/
	bmp.LoadBitmap(IDB_BITMAP40);										//����ʱ���ͼƬ����
	/*����ͼƬ��С���ÿ��*/
	BITMAP  bmpInfo;
	bmp.GetBitmap(&bmpInfo);

	MoveWindow(1200, 600, bmpInfo.bmWidth, bmpInfo.bmHeight);

}


void Rocket::Draw(CDC *dc)
{
	//��ӡͼƬ��������,��Ҫpaint��Ϣ��ͣ�ٻ�
	CDC  hMen;
	hMen.CreateCompatibleDC(dc);

	hMen.SelectObject(bmp);
	CRect rt;
	GetClientRect(rt);
	/*ʹ�õȱȿ���*/
	BITMAP bmpInfo;
	bmp.GetBitmap(&bmpInfo);
	dc->BitBlt(0, 0, rt.Width(), rt.Height(), &hMen, 0, 0, SRCCOPY);
}

BOOL Rocket::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


int Rocket::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetStyle();
	return 0;
}


void Rocket::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	Draw(&dc);
}


void Rocket::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CRect rt;
	GetWindowRect(rt);
	CRect old;
	GetWindowRect(old);
	while (rt.bottom > 0)
	{
		MoveWindow(rt, TRUE);
		rt.bottom--;
		rt.top--;
		Sleep(0.5);
	}
	MoveWindow(old);
	UpdateData(FALSE);
	//��ȡ����ǰ���ڴ���Ϣ
	MEMORYSTATUSEX memStatus = { sizeof(MEMORYSTATUSEX) };
	GlobalMemoryStatusEx(&memStatus);
	DOUBLE preUsedMem = (DOUBLE)(memStatus.ullTotalPhys - memStatus.ullAvailPhys) / 1024 / 1024;
	//��ʼ�����ڴ�
	ClearMemory();
	//��ȡ�������ڴ���Ϣ
	GlobalMemoryStatusEx(&memStatus);
	DOUBLE afterUsedMem = (DOUBLE)(memStatus.ullTotalPhys - memStatus.ullAvailPhys) / 1024 / 1024;
	//���������Ϣ
	UpdateData(FALSE);
	CString m_SsFree;
	m_SsFree.Format(_T("�ڴ�������ϣ��������� : %.2f MB"), preUsedMem - afterUsedMem);
	MessageBox(L"Declear  BingGo!\n" + m_SsFree, L"BingGo!", NULL);
	CDialogEx::OnLButtonDblClk(nFlags, point);
}


void Rocket::OnLButtonDown(UINT nFlags, CPoint point)
{
	SendMessage(WM_SYSCOMMAND, SC_MOVE | HTCAPTION, 0);
	CDialogEx::OnLButtonDown(nFlags, point);
}

void Rocket::ClearMemory()
{
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		return;
	}

	PROCESSENTRY32 ProcessInfo;
	ProcessInfo.dwSize = sizeof(ProcessInfo);
	int count = 0;

	//��ȡϵͳ�е�һ�����̵���Ϣ  
	BOOL Status = Process32First(hProcessSnap, &ProcessInfo);
	while (Status)
	{
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, TRUE,
			ProcessInfo.th32ProcessID);
		if (hProcess)
		{
			//���ý��̹�������С
			SetProcessWorkingSetSize(hProcess, -1, -1);
			//�����ܶ�Ľ�ָ�����̵�ҳ��ӹ������Ƴ�
			EmptyWorkingSet(hProcess);
			CloseHandle(hProcess);
		}
		//��ȡ��һ�����̵���Ϣ  
		Status = Process32Next(hProcessSnap, &ProcessInfo);
	}
}