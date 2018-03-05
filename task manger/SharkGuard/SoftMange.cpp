// SoftMange.cpp : 实现文件
//

#include "stdafx.h"
#include "SharkGuard.h"
#include "SoftMange.h"
#include "afxdialogex.h"


// SoftMange 对话框

IMPLEMENT_DYNAMIC(SoftMange, CDialogEx)

SoftMange::SoftMange(CWnd* pParent /*=NULL*/)
	: CDialogEx(SoftMange::IDD, pParent)
{
	m_Select = -1;
}

SoftMange::~SoftMange()
{
}

void SoftMange::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_P3_List, MFCList);
}


BEGIN_MESSAGE_MAP(SoftMange, CDialogEx)
	ON_WM_PAINT()
	ON_NOTIFY(NM_RCLICK, IDC_P3_List, &SoftMange::OnRclickNinthlist)
	
	ON_COMMAND(ID_DownLoad, &SoftMange::OnDownload)
	ON_COMMAND(ID_Fresh, &SoftMange::OnFresh)
	ON_COMMAND(ID_OpenPos, &SoftMange::OnOpenpos)
END_MESSAGE_MAP()


// SoftMange 消息处理程序


BOOL SoftMange::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//初始化列表
	MFCList.AddColumn(4,
		_T("名称"),
		_T("发布者"),
		_T("安装时间"),
		_T("版本"));
	MFCList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//获取软件信息
	GetSoftwareInfo();
	MFCList.SetBkColor(RGB(0, 0, 0));
	MFCList.SetTextColor(RGB(255, 215, 0));
	MFCList.SetTextBkColor(RGB(0, 0, 0));
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void SoftMange::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect rc;
	GetClientRect(&rc);

	//设置主窗口背景色
	dc.FillSolidRect(rc, RGB(0, 151, 209));
	//首页图片
	CDC dcMem0;
	dcMem0.CreateCompatibleDC(&dc);
	CBitmap bmpBackground0;
	bmpBackground0.LoadBitmap(IDB_BITMAP22);
	BITMAP bitmap0;
	bmpBackground0.GetBitmap(&bitmap0);
	CBitmap* pbmpPri0 = dcMem0.SelectObject(&bmpBackground0);
	dc.BitBlt(0, -10, 1000, 800, &dcMem0, 0, 0, SRCCOPY);
	CDialogEx::OnPaint();
	CDialogEx::OnPaint();

}

void SoftMange::GetSoftwareInfo()
{
	MFCList.DeleteAllItems();
	m_vecSoftInfo.clear();
	SOFTINFO stcSoftInfo = { 0 };
	HKEY RootKey;            // 主键
	LPCTSTR lpSubKey;        // 子键名称
	HKEY hkResult;           // 将要打开键的句柄 
	HKEY hkRKey;
	LONG lReturn;            // 记录读取注册表是否成功
	CString strBuffer;
	CString strMidReg;

	DWORD index = 0;
	TCHAR szKeyName[255] = { 0 };        // 注册表项名称
	DWORD dwKeyLen = 255;
	DWORD dwNameLen = 255;
	DWORD dwType = 0;

	RootKey = HKEY_LOCAL_MACHINE;
	lpSubKey = Is64() ? Win64PATH : Win32PATH;

	lReturn = RegOpenKeyEx(RootKey, lpSubKey, 0,
		KEY_ALL_ACCESS, &hkResult);
	if (lReturn == ERROR_SUCCESS)
	{
		DWORD index = 0;
		DWORD ListIndex = 0;
		while (ERROR_NO_MORE_ITEMS !=
			RegEnumKeyEx(hkResult, index, szKeyName, &dwKeyLen,
			0, NULL, NULL, NULL))
		{
			strBuffer.Format(_T("%s"), szKeyName);
			if (!strBuffer.IsEmpty())
			{
				strMidReg = (CString)lpSubKey + _T("\\") + strBuffer;

				if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, strMidReg,
					0, KEY_ALL_ACCESS, &hkRKey) == ERROR_SUCCESS)
				{
					RegQueryValueEx(hkRKey, _T("DisplayName"),
						0, &dwType, (LPBYTE)stcSoftInfo.szSoftName, &dwNameLen);
					dwNameLen = 255;

					RegQueryValueEx(hkRKey, _T("DisplayVersion"),
						0, &dwType, (LPBYTE)stcSoftInfo.szSoftVer, &dwNameLen);
					dwNameLen = 255;

					RegQueryValueEx(hkRKey, _T("InstallLocation"),
						0, &dwType, (LPBYTE)stcSoftInfo.strSoftInsPath, &dwNameLen);
					dwNameLen = 255;

					RegQueryValueEx(hkRKey, _T("Publisher"),
						0, &dwType, (LPBYTE)stcSoftInfo.strSoftVenRel, &dwNameLen);
					dwNameLen = 255;

					RegQueryValueEx(hkRKey, _T("UninstallString"),
						0, &dwType, (LPBYTE)stcSoftInfo.strSoftUniPath, &dwNameLen);
					dwNameLen = 255;

					RegQueryValueEx(hkRKey, _T("InstallDate"),
						0, &dwType, (LPBYTE)stcSoftInfo.szSoftData, &dwNameLen);
					if (stcSoftInfo.szSoftData[0])
					{
						stcSoftInfo.szSoftData[9] = stcSoftInfo.szSoftData[7];
						stcSoftInfo.szSoftData[8] = stcSoftInfo.szSoftData[6];
						stcSoftInfo.szSoftData[7] = '-';
						stcSoftInfo.szSoftData[6] = stcSoftInfo.szSoftData[5];
						stcSoftInfo.szSoftData[5] = stcSoftInfo.szSoftData[4];
						stcSoftInfo.szSoftData[4] = '-';
					}
					dwNameLen = 255;
					//保存数据
					if (stcSoftInfo.szSoftName[0] != '\0')
					{
						m_vecSoftInfo.push_back(stcSoftInfo);

						MFCList.AddItem(ListIndex++, 4,
							stcSoftInfo.szSoftName,
							stcSoftInfo.strSoftVenRel,
							stcSoftInfo.szSoftData,
							stcSoftInfo.szSoftVer);
					}
					index++;
				}
				dwKeyLen = 255;
				memset(szKeyName, 0, 255);
				memset(&stcSoftInfo, 0, sizeof(SOFTINFO));
			}
		}
		RegCloseKey(hkResult);
	}
}
// 判断系统是否是64位
BOOL SoftMange::Is64()
{
	SYSTEM_INFO si;
	GetNativeSystemInfo(&si);
	if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 ||
		si.wProcessorArchitecture != PROCESSOR_ARCHITECTURE_IA64)
	{
		//64 位操作系统
		return TRUE;
	}
	else
	{
		// 32 位操作系统
		return FALSE;
	}
	return FALSE;
}
//菜单
void SoftMange::OnRclickNinthlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	//防止在空白区点击弹出菜单  
	int n = pNMItemActivate->iItem;//选择了第几行
	if (n != -1)
	{
		//保存所选软件的卸载命令
		strTemp = MFCList.GetItemText(n, 0);
		for (DWORD i = 0; i < m_vecSoftInfo.size(); i++)
		{
			if (strTemp == m_vecSoftInfo[i].szSoftName)
			{
				m_Select = i;
				break;
			}
		}
		strTemp.Empty();
		//下面的这段代码, 不单单适应于ListCtrl  
		CMenu menu, *pPopup;
		menu.LoadMenu(IDR_MENU1);
		pPopup = menu.GetSubMenu(0);
		CPoint myPoint;
		ClientToScreen(&myPoint);
		GetCursorPos(&myPoint);
		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);
	}
	*pResult = 0;
}

//打开所在位置
BOOL OpenFolderAndSelectFile(TCHAR* szPath)
{
	LPSHELLFOLDER pDesktopFolder;
	if (SUCCEEDED(SHGetDesktopFolder(&pDesktopFolder)))
	{
		LPITEMIDLIST     pidl;
		ULONG             chEaten;
		ULONG             dwAttributes;
		HRESULT             hr;

		hr = pDesktopFolder->ParseDisplayName(
			NULL, NULL, szPath, &chEaten, &pidl, &dwAttributes);
		if (FAILED(hr))
		{
			pDesktopFolder->Release();
			return FALSE;
		}
		LPCITEMIDLIST pidlFolder = pidl;

		CoInitialize(NULL);
		hr = SHOpenFolderAndSelectItems(pidl, 0, NULL, 0);

		pDesktopFolder->Release();

		if (hr == S_OK)
		{
			return TRUE;
		}
	}
	return FALSE;
}



void SoftMange::OnDownload()
{
	if (m_Select == -1)
	{
		return;
	}
	ShellExecute(NULL, _T("open"),
		m_vecSoftInfo[m_Select].strSoftUniPath, NULL, NULL, SW_SHOWNORMAL);
}


void SoftMange::OnFresh()
{
	GetSoftwareInfo();
}


void SoftMange::OnOpenpos()
{
	if (!m_vecSoftInfo[m_Select].strSoftInsPath[0])
	{
		return;
	}
	//打开文件
	OpenFolderAndSelectFile(m_vecSoftInfo[m_Select].strSoftInsPath);
}
