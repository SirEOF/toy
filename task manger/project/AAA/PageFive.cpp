// PageFive.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AAA.h"
#include "PageFive.h"
#include "afxdialogex.h"
#include "PageTwo.h"
#include "PeQuDuan.h"
#include "PePosCalc.h"
#include "PeMainIndex.h"

// PageFive �Ի���

IMPLEMENT_DYNAMIC(PageFive, CDialogEx)

PageFive::PageFive(CWnd* pParent /*=NULL*/)
	: CDialogEx(PageFive::IDD, pParent)
	, P_EOP(_T(""))
	, P_IMAGEBASE(_T(""))
	, P_SIZEOFIMAGE(_T(""))
	, P_BASEOFCODE(_T(""))
	, P_BASEOFDATA(_T(""))
	, P_SECTIONALIGNMENT(_T(""))
	, P_MAGIC(_T(""))
	, P_SUBSYSYSTEM(_T(""))
	, P_NUMBEROFSECTIONS(_T(""))
	, P_TIMEDATASTAMP(_T(""))
	, P_SIZEOFHEADERS(_T(""))
	, P_CHARACTERISTICS(_T(""))
	, P_CHECKSUM(_T(""))
	, P_SIZEOFOPTIONALHEADER(_T(""))
	, P_FILEALIGNMENT(_T(""))
	, P_NUMBEROFRVAANDSIZE(_T(""))
	, P_FILENAME(_T(""))
	, P_SIZEOFFILE(_T(""))
	, P_MDFIVE(_T(""))
	, P_BUILDTIME(_T(""))
	, P_LASTINCORTIME(_T(""))
{

}

PageFive::~PageFive()
{
}


void PageFive::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, P_EOP);
	DDX_Text(pDX, IDC_EDIT2, P_IMAGEBASE);
	DDX_Text(pDX, IDC_EDIT4, P_SIZEOFIMAGE);
	DDX_Text(pDX, IDC_EDIT5, P_BASEOFCODE);
	DDX_Text(pDX, IDC_EDIT8, P_BASEOFDATA);
	DDX_Text(pDX, IDC_EDIT7, P_SECTIONALIGNMENT);
	DDX_Text(pDX, IDC_EDIT6, P_MAGIC);
	DDX_Text(pDX, IDC_EDIT3, P_SUBSYSYSTEM);
	DDX_Text(pDX, IDC_EDIT9, P_NUMBEROFSECTIONS);
	DDX_Text(pDX, IDC_EDIT10, P_TIMEDATASTAMP);
	DDX_Text(pDX, IDC_EDIT11, P_SIZEOFHEADERS);
	DDX_Text(pDX, IDC_EDIT12, P_CHARACTERISTICS);
	DDX_Text(pDX, IDC_EDIT13, P_CHECKSUM);
	DDX_Text(pDX, IDC_EDIT14, P_SIZEOFOPTIONALHEADER);
	DDX_Text(pDX, IDC_EDIT21, P_FILEALIGNMENT);
	DDX_Text(pDX, IDC_EDIT20, P_NUMBEROFRVAANDSIZE);
	DDX_Text(pDX, IDC_EDIT15, P_FILENAME);
	DDX_Text(pDX, IDC_EDIT16, P_SIZEOFFILE);
	DDX_Text(pDX, IDC_EDIT17, P_MDFIVE);
	DDX_Text(pDX, IDC_EDIT19, P_BUILDTIME);
	DDX_Text(pDX, IDC_EDIT18, P_LASTINCORTIME);
}


BEGIN_MESSAGE_MAP(PageFive, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT6, &PageFive::OnEnChangeEdit6)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_P_QuDuan, &PageFive::OnBnClickedPQuduan)
	ON_BN_CLICKED(IDC_P_Mulu, &PageFive::OnBnClickedPMulu)
	ON_BN_CLICKED(IDC_P_Baocun, &PageFive::OnBnClickedPBaocun)
	ON_BN_CLICKED(IDC_P_PosClac, &PageFive::OnBnClickedPPosclac)
END_MESSAGE_MAP()


// PageFive ��Ϣ�������


void PageFive::OnEnChangeEdit6()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void PageFive::OnDropFiles(HDROP hDropInfo)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	DragQueryFile(hDropInfo, NULL, Path, MAX_PATH);;

	GetMD5message();
	UpdateData(FALSE);
	AllPe.BeginPeInfo(Path);
	OnDropPE();
	CDialogEx::OnDropFiles(hDropInfo);
}

void PageFive::GetMD5message()
{
	TCHAR*path;
	path = Path;
	CFileFind  Finder;
	CTime  TempTime;
	//CString  Filename;
	//���û�ȡ��Ϣ�ṹ��
	WIN32_FIND_DATA  stcFData = { 0 };
	//ֻ��Ҫ��ȡһ���ļ�����Ϣ,���Բ���Ҫʹ��ѭ��
	BOOL bWorking = Finder.FindFile(path);
	if (bWorking)
	{
		bWorking = Finder.FindNextFile();
		// ��ȡ�ļ�����ʱ��
		if (Finder.GetCreationTime(TempTime))
		{
			P_BUILDTIME = TempTime.Format(_T("%c"));
		}
		// ��ȡ�ļ�����޸�ʱ��
		if (Finder.GetLastWriteTime(TempTime))
		{
			P_LASTINCORTIME = TempTime.Format(_T("%c"));
		}
		//��ȡ�ļ���С
		P_SIZEOFFILE.Format(L"%d", Finder.GetLength());
		P_SIZEOFFILE = P_SIZEOFFILE + L"    �ֽ�";
		//��ȡ�ļ�����
		P_FILENAME = Finder.GetFileTitle();

	}

	CStringA Temp;
	Temp.Format("%S", path);
	char  cPath[MAX_PATH];
	TcharToChar(path, cPath);
	memcpy(cPath, MD5->md5FileValue(cPath), MAX_PATH);
	P_MDFIVE = cPath;
}

void PageFive::TcharToChar(const TCHAR * tchar, char * _char)
{
	int iLength;
	//��ȡ�ֽڳ���   
	iLength = WideCharToMultiByte(CP_ACP, 0, tchar, -1, NULL, 0, NULL, NULL);
	//��tcharֵ����_char    
	WideCharToMultiByte(CP_ACP, 0, tchar, -1, _char, iLength, NULL, NULL);
}

void PageFive::OnDropPE()
{
	ShowPeInfo();
	UpdateData(FALSE);
}

void PageFive::ShowPeInfo()
{
	
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	if (AllPe.pDatD == NULL)
	{
		return;
	}
	AllPe.InputPeInfo(P_EOP, AllPe.pOptH->AddressOfEntryPoint);
	AllPe.InputPeInfo(P_IMAGEBASE, AllPe.pOptH->ImageBase);					//�����ַ
	AllPe.InputPeInfo(P_SIZEOFIMAGE, AllPe.pOptH->SizeOfImage);				//�����С
	AllPe.InputPeInfo(P_BASEOFCODE, AllPe.pOptH->BaseOfCode);					//�����ַ
	AllPe.InputPeInfo(P_BASEOFDATA, AllPe.pOptH->BaseOfData);					//���ݻ�ַ
	AllPe.InputPeInfo(P_SECTIONALIGNMENT, AllPe.pOptH->SectionAlignment);		//�����
	AllPe.InputPeInfo(P_FILEALIGNMENT, AllPe.pOptH->FileAlignment);			//�ļ������
	AllPe.InputPeInfo(P_MAGIC, AllPe.pOptH->Magic);							//��־��
	//�ڶ���
	AllPe.InputPeInfo(P_SUBSYSYSTEM, AllPe.pOptH->Subsystem);					//��ϵͳ
	AllPe.InputPeInfo(P_NUMBEROFSECTIONS, AllPe.pNtH->FileHeader.NumberOfSections);//������Ŀ
	AllPe.InputPeInfo(P_TIMEDATASTAMP, AllPe.pNtH->FileHeader.TimeDateStamp);//����ʱ���־
	AllPe.InputPeInfo(P_SIZEOFHEADERS, AllPe.pOptH->SizeOfHeaders);			//���״�С
	AllPe.InputPeInfo(P_CHARACTERISTICS, AllPe.pNtH->FileHeader.Characteristics);//����ֵ
	AllPe.InputPeInfo(P_CHECKSUM, AllPe.pOptH->CheckSum);						//У���
	AllPe.InputPeInfo(P_SIZEOFOPTIONALHEADER, AllPe.pNtH->FileHeader.SizeOfOptionalHeader);//��ѡͷ����С
	AllPe.InputPeInfo(P_NUMBEROFRVAANDSIZE, AllPe.pOptH->NumberOfRvaAndSizes);//RVA������С
	
}

void PageFive::OutPutPeInfo(CString &m_PeInfo, DWORD PeValue)
{
	CString str;
	str.Format(L"%08X", PeValue);//ת16����
	m_PeInfo = str;
	UpdateData(FALSE);
}



void PageFive::OnBnClickedPQuduan()
{
	//memcpy(Path, SZPath, MAX_PATH);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	PeQuDuan QuDDlg;
	QuDDlg.DoModal();
}


void PageFive::OnBnClickedPMulu()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	PeMainIndex  PeMainDlg;
	PeMainDlg.DoModal();

}


void PageFive::OnBnClickedPBaocun()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	/*
	UpdateData(TRUE);
	//���ؼ���������ֵ���ڴ��е�pe�ļ�ӳ��Ķ�Ӧ�ı���
	AllPe.pOptH->AddressOfEntryPoint = (WORD)_tcstoul(P_EOP, NULL, 16);
	AllPe.pOptH->ImageBase = (WORD)_tcstoul(P_IMAGEBASE, NULL, 16);
	AllPe.pOptH->SizeOfImage = (WORD)_tcstoul(P_SIZEOFIMAGE, NULL, 16);
	AllPe.pOptH->BaseOfCode = (WORD)_tcstoul(P_BASEOFCODE, NULL, 16);
	AllPe.pOptH->BaseOfData = (WORD)_tcstoul(P_BASEOFDATA, NULL, 16);
	AllPe.pOptH->SectionAlignment = (WORD)_tcstoul(P_SECTIONALIGNMENT, NULL, 16);
	AllPe.pOptH->FileAlignment = (WORD)_tcstoul(P_FILEALIGNMENT, NULL, 16);
	AllPe.pOptH->Magic = (WORD)_tcstoul(P_MAGIC, NULL, 16);
	//�ڶ���
	AllPe.pOptH->Subsystem = (WORD)_tcstoul(P_SUBSYSYSTEM, NULL, 16);
	AllPe.pNtH->FileHeader.NumberOfSections = (WORD)_tcstoul(P_NUMBEROFSECTIONS, NULL, 16);
	AllPe.pNtH->FileHeader.TimeDateStamp = (WORD)_tcstoul(P_TIMEDATASTAMP, NULL, 16);;
	AllPe.pOptH->SizeOfHeaders = (WORD)_tcstoul(P_SIZEOFHEADERS, NULL, 16);
	AllPe.pNtH->FileHeader.Characteristics = (WORD)_tcstoul(P_CHARACTERISTICS, NULL, 16);
	AllPe.pOptH->CheckSum = (WORD)_tcstoul(P_CHECKSUM, NULL, 16);
	AllPe.pNtH->FileHeader.SizeOfOptionalHeader = (WORD)_tcstoul(P_SIZEOFOPTIONALHEADER, NULL, 16);
	AllPe.pOptH->NumberOfRvaAndSizes = (WORD)_tcstoul(P_NUMBEROFRVAANDSIZE, NULL, 16);

	DWORD dwRet = 0;
	DWORD lenght = GetFileSize(AllPe.hFile, NULL);
	SetFilePointer(AllPe.hFile, 0, 0, FILE_BEGIN);
	BOOL  WriteInfo = WriteFile(AllPe.hFile, AllPe.Buf, lenght, &dwRet, NULL);
	//ˢ�»��棡��
	BOOL Flush = FlushFileBuffers(AllPe.hFile);
	int ss = GetLastError();
	MessageBox(L"����ɹ�!");
	UpdateData(FALSE);
	*/
}


void PageFive::OnBnClickedPPosclac()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	PePosCalc CalcDlg;
	CalcDlg.DoModal();
}







