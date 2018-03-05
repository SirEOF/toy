// PeChongDW.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AAA.h"
#include "PeChongDW.h"
#include "afxdialogex.h"
#include <vector>
using namespace std;

vector<PIMAGE_BASE_RELOCATION> m_VecpBseRInfo;

DWORD v;
/***************-�ض�λ��-*****************/
//��һ����Ա������
typedef struct _RELOCINFO
{
	DWORD dwRelocRVA;		//��Ҫ�ض�λ����������ַ
	DWORD dwOffset;			//������������ַ������ļ�����
	BYTE bType;				//�ض�λ��ʽ
	DWORD dwRelocValue;		//��������ļ�ƫ��ȡ�������� ������ݾ��������ַ��VA��
	BYTE bData[10];			//�øղŵĵ�ַ��VA����ȥ��ַ�õ���������ַRVA �������ļ�ƫ�� �����е�����ȡ�� �ŵ��������
}RELOCINFO, *PRELOCINFO;

//�ڶ�����Ա������
typedef struct _RELOCAREAINFO
{
	CHAR szSectionName[8];  //�������ڵĽ���
	DWORD dwAreaRVA;		//�����ַ
	DWORD NumberOfReloc;	//��������ض�λ�ľ������
	std::vector<RELOCINFO> VecRelocInfo;//��������ض�λ�ľ�����Ϣ
}RELOCAREAINFO, *PRELOCAREAINFO;

vector<RELOCAREAINFO> m_VecRelocAreaInfo;
//��������Ա������
typedef struct _TYPEOFFSET
{
	WORD Offset : 12;		//ƫ��ֵ
	WORD Type : 4;		//�ض�λ���ԣ���ʽ��
}TYPEOFFSET, *PTYPEOFFSET;

//�ض�λ��Ҫ ��������΢��Щ��ͬ
DWORD RelCalcOffset(DWORD Rva, PIMAGE_NT_HEADERS32 pNtH, char *TempBuf, PCHAR pName = NULL, PCHAR pData = NULL, int Flag = NULL)
{
	//PIMAGE_NT_HEADERS32 pnt=pNtH;
	PIMAGE_SECTION_HEADER pSecHTemp = IMAGE_FIRST_SECTION(pNtH);//����ͷ
	int index = 0;

	while (!(Rva >= pSecHTemp->VirtualAddress&&
		Rva<pSecHTemp->VirtualAddress + pSecHTemp->SizeOfRawData))
	{
		//�����������λ�û���ҵ�
		if (index>pNtH->FileHeader.NumberOfSections)
		{
			//	m_Section=L"����";
			////	DWORD a[5];
			//	_memccpy(&Address,pSecHTemp,6,24);
			//	//Address=(int);
			if (Flag == 2)
			{
				return Rva - pNtH->OptionalHeader.ImageBase;
			}
			return Rva;
		}
		++index;
		++pSecHTemp;
	}
	//��ȡ������
	if (pName != NULL)
	{
		//return Rva-pNtH->OptionalHeader.ImageBase;
		memcpy(pName, pSecHTemp->Name, 8);
	}
	v = Rva - pSecHTemp->VirtualAddress + pSecHTemp->PointerToRawData;;
	DWORD iiii = (long)TempBuf + v;
	//��ȡ����
	if (pData != NULL)
	{
		//if (Flag==NULL)
		//{
		//	return Rva-pNtH->OptionalHeader.ImageBase;
		//}
		if (Flag == 2)
		{
			return Rva - pNtH->OptionalHeader.ImageBase;
		}
		//flag Ϊ1ʱ 
		memcpy(pData, PCHAR((long)TempBuf + v), 10);
	}
	return v;
}
/***************-�ض�λ��-*****************/

IMPLEMENT_DYNAMIC(PeChongDW, CDialogEx)

PeChongDW::PeChongDW(CWnd* pParent /*=NULL*/)
	: CDialogEx(PeChongDW::IDD, pParent)
{

}

PeChongDW::~PeChongDW()
{
}

void PeChongDW::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Pe_CDW_L1, mP_Cdw_L1);
	DDX_Control(pDX, IDC_Pe_CDW_L2, mP_Cdw_L2);
}


BEGIN_MESSAGE_MAP(PeChongDW, CDialogEx)
	ON_NOTIFY(NM_CLICK, IDC_Pe_CDW_L1, &PeChongDW::OnNMClickPeCdwL1)
END_MESSAGE_MAP()


// PeChongDW ��Ϣ�������
BOOL PeChongDW::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CDialogEx::OnInitDialog();
	CString str[] = { L"����", L"����", L"RVA", L"��Ŀ" };
	CString str1[] = { L"����", L"RVA", L"ƫ��", L"����", L"FAR ��ַ", L"���ݽ���" };
	mP_Cdw_L1.SetExtendedStyle(mP_Cdw_L1.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);//��ѡ�з��
	mP_Cdw_L2.SetExtendedStyle(mP_Cdw_L2.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	int z = _countof(str1);
	//����Ӧ��С Ҫ���� �������� ���ֶ�΢��....
	for (int i = 0; i < sizeof(str) / sizeof(str[0]); i++)
	{
		mP_Cdw_L1.InsertColumn(i, str[i], LVCFMT_LEFT, 67);
	}
	for (int i = 0; i < sizeof(str1) / sizeof(str1[0]); i++)
	{

		//�з�б��0
		if (i == _countof(str1) - 1)
		{
			mP_Cdw_L2.InsertColumn(i, str1[i], LVCFMT_LEFT, 200);
		}
		else
		{
			mP_Cdw_L2.InsertColumn(i, str1[i], LVCFMT_LEFT, 67);
		}
	}
	ShowRelocation();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void PeChongDW::ShowRelocation()
{
	AllPe.pDatD = &(AllPe.pOptH->DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC]);//Ҳ����5
	PIMAGE_BASE_RELOCATION pBasR = (PIMAGE_BASE_RELOCATION)((long)AllPe.Buf + AllPe.RvaOffset(AllPe.pDatD->VirtualAddress));
	RELOCAREAINFO Temp = { 0 };
	int j = 0;//����
	CString str;
	while (pBasR->VirtualAddress)
	{
		//printf_s("������%d  ",j);
		str.Format(L"%d", j + 1);
		mP_Cdw_L1.InsertItem(j, str);
		//����������ַ������ȡ�������ط�
		Temp.dwAreaRVA = pBasR->VirtualAddress;

		RelCalcOffset(Temp.dwAreaRVA, AllPe.pNtH, AllPe.Buf, Temp.szSectionName, NULL);
		//	printf_s("%s   ",Temp.szSectionName);
		CString str(Temp.szSectionName);
		mP_Cdw_L1.SetItemText(j, 1, str);
		//printf_s("%08X   ",pBasR->VirtualAddress);
		str.Format(L"%08X", pBasR->VirtualAddress);
		mP_Cdw_L1.SetItemText(j, 2, str);
		Temp.NumberOfReloc = (pBasR->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / 2;
		//	printf_s("%02X  %d\n", Temp.NumberOfReloc, Temp.NumberOfReloc);
		str.Format(L"%02X", Temp.NumberOfReloc);
		CString str1;
		str1.Format(L"%d", Temp.NumberOfReloc);
		mP_Cdw_L1.SetItemText(j, 3, str + L" " + str1);
		//dwCount=Temp.NumberOfReloc;

		m_VecpBseRInfo.push_back(pBasR);
		//��һ�������ض�λ��Ϣ���
		m_VecRelocAreaInfo.push_back(Temp);
		pBasR = (PIMAGE_BASE_RELOCATION)((long)pBasR + pBasR->SizeOfBlock);
		j++;
	}
	int i = 0;
}



void PeChongDW::OnNMClickPeCdwL1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	POSITION pos = mP_Cdw_L1.GetFirstSelectedItemPosition();
	int nIndex = (int)pos;
	if (pos == NULL)//�ж��Ƿ�Ϊ��
	{
		return;
	}
	mP_Cdw_L2.DeleteAllItems();
	int i = 0;
	CString str;

	//�õ���������Ա��TYPEOFFEST��ʼλ�� ֮��ʼѭ����ȡ�ض�λ��Ϣ
	PTYPEOFFSET pOffset = (PTYPEOFFSET)((long)m_VecpBseRInfo[nIndex - 1] + sizeof(IMAGE_BASE_RELOCATION));
	int z = m_VecRelocAreaInfo[nIndex - 1].NumberOfReloc;
	for (DWORD i = 0; i < m_VecRelocAreaInfo[nIndex - 1].NumberOfReloc; i++)
	{
		//printf_s("������%d  ",i);
		str.Format(L"%d", i + 1);
		mP_Cdw_L2.InsertItem(i, str);
		RELOCINFO RelocInfoTemp = { 0 };
		//��Ҫ�ض�λ�������ַ��RVA��
		RelocInfoTemp.dwRelocRVA = m_VecRelocAreaInfo[nIndex - 1].dwAreaRVA + pOffset->Offset;
		//	printf_s("RVA��%08X  ", RelocInfoTemp.dwRelocRVA);
		str.Format(L"%08X", RelocInfoTemp.dwRelocRVA);
		mP_Cdw_L2.SetItemText(i, 1, str);
		//������������ַ������ļ�ƫ��
		RelocInfoTemp.dwOffset = RelCalcOffset(RelocInfoTemp.dwRelocRVA, AllPe.pNtH, NULL, NULL);
		//	printf_s("ƫ�ƣ�%08X  ", RelocInfoTemp.dwOffset);
		str.Format(L"%08X", RelocInfoTemp.dwOffset);
		mP_Cdw_L2.SetItemText(i, 2, str);
		//�ض�λ��ʽ
		RelocInfoTemp.bType = pOffset->Type;
		//printf_s("���ͣ�HIGHLOW (%d)  ",RelocInfoTemp.bType);
		str.Format(L"HIGHLOW (%d)", RelocInfoTemp.bType);
		mP_Cdw_L2.SetItemText(i, 3, str);
		//��������ļ�ƫ��ȡ�������� ������ݾ�����Ҫ�ض�λ�������ַ(VA)
		RelocInfoTemp.dwRelocValue = *(PDWORD)((long)AllPe.Buf + RelocInfoTemp.dwOffset);
		//printf_s("FAR��ַ��%08X  ",RelocInfoTemp.dwRelocValue);
		str.Format(L"%08X", RelocInfoTemp.dwRelocValue);
		mP_Cdw_L2.SetItemText(i, 4, str);
		//RelocInfoTemp.bData
		DWORD VA = RelCalcOffset(RelocInfoTemp.dwRelocValue, AllPe.pNtH, AllPe.Buf, NULL, (PCHAR)RelocInfoTemp.bData, 2);
		RelCalcOffset(VA, AllPe.pNtH, AllPe.Buf, NULL, (PCHAR)RelocInfoTemp.bData, 1);
		CString str1;
		CString str2;
		for (int j = 0; j < 10; j++)
		{
			//�ж��Ƿ�����Ч�ַ�32-126������
			if (32 <= (RelocInfoTemp.bData)[0] && (RelocInfoTemp.bData)[0] <= 126)
			{
				//printf_s("%c",(RelocInfoTemp.bData)[j]);

				str1.Format(L"%c", (RelocInfoTemp.bData)[j]);
				str2 += str1;
			}
			else
			{
				//printf_s("%02X ",(RelocInfoTemp.bData)[j]);
				str1.Format(L"%02X", (RelocInfoTemp.bData)[j]);
				str2 += L" " + str1;
			}
		}
		mP_Cdw_L2.SetItemText(i, 5, str2);
		pOffset++;
	}
	*pResult = 0;
}
