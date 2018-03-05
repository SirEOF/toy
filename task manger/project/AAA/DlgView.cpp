// DlgView.cpp : 实现文件
//

#include "stdafx.h"
#include "AAA.h"
#include "DlgView.h"
#include "afxdialogex.h"


// DlgView 对话框

IMPLEMENT_DYNAMIC(DlgView, CDialogEx)

int DlgView::flag = 0;
DlgView::DlgView(CWnd* pParent /*=NULL*/)
	: CDialogEx(DlgView::IDD, pParent)
{

}

DlgView::~DlgView()
{
}

void DlgView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_WindowList, m_EnumWindow);
}


BEGIN_MESSAGE_MAP(DlgView, CDialogEx)
	//ON_BN_CLICKED(IDOK, &DlgView::OnBnClickedOk)
	ON_MESSAGE(WM_SHOWWINDOWS, OnProcName)
END_MESSAGE_MAP()


// DlgView 消息处理程序


// CEnumWindow 消息处理程序


void DlgView::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}





LRESULT DlgView::OnProcName(WPARAM wParam, LPARAM lParam)
{
	ShowWindows();
	return 0;
}

BOOL CALLBACK DlgView::WndEnumProc1(HWND hWnd, LPARAM lParam)
{
	static int i = 0;
	WCHAR szName[MAXBYTE];
	WCHAR szClass[MAXBYTE];
	DlgView *This = (DlgView *)lParam;
	::GetWindowText(hWnd, szName, MAXBYTE);
	CString temp = szName;
	if (flag)
	{
		if (!::IsWindowVisible(hWnd))
		{
			return TRUE;
		}
	}
	if (temp != L""&&temp != L"Default IME"&&temp != L"MSCTFIME UI")
	{
		This->m_EnumWindow.InsertItem(i, temp);
		GetClassName(hWnd, szClass, MAXBYTE);
		This->m_EnumWindow.SetItemText(i, 1, szClass);
		if (::IsWindowVisible(hWnd))
			This->m_EnumWindow.SetItemText(i, 2, L"显示");
		else
			This->m_EnumWindow.SetItemText(i, 2, L"隐藏");
	}

	return TRUE;
}

BOOL DlgView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	DWORD dwStyle = m_EnumWindow.GetExtendedStyle();
	m_EnumWindow.SetExtendedStyle(dwStyle | LVS_EX_FULLROWSELECT);
	CRect rc;
	m_EnumWindow.GetClientRect(rc);
	DWORD dwWidth = rc.Width() / 12;
	m_EnumWindow.InsertColumn(0, L"窗口名称", 0, dwWidth * 6);
	m_EnumWindow.InsertColumn(1, L"窗口类名", 0, dwWidth * 4);
	m_EnumWindow.InsertColumn(2, L"窗口状态", 0, dwWidth * 2);
	ShowWindows();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void DlgView::ShowWindows()
{
	m_EnumWindow.DeleteAllItems();
	EnumWindows(WndEnumProc1, (LPARAM)this);
}


