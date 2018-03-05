// ModelPro.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AAA.h"
#include "ModelPro.h"
#include "afxdialogex.h"


// ModelPro �Ի���

IMPLEMENT_DYNAMIC(ModelPro, CDialogEx)

ModelPro::ModelPro(CWnd* pParent /*=NULL*/)
	: CDialogEx(ModelPro::IDD, pParent)
{

}

ModelPro::~ModelPro()
{
}

void ModelPro::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ModelProD, m_MoudleList);
}


BEGIN_MESSAGE_MAP(ModelPro, CDialogEx)
	ON_WM_CONTEXTMENU()
	ON_WM_SIZE()
	ON_COMMAND(ID_XIEZAIm, &ModelPro::KillMoudle)
	ON_COMMAND(ID_SHUAXINm, &ModelPro::ReMoudleList)

END_MESSAGE_MAP()


// ModelPro ��Ϣ�������
TCHAR MoudleId[MAX_PATH];
TCHAR MoudleBaseAdd[MAX_PATH];

// MoudleDlg ��Ϣ�������


void ModelPro::OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/)
{
	// TODO:  �ڴ˴������Ϣ����������
	CRect rect;
	m_MoudleList.GetClientRect(&rect);//�ɵ����Χ  
	CPoint p;
	GetCursorPos(&p);
	rect.DeflateRect(0, 23, 0, 0);
	m_MoudleList.ClientToScreen(rect);//������Ļ����
	if (rect.PtInRect(p))//�ж��Ƿ��ڿͻ���listctrl��Χ��
	{
		CMenu Menu;
		Menu.LoadMenuW(IDR_ModelView);//�˵���Դ
		CMenu *SubMenu = Menu.GetSubMenu(0);
		SubMenu->TrackPopupMenu(TPM_LEFTBUTTON | TPM_RIGHTBUTTON, p.x, p.y, this);
	}
}

BOOL ModelPro::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	if (!isInitEnd)
	{
		m_MoudleList.SetExtendedStyle(m_MoudleList.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
		m_MoudleList.InsertColumn(0, L"ģ������", 0, 160);
		m_MoudleList.InsertColumn(1, L"ģ���ַ", 0, 100);
		m_MoudleList.InsertColumn(2, L"ģ���С", 0, 100);
		m_MoudleList.InsertColumn(3, L"ģ��·��", 0, 200);
		isInitEnd = TRUE;
	}
	initMoudle();
	return 0;
}

void ModelPro::initMoudle()
{
	SetWindowText(m_StrMoudle);
	MODULEENTRY32 mod32 = { sizeof(MODULEENTRY32) };
	HANDLE hMoudleSnap = INVALID_HANDLE_VALUE;
	hMoudleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, m_dwPID);//TH32CS_SNAPMODULE
	int nCount = 0;
	if (hMoudleSnap == INVALID_HANDLE_VALUE)
	{
		return;
	}
	if (!Module32First(hMoudleSnap, &mod32))
	{
		CloseHandle(hMoudleSnap);
		return;
	}
	m_VecModList.clear();
	do
	{
		CString str;
		m_MoudleList.InsertItem(nCount, L"");
		m_MoudleList.SetItemText(nCount, 0, mod32.szModule);
		str.Format(_T("%08X"), mod32.modBaseAddr);
		m_MoudleList.SetItemText(nCount, 1, str);
		str.Format(_T("%08X"), mod32.modBaseSize);
		m_MoudleList.SetItemText(nCount, 2, str);
		m_MoudleList.SetItemText(nCount, 3, mod32.szExePath);
		nCount++;
		m_VecModList.push_back(mod32);
	} while (Module32Next(hMoudleSnap, &mod32));
}

void ModelPro::KillMoudle()
{
	POSITION pos = m_MoudleList.GetFirstSelectedItemPosition();
	HMODULE hProcessHandle;
	if (pos == NULL)//�ж��Ƿ�Ϊ��
	{
		return;
	}
	else
	{
		//�ɰ�ctrl+���ѡ�ж��н�������
		while (pos)
		{
			int nItem = m_MoudleList.GetNextSelectedItem(pos);
			m_MoudleList.DeleteItem(nItem);
			CString MoudleName(m_VecModList[m_VecModList.size() - (nItem + 1)].szExePath);
			int index = MoudleName.ReverseFind(_T('\\'));//��ȴģ����
			MoudleName = MoudleName.Right(MoudleName.GetLength() - index - 1);
			hProcessHandle = LoadLibrary(MoudleName);
			FreeLibrary(hProcessHandle);
		}
	}
}


/*
void ModelPro::KillMoudle()
{
	//HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, dwProcessId);
	
}
*/



void ModelPro::ReMoudleList()
{
	initMoudle();
}
