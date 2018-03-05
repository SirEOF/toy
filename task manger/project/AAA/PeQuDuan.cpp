// PeQuDuan.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AAA.h"
#include "PeQuDuan.h"
#include "afxdialogex.h"


// PeQuDuan �Ի���

IMPLEMENT_DYNAMIC(PeQuDuan, CDialogEx)

PeQuDuan::PeQuDuan(CWnd* pParent /*=NULL*/)
	: CDialogEx(PeQuDuan::IDD, pParent)
{

}

PeQuDuan::~PeQuDuan()
{
}

void PeQuDuan::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PeQuDuanList, mP_QD_list);
}


BEGIN_MESSAGE_MAP(PeQuDuan, CDialogEx)
END_MESSAGE_MAP()



BOOL PeQuDuan::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	mP_QD_list.InsertColumn(0, L"Name", LVCFMT_LEFT, 40);
	mP_QD_list.InsertColumn(1, L"Voffset", LVCFMT_LEFT, 70);
	mP_QD_list.InsertColumn(2, L"Vsize", LVCFMT_LEFT, 70);
	mP_QD_list.InsertColumn(3, L"Roffset", LVCFMT_LEFT, 70);
	mP_QD_list.InsertColumn(4, L"Rsize", LVCFMT_LEFT, 70);
	mP_QD_list.InsertColumn(5, L"��־", LVCFMT_LEFT, 80);
	ShowQuDuan();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

void PeQuDuan::ShowQuDuan()
{
	if (AllPe.pSecH == NULL)
	{
		return;
	}
	PIMAGE_SECTION_HEADER pSec = AllPe.pSecH;
	CString str;
	WORD Num = AllPe.pNtH->FileHeader.NumberOfSections;
	int i = 0;
	while (i < Num)
	{
		str = pSec->Name;
		mP_QD_list.InsertItem(i, str);
		str.Format(L"%08X", pSec->VirtualAddress);
		mP_QD_list.SetItemText(i, 1, str);
		str.Format(L"%08X", pSec->Misc.VirtualSize);
		mP_QD_list.SetItemText(i, 2, str);
		str.Format(L"%08X", pSec->PointerToRawData);
		mP_QD_list.SetItemText(i, 3, str);
		str.Format(L"%08X", pSec->SizeOfRawData);
		mP_QD_list.SetItemText(i, 4, str);
		str.Format(L"%08X", pSec->Characteristics);
		mP_QD_list.SetItemText(i, 5, str);
		++pSec;
		i++;
	}
}


