// PageOne.cpp : 实现文件
//

#include "stdafx.h"
#include "AAA.h"
#include "AAADlg.h"
#include "PageOne.h"
#include "afxdialogex.h"
#include "resource.h"

//#include "AAADlg.h"

// PageOne 对话框

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

//用于缓存程序名的缓存
_TCHAR str[MAX_PATH];

//用于缓存图片的句柄
HICON hIcon[20] = { 0 };
//图片索引
int i = 0;
//向list控件插入图片的类。必须有
CImageList imList;
// PageOne 消息处理程序

//图标枚举
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
		//枚举图标
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
						//向类中添加图标
						imList.Add(hIcon[i]);
						//设置图标
						m_myThis->m_L1.SetImageList(&imList, LVSIL_SMALL);
						m_myThis->m_L1.InsertItem(0, str, i);
						break;
					}
				}
			}
			i++;
		}
	}
	m_myThis->m_L1.SetItemText(0, 1, L"正在运行");
	return TRUE;
}

void PageOne::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
	if (!isInitEnd)
	{
		return;
	}
	
}

BOOL PageOne::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	
	CRect rect;
	m_L1.GetClientRect(rect);
	
	m_L1.SetExtendedStyle(m_L1.GetExtendedStyle()/*| LVS_EX_FULLROWSELECT /*LVS_EX_GRIDLINES*/);//可选中风格
	CString str[] = { _T("任务"), _T("状态") };
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
	//创建图像列表必须做的
	imList.Create(16, 16, ILC_COLOR8, 0, 4);

	EnumWindows(PROC1, 0);
	m_myThis->isInitEnd = TRUE;
	SetTimer(0x2, 5000, NULL);//实时刷新 每1000毫秒
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
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
	
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
}


void PageOne::OnBnClickServer()
{
	// TODO:  在此添加控件通知处理程序代码
}
