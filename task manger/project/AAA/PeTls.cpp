// PeTls.cpp : 实现文件
//

#include "stdafx.h"
#include "AAA.h"
#include "PeTls.h"
#include "afxdialogex.h"


// PeTls 对话框

IMPLEMENT_DYNAMIC(PeTls, CDialogEx)

PeTls::PeTls(CWnd* pParent /*=NULL*/)
	: CDialogEx(PeTls::IDD, pParent)
	, mP_EDIT_Pe_TSL_1(_T(""))
	, mP_EDIT_Pe_TSL_2(_T(""))
	, mP_EDIT_Pe_TSL_3(_T(""))
	, mP_EDIT_Pe_TSL_4(_T(""))
	, mP_EDIT_Pe_TSL_5(_T(""))
	, mP_EDIT_Pe_TSL_6(_T(""))
{

}

PeTls::~PeTls()
{
}

void PeTls::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_Pe_TSL_1, mP_EDIT_Pe_TSL_1);
	DDX_Text(pDX, IDC_EDIT_Pe_TSL_2, mP_EDIT_Pe_TSL_2);
	DDX_Text(pDX, IDC_EDIT_Pe_TSL_3, mP_EDIT_Pe_TSL_3);
	DDX_Text(pDX, IDC_EDIT_Pe_TSL_4, mP_EDIT_Pe_TSL_4);
	DDX_Text(pDX, IDC_EDIT_Pe_TSL_5, mP_EDIT_Pe_TSL_5);
	DDX_Text(pDX, IDC_EDIT_Pe_TSL_6, mP_EDIT_Pe_TSL_6);
}


BEGIN_MESSAGE_MAP(PeTls, CDialogEx)
	ON_BN_CLICKED(IDC_Btn_Pe_TSL, &PeTls::OnBnClickedBtnPeTsl)
END_MESSAGE_MAP()


// PeTls 消息处理程序
BOOL PeTls:: OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
	PIMAGE_DATA_DIRECTORY pOptional = &(AllPe.pDatD[9]);
	PIMAGE_TLS_DIRECTORY32 pTls = (PIMAGE_TLS_DIRECTORY32)((long)AllPe.Buf + AllPe.RvaOffset(pOptional->VirtualAddress));
	mP_EDIT_Pe_TSL_1.Format(L"%X", pTls->StartAddressOfRawData);
	mP_EDIT_Pe_TSL_2.Format(L"%X", pTls->EndAddressOfRawData);
	mP_EDIT_Pe_TSL_3.Format(L"%X", pTls->AddressOfIndex);
	mP_EDIT_Pe_TSL_4.Format(L"%X", pTls->AddressOfCallBacks);
	mP_EDIT_Pe_TSL_5.Format(L"%X", pTls->SizeOfZeroFill);
	mP_EDIT_Pe_TSL_6.Format(L"%X", pTls->Characteristics);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
}

void PeTls::OnBnClickedBtnPeTsl()
{
	// TODO:  在此添加控件通知处理程序代码
	SendMessage(WM_CLOSE);
}
