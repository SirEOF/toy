// PeZiYuan.cpp : 实现文件
//

#include "stdafx.h"
#include "AAA.h"
#include "PeZiYuan.h"
#include "afxdialogex.h"
#include "vector"

using namespace std;
typedef struct _RESTHIRDINFO
{
	DWORD Rva;
	DWORD Offset;
	DWORD Size;
}RESTHIRDINFO, *PRESTHIRDINFO;

typedef struct _RESSENCONDINFO
{
	DWORD NameIsString;
	DWORD ReSize2;
}RESSENCONDINFO, *PRESSENCONDINFO;

vector<RESTHIRDINFO> m_VecResthdInfo[20];
vector<RESSENCONDINFO> m_VecResSedInfo;
vector<HTREEITEM> m_VecHtreeItem;


// PeZiYuan 对话框

IMPLEMENT_DYNAMIC(PeZiYuan, CDialogEx)

PeZiYuan::PeZiYuan(CWnd* pParent /*=NULL*/)
	: CDialogEx(PeZiYuan::IDD, pParent)
	, mP_EDIT_ZY_1_1(_T(""))
	, mP_EDIT_ZY_1_2(_T(""))
	, mP_EDIT_ZY_2_1(_T(""))
	, mP_EDIT_ZY_2_2(_T(""))
	, mP_EDIT_ZY_3_1(_T(""))
	, mP_EDIT_ZY_3_2(_T(""))
	, mP_EDIT_ZY_3_3(_T(""))
{

}

PeZiYuan::~PeZiYuan()
{
}

void PeZiYuan::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Pe_EDIT_ZY_1_1, mP_EDIT_ZY_1_1);
	DDX_Text(pDX, IDC_Pe_EDIT_ZY_1_2, mP_EDIT_ZY_1_2);
	DDX_Text(pDX, IDC_Pe_EDIT_ZY_2_1, mP_EDIT_ZY_2_1);
	DDX_Text(pDX, IDC_Pe_EDIT_ZY_2_2, mP_EDIT_ZY_2_2);
	DDX_Text(pDX, IDC_Pe_EDIT_ZY_3_1, mP_EDIT_ZY_3_1);
	DDX_Text(pDX, IDC_Pe_EDIT_ZY_3_2, mP_EDIT_ZY_3_2);
	DDX_Text(pDX, IDC_Pe_EDIT_ZY_3_3, mP_EDIT_ZY_3_3);
	DDX_Control(pDX, IDC_TREE1, mP_Tree_ReSouce);
}


BEGIN_MESSAGE_MAP(PeZiYuan, CDialogEx)
	ON_NOTIFY(NM_CLICK, IDC_TREE1, &PeZiYuan::OnNMClickTree1)
END_MESSAGE_MAP()


// PeZiYuan 消息处理程序


BOOL PeZiYuan::OnInitDialog()
{
	
	CDialogEx::OnInitDialog();
	mP_Tree_ReSouce.ModifyStyle(NULL, TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT);
	
	ShowResourcesInfo();

	return TRUE;  // return TRUE unless you set the focus to a control
		
		
}

void::PeZiYuan:: ShowResourcesInfo()
{
	RESSENCONDINFO ResSendInfo;
	RESTHIRDINFO ResThirdInfo;
	AllPe.pDatD = &(AllPe.pOptH->DataDirectory[2]);
	PIMAGE_RESOURCE_DIRECTORY pResD = (PIMAGE_RESOURCE_DIRECTORY)(AllPe.Buf + AllPe.RvaOffset(AllPe.pDatD->VirtualAddress));
	DWORD ReSize = pResD->NumberOfIdEntries + pResD->NumberOfNamedEntries;
	PIMAGE_RESOURCE_DIRECTORY_ENTRY pResDE = (PIMAGE_RESOURCE_DIRECTORY_ENTRY)((long)pResD + sizeof(IMAGE_RESOURCE_DIRECTORY));
	//AllPe.OutPutPeInfo(m_Name,pResDE->NameIsString);
	//AllPe.OutPutPeInfo(m_Id,ReSize);
	//另一种写法
	mP_EDIT_ZY_1_1.Format(L"%04X", pResDE->NameIsString);
	mP_EDIT_ZY_1_2.Format(L"%04X", ReSize);
	
	//HTREEITEM hThirdItem;
	HTREEITEM hItem;
	HTREEITEM hSubItem;

	CString str;
	for (DWORD FirstOrder = 0; FirstOrder < ReSize; FirstOrder++)
	{
		//第一层 假如是字符串标识
		if (pResDE->NameIsString == 1)
		{
			PIMAGE_RESOURCE_DIR_STRING_U pREsDStrU = (PIMAGE_RESOURCE_DIR_STRING_U)((long)pResD + pResDE->NameOffset);
			//printf_s("资源类型名：%s",pREsDStrU->NameString);
			hItem = mP_Tree_ReSouce.InsertItem(pREsDStrU->NameString, NULL, NULL);///root就是节点的标题
		}
		//假如是一直类型 用序号作为标识
		else
		{
			switch (pResDE->Name)
			{
			case 0x1:
				//printf_s("第一层：%s\n",ResourceName[0]);
				hItem = mP_Tree_ReSouce.InsertItem(L"鼠标指针", NULL, NULL);
				break;
			case 0x2:
				//printf_s("第一层：%s\n",ResourceName[1]);
				hItem = mP_Tree_ReSouce.InsertItem(L"位图", NULL, NULL);
				break;
			case 0x3:
				//printf_s("第一层：%s\n",ResourceName[2]);
				hItem = mP_Tree_ReSouce.InsertItem(L"图标", NULL, NULL);
				break;
			case 0x4:
				//printf_s("第一层：%s\n",ResourceName[3]);
				hItem = mP_Tree_ReSouce.InsertItem(L"菜单", NULL, NULL);
				break;
			case 0x5:
				//printf_s("第一层：%s\n",ResourceName[4]);
				hItem = mP_Tree_ReSouce.InsertItem(L"对话框", NULL, NULL);
				break;
			case 0x6:
				//printf_s("第一层：%s\n",ResourceName[5]);
				hItem = mP_Tree_ReSouce.InsertItem(L"字符串列表", NULL, NULL);
				break;
			case 0x7:
				//printf_s("第一层：%s\n",ResourceName[6]);
				hItem = mP_Tree_ReSouce.InsertItem(L"字体目录", NULL, NULL);
				break;
			case 0x8:
				//printf_s("第一层：%s\n",ResourceName[7]);
				hItem = mP_Tree_ReSouce.InsertItem(L"字体", NULL, NULL);
				break;
			case 0x9:
				//printf_s("第一层：%s\n",ResourceName[8]);
				hItem = mP_Tree_ReSouce.InsertItem(L"快捷键", NULL, NULL);
				break;
			case 0xA:
				//printf_s("第一层：%s\n",ResourceName[9]);
				hItem = mP_Tree_ReSouce.InsertItem(L"非格式化资源", NULL, NULL);
				break;
			case 0xB:
				//printf_s("第一层：%s\n",ResourceName[10]);
				hItem = mP_Tree_ReSouce.InsertItem(L"消息列表", NULL, NULL);
				break;
			case 0xC:
				//printf_s("第一层：%s\n",ResourceName[11]);
				hItem = mP_Tree_ReSouce.InsertItem(L"鼠标指针组", NULL, NULL);
				break;
			case 0xE:
				//printf_s("第一层：%s\n",ResourceName[12]);
				hItem = mP_Tree_ReSouce.InsertItem(L"图标组", NULL, NULL);
				break;
			case 0x10:
				//printf_s("第一层：%s\n",ResourceName[13]);
				hItem = mP_Tree_ReSouce.InsertItem(L"版本信息", NULL, NULL);
				break;
			default:
				//printf_s("第一层：%d\n",pResDE->Name);
				str.Format(L"%d", pResDE->Name);
				hItem = mP_Tree_ReSouce.InsertItem(str, NULL, NULL);
				break;
			}
		}
		//找第二层 注意OFFEST 是相对于pResD也就是资源开始位置的偏移
		PIMAGE_RESOURCE_DIRECTORY pResD2 = (PIMAGE_RESOURCE_DIRECTORY)((long)pResD + pResDE->OffsetToDirectory);
		DWORD ReSize2 = pResD2->NumberOfIdEntries + pResD2->NumberOfNamedEntries;
		PIMAGE_RESOURCE_DIRECTORY_ENTRY pResDE2 = (PIMAGE_RESOURCE_DIRECTORY_ENTRY)((long)pResD2 + sizeof(IMAGE_RESOURCE_DIRECTORY));

		mP_Tree_ReSouce.SetItemData(hItem, FirstOrder);
		//printf_s("第er层[名称条目]->：%04X   ",pResDE2->NameIsString);	
		//AllPe.OutPutPeInfo(m_Name2,pResDE2->NameIsString);
		ResSendInfo.NameIsString = pResD2->NumberOfNamedEntries;
		ResSendInfo.ReSize2 = pResD2->NumberOfIdEntries;
		m_VecResSedInfo.push_back(ResSendInfo);
		//printf_s("第er层[ID条目]->：%04X   \n",pResDE2->Id);
		//AllPe.OutPutPeInfo(m_Id2,ReSize2);	

		DWORD SecondOrder = 0;
		for (; SecondOrder < ReSize2; SecondOrder++)
		{
			if (pResDE2->DataIsDirectory == 1)
			{
				//输出第二层资源的标识看是数字还是字符串
				if (pResDE2->NameIsString == 1)
				{
					PIMAGE_RESOURCE_DIR_STRING_U pREsDStrU2 = (PIMAGE_RESOURCE_DIR_STRING_U)((long)pResD + pResDE2->NameOffset);
					//输出资源类型名字
					//printf("第二层->资源类型名：%ls   ",pREsDStrU2->NameString);
					hSubItem = mP_Tree_ReSouce.InsertItem(pREsDStrU2->NameString, NULL, NULL, hItem);
					mP_Tree_ReSouce.SetItemData(hSubItem, SecondOrder);
				}
				else
				{
					//printf_s("第二层->资源类型名ID：%d   ",pResDE2->Id);	
					str.Format(L"%d", pResDE2->Id);
					hSubItem = mP_Tree_ReSouce.InsertItem(str, NULL, NULL, hItem);
					mP_Tree_ReSouce.SetItemData(hSubItem, SecondOrder);
				}
				//解析第三层 
				PIMAGE_RESOURCE_DIRECTORY pResD3 = (PIMAGE_RESOURCE_DIRECTORY)((long)pResD + pResDE2->OffsetToDirectory);

				PIMAGE_RESOURCE_DIRECTORY_ENTRY pResDE3 = (PIMAGE_RESOURCE_DIRECTORY_ENTRY)((long)pResD3 + sizeof(IMAGE_RESOURCE_DIRECTORY));
				PIMAGE_RESOURCE_DATA_ENTRY pResDataE = (PIMAGE_RESOURCE_DATA_ENTRY)((long)pResD + pResDE3->OffsetToData);
				//printf_s("第三层->RVA：%08X   ",pResDataE->OffsetToData);  
				//AllPe.OutPutPeInfo()
				//根据第一层 也就是父节点 区分 
				ResThirdInfo.Rva = pResDataE->OffsetToData;
				ResThirdInfo.Offset = (AllPe.RvaOffset(pResDataE->OffsetToData));
				ResThirdInfo.Size = pResDataE->Size;
				m_VecResthdInfo[FirstOrder].push_back(ResThirdInfo);
				

			}
			else
			{
				break;
			}
			pResDE2++;
		}
		//保存父节点的句柄
		m_VecHtreeItem.push_back(hItem);
		pResDE++;
	}
	mP_EDIT_ZY_2_1.Format(L"%04X", m_VecResSedInfo[0].NameIsString);
	mP_EDIT_ZY_2_2.Format(L"%04X", m_VecResSedInfo[0].ReSize2);
	UpdateData(FALSE);


}

void PeZiYuan::OnNMClickTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	//获取当前鼠标点击消息的坐标点
	CPoint pt = GetCurrentMessage()->pt;
	//将鼠标的屏幕坐标，转换成树形控件的客户区坐标
	mP_Tree_ReSouce.ScreenToClient(&pt);
	UINT uFlags = 0;
	HTREEITEM hItem = mP_Tree_ReSouce.HitTest(pt, &uFlags);
	//获得父节点句柄
	HTREEITEM RootHItem = mP_Tree_ReSouce.GetParentItem(hItem);
	int RootTreePos;

	//找到对应父节点位置
	for (UINT i = 0; i<m_VecHtreeItem.size(); i++)
	{
		if (RootHItem == NULL)
		{
			break;
		}
		if (RootHItem == m_VecHtreeItem[i])
		{
			RootTreePos = i;
			break;
		}
		//最后一个
		RootTreePos = i;
	}
	//mP_Tree_ReSouce.getn
	//如果点击的位置是在节点位置上面
	if ((hItem != NULL) && (TVHT_ONITEM & uFlags))
	{
		//得到点中的序号
		mP_Tree_ReSouce.SelectItem(hItem);
		int nDat = mP_Tree_ReSouce.GetItemData(hItem);
		//判断是父节点还是子节点
		if (RootHItem == NULL)
		{
			mP_EDIT_ZY_2_1.Format(L"%04X", m_VecResSedInfo[nDat].NameIsString);
			mP_EDIT_ZY_2_2.Format(L"%04X", m_VecResSedInfo[nDat].ReSize2);
		}
		else
		{
			AllPe.InputPeInfo(mP_EDIT_ZY_3_1, m_VecResthdInfo[RootTreePos][nDat].Rva);
			AllPe.InputPeInfo(mP_EDIT_ZY_3_2, m_VecResthdInfo[RootTreePos][nDat].Offset);
			AllPe.InputPeInfo(mP_EDIT_ZY_3_3, m_VecResthdInfo[RootTreePos][nDat].Size);
		}
		/*	if (hItem==m_VecHtreeItem[nDat])
		{
		m_Name2.Format(L"%04X",m_VecResSedInfo[nDat].NameIsString);
		m_Id2.Format(L"%04X",m_VecResSedInfo[nDat].ReSize2);
		}
		else
		{
		AllPe.OutPutPeInfo(m_Rva,m_VecResthdInfo[RootTreePos][nDat].Rva);
		AllPe.OutPutPeInfo(m_Offset,m_VecResthdInfo[RootTreePos][nDat].Offset);
		AllPe.OutPutPeInfo(m_Size,	m_VecResthdInfo[RootTreePos][nDat].Size);
		}*/

	}
	UpdateData(FALSE);


}