// PePosCalc.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AAA.h"
#include "PePosCalc.h"
#include "afxdialogex.h"


// PePosCalc �Ի���

IMPLEMENT_DYNAMIC(PePosCalc, CDialogEx)

PePosCalc::PePosCalc(CWnd* pParent /*=NULL*/)
	: CDialogEx(PePosCalc::IDD, pParent)
	, mP_Pos_Edit_RA(_T(""))
	, mP_Pos_Edit_RVA(_T(""))
	, mP_Pos_Edit_PianYi(_T(""))
	, mP_Pos_Edit_QuDuan(_T(""))
	, mP_Pos_Edit_ZiJie(_T(""))
{

}

PePosCalc::~PePosCalc()
{
}

void PePosCalc::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Pe_Pos_Edit_Ra, mP_Pos_Edit_RA);
	DDX_Text(pDX, IDC_Pe_Pos_Edit_RVa, mP_Pos_Edit_RVA);
	DDX_Text(pDX, IDC_Pe_Pos_Edit_PianYi, mP_Pos_Edit_PianYi);
	DDX_Text(pDX, IDC_Pe_Pos_Edit_QuDuan, mP_Pos_Edit_QuDuan);
	DDX_Text(pDX, IDC_Pe_Pos_Edit_ZiJie, mP_Pos_Edit_ZiJie);
}


BEGIN_MESSAGE_MAP(PePosCalc, CDialogEx)
	ON_BN_CLICKED(IDC_Pe_Pos_Ra, &PePosCalc::OnBnClickedPePosRa)
	ON_BN_CLICKED(IDC_Pe_Pos_Rva, &PePosCalc::OnBnClickedPePosRva)
	ON_BN_CLICKED(IDC_Pe_Pos_PianYi, &PePosCalc::OnBnClickedPePosPianyi)
	ON_BN_CLICKED(IDC_PePosWork, &PePosCalc::OnBnClickedPeposwork)
	ON_EN_CHANGE(IDC_Pe_Pos_Edit_Ra, &PePosCalc::OnEnChangePePosEditRa)
	ON_EN_CHANGE(IDC_Pe_Pos_Edit_RVa, &PePosCalc::OnEnChangePePosEditRva)
	ON_EN_CHANGE(IDC_Pe_Pos_Edit_PianYi, &PePosCalc::OnEnChangePePosEditPianyi)
END_MESSAGE_MAP()


// PePosCalc ��Ϣ�������


void PePosCalc::OnBnClickedPePosRa()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	LockEdit(IDC_Pe_Pos_Edit_Ra);
}


void PePosCalc::OnBnClickedPePosRva()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	LockEdit(IDC_Pe_Pos_Edit_RVa);
}


void PePosCalc::OnBnClickedPePosPianyi()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	LockEdit(IDC_Pe_Pos_Edit_PianYi);
}


void PePosCalc::OnBnClickedPeposwork()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	DWORD Value;
	if (mP_Pos_Edit_RA == L""&&mP_Pos_Edit_RA == L""&&mP_Pos_Edit_PianYi == L"")
	{
		return;
	}
	if (mP_Pos_Edit_RA != L"")
	{
		Value = AllPe.ChangeNumber(mP_Pos_Edit_RA);
	}
	if (mP_Pos_Edit_RVA != L"")
	{
		Value = AllPe.ChangeNumber(mP_Pos_Edit_RVA);
	}
	if (mP_Pos_Edit_PianYi != L"")
	{
		Value = AllPe.ChangeNumber(mP_Pos_Edit_RVA);
	}
	DWORD ShowValue = SwitchOffset(Value);
	AllPe.InputPeInfo(mP_Pos_Edit_RA, Value + AllPe.pOptH->ImageBase);//���VA
	AllPe.InputPeInfo(mP_Pos_Edit_RVA, Value);//���RVA
	AllPe.InputPeInfo(mP_Pos_Edit_PianYi, ShowValue);//ƫ����
	UpdateData(FALSE);
}


void PePosCalc::OnEnChangePePosEditRa()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	UpdateData(TRUE);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void PePosCalc::OnEnChangePePosEditRva()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	UpdateData(TRUE);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void PePosCalc::OnEnChangePePosEditPianyi()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	UpdateData(TRUE);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

void PePosCalc::LockEdit(int EditId)
{
	CEdit *p1 = (CEdit *)GetDlgItem(IDC_Pe_Pos_Edit_Ra);
	CEdit *p2 = (CEdit *)GetDlgItem(IDC_Pe_Pos_Edit_RVa);
	CEdit *p3 = (CEdit *)GetDlgItem(IDC_Pe_Pos_Edit_PianYi);
	CEdit *p4 = (CEdit *)GetDlgItem(IDC_Pe_Pos_Edit_QuDuan);
	CEdit *p5 = (CEdit *)GetDlgItem(IDC_Pe_Pos_Edit_ZiJie);
	p1->SetReadOnly(TRUE);
	p2->SetReadOnly(TRUE);
	p3->SetReadOnly(TRUE);
	p4->SetReadOnly(TRUE);
	p5->SetReadOnly(TRUE);
	switch (EditId)
	{
	case IDC_Pe_Pos_Edit_Ra:
		p1->SetReadOnly(FALSE);
		break;
	case IDC_Pe_Pos_Edit_RVa:
		p2->SetReadOnly(FALSE);
		break;
	case IDC_Pe_Pos_Edit_PianYi:
		p3->SetReadOnly(FALSE);
		break;
	default:
		break;
	}
	p1->SetWindowText(_T(""));
	p2->SetWindowText(_T(""));
	p3->SetWindowText(_T(""));
}
//ת��ƫ��
DWORD PePosCalc::SwitchOffset(DWORD Rva)
{
	PIMAGE_SECTION_HEADER pSec = IMAGE_FIRST_SECTION(AllPe.pNtH);
	int Num = 0;
	while (!(Rva >= pSec->VirtualAddress&&
		Rva < pSec->VirtualAddress + pSec->SizeOfRawData))
	{
		if (Num>AllPe.pNtH->FileHeader.NumberOfSections)
		{
			mP_Pos_Edit_QuDuan = L"����";
			return Rva;
		}
		++Num;
		++pSec;
	}
	PBYTE data = (PBYTE)(Rva - pSec->VirtualAddress + pSec->PointerToRawData + (long)AllPe.Buf);
	for (int i = 0; i < 10; i++)
	{
		CString str;
		str.Format(L"%X", *(data++));
		mP_Pos_Edit_ZiJie += str;
	}
	mP_Pos_Edit_QuDuan = pSec->Name;
	return Rva - pSec->VirtualAddress + pSec->PointerToRawData;
}
