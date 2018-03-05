// LJClean.cpp : ʵ���ļ�
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
// LJClean �Ի���
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


// LJClean ��Ϣ�������


BOOL LJClean::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	OnBnClickedP2record();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	Cl1.SetBkColor(RGB(247, 247, 255));
	Cl1.SetTextColor(RGB(255, 215, 0));
	Cl1.SetTextBkColor(RGB(0, 0, 0));
	Cl1.InsertColumn(0, _T("�ļ�·��"), 0, 320);
	Cl1.InsertColumn(1, _T("�ļ���С"), 0, 150);
	OnBnClickedP2record();
	Cl1.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

void LJClean::OnPaint()
{


		CPaintDC dc(this);

		CRect rc;
		GetClientRect(&rc);

		//���������ڱ���ɫ
		dc.FillSolidRect(rc, RGB(0, 151, 209));
		//��ҳͼƬ
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
	if (bSuccess)//�õ�ϵͳ��ʱĿ¼
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
	//SHGetSpecialFolderPath ��ȡϵͳָ��ϵͳ·��
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
					 if (bSuccess)//�õ�ϵͳ��ʱĿ¼
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
						 //SHGetSpecialFolderPath ��ȡϵͳָ��ϵͳ·��
						 BOOL bSuccess = SHGetSpecialFolderPath(NULL,
							 strPath.GetBuffer(MAX_PATH), CSIDL_INTERNET_CACHE, FALSE);
						 strPath.ReleaseBuffer();
						 if (bSuccess)
						 {  //�õ���ʱĿ¼���������.
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


//����Ŀ¼
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
				//���뵽List
				if (wfd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
				{
					//�����Ŀ¼����ݹ���ã��о��¼�Ŀ¼
					FirstShow(sFullPath);
					continue;
				}
				//�����ļ�·��
				Cl1.InsertItem(0, sFullPath);
				//�����ļ���С
				CString SzTMP;
				SzTMP = ShowSize(wfd.nFileSizeLow);
				Cl1.SetItemText(0, 1, SzTMP);
				//���������ļ��Ĵ�С ������ʾ�ж���
				m_AllFileSize += wfd.nFileSizeLow;
				continue;
		}

		//ȥ��ֻ������
		dwAttributes = GetFileAttributes(sFullPath);
		if (dwAttributes & FILE_ATTRIBUTE_READONLY)
		{
			dwAttributes &= ~FILE_ATTRIBUTE_READONLY;
			SetFileAttributes(sFullPath, dwAttributes);
		}
		//�ݹ��ļ����е��ļ�
		if (wfd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
		{
			//����ļ���С����0˵�����ļ��� �ݹ��ѯ
			FirstShow(sFullPath);
			//ɾ�����ļ����е��ļ�����ɾ���ļ���
			RemoveDirectory(sFullPath);
		}
		else
		{
			if (bWipeIndexDat && _tcsicmp(wfd.cFileName, TEXT("index.dat")) == 0)
			{
				WipeShow(szPath, wfd.cFileName);
			}
			//���������ļ��Ĵ�С ������ʾ�ж���
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

//��������
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

//ת����С
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

//Inet ����
BOOL LJClean::DeleteUrlCache(DEL_CACHE_TYPE type)
{
	BOOL bRet = FALSE;   //����ֵ
	HANDLE hEntry;
	LPINTERNET_CACHE_ENTRY_INFO  lpCacheEntry = NULL;
	DWORD dwEntrySize;

	//delete the files
	dwEntrySize = 0;
	//���INTERNET_CACHE_ENTRY_INFO�Ĵ�С
	hEntry = FindFirstUrlCacheEntry(NULL, NULL, &dwEntrySize);
	//������Ӧ��С�Ļ�����
	lpCacheEntry = (LPINTERNET_CACHE_ENTRY_INFO) new TCHAR[dwEntrySize];
	//��ý���ڵľ��
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

//�����б�
void LJClean::OnHdnGetdispinfoP2L1(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMHDDISPINFO pDispInfo = reinterpret_cast<LPNMHDDISPINFO>(pNMHDR);
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	
	*pResult = 0;
}






void LJClean::OnLvnItemchangedP2L1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void LJClean::OnBnClickedMemoryclean()
{
	//TCHAR sSs[128];
	
	UpdateData(FALSE);
	//��ȡ����ǰ���ڴ���Ϣ
	MEMORYSTATUSEX memStatus = { sizeof(MEMORYSTATUSEX) };
	GlobalMemoryStatusEx(&memStatus);
	DOUBLE preUsedMem = (DOUBLE)(memStatus.ullTotalPhys - memStatus.ullAvailPhys) / 1024 / 1024;
	//��ʼ�����ڴ�
	ClearMemory();
	//��ȡ�������ڴ���Ϣ
	GlobalMemoryStatusEx(&memStatus);
	DOUBLE afterUsedMem = (DOUBLE)(memStatus.ullTotalPhys - memStatus.ullAvailPhys) / 1024 / 1024;
	//���������Ϣ
	UpdateData(FALSE);
	CString m_SsFree;
	m_SsFree.Format(_T("�ڴ�������ϣ��������� : %.2f MB"), preUsedMem - afterUsedMem);
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

			//��ȡϵͳ�е�һ�����̵���Ϣ  
			BOOL Status = Process32First(hProcessSnap, &ProcessInfo);
			while (Status)
			{
				HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, TRUE,
					ProcessInfo.th32ProcessID);
				if (hProcess)
				{
					//���ý��̹�������С
					SetProcessWorkingSetSize(hProcess, -1, -1);
					//�����ܶ�Ľ�ָ�����̵�ҳ��ӹ������Ƴ�
					EmptyWorkingSet(hProcess);
					CloseHandle(hProcess);
				}
				//��ȡ��һ�����̵���Ϣ  
				Status = Process32Next(hProcessSnap, &ProcessInfo);
			}
}


void LJClean::OnBnClickedSelectfile()
{
	TCHAR szPath1[MAX_PATH] = {};
	BROWSEINFO bi = {};
	// �ļ���ѡ��Ի����������ھ��
	bi.hwndOwner = m_hWnd;
	bi.pszDisplayName = szPath1;
	// �Ի�����༭��
	bi.ulFlags = BIF_EDITBOX;
	LPITEMIDLIST pid;
	// ���ر�ʶ�ļ���·���ġ�PID���������ҵ��ļ���·��
	pid = SHBrowseForFolder(&bi);
	SHGetPathFromIDList(pid, szPath1);
	// ��·�����µ�·����ʾ�༭����

	if (LB_ERR == vsPath.FindString(0, szPath1))
	{// ���m_LISTbox����û������µ��ļ���·��������ӽ�m_LISTbox
		vsPath.AddString(szPath1);
	}
	// �ѱ������ݸ��µ��Ի���
	UpdateData(FALSE);
	CoTaskMemFree(pid);

	m_vecPath.clear();
	// ��ȡҪ�������ļ�����Ŀ
	int nCount = vsPath.GetCount();
	for (int i = 0; i < nCount; i++)
	{
		CString test;
		// ��ȡListBox�ؼ��ڵ��ļ���·��
		vsPath.GetText(i, test);
		// �����ļ����ڵ������ļ������ļ���
		ErgodicFile(test.GetBuffer());
	}
	// ����������Ҫɾ���ļ���ӵ�ListBox����ʾ����
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
	MessageBox(L"ɾ���ɹ�");
	vsPath.ResetContent(); 
}

// ���ļ���ĩβ���\\*�����������ļ�
void LJClean::ErgodicFile(TCHAR szPath[MAX_PATH])
{

	CString strPath = szPath;
	strPath += L"\\*";
	WIN32_FIND_DATA fi = {};
	// �ҵ����ļ���Ϣ�ŵ�fi����
	HANDLE hFile = FindFirstFile(strPath, &fi);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return;
	}
	do
	{
		// �ж��Ƿ�ǰĿ¼���ϼ�Ŀ¼
		if (!lstrcmp(fi.cFileName, L".") || !lstrcmp(fi.cFileName, L".."))
		{
			continue;
		}
		// �ж��Ƿ����ļ��У����ǣ��ݹ����
		if (fi.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			CString strDIr = szPath;
			strDIr += L"\\";
			strDIr += fi.cFileName;
			ErgodicFile(strDIr.GetBuffer());
			continue;
		}
		// ��ȡ�ļ���չ���������ж��Ƿ������ļ���׺
		TCHAR *p = PathFindExtension(fi.cFileName);
		// Find���ز��ҵ��Ӵ�p��m_Delete�е����������Ҳ�������-1
		CString  m_UpdataEDIT(_T(".obj.tlog.lastbuildstate.idb.pdb.pch.res.ilk.exe.sdf.ipch.log"));
		if (-1 == m_UpdataEDIT.Find(p))
		{
			continue;
		}
		// ����ɸѡ���ҵ�Ҫɾ�����ļ�����֮ǰ��·�����������·��
		CString strDIr = szPath;
		strDIr += L"\\";
		strDIr += fi.cFileName;
		// �����·��������
		m_vecPath.push_back(strDIr);
	} while (FindNextFile(hFile, &fi));

}


void LJClean::OnLbnSelchangeVspath()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
