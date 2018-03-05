// sViewHeap.cpp : 实现文件
//

#include "stdafx.h"
#include "AAA.h"
#include "sViewHeap.h"
#include "afxdialogex.h"
#include <TlHelp32.h>
#include <psapi.h>
#include "PageTwo.h"
#include <locale.h>
#define WM_HEAPget WM_USER+1002
// sViewHeap 对话框

sViewHeap op;
sViewHeap* sViewHeap::pthis = 0;

IMPLEMENT_DYNAMIC(sViewHeap, CDialogEx)

sViewHeap::sViewHeap(CWnd* pParent /*=NULL*/)
	: CDialogEx(sViewHeap::IDD, pParent)
{
	pthis = this;
}

sViewHeap::~sViewHeap()
{
}

void sViewHeap::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_ViewHeaP, m_Heap);
	DDX_Control(pDX, IDC_ViewHeaP, m_Heap);
}


BEGIN_MESSAGE_MAP(sViewHeap, CDialogEx)
	ON_MESSAGE(WM_HEAPget, GetHeapProID)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_ViewHeaP, &sViewHeap::OnLvnItemchangedViewheap)
END_MESSAGE_MAP()


LRESULT sViewHeap::GetHeapProID(WPARAM wParam, LPARAM lParam)
{
	hhnd= lParam;
	return 1;
}



// sViewHeap 消息处理程序
void sViewHeap:: SetEnvironment()
{


	if (!flag)
	{
		DWORD Style = m_Heap.GetExtendedStyle();
		m_Heap.SetExtendedStyle(Style| LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
		CString str[] = { _T(""), _T("ID"), _T("位置"), _T("大小"), };
		m_Heap.InsertColumn(0, str[0], LVCFMT_LEFT, 100);
		m_Heap.InsertColumn(1, str[1], LVCFMT_LEFT, 100);
		m_Heap.InsertColumn(2, str[2], LVCFMT_LEFT, 120);
		m_Heap.InsertColumn(3, str[3], LVCFMT_LEFT, 100);

		m_Heap.DeleteColumn(0);
		flag = TRUE;
	}

}

	
	


void sViewHeap::ShowHeap(UINT PID)
{
	//DWORD PID = *(PDWORD)LPARAM;
	HEAPLIST32 stcHeap32 = { 0 };
	stcHeap32.dwSize = sizeof(HEAPLIST32);
	HANDLE hHeap = INVALID_HANDLE_VALUE;
	
	
	hHeap = CreateToolhelp32Snapshot(TH32CS_SNAPHEAPLIST, (DWORD)PID);
	if (hHeap == INVALID_HANDLE_VALUE)
		return;
	
	Heap32ListFirst(hHeap, &stcHeap32);

	
	int a = 0;
	do
	{
		CString  DAT = {};
		HEAPENTRY32 stcHeapEntry = { 0 };
		stcHeapEntry.dwSize = sizeof(HEAPENTRY32);
		Heap32First(&stcHeapEntry, stcHeap32.th32ProcessID, stcHeap32.th32HeapID);
		m_Heap.InsertItem(a, L"");

		DAT.Format(L"ID:%u ", stcHeap32.th32HeapID);
		m_Heap.SetItemText(a,0,DAT);

		DAT.Format(L"位置:%010X ", stcHeapEntry.dwAddress);
		m_Heap.SetItemText(a,1,DAT);

		DAT.Format(L"大小:%u ", stcHeapEntry.dwBlockSize);
		m_Heap.SetItemText(a,2,DAT);
		
		a++;

	} while (Heap32ListNext(hHeap, &stcHeap32));
	CloseHandle(hHeap);
	return;	
}
/*
void sViewHeap::Show()
{
	int a = 0;
	do
	{
		HEAPENTRY32 stcHeapEntry = { 0 };
		stcHeapEntry.dwSize = sizeof(HEAPENTRY32);
		Heap32First(&stcHeapEntry, stcHeap32.th32ProcessID, stcHeap32.th32HeapID);

		DAT.Format(L"ID:%u ", stcHeap32.th32HeapID);
		m_Heap.SetItemText(a, 1, DAT);

		DAT.Format(L"位置:%010X ", stcHeapEntry.dwAddress);
		m_Heap.SetItemText(a, 2, DAT);

		DAT.Format(L"大小:%u ", stcHeapEntry.dwBlockSize);
		m_Heap.SetItemText(a, 3, DAT);

		stcHeapEntry.dwSize = sizeof(HEAPENTRY32);
		DAT += L"\r\n";

		stcHeap32.dwSize = sizeof(HEAPLIST32);
		a++;

	} while (Heap32ListNext(hHeap, &stcHeap32));


}
*/

BOOL sViewHeap::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetEnvironment();
	ShowHeap(m_HeapId);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void sViewHeap::OnLvnItemchangedViewheap(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
}
