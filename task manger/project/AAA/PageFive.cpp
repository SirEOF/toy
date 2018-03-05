// PageFive.cpp : 实现文件
//

#include "stdafx.h"
#include "AAA.h"
#include "PageFive.h"
#include "afxdialogex.h"
#include "PageTwo.h"
#include "PeQuDuan.h"
#include "PePosCalc.h"
#include "PeMainIndex.h"

// PageFive 对话框

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


// PageFive 消息处理程序


void PageFive::OnEnChangeEdit6()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void PageFive::OnDropFiles(HDROP hDropInfo)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
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
	//设置获取信息结构体
	WIN32_FIND_DATA  stcFData = { 0 };
	//只需要获取一个文件的信息,所以不需要使用循环
	BOOL bWorking = Finder.FindFile(path);
	if (bWorking)
	{
		bWorking = Finder.FindNextFile();
		// 获取文件创建时间
		if (Finder.GetCreationTime(TempTime))
		{
			P_BUILDTIME = TempTime.Format(_T("%c"));
		}
		// 获取文件最后修改时间
		if (Finder.GetLastWriteTime(TempTime))
		{
			P_LASTINCORTIME = TempTime.Format(_T("%c"));
		}
		//获取文件大小
		P_SIZEOFFILE.Format(L"%d", Finder.GetLength());
		P_SIZEOFFILE = P_SIZEOFFILE + L"    字节";
		//获取文件名称
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
	//获取字节长度   
	iLength = WideCharToMultiByte(CP_ACP, 0, tchar, -1, NULL, 0, NULL, NULL);
	//将tchar值赋给_char    
	WideCharToMultiByte(CP_ACP, 0, tchar, -1, _char, iLength, NULL, NULL);
}

void PageFive::OnDropPE()
{
	ShowPeInfo();
	UpdateData(FALSE);
}

void PageFive::ShowPeInfo()
{
	
	// TODO:  在此添加额外的初始化
	if (AllPe.pDatD == NULL)
	{
		return;
	}
	AllPe.InputPeInfo(P_EOP, AllPe.pOptH->AddressOfEntryPoint);
	AllPe.InputPeInfo(P_IMAGEBASE, AllPe.pOptH->ImageBase);					//镜像地址
	AllPe.InputPeInfo(P_SIZEOFIMAGE, AllPe.pOptH->SizeOfImage);				//镜像大小
	AllPe.InputPeInfo(P_BASEOFCODE, AllPe.pOptH->BaseOfCode);					//代码基址
	AllPe.InputPeInfo(P_BASEOFDATA, AllPe.pOptH->BaseOfData);					//数据基址
	AllPe.InputPeInfo(P_SECTIONALIGNMENT, AllPe.pOptH->SectionAlignment);		//块对齐
	AllPe.InputPeInfo(P_FILEALIGNMENT, AllPe.pOptH->FileAlignment);			//文件块对齐
	AllPe.InputPeInfo(P_MAGIC, AllPe.pOptH->Magic);							//标志字
	//第二版
	AllPe.InputPeInfo(P_SUBSYSYSTEM, AllPe.pOptH->Subsystem);					//子系统
	AllPe.InputPeInfo(P_NUMBEROFSECTIONS, AllPe.pNtH->FileHeader.NumberOfSections);//区段数目
	AllPe.InputPeInfo(P_TIMEDATASTAMP, AllPe.pNtH->FileHeader.TimeDateStamp);//日期时间标志
	AllPe.InputPeInfo(P_SIZEOFHEADERS, AllPe.pOptH->SizeOfHeaders);			//部首大小
	AllPe.InputPeInfo(P_CHARACTERISTICS, AllPe.pNtH->FileHeader.Characteristics);//特征值
	AllPe.InputPeInfo(P_CHECKSUM, AllPe.pOptH->CheckSum);						//校验和
	AllPe.InputPeInfo(P_SIZEOFOPTIONALHEADER, AllPe.pNtH->FileHeader.SizeOfOptionalHeader);//可选头部大小
	AllPe.InputPeInfo(P_NUMBEROFRVAANDSIZE, AllPe.pOptH->NumberOfRvaAndSizes);//RVA数及大小
	
}

void PageFive::OutPutPeInfo(CString &m_PeInfo, DWORD PeValue)
{
	CString str;
	str.Format(L"%08X", PeValue);//转16进制
	m_PeInfo = str;
	UpdateData(FALSE);
}



void PageFive::OnBnClickedPQuduan()
{
	//memcpy(Path, SZPath, MAX_PATH);
	// TODO:  在此添加控件通知处理程序代码
	PeQuDuan QuDDlg;
	QuDDlg.DoModal();
}


void PageFive::OnBnClickedPMulu()
{
	// TODO:  在此添加控件通知处理程序代码
	PeMainIndex  PeMainDlg;
	PeMainDlg.DoModal();

}


void PageFive::OnBnClickedPBaocun()
{
	// TODO:  在此添加控件通知处理程序代码
	/*
	UpdateData(TRUE);
	//将控件传回来的值给内存中的pe文件映射的对应的变量
	AllPe.pOptH->AddressOfEntryPoint = (WORD)_tcstoul(P_EOP, NULL, 16);
	AllPe.pOptH->ImageBase = (WORD)_tcstoul(P_IMAGEBASE, NULL, 16);
	AllPe.pOptH->SizeOfImage = (WORD)_tcstoul(P_SIZEOFIMAGE, NULL, 16);
	AllPe.pOptH->BaseOfCode = (WORD)_tcstoul(P_BASEOFCODE, NULL, 16);
	AllPe.pOptH->BaseOfData = (WORD)_tcstoul(P_BASEOFDATA, NULL, 16);
	AllPe.pOptH->SectionAlignment = (WORD)_tcstoul(P_SECTIONALIGNMENT, NULL, 16);
	AllPe.pOptH->FileAlignment = (WORD)_tcstoul(P_FILEALIGNMENT, NULL, 16);
	AllPe.pOptH->Magic = (WORD)_tcstoul(P_MAGIC, NULL, 16);
	//第二版
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
	//刷新缓存！！
	BOOL Flush = FlushFileBuffers(AllPe.hFile);
	int ss = GetLastError();
	MessageBox(L"保存成功!");
	UpdateData(FALSE);
	*/
}


void PageFive::OnBnClickedPPosclac()
{
	// TODO:  在此添加控件通知处理程序代码
	PePosCalc CalcDlg;
	CalcDlg.DoModal();
}







