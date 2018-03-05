// DlgView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AAA.h"
#include "DlgView.h"
#include "afxdialogex.h"


// DlgView �Ի���

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


// DlgView ��Ϣ�������


// CEnumWindow ��Ϣ�������


void DlgView::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
			This->m_EnumWindow.SetItemText(i, 2, L"��ʾ");
		else
			This->m_EnumWindow.SetItemText(i, 2, L"����");
	}

	return TRUE;
}

BOOL DlgView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	DWORD dwStyle = m_EnumWindow.GetExtendedStyle();
	m_EnumWindow.SetExtendedStyle(dwStyle | LVS_EX_FULLROWSELECT);
	CRect rc;
	m_EnumWindow.GetClientRect(rc);
	DWORD dwWidth = rc.Width() / 12;
	m_EnumWindow.InsertColumn(0, L"��������", 0, dwWidth * 6);
	m_EnumWindow.InsertColumn(1, L"��������", 0, dwWidth * 4);
	m_EnumWindow.InsertColumn(2, L"����״̬", 0, dwWidth * 2);
	ShowWindows();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void DlgView::ShowWindows()
{
	m_EnumWindow.DeleteAllItems();
	EnumWindows(WndEnumProc1, (LPARAM)this);
}


