// PeMainIndex.cpp : 实现文件
//

#include "stdafx.h"
#include "AAA.h"
#include "PeMainIndex.h"
#include "afxdialogex.h"
#include "PeDaoChu.h"
#include "PeDaoRu.h"
#include "PeZiYuan.h"
#include "PeChongDW.h"
#include "PeTls.h"
#include "PeDelay.h"


// PeMainIndex 对话框

IMPLEMENT_DYNAMIC(PeMainIndex, CDialogEx)

PeMainIndex::PeMainIndex(CWnd* pParent /*=NULL*/)
	: CDialogEx(PeMainIndex::IDD, pParent)
	, Pe_1_RAV(_T(""))
	, Pe_1_SIZE(_T(""))
	, Pe_2_RAV(_T(""))
	, Pe_2_SIZE(_T(""))
	, Pe_3_RAV(_T(""))
	, Pe_3_SIZE(_T(""))
	, Pe_4_RAV(_T(""))
	, Pe_4_SIZE(_T(""))
	, Pe_5_RAV(_T(""))
	, Pe_5_SIZE(_T(""))
	, Pe_6_RAV(_T(""))
	, Pe_6_SIZE(_T(""))
	, Pe_7_RAV(_T(""))
	, Pe_7_SIZE(_T(""))
	, Pe_8_RAV(_T(""))
	, Pe_8_SIZE(_T(""))
	, Pe_9_RAV(_T(""))
	, Pe_9_SIZE(_T(""))
	, Pe_10_RAV(_T(""))
	, Pe_10_SIZE(_T(""))
	, Pe_11_RAV(_T(""))
	, Pe_11_SIZE(_T(""))
	, Pe_12_RAV(_T(""))
	, Pe_12_SIZE(_T(""))
	, Pe_13_RAV(_T(""))
	, Pe_13_SIZE(_T(""))
	, Pe_14_RAV(_T(""))
	, Pe_14_SIZE(_T(""))
	, Pe_15_RAV(_T(""))
	, Pe_15_SIZE(_T(""))
	, Pe_16_RAV(_T(""))
	, Pe_16_SIZE(_T(""))
{

}

PeMainIndex::~PeMainIndex()
{
}

void PeMainIndex::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_One_RAV, Pe_1_RAV);
	DDX_Text(pDX, IDC_EDIT_One_Size, Pe_1_SIZE);
	DDX_Text(pDX, IDC_EDIT_Two_Rav, Pe_2_RAV);
	DDX_Text(pDX, IDC_EDIT_Two_Size, Pe_2_SIZE);
	DDX_Text(pDX, IDC_EDIT_Three_RAV, Pe_3_RAV);
	DDX_Text(pDX, IDC_EDIT_Three_Size, Pe_3_SIZE);
	DDX_Text(pDX, IDC_EDIT_Four_RAV, Pe_4_RAV);
	DDX_Text(pDX, IDC_EDIT_Four_Size, Pe_4_SIZE);
	DDX_Text(pDX, IDC_EDIT_Five_RAV, Pe_5_RAV);
	DDX_Text(pDX, IDC_EDIT_Five_Szie, Pe_5_SIZE);
	DDX_Text(pDX, IDC_EDIT_Six_RAV, Pe_6_RAV);
	DDX_Text(pDX, IDC_EDIT_Six_Size, Pe_6_SIZE);
	DDX_Text(pDX, IDC_EDIT_Seven_RAV, Pe_7_RAV);
	DDX_Text(pDX, IDC_EDIT_Seven_Size, Pe_7_SIZE);
	DDX_Text(pDX, IDC_EDIT_EIGHT_RAV, Pe_8_RAV);
	DDX_Text(pDX, IDC_EDIT_EIGHT_Size, Pe_8_SIZE);
	DDX_Text(pDX, IDC_EDIT_Nine_RAV, Pe_9_RAV);
	DDX_Text(pDX, IDC_EDIT_Nine_Size, Pe_9_SIZE);
	DDX_Text(pDX, IDC_EDIT_Ten_RAV, Pe_10_RAV);
	DDX_Text(pDX, IDC_EDIT_Ten_Size, Pe_10_SIZE);
	DDX_Text(pDX, IDC_EDIT_ELEVEN_RAV, Pe_11_RAV);
	DDX_Text(pDX, IDC_EDIT_Eleven_Size, Pe_11_SIZE);
	DDX_Text(pDX, IDC_EDIT_12_RAV, Pe_12_RAV);
	DDX_Text(pDX, IDC_EDIT_12_Size, Pe_12_SIZE);
	DDX_Text(pDX, IDC_EDIT_13_RAV, Pe_13_RAV);
	DDX_Text(pDX, IDC_EDIT_13_Size, Pe_13_SIZE);
	DDX_Text(pDX, IDC_EDIT_14_RAV, Pe_14_RAV);
	DDX_Text(pDX, IDC_EDIT_14_Size, Pe_14_SIZE);
	DDX_Text(pDX, IDC_EDIT_15_RAV, Pe_15_RAV);
	DDX_Text(pDX, IDC_EDIT_15_Size, Pe_15_SIZE);
	DDX_Text(pDX, IDC_EDIT_16_RAV, Pe_16_RAV);
	DDX_Text(pDX, IDC_EDIT_16_Size, Pe_16_SIZE);
}


BEGIN_MESSAGE_MAP(PeMainIndex, CDialogEx)
	
	ON_BN_CLICKED(IDC_BTN_DAOCHU, &PeMainIndex::OnBnClickedBtnDaochu)
	ON_BN_CLICKED(IDC_BTN_DAORU, &PeMainIndex::OnBnClickedBtnDaoru)
	ON_BN_CLICKED(IDC_BTN_ZIYUAN, &PeMainIndex::OnBnClickedBtnZiyuan)
	ON_BN_CLICKED(IDC_BTN_CHONGDINGWEI, &PeMainIndex::OnBnClickedBtnChongdingwei)
	
	ON_BN_CLICKED(IDC_BTN_YANCHISHURU, &PeMainIndex::OnBnClickedBtnYanchishuru)
	ON_BN_CLICKED(IDC_BTN_Pe_TLs, &PeMainIndex::OnBnClickedBtnPeTls)
END_MESSAGE_MAP()


// PeMainIndex 消息处理程序
BOOL PeMainIndex::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	ShowInfo();//显示界面
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void PeMainIndex::ShowInfo()
{
	if (AllPe.pDatD == NULL)
	{
		return;
	}
	AllPe.InputPeInfo(Pe_1_RAV, AllPe.pDatD[0].VirtualAddress);
	AllPe.InputPeInfo(Pe_1_SIZE, AllPe.pDatD[0].Size);
	AllPe.InputPeInfo(Pe_2_RAV, AllPe.pDatD[1].VirtualAddress);
	AllPe.InputPeInfo(Pe_2_SIZE, AllPe.pDatD[1].Size);
	AllPe.InputPeInfo(Pe_3_RAV, AllPe.pDatD[2].VirtualAddress);
	AllPe.InputPeInfo(Pe_3_SIZE, AllPe.pDatD[2].Size);
	AllPe.InputPeInfo(Pe_4_RAV, AllPe.pDatD[3].VirtualAddress);
	AllPe.InputPeInfo(Pe_4_SIZE, AllPe.pDatD[3].Size);
	AllPe.InputPeInfo(Pe_5_RAV, AllPe.pDatD[4].VirtualAddress);
	AllPe.InputPeInfo(Pe_5_SIZE, AllPe.pDatD[4].Size);
	AllPe.InputPeInfo(Pe_6_RAV, AllPe.pDatD[5].VirtualAddress);
	AllPe.InputPeInfo(Pe_6_SIZE, AllPe.pDatD[5].Size);
	AllPe.InputPeInfo(Pe_7_RAV, AllPe.pDatD[6].VirtualAddress);
	AllPe.InputPeInfo(Pe_7_SIZE, AllPe.pDatD[6].Size);
	AllPe.InputPeInfo(Pe_8_RAV, AllPe.pDatD[7].VirtualAddress);
	AllPe.InputPeInfo(Pe_8_SIZE, AllPe.pDatD[7].Size);
	AllPe.InputPeInfo(Pe_9_RAV, AllPe.pDatD[8].VirtualAddress);
	AllPe.InputPeInfo(Pe_9_SIZE, AllPe.pDatD[8].Size);
	AllPe.InputPeInfo(Pe_10_RAV, AllPe.pDatD[9].VirtualAddress);
	AllPe.InputPeInfo(Pe_10_SIZE, AllPe.pDatD[9].Size);
	AllPe.InputPeInfo(Pe_11_RAV, AllPe.pDatD[10].VirtualAddress);
	AllPe.InputPeInfo(Pe_11_SIZE, AllPe.pDatD[10].Size);
	AllPe.InputPeInfo(Pe_12_RAV, AllPe.pDatD[11].VirtualAddress);
	AllPe.InputPeInfo(Pe_12_SIZE, AllPe.pDatD[11].Size);
	AllPe.InputPeInfo(Pe_13_RAV, AllPe.pDatD[12].VirtualAddress);
	AllPe.InputPeInfo(Pe_13_SIZE, AllPe.pDatD[12].Size);
	AllPe.InputPeInfo(Pe_14_RAV, AllPe.pDatD[13].VirtualAddress);
	AllPe.InputPeInfo(Pe_14_SIZE, AllPe.pDatD[13].Size);
	AllPe.InputPeInfo(Pe_15_RAV, AllPe.pDatD[14].VirtualAddress);
	AllPe.InputPeInfo(Pe_15_SIZE, AllPe.pDatD[14].Size);
	AllPe.InputPeInfo(Pe_16_RAV, AllPe.pDatD[15].VirtualAddress);
	AllPe.InputPeInfo(Pe_16_SIZE, AllPe.pDatD[15].Size);
	UpdateData(FALSE);
	

}

void PeMainIndex::OutPutPeInfo(CString &m_RvaInfo, CString &m_SizeInfo, DWORD RvaValue, DWORD SizeValue)
{
	CString StrRvaValue, StrSizeValue;
	StrRvaValue.Format(L"%08X", RvaValue);//转16进制
	StrSizeValue.Format(L"%08X", SizeValue);//转16进制
	m_RvaInfo = StrRvaValue;
	m_SizeInfo = StrSizeValue;
	UpdateData(FALSE);
}


void PeMainIndex::OnBnClickedBtnDaochu()
{
	// TODO:  在此添加控件通知处理程序代码
	PeDaoChu DcDlg;
	DcDlg.DoModal();
}


void PeMainIndex::OnBnClickedBtnDaoru()
{
	// TODO:  在此添加控件通知处理程序代码
	PeDaoRu DrDlg;
	DrDlg.DoModal();
}


void PeMainIndex::OnBnClickedBtnZiyuan()
{
	// TODO:  在此添加控件通知处理程序代码

	PeZiYuan ZyDlg;
	ZyDlg.DoModal();
}


void PeMainIndex::OnBnClickedBtnChongdingwei()
{
	// TODO:  在此添加控件通知处理程序代码
	PeChongDW CdwDlg;
	CdwDlg.DoModal();
}


void PeMainIndex::OnBnClickedBtnYanchishuru()
{
	// TODO:  在此添加控件通知处理程序代码
// 	PIMAGE_DATA_DIRECTORY pData = pOptional->DataDirectory;
// 	QWORD RVA = pData[13].VirtualAddress;
// 	PIMAGE_SECTION_HEADER pSection1 = pSection;
// 	while (!(RVA >= pSection1->VirtualAddress&&
// 		RVA < pSection1->VirtualAddress + pSection1->SizeOfRawData))
// 	{
// 		++pSection1;
// 		if (pSection1->PointerToRawData == 0)
// 			return;
// 	}
	TCHAR ch2[10];
	GetDlgItem(IDC_EDIT_14_RAV)->GetWindowText(ch2, 10);
	int a = _ttoi(ch2);
	if ( a== 0)
	{
		return ;
	}

	PeDelay DelayDlg;
	DelayDlg.DoModal();
}


void PeMainIndex::OnBnClickedBtnPeTls()
{
	// TODO:  在此添加控件通知处理程序代码
	PeTls tLsDlg;
	tLsDlg.DoModal();
}
