
// AsmInJectDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AsmInJect.h"
#include "AsmInJectDlg.h"
#include "afxdialogex.h"
#include "afxwin.h"
#define WM_ASMPROID WM_USER+3

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



CAsmInJectDlg::CAsmInJectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAsmInJectDlg::IDD, pParent)

{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAsmInJectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT_Asm, m_Asm);
	DDX_Control(pDX, IDC_EDIT_ASM_PID, m_Pid);
}

BEGIN_MESSAGE_MAP(CAsmInJectDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_ASMPROID, &CAsmInJectDlg::MsgASm)
	ON_BN_CLICKED(IDC_BTN_ASM, &CAsmInJectDlg::OnBnClickedBtnAsm)
	ON_BN_CLICKED(IDC_BTN_eXIT, &CAsmInJectDlg::OnBnClickedBtnexit)
END_MESSAGE_MAP()


// CAsmInJectDlg 消息处理程序


LRESULT  CAsmInJectDlg::MsgASm(WPARAM wParam, LPARAM lParam)
{
	int a;  TCHAR Str[16]="";
	a = (int)lParam;
	_itot_s(a, Str, 10);
	GetDlgItem(IDC_EDIT_ASM_PID)->SetWindowText(Str);
	return 1;
}


BOOL CAsmInJectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAsmInJectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CAsmInJectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



CString CAsmInJectDlg::GetProPath()
{
	char buf[1024];
	CString path;
	GetModuleFileName(NULL, buf, 1024);
	path = buf;
	int nPos;
	nPos = path.ReverseFind('\\');
	path = path.Left(nPos);
	return path;
}

BOOL CAsmInJectDlg::AdjustPr()

{
	HANDLE hToken;
	LUID sedebugnameValue;
	TOKEN_PRIVILEGES tkp;

	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &hToken))
	{
		TRACE("提权失败1");
		return FALSE;
	}

	if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &sedebugnameValue))
	{
		CloseHandle(hToken);
		TRACE("提权失败2");
		return FALSE;
	}
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Luid = sedebugnameValue;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	if (!AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof tkp, NULL, NULL))
	{
		TRACE("提权失败3");
		CloseHandle(hToken);
		return FALSE;
	}
	else
		return TRUE;
}
void CAsmInJectDlg::InjectBin(DWORD pid)
{
	if (!AdjustPr())
	{
		MessageBox("提权失败");
		return;
	}
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_CREATE_THREAD | PROCESS_VM_OPERATION | PROCESS_VM_WRITE, FALSE, pid);
	if (!hProcess)
	{
		MessageBox("OpenProcess失败");
		return;
	}
	//LPVOID pParam = VirtualAllocEx(hProcess, NULL, 4, MEM_COMMIT, PAGE_READWRITE);
	LPVOID pAddr = VirtualAllocEx(hProcess, NULL, 4096, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (!pAddr)
	{
		MessageBox("VirtualAllocEx失败");
		return;
	}


	CString tmp, str;
	tmp.Format("开辟的虚拟地址:%08X", pAddr);
	OutputDebugString(tmp);
	
	char error[256] = { 0 };
	int count = m_Asm.GetLineCount();
	BYTE buf[4096] = { 0 };
	int j = 0;
	int m = 0;
	
	for (int i = 0; i < count; i++)
	{
		char cmd[256] = { 0 };
		int len = m_Asm.GetLine(i, cmd, 256);
		if (len == 0) continue;
		cmd[len] = '\0';
		t_asmmodel t_asm;
		j = m_asm.Assemble(cmd, (DWORD)pAddr + j, &t_asm, 0, 4, error);
		if (j <= 0)
		{
			tmp.Format("error=\"%s\"", error);
			OutputDebugString(tmp);
		}
		for (int k = 0; k<j; k++)
		{
			buf[m] = (BYTE)t_asm.code[k];
			tmp.Format("%02X", buf[m]);
			str = str + tmp;
			m = m + 1;
		}
		OutputDebugString(str);
		str = "";
	}
	
	buf[m] = 0x0c2;//ret 4
	buf[m + 1] = 0x04;
	buf[m + 2] = 0x00;
	if (!WriteProcessMemory(hProcess, pAddr, buf, 4096, NULL))
	{
		MessageBox("WriteProcessMemory失败");
		return;
	}
	DWORD dwThreadID;
	DWORD dwParam = 0;
	HANDLE hRemoteThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)pAddr, NULL, 0, &dwThreadID);
	if (!hRemoteThread)
	{
		MessageBox("CreateRemoteThread失败");
		return;
	}
	CloseHandle(hRemoteThread);
	CloseHandle(hProcess);

	/*
	mov ecx,0x00b450dc
	mov ecx,[ecx]
	push 1
	mov eax,0x005DBC50
	call eax

	*/


}


void CAsmInJectDlg::OnBnClickedBtnAsm()
{
	// TODO:  在此添加控件通知处理程序代码
	//取得编辑框内容
	CString str;
	GetDlgItemText(IDC_EDIT_Asm, str);
	if (str.IsEmpty())
	{
		MessageBox("请输入汇编代码");
		return;
	}
	//SetDlgItemText(IDC_EDIT4, "");
	int pid = GetDlgItemInt(IDC_EDIT_ASM_PID);
	if (pid)
	InjectBin(pid);

}


void CAsmInJectDlg::OnBnClickedBtnexit()
{
	// TODO:  在此添加控件通知处理程序代码
	SendMessage(WM_CLOSE);
}
