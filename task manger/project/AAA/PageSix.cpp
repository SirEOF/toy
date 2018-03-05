// PageSix.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AAA.h"
#include "PageSix.h"
#include "afxdialogex.h"
#include "AddUser.h"
#include "DeleteUser.h"
#include <Lmaccess.h>
#include <stdlib.h>
#include <lm.h>
#include <assert.h>

// PageSix �Ի���

#pragma comment(lib, "Netapi32.lib")
IMPLEMENT_DYNAMIC(PageSix, CDialogEx)

PageSix::PageSix(CWnd* pParent /*=NULL*/)
	: CDialogEx(PageSix::IDD, pParent)

{

}

PageSix::~PageSix()
{
}

void PageSix::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LPageSix, m_list);

}

BEGIN_MESSAGE_MAP(PageSix, CDialogEx)
	
	ON_NOTIFY(NM_RCLICK, IDC_LPageSix, &PageSix::OnNMRClickLpagesix)
END_MESSAGE_MAP()





BOOL PageSix::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_list.DeleteAllItems();//���
	//��������
	m_list.InsertColumn(0, L"�û���");
	m_list.InsertColumn(1, L"�û�����");
	//�����п�
	m_list.SetColumnWidth(0, 120);
	m_list.SetColumnWidth(1, 120);
	//���÷��
	m_list.SetExtendedStyle(
		LVS_EX_FLATSB               //��ƽ��������
		| LVS_EX_FULLROWSELECT       //��������ѡ��
		| LVS_EX_HEADERDRAGDROP      //���������ҷ
		| LVS_EX_ONECLICKACTIVATE    //������ʾ
		| LVS_EX_GRIDLINES           //����������
		);

	EnumUser1();
	//Listgroup();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
/*******************************************************************************
*�о��û�
*
********************************************************************************/
void PageSix::EnumUser1(){
	LPUSER_INFO_0 pBuf = NULL;
	LPUSER_INFO_0 pTmpBuf = NULL;
	DWORD dwLevel = 0;
	DWORD dwPrefMaxLen = MAX_PREFERRED_LENGTH;
	DWORD dwEntriesRead = 0;
	DWORD dwTotalEntries = 0;
	DWORD dwResumeHandle = 0;
	DWORD i;
	DWORD dwTotalCount = 0;
	NET_API_STATUS nStatus;
	do
	{
		//����NetUserEnum
		nStatus = NetUserEnum(NULL,				//ʹ�ñ��ؼ����
			dwLevel,					//����0 �����û��ʻ�����
			FILTER_NORMAL_ACCOUNT,		//�о���ͨ�û��ʻ�����
			(LPBYTE*)&pBuf,				//��������
			dwPrefMaxLen,				//
			&dwEntriesRead,				//
			&dwTotalEntries,			//
			&dwResumeHandle);			//
		if ((nStatus == NERR_Success) || (nStatus == ERROR_MORE_DATA)){
			if ((pTmpBuf = pBuf) != NULL){
				//ѭ����ȡ�û���Ϣ
				for (i = 0; i < dwEntriesRead; i++){
					assert(pTmpBuf != NULL);
					if (pTmpBuf == NULL){
						break;
					}
					m_list.InsertItem(0, pTmpBuf->usri0_name);
					//m_list.SetItemText(0, 1, pTmpBuf->usri0_name);
					ShowUsersInfo(pTmpBuf->usri0_name);
					pTmpBuf++;
					dwTotalCount++;
				}
			}
		}
		if (pBuf != NULL){
			NetApiBufferFree(pBuf);
		}
	} while (nStatus == ERROR_MORE_DATA);
}


//�о��û���
int PageSix::Listgroup(){
	DWORD dwLevel;
	DWORD dwPrefMaxLen = MAX_PREFERRED_LENGTH;
	DWORD dwEntriesRead = 0;
	DWORD dwTotalEntries = 0;
	DWORD dwResumeHandle = 0;
	DWORD i;
	DWORD dwTotalCount = 0;
	NET_API_STATUS nStatus;
	LPLOCALGROUP_INFO_0 pBuf = NULL;
	LPLOCALGROUP_INFO_0 pTmpBuf;
	do
	{
		nStatus = NetLocalGroupEnum(NULL, 0,
			(LPBYTE*)&pBuf,
			dwPrefMaxLen,
			&dwEntriesRead,
			&dwTotalEntries,
			&dwResumeHandle);
		if ((nStatus == NERR_Success) || (nStatus == ERROR_MORE_DATA)){
			if ((pTmpBuf = pBuf) != NULL){
				for (i = 0; (i < dwEntriesRead); i++){
					assert(pTmpBuf != NULL);
					if (pTmpBuf == NULL){
						break;
					}
					//m_list.InsertItem(0, pTmpBuf->lgrpi0_name);
					m_list.SetItemText(0, 1, pTmpBuf->lgrpi0_name);
					pTmpBuf++;
					dwTotalCount++;
				}
			}
		}
		if (pBuf != NULL){
			NetApiBufferFree(pBuf);
			pBuf = NULL;
		}
	} while (nStatus == ERROR_MORE_DATA);
	return 0;
}

//��ʾ�û���Ϣ
int PageSix::ShowUsersInfo(LPWSTR pszUserName){
	DWORD dwLevel = 4;
	LPUSER_INFO_4 pBuf = NULL;
	NET_API_STATUS nStatus;
	nStatus = NetUserGetInfo(NULL,
		pszUserName,
		dwLevel,
		(LPBYTE *)&pBuf);
	if (nStatus == NERR_Success){
		if (pBuf != NULL){
			m_list.SetItemText(0, 1, pBuf->usri4_comment);
		}
	}
	if (pBuf != NULL)
		NetApiBufferFree(pBuf);
	return 0;
}

void PageSix::OnNMRClickLpagesix(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	int index = pNMLV->iItem;
	if (index == -1)
		return;
	HMENU hMenu = ::CreatePopupMenu();
	AppendMenu(hMenu, MF_STRING, 10001, _T("����û�"));
	AppendMenu(hMenu, MF_STRING, 10002, _T("ɾ���û�"));
	AppendMenu(hMenu, MF_STRING, 10003, _T("ˢ��"));
	CPoint pt;
	GetCursorPos(&pt); //��õ�ǰ���λ��
	UINT Cmd = (UINT)::TrackPopupMenu(hMenu, TPM_LEFTALIGN | TPM_RETURNCMD, pt.x, pt.y, 0, m_hWnd, NULL);//�����˵�

	switch (Cmd)//��Ӧ����Ĳ˵�
	{
	case 10001:{
				 AddUser  Essage;
				 Essage.DoModal();
				 //ˢ��
				 OnInitDialog();
	}
		break;
	case  10002:{
				  DeleteUser  Del;
				  Del.DoModal();
				  OnInitDialog();
	}
		break;
	case 10003:{
				 OnInitDialog();
	}
		break;
	}


	*pResult = 0;
}
