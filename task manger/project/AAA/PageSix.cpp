// PageSix.cpp : 实现文件
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

// PageSix 对话框

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
	// TODO:  在此添加额外的初始化
	m_list.DeleteAllItems();//清空
	//设置名称
	m_list.InsertColumn(0, L"用户名");
	m_list.InsertColumn(1, L"用户描述");
	//设置列宽
	m_list.SetColumnWidth(0, 120);
	m_list.SetColumnWidth(1, 120);
	//设置风格
	m_list.SetExtendedStyle(
		LVS_EX_FLATSB               //扁平风格滚动条
		| LVS_EX_FULLROWSELECT       //允许整行选中
		| LVS_EX_HEADERDRAGDROP      //允许标题拖曳
		| LVS_EX_ONECLICKACTIVATE    //高亮显示
		| LVS_EX_GRIDLINES           //画出网格线
		);

	EnumUser1();
	//Listgroup();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
/*******************************************************************************
*列举用户
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
		//调用NetUserEnum
		nStatus = NetUserEnum(NULL,				//使用本地计算机
			dwLevel,					//设置0 返回用户帐户名称
			FILTER_NORMAL_ACCOUNT,		//列举普通用户帐户数据
			(LPBYTE*)&pBuf,				//接收数据
			dwPrefMaxLen,				//
			&dwEntriesRead,				//
			&dwTotalEntries,			//
			&dwResumeHandle);			//
		if ((nStatus == NERR_Success) || (nStatus == ERROR_MORE_DATA)){
			if ((pTmpBuf = pBuf) != NULL){
				//循环读取用户信息
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


//列举用户组
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

//显示用户信息
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

	// TODO:  在此添加控件通知处理程序代码
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	int index = pNMLV->iItem;
	if (index == -1)
		return;
	HMENU hMenu = ::CreatePopupMenu();
	AppendMenu(hMenu, MF_STRING, 10001, _T("添加用户"));
	AppendMenu(hMenu, MF_STRING, 10002, _T("删除用户"));
	AppendMenu(hMenu, MF_STRING, 10003, _T("刷新"));
	CPoint pt;
	GetCursorPos(&pt); //获得当前鼠标位置
	UINT Cmd = (UINT)::TrackPopupMenu(hMenu, TPM_LEFTALIGN | TPM_RETURNCMD, pt.x, pt.y, 0, m_hWnd, NULL);//弹出菜单

	switch (Cmd)//响应点击的菜单
	{
	case 10001:{
				 AddUser  Essage;
				 Essage.DoModal();
				 //刷新
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
