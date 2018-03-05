// PeDaoRu.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AAA.h"
#include "PeDaoRu.h"
#include "afxdialogex.h"
#include "vector"
using namespace std;

vector<PIMAGE_IMPORT_DESCRIPTOR> m_VecImport;
// PeDaoRu �Ի���

IMPLEMENT_DYNAMIC(PeDaoRu, CDialogEx)

PeDaoRu::PeDaoRu(CWnd* pParent /*=NULL*/)
	: CDialogEx(PeDaoRu::IDD, pParent)
{

}

PeDaoRu::~PeDaoRu()
{
}

void PeDaoRu::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Pe_DR_LIST1, mP_DR_List);
	DDX_Control(pDX, IDC_Pe_DR_LIST2, mP_DR_List2);
}


BEGIN_MESSAGE_MAP(PeDaoRu, CDialogEx)
	ON_NOTIFY(NM_CLICK, IDC_Pe_DR_LIST1, &PeDaoRu::OnNMClickPeDrList1)
END_MESSAGE_MAP()


// PeDaoRu ��Ϣ��������

BOOL PeDaoRu::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString str[] = { L"DLL����", L"OriginalFirstThunk", L"����ʱ���־", L"ForwarderChain", L"����", L"FirstThunk" };
	CString str1[] = { L"ThunkRVA", L"Thunkƫ��", L"Thunkֵ", L"��ʾ", L"API����" };
	mP_DR_List.SetExtendedStyle(mP_DR_List.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);//��ѡ�з��
	mP_DR_List2.SetExtendedStyle(mP_DR_List2.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	for (int i = 0; i < sizeof(str) / sizeof(str[0]); i++)
	{
		mP_DR_List.InsertColumn(i, str[i], LVCFMT_LEFT, 67);
	}
	for (int i = 0; i < sizeof(str1) / sizeof(str1[0]); i++)
	{
		mP_DR_List2.InsertColumn(i, str1[i], LVCFMT_LEFT, 67);
	}
	ShowImportList();
	return TRUE;  // return TRUE unless you set the focus to a control

	// �쳣: OCX ����ҳӦ���� FALSE
}



void PeDaoRu::ShowImportList()
{
	//��ȡ�����
	PIMAGE_IMPORT_DESCRIPTOR  pImpD;
	AllPe.pDatD = &(AllPe.pOptH->DataDirectory[1]);
	pImpD = (PIMAGE_IMPORT_DESCRIPTOR)((long)AllPe.Buf + AllPe.RvaOffset(AllPe.pDatD->VirtualAddress));
	//��һ��ѭ�� ÿ�������DLL���ν���
	int i = 0;
	CString str;
	while (pImpD->Name)
	{
		//DLL�������
		//printf_s("DLL���ƣ�%s  ",(AllPe.Buf+AllPe.RvaOffset(pImpD->Name)));
		CString str((AllPe.Buf + AllPe.RvaOffset(pImpD->Name)));
		//m_UpImport.InsertItem(i,L"(AllPe.Buf+AllPe.RvaOffset(pImpD->Name))");
		mP_DR_List.InsertItem(i, str);

		//printf_s("INT(�������Ʊ�)��%08X  ",pImpD->OriginalFirstThunk);
		str.Format(L"%08X", pImpD->OriginalFirstThunk);
		mP_DR_List.SetItemText(i, 1, str);
		//printf_s("����ʱ���־��%08X  ",pImpD->TimeDateStamp);
		str.Format(L"%08X", pImpD->TimeDateStamp);
		mP_DR_List.SetItemText(i, 2, str);
		//	printf_s("ForwarderChain��%08X  ",pImpD->ForwarderChain);
		str.Format(L"%08X", pImpD->ForwarderChain);
		mP_DR_List.SetItemText(i, 3, str);
		//	printf_s("���ƣ�%08X  ",pImpD->Name);
		str.Format(L"%08X", pImpD->Name);
		mP_DR_List.SetItemText(i, 4, str);
		//	printf_s("FirstThunk��%08X\n",pImpD->FirstThunk);
		str.Format(L"%08X", pImpD->FirstThunk);
		mP_DR_List.SetItemText(i, 5, str);
		m_VecImport.push_back(pImpD);
		i++;

		//system("pause");
		pImpD++;
	}
}


void PeDaoRu::OnNMClickPeDrList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ����ӿؼ�֪ͨ�����������

	POSITION pos = mP_DR_List.GetFirstSelectedItemPosition();
	int nIndex = (int)pos;
	if (pos == NULL)//�ж��Ƿ�Ϊ��
	{
		return;
	}
	//while(m_DownImport.DeleteColumn(0));
	mP_DR_List2.DeleteAllItems();
	//�ӻ�ȡ��DLL���뺯����ַ�� IAT ����ƫ��
	PIMAGE_THUNK_DATA32 pInt = (PIMAGE_THUNK_DATA32)(AllPe.Buf + AllPe.RvaOffset(m_VecImport[nIndex - 1]->FirstThunk));

	//ѭ�����������ַ��IAT
	int i = 0;
	CString str;
	while (pInt->u1.Function)
	{

		DWORD ThunkOffest = AllPe.RvaOffset(m_VecImport[nIndex - 1]->OriginalFirstThunk);
		//�ж����λ�Ƿ�Ϊ1 ��Ϊ1�����Ƶ���
		if (!IMAGE_SNAP_BY_ORDINAL32(pInt->u1.Ordinal))
		{
			//�ҵ������������ַ ������ȡ��  
			//printf_s("ThunkRVA��%08X  ",m_VecImport[nIndex]->OriginalFirstThunk);
			str.Format(L"%08X", m_VecImport[nIndex - 1]->OriginalFirstThunk);
			mP_DR_List2.InsertItem(i, str);
			//printf_s("Thunkƫ�ƣ�%08X  ",ThunkOffest);
			str.Format(L"%08X", ThunkOffest);
			mP_DR_List2.SetItemText(i, 1, str);
			//	printf_s("Thunkֵ��%08X  ",pInt->u1.AddressOfData);
			str.Format(L"%08X", pInt->u1.AddressOfData);
			mP_DR_List2.SetItemText(i, 2, str);
			PIMAGE_IMPORT_BY_NAME pFunName = (PIMAGE_IMPORT_BY_NAME)(AllPe.Buf + AllPe.RvaOffset(pInt->u1.AddressOfData));
			//	printf_s("��ʾ��%04X  ",pFunName->Hint);
			str.Format(L"%04X", pFunName->Hint);
			mP_DR_List2.SetItemText(i, 3, str);
			//	printf_s("API���ƣ�%s\n",pFunName->Name);
			CString str(pFunName->Name);
			//str.Format(L"%s",pFunName->Name);
			mP_DR_List2.SetItemText(i, 4, str);
			//ÿ��ƫ���ĸ��ֽ�
			m_VecImport[nIndex - 1]->OriginalFirstThunk += 4;
			ThunkOffest += 4;
		}
		else
		{
			//m_DownImport.DeleteColumn(0);

			////�ҵ������������ַ ������ȡ��  
			////	PIMAGE_IMPORT_BY_NAME pFunName=(PIMAGE_IMPORT_BY_NAME)(buf+CalcOffset(pInt->u1.AddressOfData,pNtH));
			////printf_s("ThunkRVA��%08X  ",m_VecImport[nIndex]->OriginalFirstThunk);
			str.Format(L"%08X", m_VecImport[nIndex - 1]->OriginalFirstThunk);
			mP_DR_List2.InsertItem(i, str);
			//	printf_s("Thunkƫ�ƣ�%08X  ",ThunkOffest);
			str.Format(L"%08X", ThunkOffest);
			mP_DR_List2.SetItemText(i, 1, str);
			//	printf_s("Thunkֵ��%08X  ",pInt->u1.AddressOfData);
			str.Format(L"%08X", pInt->u1.AddressOfData);
			mP_DR_List2.SetItemText(i, 2, str);
			//printf_s("��ʾ��-  ");
			mP_DR_List2.SetItemText(i, 3, L"-");
			//	printf_s("��ţ�%4xH  %4dD\n",pInt->u1.Ordinal&0x7fffffff,pInt->u1.Ordinal&0x7fffffff);
			CString str2;
			str2.Format(L"%4xH", pInt->u1.Ordinal & 0x7fffffff);
			str.Format(L"%4dD", pInt->u1.Ordinal & 0x7fffffff);
			mP_DR_List2.SetItemText(i, 4, str2 + L" " + str);
		}
		i++;
		pInt++;
	}
	*pResult = 0;
}