// PeZiYuan.cpp : ʵ���ļ�
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


// PeZiYuan �Ի���

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


// PeZiYuan ��Ϣ�������


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
	//��һ��д��
	mP_EDIT_ZY_1_1.Format(L"%04X", pResDE->NameIsString);
	mP_EDIT_ZY_1_2.Format(L"%04X", ReSize);
	
	//HTREEITEM hThirdItem;
	HTREEITEM hItem;
	HTREEITEM hSubItem;

	CString str;
	for (DWORD FirstOrder = 0; FirstOrder < ReSize; FirstOrder++)
	{
		//��һ�� �������ַ�����ʶ
		if (pResDE->NameIsString == 1)
		{
			PIMAGE_RESOURCE_DIR_STRING_U pREsDStrU = (PIMAGE_RESOURCE_DIR_STRING_U)((long)pResD + pResDE->NameOffset);
			//printf_s("��Դ��������%s",pREsDStrU->NameString);
			hItem = mP_Tree_ReSouce.InsertItem(pREsDStrU->NameString, NULL, NULL);///root���ǽڵ�ı���
		}
		//������һֱ���� �������Ϊ��ʶ
		else
		{
			switch (pResDE->Name)
			{
			case 0x1:
				//printf_s("��һ�㣺%s\n",ResourceName[0]);
				hItem = mP_Tree_ReSouce.InsertItem(L"���ָ��", NULL, NULL);
				break;
			case 0x2:
				//printf_s("��һ�㣺%s\n",ResourceName[1]);
				hItem = mP_Tree_ReSouce.InsertItem(L"λͼ", NULL, NULL);
				break;
			case 0x3:
				//printf_s("��һ�㣺%s\n",ResourceName[2]);
				hItem = mP_Tree_ReSouce.InsertItem(L"ͼ��", NULL, NULL);
				break;
			case 0x4:
				//printf_s("��һ�㣺%s\n",ResourceName[3]);
				hItem = mP_Tree_ReSouce.InsertItem(L"�˵�", NULL, NULL);
				break;
			case 0x5:
				//printf_s("��һ�㣺%s\n",ResourceName[4]);
				hItem = mP_Tree_ReSouce.InsertItem(L"�Ի���", NULL, NULL);
				break;
			case 0x6:
				//printf_s("��һ�㣺%s\n",ResourceName[5]);
				hItem = mP_Tree_ReSouce.InsertItem(L"�ַ����б�", NULL, NULL);
				break;
			case 0x7:
				//printf_s("��һ�㣺%s\n",ResourceName[6]);
				hItem = mP_Tree_ReSouce.InsertItem(L"����Ŀ¼", NULL, NULL);
				break;
			case 0x8:
				//printf_s("��һ�㣺%s\n",ResourceName[7]);
				hItem = mP_Tree_ReSouce.InsertItem(L"����", NULL, NULL);
				break;
			case 0x9:
				//printf_s("��һ�㣺%s\n",ResourceName[8]);
				hItem = mP_Tree_ReSouce.InsertItem(L"��ݼ�", NULL, NULL);
				break;
			case 0xA:
				//printf_s("��һ�㣺%s\n",ResourceName[9]);
				hItem = mP_Tree_ReSouce.InsertItem(L"�Ǹ�ʽ����Դ", NULL, NULL);
				break;
			case 0xB:
				//printf_s("��һ�㣺%s\n",ResourceName[10]);
				hItem = mP_Tree_ReSouce.InsertItem(L"��Ϣ�б�", NULL, NULL);
				break;
			case 0xC:
				//printf_s("��һ�㣺%s\n",ResourceName[11]);
				hItem = mP_Tree_ReSouce.InsertItem(L"���ָ����", NULL, NULL);
				break;
			case 0xE:
				//printf_s("��һ�㣺%s\n",ResourceName[12]);
				hItem = mP_Tree_ReSouce.InsertItem(L"ͼ����", NULL, NULL);
				break;
			case 0x10:
				//printf_s("��һ�㣺%s\n",ResourceName[13]);
				hItem = mP_Tree_ReSouce.InsertItem(L"�汾��Ϣ", NULL, NULL);
				break;
			default:
				//printf_s("��һ�㣺%d\n",pResDE->Name);
				str.Format(L"%d", pResDE->Name);
				hItem = mP_Tree_ReSouce.InsertItem(str, NULL, NULL);
				break;
			}
		}
		//�ҵڶ��� ע��OFFEST �������pResDҲ������Դ��ʼλ�õ�ƫ��
		PIMAGE_RESOURCE_DIRECTORY pResD2 = (PIMAGE_RESOURCE_DIRECTORY)((long)pResD + pResDE->OffsetToDirectory);
		DWORD ReSize2 = pResD2->NumberOfIdEntries + pResD2->NumberOfNamedEntries;
		PIMAGE_RESOURCE_DIRECTORY_ENTRY pResDE2 = (PIMAGE_RESOURCE_DIRECTORY_ENTRY)((long)pResD2 + sizeof(IMAGE_RESOURCE_DIRECTORY));

		mP_Tree_ReSouce.SetItemData(hItem, FirstOrder);
		//printf_s("��er��[������Ŀ]->��%04X   ",pResDE2->NameIsString);	
		//AllPe.OutPutPeInfo(m_Name2,pResDE2->NameIsString);
		ResSendInfo.NameIsString = pResD2->NumberOfNamedEntries;
		ResSendInfo.ReSize2 = pResD2->NumberOfIdEntries;
		m_VecResSedInfo.push_back(ResSendInfo);
		//printf_s("��er��[ID��Ŀ]->��%04X   \n",pResDE2->Id);
		//AllPe.OutPutPeInfo(m_Id2,ReSize2);	

		DWORD SecondOrder = 0;
		for (; SecondOrder < ReSize2; SecondOrder++)
		{
			if (pResDE2->DataIsDirectory == 1)
			{
				//����ڶ�����Դ�ı�ʶ�������ֻ����ַ���
				if (pResDE2->NameIsString == 1)
				{
					PIMAGE_RESOURCE_DIR_STRING_U pREsDStrU2 = (PIMAGE_RESOURCE_DIR_STRING_U)((long)pResD + pResDE2->NameOffset);
					//�����Դ��������
					//printf("�ڶ���->��Դ��������%ls   ",pREsDStrU2->NameString);
					hSubItem = mP_Tree_ReSouce.InsertItem(pREsDStrU2->NameString, NULL, NULL, hItem);
					mP_Tree_ReSouce.SetItemData(hSubItem, SecondOrder);
				}
				else
				{
					//printf_s("�ڶ���->��Դ������ID��%d   ",pResDE2->Id);	
					str.Format(L"%d", pResDE2->Id);
					hSubItem = mP_Tree_ReSouce.InsertItem(str, NULL, NULL, hItem);
					mP_Tree_ReSouce.SetItemData(hSubItem, SecondOrder);
				}
				//���������� 
				PIMAGE_RESOURCE_DIRECTORY pResD3 = (PIMAGE_RESOURCE_DIRECTORY)((long)pResD + pResDE2->OffsetToDirectory);

				PIMAGE_RESOURCE_DIRECTORY_ENTRY pResDE3 = (PIMAGE_RESOURCE_DIRECTORY_ENTRY)((long)pResD3 + sizeof(IMAGE_RESOURCE_DIRECTORY));
				PIMAGE_RESOURCE_DATA_ENTRY pResDataE = (PIMAGE_RESOURCE_DATA_ENTRY)((long)pResD + pResDE3->OffsetToData);
				//printf_s("������->RVA��%08X   ",pResDataE->OffsetToData);  
				//AllPe.OutPutPeInfo()
				//���ݵ�һ�� Ҳ���Ǹ��ڵ� ���� 
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
		//���游�ڵ�ľ��
		m_VecHtreeItem.push_back(hItem);
		pResDE++;
	}
	mP_EDIT_ZY_2_1.Format(L"%04X", m_VecResSedInfo[0].NameIsString);
	mP_EDIT_ZY_2_2.Format(L"%04X", m_VecResSedInfo[0].ReSize2);
	UpdateData(FALSE);


}

void PeZiYuan::OnNMClickTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	//��ȡ��ǰ�������Ϣ�������
	CPoint pt = GetCurrentMessage()->pt;
	//��������Ļ���꣬ת�������οؼ��Ŀͻ�������
	mP_Tree_ReSouce.ScreenToClient(&pt);
	UINT uFlags = 0;
	HTREEITEM hItem = mP_Tree_ReSouce.HitTest(pt, &uFlags);
	//��ø��ڵ���
	HTREEITEM RootHItem = mP_Tree_ReSouce.GetParentItem(hItem);
	int RootTreePos;

	//�ҵ���Ӧ���ڵ�λ��
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
		//���һ��
		RootTreePos = i;
	}
	//mP_Tree_ReSouce.getn
	//��������λ�����ڽڵ�λ������
	if ((hItem != NULL) && (TVHT_ONITEM & uFlags))
	{
		//�õ����е����
		mP_Tree_ReSouce.SelectItem(hItem);
		int nDat = mP_Tree_ReSouce.GetItemData(hItem);
		//�ж��Ǹ��ڵ㻹���ӽڵ�
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