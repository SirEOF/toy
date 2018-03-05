
// AsmInJectDlg.cpp : ʵ���ļ�
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


// CAsmInJectDlg ��Ϣ�������


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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CAsmInJectDlg::OnPaint()
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
		TRACE("��Ȩʧ��1");
		return FALSE;
	}

	if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &sedebugnameValue))
	{
		CloseHandle(hToken);
		TRACE("��Ȩʧ��2");
		return FALSE;
	}
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Luid = sedebugnameValue;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	if (!AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof tkp, NULL, NULL))
	{
		TRACE("��Ȩʧ��3");
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
		MessageBox("��Ȩʧ��");
		return;
	}
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_CREATE_THREAD | PROCESS_VM_OPERATION | PROCESS_VM_WRITE, FALSE, pid);
	if (!hProcess)
	{
		MessageBox("OpenProcessʧ��");
		return;
	}
	//LPVOID pParam = VirtualAllocEx(hProcess, NULL, 4, MEM_COMMIT, PAGE_READWRITE);
	LPVOID pAddr = VirtualAllocEx(hProcess, NULL, 4096, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (!pAddr)
	{
		MessageBox("VirtualAllocExʧ��");
		return;
	}


	CString tmp, str;
	tmp.Format("���ٵ������ַ:%08X", pAddr);
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
		MessageBox("WriteProcessMemoryʧ��");
		return;
	}
	DWORD dwThreadID;
	DWORD dwParam = 0;
	HANDLE hRemoteThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)pAddr, NULL, 0, &dwThreadID);
	if (!hRemoteThread)
	{
		MessageBox("CreateRemoteThreadʧ��");
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//ȡ�ñ༭������
	CString str;
	GetDlgItemText(IDC_EDIT_Asm, str);
	if (str.IsEmpty())
	{
		MessageBox("�����������");
		return;
	}
	//SetDlgItemText(IDC_EDIT4, "");
	int pid = GetDlgItemInt(IDC_EDIT_ASM_PID);
	if (pid)
	InjectBin(pid);

}


void CAsmInJectDlg::OnBnClickedBtnexit()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	SendMessage(WM_CLOSE);
}
