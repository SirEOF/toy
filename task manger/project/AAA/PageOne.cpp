// PageOne.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AAA.h"
#include "AAADlg.h"
#include "PageOne.h"
#include "afxdialogex.h"
#include "resource.h"

//#include "AAADlg.h"

// PageOne �Ի���

IMPLEMENT_DYNAMIC(PageOne, CDialogEx)
PageOne* PageOne::m_myThis = NULL;
PageOne::PageOne(CWnd* pParent /*=NULL*/)
	: CDialogEx(PageOne::IDD, pParent)
{
	isInitEnd = FALSE;
	m_myThis = this;
}

PageOne::~PageOne()
{
}

void PageOne::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LT1, m_L1);
}


BEGIN_MESSAGE_MAP(PageOne, CDialogEx)
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LT1, &PageOne::OnLvnItemchangedLt1)
	ON_BN_CLICKED(IDC_NewTask, &PageOne::OnBnClickServer)
END_MESSAGE_MAP()

//���ڻ���������Ļ���
_TCHAR str[MAX_PATH];

//���ڻ���ͼƬ�ľ��
HICON hIcon[20] = { 0 };
//ͼƬ����
int i = 0;
//��list�ؼ�����ͼƬ���ࡣ������
CImageList imList;
// PageOne ��Ϣ�������

//ͼ��ö��
BOOL CALLBACK PageOne::PROC1(HWND hwnd, LPARAM lparam)
{
	if (!::IsWindowVisible(hwnd))
	{
		return TRUE;
	}
	if (!::GetWindowText(hwnd, str, MAX_PATH))
	{
		return TRUE;
	}
	else
	{
		//ö��ͼ��
		hIcon[i] = (HICON)GetWindowLong(hwnd, GCL_HICON);

		if (hIcon[i] == NULL)
		{
			hIcon[i] = (HICON)GetClassLong(hwnd, GCL_HICON);
		}
		if (hIcon[i] == NULL)
		{
			hIcon[i] = (HICON)::SendMessage(hwnd, WM_GETICON, ICON_SMALL, 0);
		}
		if (hIcon[i] == NULL)
		{
			hIcon[i] = (HICON)::SendMessage(hwnd, WM_GETICON, ICON_BIG, 0);
		}
		if (hIcon[i] != NULL)
		{
			if (lstrcmp(_T("Program Manager"), str) != 0)
			{
				for (; i < 20; i++)
				{
					if (hIcon[i] != NULL)
					{
						//���������ͼ��
						imList.Add(hIcon[i]);
						//����ͼ��
						m_myThis->m_L1.SetImageList(&imList, LVSIL_SMALL);
						m_myThis->m_L1.InsertItem(0, str, i);
						break;
					}
				}
			}
			i++;
		}
	}
	m_myThis->m_L1.SetItemText(0, 1, L"��������");
	return TRUE;
}

void PageOne::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������
	if (!isInitEnd)
	{
		return;
	}
	
}

BOOL PageOne::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	
	CRect rect;
	m_L1.GetClientRect(rect);
	
	m_L1.SetExtendedStyle(m_L1.GetExtendedStyle()/*| LVS_EX_FULLROWSELECT /*LVS_EX_GRIDLINES*/);//��ѡ�з��
	CString str[] = { _T("����"), _T("״̬") };
	for (int i = 0; i < sizeof(str) / sizeof(str[0]); i++)
	{
		if (i == 0)
		{
			m_L1.InsertColumn(i, str[i], LVCFMT_LEFT, 250);
		}
		else
		{
			m_L1.InsertColumn(i, str[i], LVCFMT_LEFT, rect.Width() / 2);
		}
	}
	//����ͼ���б��������
	imList.Create(16, 16, ILC_COLOR8, 0, 4);

	EnumWindows(PROC1, 0);
	m_myThis->isInitEnd = TRUE;
	SetTimer(0x2, 5000, NULL);//ʵʱˢ�� ÿ1000����
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

void PageOne::OnTimer(UINT_PTR nIDEvent)
{
	m_L1.DeleteAllItems();
	imList.SetImageCount(0);
	memset(hIcon, NULL, 20 * sizeof(HICON));
	i = 0;
	EnumWindows(PROC1, 0);
}







void PageOne::OnLvnItemchangedLt1(NMHDR *pNMHDR, LRESULT *pResult)
{
	
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void PageOne::OnBnClickServer()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
