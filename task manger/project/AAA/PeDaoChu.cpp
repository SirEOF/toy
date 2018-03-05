// PeDaoChu.cpp : 实现文件
//

#include "stdafx.h"
#include "AAA.h"
#include "PeDaoChu.h"
#include "afxdialogex.h"
#include <afxmsg_.h>

// PeDaoChu 对话框

IMPLEMENT_DYNAMIC(PeDaoChu, CDialogEx)

PeDaoChu::PeDaoChu(CWnd* pParent /*=NULL*/)
	: CDialogEx(PeDaoChu::IDD, pParent)
	, mP_Dc_1(_T(""))
	, mP_Dc_2(_T(""))
	, mP_Dc_3(_T(""))
	, mP_Dc_4(_T(""))
	, mP_Dc_5(_T(""))
	, mP_Dc_6(_T(""))
	, mP_Dc_7(_T(""))
	, mP_Dc_8(_T(""))
	, mP_Dc_9(_T(""))
	, mP_Dc_10(_T(""))
{

}

PeDaoChu::~PeDaoChu()
{
}

void PeDaoChu::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Pe_DC_EDIT_SHUCHUPY, mP_Dc_1);
	DDX_Text(pDX, IDC_Pe_DC_EDIT_HANSHUSHULIANG, mP_Dc_2);
	DDX_Text(pDX, IDC_Pe_DC_EDIT_TEZHENGZHI, mP_Dc_3);
	DDX_Text(pDX, IDC_Pe_DC_EDIT_HANSHUMINGSHULIANG, mP_Dc_4);
	DDX_Text(pDX, IDC_Pe_DC_EDIT_JIZHI, mP_Dc_5);
	DDX_Text(pDX, IDC_Pe_DC_EDIT_HANSHUDIZHI, mP_Dc_6);
	DDX_Text(pDX, IDC_Pe_DC_EDIT_MINGCHENG, mP_Dc_7);
	DDX_Text(pDX, IDC_Pe_DC_EDIT_HANSHUMINGDIZHI, mP_Dc_8);
	DDX_Text(pDX, IDC_Pe_DC_EDIT_ZICHUAN, mP_Dc_9);
	DDX_Text(pDX, IDC_Pe_DC_EDIT_XUHAODIZHI, mP_Dc_10);
	DDX_Control(pDX, IDC_Pe_DC_LIST, mP_DC_List);
}


BEGIN_MESSAGE_MAP(PeDaoChu, CDialogEx)
	
END_MESSAGE_MAP()


DWORD NumberOfFun;
DWORD NumberOfName;
PDWORD pFunAddr;
PDWORD pFunNameAddr;
PWORD pOrdinalAddr;

BOOL PeDaoChu::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//获取数据目录
	AllPe.pDatD = &(AllPe.pOptH->DataDirectory[0]);
	//获取导出表数据
	AllPe.pExpD = (PIMAGE_EXPORT_DIRECTORY)(AllPe.Buf + AllPe.RvaOffset(AllPe.pDatD->VirtualAddress));
	//判断是否有导出函数

	//取出三个表的函数地址
	pFunAddr = (PDWORD)(AllPe.Buf + AllPe.RvaOffset(AllPe.pExpD->AddressOfFunctions));	//函数地址
	pFunNameAddr = (PDWORD)(AllPe.Buf + AllPe.RvaOffset(AllPe.pExpD->AddressOfNames));	//函数名地址
	pOrdinalAddr = (PWORD)(AllPe.Buf + AllPe.RvaOffset(AllPe.pExpD->AddressOfNameOrdinals));//函数序号地址

	NumberOfFun = AllPe.pExpD->NumberOfFunctions; //函数数量
	NumberOfName = AllPe.pExpD->AddressOfNames;	//函数名称数量

	//AfxBeginThread(ShowInfo, NULL,0);
	//WaitForSingleObject(hThread, -1);

	ShowInfo();
	ShowLIST();
//	_beginthread(ShowList, 0, NULL);
	
	//ShowList();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void PeDaoChu::ShowInfo()
{
	//函数偏移表地址：
	AllPe.InputPeInfo(mP_Dc_1, AllPe.RvaOffset(AllPe.pDatD->VirtualAddress));  //180200
	//("函数数量：
	AllPe.InputPeInfo(mP_Dc_2, AllPe.RvaOffset(AllPe.pExpD->NumberOfFunctions));
	//特征值：
	AllPe.InputPeInfo(mP_Dc_3, AllPe.RvaOffset(AllPe.pExpD->Characteristics));
	//函数名数量：
	AllPe.InputPeInfo(mP_Dc_4, AllPe.RvaOffset(AllPe.pExpD->NumberOfNames));
	//基址：
	AllPe.InputPeInfo(mP_Dc_5, AllPe.RvaOffset(AllPe.pExpD->Base));
	//函数地址：
	AllPe.InputPeInfo(mP_Dc_6, AllPe.pExpD->AddressOfFunctions);
	//名称：
	AllPe.InputPeInfo(mP_Dc_7, AllPe.RvaOffset(AllPe.pExpD->Name));
	//函数名称地址：
	AllPe.InputPeInfo(mP_Dc_8, AllPe.pExpD->AddressOfNames);
	//名称字串：
	mP_Dc_9 = AllPe.PeFile;
	int i = mP_Dc_9.ReverseFind('\\');
	mP_Dc_9.Delete(0, i + 1);
	//函数名序号地址：
	AllPe.InputPeInfo(mP_Dc_10, AllPe.pExpD->AddressOfNameOrdinals);
	UpdateData(FALSE);
}

void PeDaoChu::ShowLIST()
{
	CString str[] = { _T("序号"), _T("RVA"), _T("偏移"), _T("函数") };
	for (int i = 0; i < sizeof(str) / sizeof(str[0]); i++)
	{
		mP_DC_List.InsertColumn(i, str[i], LVCFMT_LEFT, 67);
	}
	for (DWORD i = 0; i < NumberOfFun; i++)
	{

		//如果是无效函数 进行下一次
		if (!pFunAddr[i])
		{
			continue;
		}
		//此时为有效函数  在序号表查找是否有这个序号 用以判断是函数名导出函数序号导出
		DWORD j = 0;
		CString str;
		for (; j < NumberOfName; j++)
		{

			if (i == pOrdinalAddr[j])
			{
				break;
			}
		}
		if (j != NumberOfName)
		{
			str.Format(L"%08X", pOrdinalAddr[j] + AllPe.pExpD->Base);
			mP_DC_List.InsertItem(i, str);
			str.Format(L"%08X", pFunAddr[i]);
			mP_DC_List.SetItemText(i, 1, str);
			str.Format(L"%08X", AllPe.RvaOffset(pFunAddr[i]));
			mP_DC_List.SetItemText(i, 2, str);
			CString str((AllPe.Buf + AllPe.RvaOffset(pFunNameAddr[j])));
			mP_DC_List.SetItemText(i, 3, str);
		}
		else
		{
			str.Format(L"%08X", i + AllPe.pExpD->Base);
			mP_DC_List.InsertItem(i, str);
			mP_DC_List.SetItemText(i, 1, L"-");
			mP_DC_List.SetItemText(i, 2, L"-");
			if (strcmp((AllPe.Buf + AllPe.RvaOffset(pFunNameAddr[i])), "") == 0)
			{
				mP_DC_List.SetItemText(i, 3, L"-");
			}
		}
	}
}