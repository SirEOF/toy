// HackAv.cpp : ʵ���ļ�
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
// HackAv �Ի���

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


// HackAv ��Ϣ�������


BOOL HackAv::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	listAv.InsertColumn(0, _T("�����ļ���"), 0, 100);
	listAv.InsertColumn(1, _T("�ļ�·��"), 0, 300);
	listAv.InsertColumn(2, _T("�ļ���С"), 0, 100);
	listAv.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);


	//************************************************************************��������
	LOGFONT lf;  //�߼�����ṹ
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
	// �쳣:  OCX ����ҳӦ���� FALSE
}

void HackAv::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect rc;
	GetClientRect(&rc);

	//���������ڱ���ɫ
	dc.FillSolidRect(rc, RGB(0, 151, 209));
	//��ҳͼƬ
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//��ȡ��ť״̬
	IsSelect[0] = ((CButton*)GetDlgItem(IDC_SingleFile))->GetCheck();
	IsSelect[1] = ((CButton*)GetDlgItem(IDC_DiskSyn))->GetCheck();
	IsSelect[2] = ((CButton*)GetDlgItem(IDC_MD5syn))->GetCheck();
	IsSelect[3] = ((CButton*)GetDlgItem(IDC_user))->GetCheck();
	IsSelect[4] = ((CButton*)GetDlgItem(IDC_LocalAv))->GetCheck();
	IsSelect[5] = ((CButton*)GetDlgItem(IDC_CloudAv))->GetCheck();
	if (IsSelect[0] == 0 && IsSelect[1] == 0)
	{
		MessageBox(L"��ѡ���ɱ·��");
		UpdateData(FALSE);
		return;
	}
	if (IsSelect[2] == 0 && IsSelect[3] == 0)
	{
		MessageBox(L"��ѡ���ɱ��ʽ");
		UpdateData(FALSE);
		return;
	}
	if (IsSelect[4] == 0 && IsSelect[5] == 0)
	{
		MessageBox(L"��ѡ���ɱ������");
		UpdateData(FALSE);
		return;
	}
	//��ʼ��ѡ������
	m_vecVirInfo.clear();
	m_LocalMD5.clear();
	m_LocalWhite.clear();
	m_ServerMD5.clear();
	m_ServerWhite.clear();
	InitSelect();
	//��ʼɨ��
	StartScan();
}

void HackAv::OnBnClickedHackout()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//���жϲ���Vector�Ƿ�Ϊ�գ���Ϊ�գ�����ʾû�п���������ļ�
	if (m_vecVirInfo.size() == 0)
	{
		return;
	}
	//ɾ������
	for (DWORD i = 0; i < m_vecVirInfo.size(); i++)
	{
		DeleteFile(m_vecVirInfo[i].szVirPath);
	}
	m_vecVirInfo.clear();
	listAv.DeleteAllItems();
	MessageBox(L"BingGo�� ����������");
	UpdateData(FALSE);
}

DWORD WINAPI ScanThread(LPVOID lpVoid)
{
	HackAv* pScanCtrl = (HackAv*)lpVoid;
	//��ɱ·���ж�
	if (pScanCtrl->IsSingleScan)
	{
		//���ļ���ɱ
		pScanCtrl->Scan_Single(pScanCtrl->m_SinglePath);
	}
	else
	{
		//ȫ·����ɱ
		//����·��ɨ�裬����·������
		pScanCtrl->Scam_All(pScanCtrl->m_AllPath);
	}
	CString TOTAL;
	TOTAL.Format(	_T("�� ɱ �� �� �� �� �� �� ɱ �� �� �� �� �� ��%d"),	pScanCtrl->m_vecVirInfo.size());
	MessageBox( 0,TOTAL, L"BingGo", NULL);
	
	pScanCtrl->SendMessage(WM_MYUPDATEDATA, FALSE);
	return 0;
}

//��ʼ��
void HackAv::InitSelect()
{
	if (IsSelect[0])
	{
		//���ļ���ɱ
		IsSingleScan = TRUE;
	}
	else
	{
		//ȫ·����ɱ
		IsSingleScan = FALSE;
	}
	if (IsSelect[2])
	{
		//MD5
		IsMD5 = TRUE;
	}
	else
	{
		//������
		IsMD5 = FALSE;
	}
	if (IsSelect[4])
	{
		//����
		IsLocal = TRUE;
	}
}

// ��ʼɨ��
void HackAv::StartScan()
{
	//1.���ж�ɨ��·��
	if (IsSingleScan)
	{
		m_SinglePath.Empty();
		//���Ϊ�����ļ���ɱ�������ļ�ѡ���·��������m_szSingleFilePath
		CFileDialog dlg(TRUE, //TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���
			NULL,
			NULL,
			OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
			(LPCTSTR)_TEXT("All Files (*.*)|*.*||"),
			NULL);
		if (dlg.DoModal() == IDOK)
		{
			//�򿪳ɹ��������ļ�·��
			m_SinglePath = dlg.GetPathName();
		}
		else
		{
			MessageBox(L"���ļ�ʧ��");
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
		//���Ϊȫ·����ɱ�������ļ���ѡ���·��������m_AllPath
		m_AllPath.Empty();
		m_AllPath = BrowseFolder(this->m_hWnd, _T("��ѡ���ɱ·��"));
		if (m_AllPath.IsEmpty())
		{
			return;
		}
	}

	listAv.DeleteAllItems();
	//2.�жϱ���
	//����Ǳ��أ����ж���MD5���ǰ����������ر��ز�������Ϣ
	if (IsLocal)
	{
		if (IsMD5)
		{
			//����MD5	���ر���MD5������
			//�Ȼ�ȡ��������MD5�ĸ���
			CString Temp;
			GetPrivateProfileString(_T("Num"),
				_T("MD5"), _T("DefaultName"),
				Temp.GetBuffer(MAX_PATH), MAX_PATH,
				_T(".\\Virus.txt"));
			Temp.ReleaseBuffer();
			int n = _ttoi(Temp);
			//�ٸ��ݸ�������MD5��Ϣ�����ص�Vector
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
				MessageBox(L"���ݶ�ȡʧ��");
				UpdateData(FALSE);
				return;
			}
		}
		else
		{
			//���ذ�����	���ر��ذ�����������
			//�Ȼ�ȡ�������а������ĸ���
			CString Temp;
			GetPrivateProfileString(_T("Num"),
				_T("White"), _T("DefaultName"),
				Temp.GetBuffer(MAX_PATH), MAX_PATH,
				_T(".\\Virus.txt"));
			Temp.ReleaseBuffer();
			int n = _ttoi(Temp);
			//�ڸ��ݸ�������MD5��Ϣ�����ص�Vector
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
				MessageBox(L"��������ȡʧ��");
				UpdateData(FALSE);
				return;
			}
		}
	}
	//3.��������ɨ���߳�
	//������������������߳��еĺ������в�ɱ����������������̵߳�Vector��
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
		if (SUCCEEDED(::SHGetMalloc(&pMalloc))) // ȡ��IMalloc�������ӿ�
		{
			pMalloc->Free(pidl); // �ͷ��ڴ�
			pMalloc->Release(); // �ͷŽӿ�
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

	//�ж��Ƿ��ǲ���
	if (IsMD5)
	{
		//MD5��ɱ
		if (MD5Scan(szPath))
		{
			//����List
			listAv.InsertItem(0, wfd.cFileName);	//�ļ���
			listAv.SetItemText(0, 1, szPath);		//�ļ�·��
			listAv.SetItemText(0, 2,				//�ļ���С
				GetShowSize(wfd.nFileSizeLow));
			//���浽Vector
			VIRINFO VirInfo;
			_tcscpy_s(VirInfo.szVirName, wfd.cFileName);
			_tcscpy_s(VirInfo.szVirPath, szPath);
			_tcscpy_s(VirInfo.szVirSize, GetShowSize(wfd.nFileSizeLow));
			m_vecVirInfo.push_back(VirInfo);
		}
	}
	else
	{
		//��������ɱ
		//����ǲ��� ���ļ���Ϣ���浽����Vector
		if (WhiteScan(szPath))
		{
			//����List
			listAv.InsertItem(0, wfd.cFileName);	//�ļ���
			listAv.SetItemText(0, 1, szPath);		//�ļ�·��
			listAv.SetItemText(0, 2,				//�ļ���С
				GetShowSize(wfd.nFileSizeLow));
			//���浽Vector
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

		//��ȡ����·����
		sFullPath = szPath;
		sFullPath += TEXT("\\");
		sFullPath += wfd.cFileName;

		//�����ǰ·�����ļ��У�����Ҫ�ݹ��ļ����е��ļ�
		if (wfd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
		{
			Scam_All(sFullPath);
		}
		//��������һ���ļ�
		else
		{
			CString m_szStatus;
			m_szStatus = _T("����ɨ�� : ") + sFullPath;
			GetDlgItem(IDC_PathDisk)->SetWindowText(m_szStatus);
			RefreshControl(IDC_PathDisk);
		//	RefreshControl(IDC_MD5syn);
			SendMessage(WM_MYUPDATEDATA, FALSE);

			//�ж��Ƿ��ǲ���
			if (IsMD5)
			{
				//MD5��ɱ
				//����ǲ��� ���ļ���Ϣ���浽����Vector
				if (MD5Scan(sFullPath))
				{
					//����List����ʾ
					listAv.InsertItem(0, wfd.cFileName);	//�ļ���
					listAv.SetItemText(0, 1, sFullPath);	//�ļ�·��
					listAv.SetItemText(0, 2,				//�ļ���С
						GetShowSize(wfd.nFileSizeLow));
					//���没����Ϣ��Vector����
					VIRINFO VirInfo;
					_tcscpy_s(VirInfo.szVirName, wfd.cFileName);
					_tcscpy_s(VirInfo.szVirPath, sFullPath);
					_tcscpy_s(VirInfo.szVirSize, GetShowSize(wfd.nFileSizeLow));
					m_vecVirInfo.push_back(VirInfo);
				}
			}
			else
			{
				//��������ɱ
				//����ǲ��� ���ļ���Ϣ���浽����Vector
				if (WhiteScan(sFullPath))
				{
					//����List����ʾ
					listAv.InsertItem(0, wfd.cFileName);	//�ļ���
					listAv.SetItemText(0, 1, sFullPath);	//�ļ�·��
					listAv.SetItemText(0, 2,				//�ļ���С
						GetShowSize(wfd.nFileSizeLow));
					//���没����Ϣ��Vector����
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
	CString bb("ɨ�����");
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

	//��ȡ�ļ�MD5��Ϣ���
	//�ж��Ǳ��ز�ɱ�����ƶ˲�ɱ
	if (IsLocal)
	{
		//����MD5��ɱ		��m_LocalMD5���Ա�
		for (DWORD i = 0; i < m_LocalMD5.size(); i++)
		{
			if (m_LocalMD5[i] == cPath)
			{
				//�ǲ��� ������
				return TRUE;
			}
		}
	}
	else
	{
		//�ƶ�MD5��ɱ		��m_ServerMD5���Ա�
		//����MD5��ɱ		��m_LocalMD5���Ա�
		for (DWORD i = 0; i < m_ServerMD5.size(); i++)
		{
			if (m_ServerMD5[i] == m_szMD5)
			{
				//�ǲ��� ������
				return TRUE;
			}
		}
	}
	return FALSE;
}

void HackAv::TchartoChar(const TCHAR * tchar, char * _char)
{
	int iLength;
	//��ȡ�ֽڳ���   
	iLength = WideCharToMultiByte(CP_ACP, 0, tchar, -1, NULL, 0, NULL, NULL);
	//��tcharֵ����_char    
	WideCharToMultiByte(CP_ACP, 0, tchar, -1, _char, iLength, NULL, NULL);
}


BOOL HackAv::WhiteScan(LPCTSTR szPath)
{
	//�ж��Ǳ��ز�ɱ�����ƶ˲�ɱ
	if (IsLocal)
	{
		//���ذ�������ɱ		��m_LocalWhite���Ա�
		for (DWORD i = 0; i < m_LocalWhite.size(); i++)
		{
			if (m_LocalWhite[i] == szPath)
			{
				//�ǲ��� ������
				return FALSE;
			}
		}
	}
	else
	{
		//�ƶ�MD5��ɱ		��m_ServerWhite���Ա�
		for (DWORD i = 0; i < m_ServerWhite.size(); i++)
		{
			if (m_ServerWhite[i] == szPath)
			{
				//�ǲ��� ������
				return FALSE;
			}
		}
	}
	return TRUE;
}

void HackAv::OnStnClickedPathdisk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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

		pDC->BitBlt(0, 0, rc.Width(), rc.Height(), dc, rc.left, rc.top, SRCCOPY);	//�Ѹ����ڱ���ͼƬ�Ȼ�����ť��

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
	sql.Format(L"DELETE FROM ������ WHERE ID = %s", id);


	adoConn.m_pRecordset = adoConn.GetRecordSet((_bstr_t)sql);
	int nIndex = list_virsDb.GetNextItem(-1, LVNI_SELECTED); // �õ�ѡ���е�����
	id = list_virsDb.GetItemText(nIndex, 0);  // ѡ���е�0�е��ı�
	list_virsDb.DeleteItem(nIndex);  // ɾ��
	MessageBox(L"ɾ���ɹ�");
	
}

void HackAv::Show()
{

	while (list_virsDb.DeleteColumn(0));
	list_virsDb.DeleteAllItems();

	CADOConn adoConn;
	adoConn.OnInitCADOConn();
	CString sql;
	
	adoConn.GetRecordSet("SELECT * FROM ������");
	//��ʼ�����ݱ�
	list_virsDb.SetExtendedStyle(list_virsDb.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//��������ݱ�
	list_virsDb.DeleteAllItems();
	
	list_virsDb.InsertColumn(0, L"ID", LVCFMT_LEFT, 40);
	list_virsDb.InsertColumn(1, L"��������", LVCFMT_LEFT, 70);
	list_virsDb.InsertColumn(2, L"MD5", LVCFMT_LEFT, 100);
	list_virsDb.InsertColumn(3, L"����ʱ��", LVCFMT_LEFT, 120);
	list_virsDb.InsertColumn(4, L"�ļ�·��", LVCFMT_LEFT, 500);
	int i = 0;
	while (!adoConn.m_pRecordset->adoEOF)
	{
		list_virsDb.InsertItem(i, L"");
		list_virsDb.SetItemText(i, 0, (wchar_t*)(_bstr_t)adoConn.m_pRecordset->GetCollect("ID"));
		list_virsDb.SetItemText(i, 1, (wchar_t*)(_bstr_t)adoConn.m_pRecordset->GetCollect("�ļ�����"));
		list_virsDb.SetItemText(i, 2, (wchar_t*)(_bstr_t)adoConn.m_pRecordset->GetCollect("MD5"));
		list_virsDb.SetItemText(i, 3, (wchar_t*)(_bstr_t)adoConn.m_pRecordset->GetCollect("����ʱ��"));
		list_virsDb.SetItemText(i, 4, (wchar_t*)(_bstr_t)adoConn.m_pRecordset->GetCollect("�ļ�·��"));
		adoConn.m_pRecordset->MoveNext();
		i++;
	}
	adoConn.ExitConnect();
	

	/*
	vector<CString> title;
	title.push_back(L"ID");
	title.push_back(L"�ļ�����");
	title.push_back(L"MD5");
	title.push_back(L"����ʱ��");
	title.push_back(L"�ļ�·��");

	//sql.Format(L"SELECT * FROM ��ʦ�� WHERE ��� = %s OR ����='%s'", m_id, m_name);

	sql = L"SELECT * FROM ������";

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
		MessageBox(L"û�в�ѯ������");
	}
	*/
}

//˫���޸�
void HackAv::OnDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ReDataEdit input;
	input.doUpdate(list_virsDb.GetItemText(list_virsDb.GetSelectionMark(), 0));
	input.DoModal();
	*pResult = 0;
}

//�Ҽ��˵�
void HackAv::OnRclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CPoint p;
	GetCursorPos(&p);//�������Ļ����

	CMenu menu;
	menu.LoadMenu(IDR_MENU4);//�༭�õĲ˵���Դ  
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
