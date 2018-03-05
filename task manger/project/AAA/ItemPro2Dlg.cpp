// ItemPro2Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AAA.h"
#include "ItemPro2Dlg.h"
#include "afxdialogex.h"
#include <TlHelp32.h>

// CItemPro2Dlg 对话框

IMPLEMENT_DYNAMIC(CItemPro2Dlg, CDialogEx)
CItemPro2Dlg*  CItemPro2Dlg::pthis = 0;
CItemPro2Dlg::CItemPro2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CItemPro2Dlg::IDD, pParent)
{
	pthis = this;
}

CItemPro2Dlg::~CItemPro2Dlg()
{
}

void CItemPro2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ItemProD, M_FuckThread);
}


BEGIN_MESSAGE_MAP(CItemPro2Dlg, CDialogEx)
	ON_NOTIFY(NM_RCLICK, IDC_ItemProD, &CItemPro2Dlg::OnNMRClickItemprod)
//	ON_NOTIFY(NM_CLICK, IDC_ItemProD, &CItemPro2Dlg::OnNMClickItemprod)
END_MESSAGE_MAP()


// CItemPro2Dlg 消息处理程序







BOOL CItemPro2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	DWORD dwstyle = M_FuckThread.GetExtendedStyle();
	//m_list.SetExtendedStyle(dwstyle | LVS_EX_FULLROWSELECT);
	CRect rc;
	M_FuckThread.SetParent(this);
	CWnd * TMP = M_FuckThread.GetParent();
	M_FuckThread.GetClientRect(rc);


	M_FuckThread.InsertColumn(0, L"", 0, 100);
	M_FuckThread.InsertColumn(0, L"所属进程", 0, 50);
	M_FuckThread.InsertColumn(1, L"线程ID", 0, 50);
	M_FuckThread.InsertColumn(2, L"优先级", 0, 50);
	M_FuckThread.InsertColumn(3, L"运行状态", 0, 50);
	_beginthread(ShowThread, 0, 0);
	//ShowThread(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CItemPro2Dlg::ShowThread(void *temp)
{
	pthis->M_FuckThread.DeleteAllItems();
	HANDLE hThread = 0;
	hThread = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (hThread == INVALID_HANDLE_VALUE)
		return;
	THREADENTRY32 stcTe32 = { sizeof(THREADENTRY32) };
	Thread32First(hThread, &stcTe32);
	int i = 0;
	CString Temp;
	do
	{
		if (stcTe32.th32ThreadID)
		{
			pthis->M_FuckThread.InsertItem(i, L"");
			Temp.Format(L"%8d", stcTe32.th32ThreadID);
			pthis->M_FuckThread.SetItemText(i, 1, Temp);
			Temp.Format(L"%2d", stcTe32.tpBasePri);
			pthis->M_FuckThread.SetItemText(i, 2, Temp);
			HANDLE hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
			if (hProcess == INVALID_HANDLE_VALUE)
				return;
			PROCESSENTRY32 stcpro32 = { sizeof(PROCESSENTRY32) };
			Process32First(hProcess, &stcpro32);
			do
			{
				if (stcpro32.th32ProcessID == stcTe32.th32OwnerProcessID)
				{
					pthis->M_FuckThread.SetItemText(i, 0, stcpro32.szExeFile);
					break;
				}
			} while (Process32Next(hProcess, &stcpro32));
			HANDLE Flag = OpenThread(THREAD_SUSPEND_RESUME, FALSE, stcTe32.th32ThreadID);
			if (Flag)
			{//打开成功
				QWORD dwIsSuspend = ResumeThread(Flag);
				if (dwIsSuspend == 0)
					pthis->M_FuckThread.SetItemText(i, 3, L"运行");
				else if (dwIsSuspend != -1)
				{
					SuspendThread(Flag);
					pthis->M_FuckThread.SetItemText(i, 3, L"已挂起");
				}
				else
					pthis->M_FuckThread.SetItemText(i, 3, L"  —");
			}
			else
				pthis->M_FuckThread.SetItemText(i, 3, L"  —");
			i++;
		}
	} while (Thread32Next(hThread, &stcTe32));
	return;
}




void CItemPro2Dlg::OnNMRClickItemprod(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	CPoint point;
	GetCursorPos(&point);//得到鼠标基于窗口坐标
	CMenu menuTray;
	menuTray.LoadMenu(IDR_DlgEndPro);
	CMenu * subMenu = menuTray.GetSubMenu(0);
	int id = subMenu->TrackPopupMenu(TPM_RETURNCMD|TPM_LEFTBUTTON | TPM_RIGHTBUTTON, point.x, point.y, this);

	switch (id)
	{
	case ID_Mpick:
	{//挂起线程
				   DWORD dwThread = 0;
				   swscanf_s(M_FuckThread.GetItemText(pNMItemActivate->iItem, 1), L"%d", &dwThread);
				   HANDLE hThread = OpenThread(THREAD_SUSPEND_RESUME, FALSE, dwThread);
				   if (hThread == NULL)
				   {
					   MessageBox(L"错误", 0);
					   return;
				   }
				   dwThread = SuspendThread(hThread);
				   if (dwThread == -1)
				   {
					   MessageBox(L"错误", 0);
					   return;
				   }
				   M_FuckThread.SetItemText(pNMItemActivate->iItem, 3, L"已挂起");
				   break;
	}
	case ID_Mre:
	{ // 恢复线程
				 if (M_FuckThread.GetItemText(pNMItemActivate->iItem, 3) == L"—" ||
					 M_FuckThread.GetItemText(pNMItemActivate->iItem, 3) == L"已挂起")
				 {
					 DWORD dwThread = 0;
					 swscanf_s(M_FuckThread.GetItemText(pNMItemActivate->iItem, 1), L"%d", &dwThread);
					 HANDLE hThread = OpenThread(THREAD_SUSPEND_RESUME, FALSE, dwThread);
					 dwThread = ResumeThread(hThread);
					 if (dwThread == -1)
					 {
						 MessageBox(L"唤醒失败", 0);
						 return;
					 }
					 else if (dwThread == 1 || dwThread == 0)
						 M_FuckThread.SetItemText(pNMItemActivate->iItem, 3, L"运行");
				 }
				 else
					 MessageBox(L"线程未被挂起");
				 break;
	}

	case ID_Mend:
	{				// 结束线程
				  DWORD dwThread = 0;
				  swscanf_s(M_FuckThread.GetItemText(pNMItemActivate->iItem, 1), L"%d", &dwThread);
				  HANDLE hThread = OpenThread(THREAD_TERMINATE, FALSE, dwThread);
				  BOOL Flag = TerminateThread(hThread, 1);
				  if (Flag)
				  {
					  CloseHandle(hThread);
					  M_FuckThread.SetItemText(pNMItemActivate->iItem, 3, L"已终止");
				  }
				  else
					  MessageBox(L"结束线程失败", 0);
	}
	case ID_Mfresh:
		MessageBox(L"结束线程失败", 0);
		break;
	default:
		break;
	}

	//AfxMessageBox(L"123r3r4");
	*pResult = 0;
}


//void CItemPro2Dlg::OnNMClickItemprod(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
//	// TODO:  在此添加控件通知处理程序代码
//	*pResult = 0;
//}
