// LJClean.cpp : 实现文件
//

#include "stdafx.h"
#include "SharkGuard.h"
#include "LJClean.h"
#include "afxdialogex.h"
#include "tchar.h"
#include "TlHelp32.h"
#include <psapi.h>
#include <wininet.h>
#include <UrlHist.h>
#pragma comment(lib,"Wininet.lib")
// LJClean 对话框
int fLAG;
IMPLEMENT_DYNAMIC(LJClean, CDialogEx)

LJClean::LJClean(CWnd* pParent /*=NULL*/)
	: CDialogEx(LJClean::IDD, pParent)
{
	IsScanFile = TRUE;
	m_AllFileSize = 0;
}

LJClean::~LJClean()
{
}

void LJClean::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_P2sysfile, sys);
	DDX_Control(pDX, IDC_P2record, file);
	DDX_Control(pDX, IDC_NewFile, bWn);
	DDX_Control(pDX, IDC_Cookies, cookie);
	DDX_Control(pDX, IDC_Delete, deLete);
	DDX_Control(pDX, IDC_P2_L1, Cl1);
	DDX_Control(pDX, IDC_MemoryClean, MemClear);
	DDX_Control(pDX, IDC_VsPath, vsPath);
	DDX_Control(pDX, IDC_SelectFile, vsSelect);
	DDX_Control(pDX, IDC_VsClear, vsClear);
	
}


BEGIN_MESSAGE_MAP(LJClean, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_P2sysfile, &LJClean::OnBnClickedP2sysfile)

	ON_BN_CLICKED(IDC_P2record, &LJClean::OnBnClickedP2record)
	ON_BN_CLICKED(IDC_Delete, &LJClean::OnBnClickedDelete)
	ON_NOTIFY(HDN_GETDISPINFO, 0, &LJClean::OnHdnGetdispinfoP2L1)
	ON_BN_CLICKED(IDC_NewFile, &LJClean::OnBnClickedNewfile)
	ON_BN_CLICKED(IDC_Cookies, &LJClean::OnBnClickedCookies)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_P2_L1, &LJClean::OnLvnItemchangedP2L1)
	ON_BN_CLICKED(IDC_MemoryClean, &LJClean::OnBnClickedMemoryclean)
	ON_BN_CLICKED(IDC_SelectFile, &LJClean::OnBnClickedSelectfile)
	ON_BN_CLICKED(IDC_VsClear, &LJClean::OnBnClickedVsclear)
	ON_LBN_SELCHANGE(IDC_VsPath, &LJClean::OnLbnSelchangeVspath)
END_MESSAGE_MAP()


// LJClean 消息处理程序


BOOL LJClean::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	OnBnClickedP2record();
	// TODO:  在此添加额外的初始化
	Cl1.SetBkColor(RGB(247, 247, 255));
	Cl1.SetTextColor(RGB(255, 215, 0));
	Cl1.SetTextBkColor(RGB(0, 0, 0));
	Cl1.InsertColumn(0, _T("文件路径"), 0, 320);
	Cl1.InsertColumn(1, _T("文件大小"), 0, 150);
	OnBnClickedP2record();
	Cl1.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void LJClean::OnPaint()
{


		CPaintDC dc(this);

		CRect rc;
		GetClientRect(&rc);

		//设置主窗口背景色
		dc.FillSolidRect(rc, RGB(0, 151, 209));
		//首页图片
		CDC dcMem0;
		dcMem0.CreateCompatibleDC(&dc);
		CBitmap bmpBackground0;
		bmpBackground0.LoadBitmap(IDB_BITMAP46);
		BITMAP bitmap0;
		bmpBackground0.GetBitmap(&bitmap0);
		CBitmap* pbmpPri0 = dcMem0.SelectObject(&bmpBackground0);
		dc.BitBlt(0, -10, 1000, 800, &dcMem0, 0, 0, SRCCOPY);
		CDialogEx::OnPaint();
		CDialogEx::OnPaint();
	
}

/*******************************************************************************************/
void LJClean::OnBnClickedP2sysfile()
{
	fLAG = 1;
	CString strPath;
	BOOL bSuccess = GetTempPath(MAX_PATH, strPath.GetBuffer(MAX_PATH));
	
	strPath.ReleaseBuffer();
	if (bSuccess)//得到系统临时目录
	{
		Cl1.DeleteAllItems();
		FirstShow(strPath);
	}

}

void LJClean::OnBnClickedP2record()
{
	fLAG = 2;
	CString strPath;
	BOOL bSuccess = SHGetSpecialFolderPath(NULL, strPath.GetBuffer(MAX_PATH), CSIDL_RECENT, FALSE);
	strPath.ReleaseBuffer();
	if (bSuccess)
	{
		Cl1.DeleteAllItems();
		FirstShow(strPath);
	}
	if (IsScanFile)
		return;
	SHDeleteKey(HKEY_CURRENT_USER,
		TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\RecentDocs"));

}

void LJClean::OnBnClickedNewfile()
{
	 fLAG= 3;
	CString strPath;
	if (!IsScanFile)
	{
		DeleteUrlCache(FILES);
	}
	//SHGetSpecialFolderPath 获取系统指定系统路径
	BOOL bSuccess = SHGetSpecialFolderPath(NULL,
		strPath.GetBuffer(MAX_PATH), CSIDL_INTERNET_CACHE, FALSE);
	strPath.ReleaseBuffer();
	if (bSuccess)
	{  
		Cl1.DeleteAllItems();
		FirstShow(strPath);
	}
}                                                                                                               

void LJClean::OnBnClickedCookies()
{

	CString strPath;
	DeleteUrlCache(COOKIES);
	BOOL bSuccess = SHGetSpecialFolderPath(NULL,strPath.GetBuffer(MAX_PATH), CSIDL_COOKIES, FALSE);
	strPath.ReleaseBuffer();
	if (bSuccess)
	{
		Cl1.DeleteAllItems();
		FirstShow(strPath);
	}
}

void LJClean::OnBnClickedDelete()
{
	IsScanFile = FALSE;
	m_AllFileSize = 0;
	switch (fLAG)
	{
		case 1:
				{
					 CString strPath;
					 BOOL bSuccess = GetTempPath(MAX_PATH, strPath.GetBuffer(MAX_PATH));

					 strPath.ReleaseBuffer();
					 if (bSuccess)//得到系统临时目录
					 {
						 FirstShow(strPath);
						 Cl1.DeleteAllItems();
						 MessageBox(L"BingGo!");
					 }
				}
			IsScanFile = TRUE;
			break;
		case 2:
				{
					 CString strPath;
					 BOOL bSuccess = SHGetSpecialFolderPath(NULL, strPath.GetBuffer(MAX_PATH), CSIDL_RECENT, FALSE);
					 strPath.ReleaseBuffer();
					 if (bSuccess)
					 {
						 FirstShow(strPath);
						 Cl1.DeleteAllItems();
						 MessageBox(L"BingGo!");
					 }
					 if (IsScanFile)
						 return;
					 SHDeleteKey(HKEY_CURRENT_USER,
					 TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\RecentDocs"));

				}
			IsScanFile = TRUE;
				break;
	case 3:
				{
						 CString strPath;
						 if (!IsScanFile)
						 {
							 DeleteUrlCache(FILES);
						 }
						 //SHGetSpecialFolderPath 获取系统指定系统路径
						 BOOL bSuccess = SHGetSpecialFolderPath(NULL,
							 strPath.GetBuffer(MAX_PATH), CSIDL_INTERNET_CACHE, FALSE);
						 strPath.ReleaseBuffer();
						 if (bSuccess)
						 {  //得到临时目录，并清空它.
							 FirstShow(strPath);
							 Cl1.DeleteAllItems();
							 MessageBox(L"BingGo!");
						 }
				
				}
			IsScanFile = TRUE;
				break;
	case 4:
				{
						 CString strPath;
						 DeleteUrlCache(COOKIES);
						 BOOL bSuccess = SHGetSpecialFolderPath(NULL, strPath.GetBuffer(MAX_PATH), CSIDL_COOKIES, FALSE);
						 strPath.ReleaseBuffer();
						 if (bSuccess)
						 {
							 FirstShow(strPath);
							 Cl1.DeleteAllItems();
							 MessageBox(L"BingGo!");
						 }
				}
			IsScanFile = TRUE;
				break;
	
	}

}
/**********************************************************************************************/


//遍历目录
BOOL LJClean::FirstShow(LPCTSTR szPath, BOOL bDeleteDesktopIni /*= FALSE*/, BOOL bWipeIndexDat /*= FALSE*/)
{
	WIN32_FIND_DATA wfd;
	HANDLE hFind;
	CString sFullPath;
	CString sFindFilter;
	DWORD dwAttributes = 0;

	sFindFilter = szPath;
	sFindFilter += TEXT("\\*.*");
	if ((hFind = FindFirstFile(sFindFilter, &wfd)) == INVALID_HANDLE_VALUE)
		return FALSE;
	
	do
	{
		if (_tcscmp(wfd.cFileName, TEXT(".")) == 0 ||
			_tcscmp(wfd.cFileName, TEXT("..")) == 0 ||
			(bDeleteDesktopIni == FALSE && _tcsicmp(wfd.cFileName, TEXT("desktop.ini")) == 0))
		{
			continue;
		}

		sFullPath = szPath;
		sFullPath += TEXT("\\");
		sFullPath += wfd.cFileName;
		if (IsScanFile )
		{
				//插入到List
				if (wfd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
				{
					//如果是目录，则递归调用，列举下级目录
					FirstShow(sFullPath);
					continue;
				}
				//插入文件路径
				Cl1.InsertItem(0, sFullPath);
				//插入文件大小
				CString SzTMP;
				SzTMP = ShowSize(wfd.nFileSizeLow);
				Cl1.SetItemText(0, 1, SzTMP);
				//保存所有文件的大小 用于显示有多少
				m_AllFileSize += wfd.nFileSizeLow;
				continue;
		}

		//去掉只读属性
		dwAttributes = GetFileAttributes(sFullPath);
		if (dwAttributes & FILE_ATTRIBUTE_READONLY)
		{
			dwAttributes &= ~FILE_ATTRIBUTE_READONLY;
			SetFileAttributes(sFullPath, dwAttributes);
		}
		//递归文件夹中的文件
		if (wfd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
		{
			//如果文件大小等于0说明是文件夹 递归查询
			FirstShow(sFullPath);
			//删除完文件夹中的文件，再删除文件夹
			RemoveDirectory(sFullPath);
		}
		else
		{
			if (bWipeIndexDat && _tcsicmp(wfd.cFileName, TEXT("index.dat")) == 0)
			{
				WipeShow(szPath, wfd.cFileName);
			}
			//保存所有文件的大小 用于显示有多少
			m_AllFileSize += wfd.nFileSizeLow;
			if (!DeleteFile(sFullPath))
			{
				m_AllFileSize -= wfd.nFileSizeLow;
			}
		}
	} while (FindNextFile(hFind, &wfd));
	FindClose(hFind);

	return TRUE;
}

//遍历磁盘
bool LJClean::WipeShow(LPCTSTR szDir, LPCTSTR szFile)
{
	CString sPath;
	HANDLE	hFile;
	DWORD	dwSize;
	DWORD	dwWrite;
	TCHAR	sZero[10000];
	memset(sZero, 0, 10000);

	sPath = szDir;
	sPath += TEXT("\\");
	sPath += szFile;

	hFile = CreateFile(sPath, GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return FALSE;

	dwSize = GetFileSize(hFile, NULL);

	//skip file header (actually, I don't know the file format of index.dat)
	dwSize -= 64;
	SetFilePointer(hFile, 64, NULL, FILE_BEGIN);

	while (dwSize > 0)
	{
		if (dwSize > 10000)
		{
			WriteFile(hFile, sZero, 10000, &dwWrite, NULL);
			dwSize -= 10000;
		}
		else
		{
			WriteFile(hFile, sZero, dwSize, &dwWrite, NULL);
			break;
		}
	}

	CloseHandle(hFile);
	return TRUE;
}

//转换大小
CString LJClean::ShowSize(DOUBLE dwSize)
{
	CString szSize;
	if (dwSize < 1024)
	{
		//B
		szSize.Format(_T("%d B"), (DWORD)dwSize);
		return szSize;
	}
	else if (dwSize < 1024 * 1024)
	{
		//KB
		szSize.Format(_T("%.2f KB"), ((DOUBLE)dwSize) / 1024);
		return szSize;
	}
	else if (dwSize < 1024 * 1024 * 1024)
	{
		//MB
		szSize.Format(_T("%.2f MB"), (DOUBLE)dwSize / 1024 / 1024);
		return szSize;
	}if (dwSize > 1024 * 1024 * 1024)
	{
		//GB
		szSize.Format(_T("%.2f GB"), (DOUBLE)dwSize / 1024 / 1024 / 1024);
		return szSize;
	}
	return _T("");
}

//Inet 缓存
BOOL LJClean::DeleteUrlCache(DEL_CACHE_TYPE type)
{
	BOOL bRet = FALSE;   //返回值
	HANDLE hEntry;
	LPINTERNET_CACHE_ENTRY_INFO  lpCacheEntry = NULL;
	DWORD dwEntrySize;

	//delete the files
	dwEntrySize = 0;
	//获得INTERNET_CACHE_ENTRY_INFO的大小
	hEntry = FindFirstUrlCacheEntry(NULL, NULL, &dwEntrySize);
	//分配响应大小的缓冲区
	lpCacheEntry = (LPINTERNET_CACHE_ENTRY_INFO) new TCHAR[dwEntrySize];
	//获得进入口的句柄
	hEntry = FindFirstUrlCacheEntry(NULL, lpCacheEntry, &dwEntrySize);

	if (hEntry)
	{
		do
		{
			if (type == FILES &&
				!(lpCacheEntry->CacheEntryType & COOKIE_CACHE_ENTRY))
			{
				DeleteUrlCacheEntry(lpCacheEntry->lpszSourceUrlName);
			}
			else if (type == COOKIES &&
				(lpCacheEntry->CacheEntryType & COOKIE_CACHE_ENTRY))
			{
				DeleteUrlCacheEntry(lpCacheEntry->lpszSourceUrlName);
			}
			dwEntrySize = 0;
			FindNextUrlCacheEntry(hEntry, NULL, &dwEntrySize);
			delete[] lpCacheEntry;
			lpCacheEntry = NULL;
			lpCacheEntry = (LPINTERNET_CACHE_ENTRY_INFO) new TCHAR[dwEntrySize];
		} while (FindNextUrlCacheEntry(hEntry, lpCacheEntry, &dwEntrySize));

		bRet = TRUE;
	}

	if (lpCacheEntry)
	{
		delete[] lpCacheEntry;
		lpCacheEntry = NULL;
	}
	return bRet;
}

//虚拟列表
void LJClean::OnHdnGetdispinfoP2L1(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMHDDISPINFO pDispInfo = reinterpret_cast<LPNMHDDISPINFO>(pNMHDR);
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	
	*pResult = 0;
}






void LJClean::OnLvnItemchangedP2L1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
}


void LJClean::OnBnClickedMemoryclean()
{
	//TCHAR sSs[128];
	
	UpdateData(FALSE);
	//获取清理前的内存信息
	MEMORYSTATUSEX memStatus = { sizeof(MEMORYSTATUSEX) };
	GlobalMemoryStatusEx(&memStatus);
	DOUBLE preUsedMem = (DOUBLE)(memStatus.ullTotalPhys - memStatus.ullAvailPhys) / 1024 / 1024;
	//开始清理内存
	ClearMemory();
	//获取清理后的内存信息
	GlobalMemoryStatusEx(&memStatus);
	DOUBLE afterUsedMem = (DOUBLE)(memStatus.ullTotalPhys - memStatus.ullAvailPhys) / 1024 / 1024;
	//输出清理信息
	UpdateData(FALSE);
	CString m_SsFree;
	m_SsFree.Format(_T("内存清理完毕！本次清理 : %.2f MB"), preUsedMem - afterUsedMem);
	MessageBox(L"Declear  BingGo!\n" + m_SsFree, L"BingGo!", NULL);
}

void LJClean::ClearMemory()
{
			HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
			if (hProcessSnap == INVALID_HANDLE_VALUE)
			{
				return;
			}

			PROCESSENTRY32 ProcessInfo;
			ProcessInfo.dwSize = sizeof(ProcessInfo);
			int count = 0;

			//获取系统中第一个进程的信息  
			BOOL Status = Process32First(hProcessSnap, &ProcessInfo);
			while (Status)
			{
				HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, TRUE,
					ProcessInfo.th32ProcessID);
				if (hProcess)
				{
					//设置进程工作区大小
					SetProcessWorkingSetSize(hProcess, -1, -1);
					//尽可能多的将指定进程的页面从工作区移除
					EmptyWorkingSet(hProcess);
					CloseHandle(hProcess);
				}
				//获取下一个进程的信息  
				Status = Process32Next(hProcessSnap, &ProcessInfo);
			}
}


void LJClean::OnBnClickedSelectfile()
{
	TCHAR szPath1[MAX_PATH] = {};
	BROWSEINFO bi = {};
	// 文件夹选择对话框所属窗口句柄
	bi.hwndOwner = m_hWnd;
	bi.pszDisplayName = szPath1;
	// 对话框带编辑框
	bi.ulFlags = BIF_EDITBOX;
	LPITEMIDLIST pid;
	// 返回标识文件夹路径的“PID”，用它找到文件夹路径
	pid = SHBrowseForFolder(&bi);
	SHGetPathFromIDList(pid, szPath1);
	// 把路径更新到路径显示编辑框内

	if (LB_ERR == vsPath.FindString(0, szPath1))
	{// 如果m_LISTbox里面没有这个新的文件夹路径，再添加进m_LISTbox
		vsPath.AddString(szPath1);
	}
	// 把变量内容更新到对话框
	UpdateData(FALSE);
	CoTaskMemFree(pid);

	m_vecPath.clear();
	// 获取要遍历的文件夹数目
	int nCount = vsPath.GetCount();
	for (int i = 0; i < nCount; i++)
	{
		CString test;
		// 获取ListBox控件内的文件夹路径
		vsPath.GetText(i, test);
		// 遍历文件夹内的所有文件和子文件夹
		ErgodicFile(test.GetBuffer());
	}
	// 将遍历到的要删除文件添加到ListBox内显示出来
	for (DWORD i = 0; i < m_vecPath.size(); i++)
	{
		vsPath.AddString(m_vecPath[i]);
	}
}


void LJClean::OnBnClickedVsclear()
{
	for (DWORD i = 0; i < m_vecPath.size(); i++)
	{
		DeleteFile(m_vecPath[i]);
	}
	MessageBox(L"删除成功");
	vsPath.ResetContent(); 
}

// 向文件夹末尾添加\\*，遍历所有文件
void LJClean::ErgodicFile(TCHAR szPath[MAX_PATH])
{

	CString strPath = szPath;
	strPath += L"\\*";
	WIN32_FIND_DATA fi = {};
	// 找到的文件信息放到fi里面
	HANDLE hFile = FindFirstFile(strPath, &fi);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return;
	}
	do
	{
		// 判断是否当前目录或上级目录
		if (!lstrcmp(fi.cFileName, L".") || !lstrcmp(fi.cFileName, L".."))
		{
			continue;
		}
		// 判断是否是文件夹，若是，递归遍历
		if (fi.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			CString strDIr = szPath;
			strDIr += L"\\";
			strDIr += fi.cFileName;
			ErgodicFile(strDIr.GetBuffer());
			continue;
		}
		// 获取文件扩展名，用于判断是否垃圾文件后缀
		TCHAR *p = PathFindExtension(fi.cFileName);
		// Find返回查找的子串p在m_Delete中的索引，若找不到返回-1
		CString  m_UpdataEDIT(_T(".obj.tlog.lastbuildstate.idb.pdb.pch.res.ilk.exe.sdf.ipch.log"));
		if (-1 == m_UpdataEDIT.Find(p))
		{
			continue;
		}
		// 经过筛选，找到要删除的文件名和之前的路径构造成完整路径
		CString strDIr = szPath;
		strDIr += L"\\";
		strDIr += fi.cFileName;
		// 保存进路径向量里
		m_vecPath.push_back(strDIr);
	} while (FindNextFile(hFile, &fi));

}


void LJClean::OnLbnSelchangeVspath()
{
	// TODO:  在此添加控件通知处理程序代码
}
