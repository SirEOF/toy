// SoftMange.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SharkGuard.h"
#include "SoftMange.h"
#include "afxdialogex.h"


// SoftMange �Ի���

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


// SoftMange ��Ϣ�������


BOOL SoftMange::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//��ʼ���б�
	MFCList.AddColumn(4,
		_T("����"),
		_T("������"),
		_T("��װʱ��"),
		_T("�汾"));
	MFCList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//��ȡ�����Ϣ
	GetSoftwareInfo();
	MFCList.SetBkColor(RGB(0, 0, 0));
	MFCList.SetTextColor(RGB(255, 215, 0));
	MFCList.SetTextBkColor(RGB(0, 0, 0));
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void SoftMange::OnPaint()
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

void SoftMange::GetSoftwareInfo()
{
	MFCList.DeleteAllItems();
	m_vecSoftInfo.clear();
	SOFTINFO stcSoftInfo = { 0 };
	HKEY RootKey;            // ����
	LPCTSTR lpSubKey;        // �Ӽ�����
	HKEY hkResult;           // ��Ҫ�򿪼��ľ�� 
	HKEY hkRKey;
	LONG lReturn;            // ��¼��ȡע����Ƿ�ɹ�
	CString strBuffer;
	CString strMidReg;

	DWORD index = 0;
	TCHAR szKeyName[255] = { 0 };        // ע���������
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
					//��������
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
// �ж�ϵͳ�Ƿ���64λ
BOOL SoftMange::Is64()
{
	SYSTEM_INFO si;
	GetNativeSystemInfo(&si);
	if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 ||
		si.wProcessorArchitecture != PROCESSOR_ARCHITECTURE_IA64)
	{
		//64 λ����ϵͳ
		return TRUE;
	}
	else
	{
		// 32 λ����ϵͳ
		return FALSE;
	}
	return FALSE;
}
//�˵�
void SoftMange::OnRclickNinthlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//��ֹ�ڿհ�����������˵�  
	int n = pNMItemActivate->iItem;//ѡ���˵ڼ���
	if (n != -1)
	{
		//������ѡ�����ж������
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
		//�������δ���, ��������Ӧ��ListCtrl  
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

//������λ��
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
	//���ļ�
	OpenFolderAndSelectFile(m_vecSoftInfo[m_Select].strSoftInsPath);
}
