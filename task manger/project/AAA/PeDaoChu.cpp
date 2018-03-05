// PeDaoChu.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AAA.h"
#include "PeDaoChu.h"
#include "afxdialogex.h"
#include <afxmsg_.h>

// PeDaoChu �Ի���

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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//��ȡ����Ŀ¼
	AllPe.pDatD = &(AllPe.pOptH->DataDirectory[0]);
	//��ȡ����������
	AllPe.pExpD = (PIMAGE_EXPORT_DIRECTORY)(AllPe.Buf + AllPe.RvaOffset(AllPe.pDatD->VirtualAddress));
	//�ж��Ƿ��е�������

	//ȡ��������ĺ�����ַ
	pFunAddr = (PDWORD)(AllPe.Buf + AllPe.RvaOffset(AllPe.pExpD->AddressOfFunctions));	//������ַ
	pFunNameAddr = (PDWORD)(AllPe.Buf + AllPe.RvaOffset(AllPe.pExpD->AddressOfNames));	//��������ַ
	pOrdinalAddr = (PWORD)(AllPe.Buf + AllPe.RvaOffset(AllPe.pExpD->AddressOfNameOrdinals));//������ŵ�ַ

	NumberOfFun = AllPe.pExpD->NumberOfFunctions; //��������
	NumberOfName = AllPe.pExpD->AddressOfNames;	//������������

	//AfxBeginThread(ShowInfo, NULL,0);
	//WaitForSingleObject(hThread, -1);

	ShowInfo();
	ShowLIST();
//	_beginthread(ShowList, 0, NULL);
	
	//ShowList();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

void PeDaoChu::ShowInfo()
{
	//����ƫ�Ʊ��ַ��
	AllPe.InputPeInfo(mP_Dc_1, AllPe.RvaOffset(AllPe.pDatD->VirtualAddress));  //180200
	//("����������
	AllPe.InputPeInfo(mP_Dc_2, AllPe.RvaOffset(AllPe.pExpD->NumberOfFunctions));
	//����ֵ��
	AllPe.InputPeInfo(mP_Dc_3, AllPe.RvaOffset(AllPe.pExpD->Characteristics));
	//������������
	AllPe.InputPeInfo(mP_Dc_4, AllPe.RvaOffset(AllPe.pExpD->NumberOfNames));
	//��ַ��
	AllPe.InputPeInfo(mP_Dc_5, AllPe.RvaOffset(AllPe.pExpD->Base));
	//������ַ��
	AllPe.InputPeInfo(mP_Dc_6, AllPe.pExpD->AddressOfFunctions);
	//���ƣ�
	AllPe.InputPeInfo(mP_Dc_7, AllPe.RvaOffset(AllPe.pExpD->Name));
	//�������Ƶ�ַ��
	AllPe.InputPeInfo(mP_Dc_8, AllPe.pExpD->AddressOfNames);
	//�����ִ���
	mP_Dc_9 = AllPe.PeFile;
	int i = mP_Dc_9.ReverseFind('\\');
	mP_Dc_9.Delete(0, i + 1);
	//��������ŵ�ַ��
	AllPe.InputPeInfo(mP_Dc_10, AllPe.pExpD->AddressOfNameOrdinals);
	UpdateData(FALSE);
}

void PeDaoChu::ShowLIST()
{
	CString str[] = { _T("���"), _T("RVA"), _T("ƫ��"), _T("����") };
	for (int i = 0; i < sizeof(str) / sizeof(str[0]); i++)
	{
		mP_DC_List.InsertColumn(i, str[i], LVCFMT_LEFT, 67);
	}
	for (DWORD i = 0; i < NumberOfFun; i++)
	{

		//�������Ч���� ������һ��
		if (!pFunAddr[i])
		{
			continue;
		}
		//��ʱΪ��Ч����  ����ű�����Ƿ��������� �����ж��Ǻ���������������ŵ���
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