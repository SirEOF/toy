// DeleteUser.cpp : 实现文件
//

#include "stdafx.h"
#include "AAA.h"
#include "DeleteUser.h"
#include "afxdialogex.h"
#include <Lmaccess.h>
#include <stdlib.h>
#include <lm.h>
#include <assert.h>

#pragma comment(lib, "Netapi32.lib")
// DeleteUser 对话框

IMPLEMENT_DYNAMIC(DeleteUser, CDialogEx)

DeleteUser::DeleteUser(CWnd* pParent /*=NULL*/)
	: CDialogEx(DeleteUser::IDD, pParent)
	, DelName(_T(""))
{

}

DeleteUser::~DeleteUser()
{
}

void DeleteUser::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_GetUser, DelName);
}


BEGIN_MESSAGE_MAP(DeleteUser, CDialogEx)
	ON_BN_CLICKED(IDC_ExitDelete, &DeleteUser::OnBnClickedExitdelete)
	ON_BN_CLICKED(IDC_TureDelete, &DeleteUser::OnBnClickedTuredelete)
END_MESSAGE_MAP()


// DeleteUser 消息处理


// CDelUser 消息处理程序

/*************************************************************************************
*删除用户
*
**************************************************************************************/
int DeleteUser::DelUser(LPWSTR szUserName){
	DWORD dwError = 0;
	NET_API_STATUS nStatus;
	//删除用户
	nStatus = NetUserDel(NULL, szUserName);
	//判断
	if (nStatus == NERR_Success){
		MessageBox(L"删除成功!");
	}
	else
	{
		MessageBox(L"删除失败!");
	}
	return 0;
}





void DeleteUser::OnBnClickedExitdelete()
{
	EndDialog(0);
	// TODO:  在此添加控件通知处理程序代码
}


void DeleteUser::OnBnClickedTuredelete()
{
	UpdateData(TRUE);
	WCHAR   NameDel[MAX_PATH] = { 0 };
	wcscpy_s(NameDel, CT2CW(DelName));
	DelUser(NameDel);
	CDialogEx::OnOK();
	// TODO:  在此添加控件通知处理程序代码
}
