// PeDelay.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AAA.h"
#include "PeDelay.h"
#include "afxdialogex.h"


// PeDelay �Ի���

IMPLEMENT_DYNAMIC(PeDelay, CDialogEx)

PeDelay::PeDelay(CWnd* pParent /*=NULL*/)
	: CDialogEx(PeDelay::IDD, pParent)
	, mP_EDIT_Pe_Delat_1(_T(""))
	, mP_EDIT_Pe_Delat_2(_T(""))
	, mP_EDIT_Pe_Delat_3(_T(""))
	, mP_EDIT_Pe_Delat_4(_T(""))
	, mP_EDIT_Pe_Delat_5(_T(""))
	, mP_EDIT_Pe_Delat_6(_T(""))
{

}

PeDelay::~PeDelay()
{
}

void PeDelay::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_Pe_Delat_1, mP_EDIT_Pe_Delat_1);
	DDX_Text(pDX, IDC_EDIT_Pe_Delat_2, mP_EDIT_Pe_Delat_2);
	DDX_Text(pDX, IDC_EDIT_Pe_Delat_3, mP_EDIT_Pe_Delat_3);
	DDX_Text(pDX, IDC_EDIT_Pe_Delat_4, mP_EDIT_Pe_Delat_4);
	DDX_Text(pDX, IDC_EDIT_Pe_Delat_5, mP_EDIT_Pe_Delat_5);
	DDX_Text(pDX, IDC_EDIT_Pe_Delat_6, mP_EDIT_Pe_Delat_6);
}


BEGIN_MESSAGE_MAP(PeDelay, CDialogEx)
END_MESSAGE_MAP()


// PeDelay ��Ϣ�������
BOOL PeDelay::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CString temp;
	temp.Format(L"%08X", pDelay->DllNameRVA);
	//mP_EDIT_Pe_Delat_1.SetWindowTextW(temp);
	GetDlgItem(IDC_EDIT_Pe_Delat_1)->SetWindowTextW(temp);

	temp.Format(L"%08X", pDelay->ImportAddressTableRVA);
	//mP_EDIT_Pe_Delat_2.SetWindowTextW(temp);
	GetDlgItem(IDC_EDIT_Pe_Delat_2)->SetWindowTextW(temp);

	temp.Format(L"%08X", pDelay->ImportNameTableRVA);
	//mP_EDIT_Pe_Delat_3.SetWindowTextW(temp);
	GetDlgItem(IDC_EDIT_Pe_Delat_3)->SetWindowTextW(temp);

	temp.Format(L"%08X", pDelay->BoundImportAddressTableRVA);
	//mP_EDIT_Pe_Delat_4.SetWindowTextW(temp);
	GetDlgItem(IDC_EDIT_Pe_Delat_4)->SetWindowTextW(temp);

	temp.Format(L"%08X", pDelay->UnloadInformationTableRVA);
	//mP_EDIT_Pe_Delat_5.SetWindowTextW(temp);
	GetDlgItem(IDC_EDIT_Pe_Delat_5)->SetWindowTextW(temp);

	temp.Format(L"%08X", pDelay->ModuleHandleRVA);
	//mP_EDIT_Pe_Delat_6.SetWindowTextW(temp);
	GetDlgItem(IDC_EDIT_Pe_Delat_6)->SetWindowTextW(temp);

	return TRUE;  
	// �쳣:  OCX ����ҳӦ���� FALSE
}
