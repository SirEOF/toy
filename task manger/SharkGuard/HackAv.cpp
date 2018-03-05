// HackAv.cpp : 实现文件
//

#include "stdafx.h"
#include "SharkGuard.h"
#include "HackAv.h"
#include "afxdialogex.h"
#include "ADOCoon.h"
#include <vector>
#include <Gdiplus.h>
#include "ReDataEdit.h"
using std::vector;
// HackAv 对话框

IMPLEMENT_DYNAMIC(HackAv, CDialogEx)

HackAv::HackAv(CWnd* pParent /*=NULL*/)
	: CDialogEx(HackAv::IDD, pParent)
{

}

HackAv::~HackAv()
{
}

void HackAv::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_HackAv, listAv);
	DDX_Control(pDX, IDC_Virs_db, list_virsDb);
	DDX_Control(pDX, IDC_HackGo, Bscan);
	DDX_Control(pDX, IDC_Hackout, Bclear);
}

BEGIN_MESSAGE_MAP(HackAv, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_HackGo, &HackAv::OnBnClickedHackgo)
	ON_BN_CLICKED(IDC_Hackout, &HackAv::OnBnClickedHackout)
	ON_MESSAGE(WM_MYUPDATEDATA, OnUpdateMyData)
	ON_STN_CLICKED(IDC_PathDisk, &HackAv::OnStnClickedPathdisk)
	ON_WM_CTLCOLOR()
	ON_NOTIFY(NM_DBLCLK, IDC_Virs_db, &HackAv::OnDblclkList)
	ON_NOTIFY(NM_RCLICK, IDC_Virs_db, &HackAv::OnRclickList1)
	ON_COMMAND(ID_DeleteVirs, &HackAv::OnDeletevirs)
	ON_COMMAND(ID_AddVirs, &HackAv::OnAddvirs)
	ON_COMMAND(ID_ReShow, &HackAv::OnReshow)
END_MESSAGE_MAP()


// HackAv 消息处理程序


BOOL HackAv::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	listAv.InsertColumn(0, _T("病毒文件名"), 0, 100);
	listAv.InsertColumn(1, _T("文件路径"), 0, 300);
	listAv.InsertColumn(2, _T("文件大小"), 0, 100);
	listAv.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);


	//************************************************************************字体设置
	LOGFONT lf;  //逻辑字体结构
	::ZeroMemory(&lf, sizeof(lf));
	CFont m_font1;
	lf.lfHeight = 40;
	lf.lfWidth = 0;
	lf.lfEscapement = 0;
	lf.lfOrientation = 0;
	lf.lfWeight = FW_BOLD;
	lf.lfItalic = FALSE;
	lf.lfUnderline = FALSE;
	lf.lfStrikeOut = FALSE;
	lf.lfCharSet = DEFAULT_CHARSET;
	lf.lfOutPrecision = OUT_DEFAULT_PRECIS;
	lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	lf.lfQuality = DEFAULT_QUALITY;
	//lf.lfPitchAndFamily = VARIABLE_PITCH | FF_ROMAN;
	m_font1.CreateFontIndirect(&lf);
	GetDlgItem(IDC_Lj)->SetFont(&m_font1);
	GetDlgItem(IDC_HackArivs)->SetFont(&m_font1);
	GetDlgItem(IDC_SingleFile)->SetFont(&m_font1);
	GetDlgItem(IDC_DiskSyn)->SetFont(&m_font1);
	GetDlgItem(IDC_CSFS)->SetFont(&m_font1);
	GetDlgItem(IDC_MD5syn)->SetFont(&m_font1);
	GetDlgItem(IDC_user)->SetFont(&m_font1);
	GetDlgItem(IDC_BDK)->SetFont(&m_font1);
	GetDlgItem(IDC_LocalAv)->SetFont(&m_font1);
	GetDlgItem(IDC_CloudAv)->SetFont(&m_font1);
	GetDlgItem(IDC_PathDisk)->SetFont(&m_font1);
	//*****************************************************************************

	list_virsDb.SetExtendedStyle(LVS_EX_FLATSB
		| LVS_EX_FULLROWSELECT
		| LVS_EX_HEADERDRAGDROP
		| LVS_EX_ONECLICKACTIVATE
		| LVS_EX_GRIDLINES);
	list_virsDb.SetBkColor(RGB(0, 0, 0));
	list_virsDb.SetTextColor(RGB(255, 215, 0));
	list_virsDb.SetTextBkColor(RGB(0, 0, 0));

	listAv.SetBkColor(RGB(0, 0, 0));
	listAv.SetTextColor(RGB(255, 0, 0));
	listAv.SetTextBkColor(RGB(0, 0, 0));

	Show();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void HackAv::OnPaint()
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

void HackAv::RefreshControl(UINT uCtlID)
{
	CRect    rc;
	GetDlgItem(uCtlID)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	InvalidateRect(rc);
}

void HackAv::OnBnClickedHackgo()
{
	// TODO:  在此添加控件通知处理程序代码
	//获取按钮状态
	IsSelect[0] = ((CButton*)GetDlgItem(IDC_SingleFile))->GetCheck();
	IsSelect[1] = ((CButton*)GetDlgItem(IDC_DiskSyn))->GetCheck();
	IsSelect[2] = ((CButton*)GetDlgItem(IDC_MD5syn))->GetCheck();
	IsSelect[3] = ((CButton*)GetDlgItem(IDC_user))->GetCheck();
	IsSelect[4] = ((CButton*)GetDlgItem(IDC_LocalAv))->GetCheck();
	IsSelect[5] = ((CButton*)GetDlgItem(IDC_CloudAv))->GetCheck();
	if (IsSelect[0] == 0 && IsSelect[1] == 0)
	{
		MessageBox(L"请选择查杀路径");
		UpdateData(FALSE);
		return;
	}
	if (IsSelect[2] == 0 && IsSelect[3] == 0)
	{
		MessageBox(L"请选择查杀方式");
		UpdateData(FALSE);
		return;
	}
	if (IsSelect[4] == 0 && IsSelect[5] == 0)
	{
		MessageBox(L"请选择查杀病毒库");
		UpdateData(FALSE);
		return;
	}
	//初始化选项设置
	m_vecVirInfo.clear();
	m_LocalMD5.clear();
	m_LocalWhite.clear();
	m_ServerMD5.clear();
	m_ServerWhite.clear();
	InitSelect();
	//开始扫描
	StartScan();
}

void HackAv::OnBnClickedHackout()
{
	// TODO:  在此添加控件通知处理程序代码
	//先判断病毒Vector是否为空，若为空，则提示没有可以清除的文件
	if (m_vecVirInfo.size() == 0)
	{
		return;
	}
	//删除病毒
	for (DWORD i = 0; i < m_vecVirInfo.size(); i++)
	{
		DeleteFile(m_vecVirInfo[i].szVirPath);
	}
	m_vecVirInfo.clear();
	listAv.DeleteAllItems();
	MessageBox(L"BingGo！ 病毒清除完毕");
	UpdateData(FALSE);
}

DWORD WINAPI ScanThread(LPVOID lpVoid)
{
	HackAv* pScanCtrl = (HackAv*)lpVoid;
	//查杀路径判断
	if (pScanCtrl->IsSingleScan)
	{
		//单文件查杀
		pScanCtrl->Scan_Single(pScanCtrl->m_SinglePath);
	}
	else
	{
		//全路径查杀
		//调用路径扫描，传入路径参数
		pScanCtrl->Scam_All(pScanCtrl->m_AllPath);
	}
	CString TOTAL;
	TOTAL.Format(	_T("查 杀 完 毕 ！ 本 次 查 杀 发 现 病 毒 数 ：%d"),	pScanCtrl->m_vecVirInfo.size());
	MessageBox( 0,TOTAL, L"BingGo", NULL);
	
	pScanCtrl->SendMessage(WM_MYUPDATEDATA, FALSE);
	return 0;
}

//初始化
void HackAv::InitSelect()
{
	if (IsSelect[0])
	{
		//单文件查杀
		IsSingleScan = TRUE;
	}
	else
	{
		//全路径查杀
		IsSingleScan = FALSE;
	}
	if (IsSelect[2])
	{
		//MD5
		IsMD5 = TRUE;
	}
	else
	{
		//白名单
		IsMD5 = FALSE;
	}
	if (IsSelect[4])
	{
		//本地
		IsLocal = TRUE;
	}
}

// 开始扫描
void HackAv::StartScan()
{
	//1.先判断扫描路径
	if (IsSingleScan)
	{
		m_SinglePath.Empty();
		//如果为单个文件查杀，弹出文件选择框，路径保存在m_szSingleFilePath
		CFileDialog dlg(TRUE, //TRUE为OPEN对话框，FALSE为SAVE AS对话框
			NULL,
			NULL,
			OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
			(LPCTSTR)_TEXT("All Files (*.*)|*.*||"),
			NULL);
		if (dlg.DoModal() == IDOK)
		{
			//打开成功，保存文件路径
			m_SinglePath = dlg.GetPathName();
		}
		else
		{
			MessageBox(L"打开文件失败");
			UpdateData(FALSE);
			return;
		}
		if (m_SinglePath.IsEmpty())
		{
			return;
		}
	}
	else
	{
		//如果为全路径查杀，弹出文件夹选择框，路径保存在m_AllPath
		m_AllPath.Empty();
		m_AllPath = BrowseFolder(this->m_hWnd, _T("请选择查杀路径"));
		if (m_AllPath.IsEmpty())
		{
			return;
		}
	}

	listAv.DeleteAllItems();
	//2.判断本地
	//如果是本地，再判断是MD5还是白名单，加载本地病毒库信息
	if (IsLocal)
	{
		if (IsMD5)
		{
			//本地MD5	加载本地MD5病毒库
			//先获取病毒库中MD5的个数
			CString Temp;
			GetPrivateProfileString(_T("Num"),
				_T("MD5"), _T("DefaultName"),
				Temp.GetBuffer(MAX_PATH), MAX_PATH,
				_T(".\\Virus.txt"));
			Temp.ReleaseBuffer();
			int n = _ttoi(Temp);
			//再根据个数遍历MD5信息，加载到Vector
			for (int i = 0; i < n; i++)
			{
				CString tempCount;
				tempCount.Format(_T("%d"), i);
				GetPrivateProfileString(_T("MD5"),
					tempCount, _T("DefaultName"),
					Temp.GetBuffer(MAX_PATH), MAX_PATH,
					_T(".\\Virus.txt"));
				Temp.ReleaseBuffer();
				m_LocalMD5.push_back(Temp);
			}
			if (m_LocalMD5.size() == 0)
			{
				MessageBox(L"数据读取失败");
				UpdateData(FALSE);
				return;
			}
		}
		else
		{
			//本地白名单	加载本地白名单病毒库
			//先获取病毒库中白名单的个数
			CString Temp;
			GetPrivateProfileString(_T("Num"),
				_T("White"), _T("DefaultName"),
				Temp.GetBuffer(MAX_PATH), MAX_PATH,
				_T(".\\Virus.txt"));
			Temp.ReleaseBuffer();
			int n = _ttoi(Temp);
			//在根据个数遍历MD5信息，加载到Vector
			for (int i = 0; i < n; i++)
			{
				CString tempCount;
				tempCount.Format(_T("%d"), i);
				GetPrivateProfileString(_T("White"),
					tempCount, _T("DefaultName"),
					Temp.GetBuffer(MAX_PATH), MAX_PATH,
					_T(".\\Virus.txt"));
				Temp.ReleaseBuffer();
				m_LocalWhite.push_back(Temp);
			}
			if (m_LocalWhite.size() == 0)
			{
				MessageBox(L"白名单获取失败");
				UpdateData(FALSE);
				return;
			}
		}
	}
	//3.创建启动扫描线程
	//根据以上四项，调用主线程中的函数进行查杀，将结果保存在主线程的Vector中
	CloseHandle(CreateThread(NULL, 0, ScanThread, this, 0, NULL));
}

CString HackAv::BrowseFolder(HWND hWnd, LPCTSTR lpTitle)
{

	TCHAR szPath[MAX_PATH] = { 0 };
	BROWSEINFO m_bi;

	m_bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_STATUSTEXT;
	m_bi.hwndOwner = hWnd;
	m_bi.pidlRoot = NULL;
	m_bi.lpszTitle = lpTitle;
	m_bi.lpfn = NULL;
	m_bi.lParam = NULL;
	m_bi.pszDisplayName = szPath;

	LPITEMIDLIST pidl = ::SHBrowseForFolder(&m_bi);
	if (pidl)
	{
		if (!::SHGetPathFromIDList(pidl, szPath)) szPath[0] = 0;

		IMalloc * pMalloc = NULL;
		if (SUCCEEDED(::SHGetMalloc(&pMalloc))) // 取得IMalloc分配器接口
		{
			pMalloc->Free(pidl); // 释放内存
			pMalloc->Release(); // 释放接口
		}
	}
	return szPath;
}

void HackAv::Scan_Single(LPCTSTR szPath)
{
	WIN32_FIND_DATA wfd;
	CString sFindFilter;
	DWORD dwAttributes = 0;

	sFindFilter = szPath;
	FindFirstFile(sFindFilter, &wfd);

	//判断是否是病毒
	if (IsMD5)
	{
		//MD5查杀
		if (MD5Scan(szPath))
		{
			//插入List
			listAv.InsertItem(0, wfd.cFileName);	//文件名
			listAv.SetItemText(0, 1, szPath);		//文件路径
			listAv.SetItemText(0, 2,				//文件大小
				GetShowSize(wfd.nFileSizeLow));
			//保存到Vector
			VIRINFO VirInfo;
			_tcscpy_s(VirInfo.szVirName, wfd.cFileName);
			_tcscpy_s(VirInfo.szVirPath, szPath);
			_tcscpy_s(VirInfo.szVirSize, GetShowSize(wfd.nFileSizeLow));
			m_vecVirInfo.push_back(VirInfo);
		}
	}
	else
	{
		//白名单查杀
		//如果是病毒 将文件信息保存到病毒Vector
		if (WhiteScan(szPath))
		{
			//插入List
			listAv.InsertItem(0, wfd.cFileName);	//文件名
			listAv.SetItemText(0, 1, szPath);		//文件路径
			listAv.SetItemText(0, 2,				//文件大小
				GetShowSize(wfd.nFileSizeLow));
			//保存到Vector
			VIRINFO VirInfo;
			_tcscpy_s(VirInfo.szVirName, wfd.cFileName);
			_tcscpy_s(VirInfo.szVirPath, szPath);
			_tcscpy_s(VirInfo.szVirSize, GetShowSize(wfd.nFileSizeLow));
			m_vecVirInfo.push_back(VirInfo);
		}
	}
}

void HackAv::Scam_All(LPCTSTR szPath)
{
	WIN32_FIND_DATA wfd;
	HANDLE hFind;
	CString sFullPath;
	CString sFindFilter;
	DWORD dwAttributes = 0;

	sFindFilter = szPath;
	sFindFilter += TEXT("\\*.*");
	if ((hFind = FindFirstFile(sFindFilter, &wfd)) == INVALID_HANDLE_VALUE)
		return;

	do
	{
		if (_tcscmp(wfd.cFileName, TEXT(".")) == 0 ||
			_tcscmp(wfd.cFileName, TEXT("..")) == 0)
		{
			continue;
		}

		//获取完整路径名
		sFullPath = szPath;
		sFullPath += TEXT("\\");
		sFullPath += wfd.cFileName;

		//如果当前路径是文件夹，则需要递归文件夹中的文件
		if (wfd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
		{
			Scam_All(sFullPath);
		}
		//否则，这是一个文件
		else
		{
			CString m_szStatus;
			m_szStatus = _T("正在扫描 : ") + sFullPath;
			GetDlgItem(IDC_PathDisk)->SetWindowText(m_szStatus);
			RefreshControl(IDC_PathDisk);
		//	RefreshControl(IDC_MD5syn);
			SendMessage(WM_MYUPDATEDATA, FALSE);

			//判断是否是病毒
			if (IsMD5)
			{
				//MD5查杀
				//如果是病毒 将文件信息保存到病毒Vector
				if (MD5Scan(sFullPath))
				{
					//插入List中显示
					listAv.InsertItem(0, wfd.cFileName);	//文件名
					listAv.SetItemText(0, 1, sFullPath);	//文件路径
					listAv.SetItemText(0, 2,				//文件大小
						GetShowSize(wfd.nFileSizeLow));
					//保存病毒信息到Vector容器
					VIRINFO VirInfo;
					_tcscpy_s(VirInfo.szVirName, wfd.cFileName);
					_tcscpy_s(VirInfo.szVirPath, sFullPath);
					_tcscpy_s(VirInfo.szVirSize, GetShowSize(wfd.nFileSizeLow));
					m_vecVirInfo.push_back(VirInfo);
				}
			}
			else
			{
				//白名单查杀
				//如果是病毒 将文件信息保存到病毒Vector
				if (WhiteScan(sFullPath))
				{
					//插入List中显示
					listAv.InsertItem(0, wfd.cFileName);	//文件名
					listAv.SetItemText(0, 1, sFullPath);	//文件路径
					listAv.SetItemText(0, 2,				//文件大小
						GetShowSize(wfd.nFileSizeLow));
					//保存病毒信息到Vector容器
					VIRINFO VirInfo;
					_tcscpy_s(VirInfo.szVirName, wfd.cFileName);
					_tcscpy_s(VirInfo.szVirPath, sFullPath);
					_tcscpy_s(VirInfo.szVirSize, GetShowSize(wfd.nFileSizeLow));
					m_vecVirInfo.push_back(VirInfo);
				}
			}
		}
	} while (FindNextFile(hFind, &wfd));
	RefreshControl(IDC_PathDisk);
	CString bb("扫描完毕");
	GetDlgItem(IDC_PathDisk)->SetWindowText(bb);
	RefreshControl(IDC_PathDisk);
	FindClose(hFind);
}

CString HackAv::GetShowSize(DOUBLE dwSize)
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

BOOL HackAv::MD5Scan(LPCTSTR szPath)
{
	CStringA Temp;
	Temp.Format("%s", szPath);
	char  cPath[MAX_PATH];
	TchartoChar(szPath, cPath);
	memcpy(cPath, QQMD5.md5FileValue(cPath), MAX_PATH);

	//获取文件MD5信息完毕
	//判断是本地查杀还是云端查杀
	if (IsLocal)
	{
		//本地MD5查杀		与m_LocalMD5作对比
		for (DWORD i = 0; i < m_LocalMD5.size(); i++)
		{
			if (m_LocalMD5[i] == cPath)
			{
				//是病毒 返回真
				return TRUE;
			}
		}
	}
	else
	{
		//云端MD5查杀		与m_ServerMD5作对比
		//本地MD5查杀		与m_LocalMD5作对比
		for (DWORD i = 0; i < m_ServerMD5.size(); i++)
		{
			if (m_ServerMD5[i] == m_szMD5)
			{
				//是病毒 返回真
				return TRUE;
			}
		}
	}
	return FALSE;
}

void HackAv::TchartoChar(const TCHAR * tchar, char * _char)
{
	int iLength;
	//获取字节长度   
	iLength = WideCharToMultiByte(CP_ACP, 0, tchar, -1, NULL, 0, NULL, NULL);
	//将tchar值赋给_char    
	WideCharToMultiByte(CP_ACP, 0, tchar, -1, _char, iLength, NULL, NULL);
}


BOOL HackAv::WhiteScan(LPCTSTR szPath)
{
	//判断是本地查杀还是云端查杀
	if (IsLocal)
	{
		//本地白名单查杀		与m_LocalWhite作对比
		for (DWORD i = 0; i < m_LocalWhite.size(); i++)
		{
			if (m_LocalWhite[i] == szPath)
			{
				//是病毒 返回真
				return FALSE;
			}
		}
	}
	else
	{
		//云端MD5查杀		与m_ServerWhite作对比
		for (DWORD i = 0; i < m_ServerWhite.size(); i++)
		{
			if (m_ServerWhite[i] == szPath)
			{
				//是病毒 返回真
				return FALSE;
			}
		}
	}
	return TRUE;
}

void HackAv::OnStnClickedPathdisk()
{
	// TODO:  在此添加控件通知处理程序代码
}

HBRUSH HackAv::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	UINT id = pWnd->GetDlgCtrlID();
	if (id == IDC_HackArivs || id == IDC_Lj || id == IDC_SingleFile || id == IDC_DiskSyn || id == IDC_CSFS || id == IDC_MD5syn || id == IDC_user || id == IDC_BDK || id == IDC_LocalAv || id == IDC_CloudAv || id == IDC_PathDisk)
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255, 153, 18));
		CRect rc;
		pWnd->GetWindowRect(&rc);
		ScreenToClient(&rc);

		CDC* dc = GetDC();

		pDC->BitBlt(0, 0, rc.Width(), rc.Height(), dc, rc.left, rc.top, SRCCOPY);	//把父窗口背景图片先画到按钮上

		ReleaseDC(dc);

		hbr = (HBRUSH) ::GetStockObject(NULL_BRUSH);
	}
	return hbr;
}


void HackAv::OnDeletevirs()
{
	// int type = m_type.GetCurSel();
	CString id = list_virsDb.GetItemText(list_virsDb.GetSelectionMark(), 0);

	CADOConn adoConn;
	adoConn.OnInitCADOConn();
	CString sql;
	sql.Format(L"DELETE FROM 病毒库 WHERE ID = %s", id);


	adoConn.m_pRecordset = adoConn.GetRecordSet((_bstr_t)sql);
	int nIndex = list_virsDb.GetNextItem(-1, LVNI_SELECTED); // 得到选中行的索引
	id = list_virsDb.GetItemText(nIndex, 0);  // 选中行第0列的文本
	list_virsDb.DeleteItem(nIndex);  // 删除
	MessageBox(L"删除成功");
	
}

void HackAv::Show()
{

	while (list_virsDb.DeleteColumn(0));
	list_virsDb.DeleteAllItems();

	CADOConn adoConn;
	adoConn.OnInitCADOConn();
	CString sql;
	
	adoConn.GetRecordSet("SELECT * FROM 病毒库");
	//初始化数据表
	list_virsDb.SetExtendedStyle(list_virsDb.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//先清空数据表
	list_virsDb.DeleteAllItems();
	
	list_virsDb.InsertColumn(0, L"ID", LVCFMT_LEFT, 40);
	list_virsDb.InsertColumn(1, L"病毒名称", LVCFMT_LEFT, 70);
	list_virsDb.InsertColumn(2, L"MD5", LVCFMT_LEFT, 100);
	list_virsDb.InsertColumn(3, L"创建时间", LVCFMT_LEFT, 120);
	list_virsDb.InsertColumn(4, L"文件路径", LVCFMT_LEFT, 500);
	int i = 0;
	while (!adoConn.m_pRecordset->adoEOF)
	{
		list_virsDb.InsertItem(i, L"");
		list_virsDb.SetItemText(i, 0, (wchar_t*)(_bstr_t)adoConn.m_pRecordset->GetCollect("ID"));
		list_virsDb.SetItemText(i, 1, (wchar_t*)(_bstr_t)adoConn.m_pRecordset->GetCollect("文件名称"));
		list_virsDb.SetItemText(i, 2, (wchar_t*)(_bstr_t)adoConn.m_pRecordset->GetCollect("MD5"));
		list_virsDb.SetItemText(i, 3, (wchar_t*)(_bstr_t)adoConn.m_pRecordset->GetCollect("创建时间"));
		list_virsDb.SetItemText(i, 4, (wchar_t*)(_bstr_t)adoConn.m_pRecordset->GetCollect("文件路径"));
		adoConn.m_pRecordset->MoveNext();
		i++;
	}
	adoConn.ExitConnect();
	

	/*
	vector<CString> title;
	title.push_back(L"ID");
	title.push_back(L"文件名称");
	title.push_back(L"MD5");
	title.push_back(L"创建时间");
	title.push_back(L"文件路径");

	//sql.Format(L"SELECT * FROM 教师表 WHERE 编号 = %s OR 姓名='%s'", m_id, m_name);

	sql = L"SELECT * FROM 病毒库";

	adoConn.m_pRecordset = adoConn.GetRecordSet((_bstr_t)sql);
	CRect rect;
	list_virsDb.GetClientRect(&rect);

	for (int i = 0; i < title.size(); i++)
	{
		list_virsDb.InsertColumn(i, title[i], LVCFMT_LEFT, rect.Width() / title.size());
	}
	int i = 0;
	for (; !adoConn.m_pRecordset->adoEOF; i++)
	{
		list_virsDb.InsertItem(i, L" ");
		for (int j = 0; j < title.size(); j++)
		{
			list_virsDb.SetItemText(i, j, (wchar_t *)(_bstr_t)adoConn.m_pRecordset->GetCollect(long(j)));
		}
		adoConn.m_pRecordset->MoveNext();
	}
	if (i == 0)
	{
		MessageBox(L"没有查询到数据");
	}
	*/
}

//双击修改
void HackAv::OnDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	ReDataEdit input;
	input.doUpdate(list_virsDb.GetItemText(list_virsDb.GetSelectionMark(), 0));
	input.DoModal();
	*pResult = 0;
}

//右键菜单
void HackAv::OnRclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	CPoint p;
	GetCursorPos(&p);//鼠标点的屏幕坐标

	CMenu menu;
	menu.LoadMenu(IDR_MENU4);//编辑好的菜单资源  
	CMenu * pSubMenu = menu.GetSubMenu(0);
	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, p.x, p.y, this);

	*pResult = 0;
}

void HackAv::doSelect(CString id, CString name)
{

	m_isSelect = TRUE;
	m_id = id;
	m_name = name;
}

void HackAv::OnAddvirs()
{
	ReDataEdit input;
	input.DoModal();
}

void HackAv::OnReshow()
{
	Show();
}
