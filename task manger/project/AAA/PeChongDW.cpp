// PeChongDW.cpp : 实现文件
//

#include "stdafx.h"
#include "AAA.h"
#include "PeChongDW.h"
#include "afxdialogex.h"
#include <vector>
using namespace std;

vector<PIMAGE_BASE_RELOCATION> m_VecpBseRInfo;

DWORD v;
/***************-重定位表-*****************/
//第一个成员的描述
typedef struct _RELOCINFO
{
	DWORD dwRelocRVA;		//需要重定位的相对虚拟地址
	DWORD dwOffset;			//根据相对虚拟地址算出的文件属性
	BYTE bType;				//重定位方式
	DWORD dwRelocValue;		//从算出的文件偏移取出的数据 这个数据就是虚拟地址（VA）
	BYTE bData[10];			//用刚才的地址（VA）减去基址得到相对虚拟地址RVA 再算下文件偏移 将其中的数据取出 放到这个数组
}RELOCINFO, *PRELOCINFO;

//第二个成员的描述
typedef struct _RELOCAREAINFO
{
	CHAR szSectionName[8];  //区域所在的节名
	DWORD dwAreaRVA;		//区域基址
	DWORD NumberOfReloc;	//这个区域重定位的具体个数
	std::vector<RELOCINFO> VecRelocInfo;//这个区域重定位的具体信息
}RELOCAREAINFO, *PRELOCAREAINFO;

vector<RELOCAREAINFO> m_VecRelocAreaInfo;
//第三个成员的描述
typedef struct _TYPEOFFSET
{
	WORD Offset : 12;		//偏移值
	WORD Type : 4;		//重定位属性（方式）
}TYPEOFFSET, *PTYPEOFFSET;

//重定位需要 和下面稍微有些不同
DWORD RelCalcOffset(DWORD Rva, PIMAGE_NT_HEADERS32 pNtH, char *TempBuf, PCHAR pName = NULL, PCHAR pData = NULL, int Flag = NULL)
{
	//PIMAGE_NT_HEADERS32 pnt=pNtH;
	PIMAGE_SECTION_HEADER pSecHTemp = IMAGE_FIRST_SECTION(pNtH);//区段头
	int index = 0;

	while (!(Rva >= pSecHTemp->VirtualAddress&&
		Rva<pSecHTemp->VirtualAddress + pSecHTemp->SizeOfRawData))
	{
		//找完所有区段还没有找到
		if (index>pNtH->FileHeader.NumberOfSections)
		{
			//	m_Section=L"部首";
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
	//获取区段名
	if (pName != NULL)
	{
		//return Rva-pNtH->OptionalHeader.ImageBase;
		memcpy(pName, pSecHTemp->Name, 8);
	}
	v = Rva - pSecHTemp->VirtualAddress + pSecHTemp->PointerToRawData;;
	DWORD iiii = (long)TempBuf + v;
	//获取数据
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
		//flag 为1时 
		memcpy(pData, PCHAR((long)TempBuf + v), 10);
	}
	return v;
}
/***************-重定位表-*****************/

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


// PeChongDW 消息处理程序
BOOL PeChongDW::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CDialogEx::OnInitDialog();
	CString str[] = { L"索引", L"区段", L"RVA", L"项目" };
	CString str1[] = { L"索引", L"RVA", L"偏移", L"类型", L"FAR 地址", L"数据解释" };
	mP_Cdw_L1.SetExtendedStyle(mP_Cdw_L1.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);//可选中风格
	mP_Cdw_L2.SetExtendedStyle(mP_Cdw_L2.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	int z = _countof(str1);
	//自适应大小 要重载 不重载了 我手动微调....
	for (int i = 0; i < sizeof(str) / sizeof(str[0]); i++)
	{
		mP_Cdw_L1.InsertColumn(i, str[i], LVCFMT_LEFT, 67);
	}
	for (int i = 0; i < sizeof(str1) / sizeof(str1[0]); i++)
	{

		//有反斜杠0
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
	// 异常: OCX 属性页应返回 FALSE
}


void PeChongDW::ShowRelocation()
{
	AllPe.pDatD = &(AllPe.pOptH->DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC]);//也就是5
	PIMAGE_BASE_RELOCATION pBasR = (PIMAGE_BASE_RELOCATION)((long)AllPe.Buf + AllPe.RvaOffset(AllPe.pDatD->VirtualAddress));
	RELOCAREAINFO Temp = { 0 };
	int j = 0;//索引
	CString str;
	while (pBasR->VirtualAddress)
	{
		//printf_s("索引：%d  ",j);
		str.Format(L"%d", j + 1);
		mP_Cdw_L1.InsertItem(j, str);
		//区域的虚拟地址输出或获取到其他地方
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
		//讲一个区域重定位信息添加
		m_VecRelocAreaInfo.push_back(Temp);
		pBasR = (PIMAGE_BASE_RELOCATION)((long)pBasR + pBasR->SizeOfBlock);
		j++;
	}
	int i = 0;
}



void PeChongDW::OnNMClickPeCdwL1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	POSITION pos = mP_Cdw_L1.GetFirstSelectedItemPosition();
	int nIndex = (int)pos;
	if (pos == NULL)//判断是否为空
	{
		return;
	}
	mP_Cdw_L2.DeleteAllItems();
	int i = 0;
	CString str;

	//得到第三个成员的TYPEOFFEST起始位置 之后开始循环获取重定位信息
	PTYPEOFFSET pOffset = (PTYPEOFFSET)((long)m_VecpBseRInfo[nIndex - 1] + sizeof(IMAGE_BASE_RELOCATION));
	int z = m_VecRelocAreaInfo[nIndex - 1].NumberOfReloc;
	for (DWORD i = 0; i < m_VecRelocAreaInfo[nIndex - 1].NumberOfReloc; i++)
	{
		//printf_s("索引：%d  ",i);
		str.Format(L"%d", i + 1);
		mP_Cdw_L2.InsertItem(i, str);
		RELOCINFO RelocInfoTemp = { 0 };
		//需要重定位的虚拟地址（RVA）
		RelocInfoTemp.dwRelocRVA = m_VecRelocAreaInfo[nIndex - 1].dwAreaRVA + pOffset->Offset;
		//	printf_s("RVA：%08X  ", RelocInfoTemp.dwRelocRVA);
		str.Format(L"%08X", RelocInfoTemp.dwRelocRVA);
		mP_Cdw_L2.SetItemText(i, 1, str);
		//根据相对虚拟地址算出的文件偏移
		RelocInfoTemp.dwOffset = RelCalcOffset(RelocInfoTemp.dwRelocRVA, AllPe.pNtH, NULL, NULL);
		//	printf_s("偏移：%08X  ", RelocInfoTemp.dwOffset);
		str.Format(L"%08X", RelocInfoTemp.dwOffset);
		mP_Cdw_L2.SetItemText(i, 2, str);
		//重定位方式
		RelocInfoTemp.bType = pOffset->Type;
		//printf_s("类型：HIGHLOW (%d)  ",RelocInfoTemp.bType);
		str.Format(L"HIGHLOW (%d)", RelocInfoTemp.bType);
		mP_Cdw_L2.SetItemText(i, 3, str);
		//从算出的文件偏移取出的数据 这个数据就是需要重定位的虚拟地址(VA)
		RelocInfoTemp.dwRelocValue = *(PDWORD)((long)AllPe.Buf + RelocInfoTemp.dwOffset);
		//printf_s("FAR地址：%08X  ",RelocInfoTemp.dwRelocValue);
		str.Format(L"%08X", RelocInfoTemp.dwRelocValue);
		mP_Cdw_L2.SetItemText(i, 4, str);
		//RelocInfoTemp.bData
		DWORD VA = RelCalcOffset(RelocInfoTemp.dwRelocValue, AllPe.pNtH, AllPe.Buf, NULL, (PCHAR)RelocInfoTemp.bData, 2);
		RelCalcOffset(VA, AllPe.pNtH, AllPe.Buf, NULL, (PCHAR)RelocInfoTemp.bData, 1);
		CString str1;
		CString str2;
		for (int j = 0; j < 10; j++)
		{
			//判断是否在有效字符32-126区间内
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
