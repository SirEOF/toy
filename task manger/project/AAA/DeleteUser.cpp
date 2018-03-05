// DeleteUser.cpp : ʵ���ļ�
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
// DeleteUser �Ի���

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


// DeleteUser ��Ϣ����


// CDelUser ��Ϣ�������

/*************************************************************************************
*ɾ���û�
*
**************************************************************************************/
int DeleteUser::DelUser(LPWSTR szUserName){
	DWORD dwError = 0;
	NET_API_STATUS nStatus;
	//ɾ���û�
	nStatus = NetUserDel(NULL, szUserName);
	//�ж�
	if (nStatus == NERR_Success){
		MessageBox(L"ɾ���ɹ�!");
	}
	else
	{
		MessageBox(L"ɾ��ʧ��!");
	}
	return 0;
}





void DeleteUser::OnBnClickedExitdelete()
{
	EndDialog(0);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void DeleteUser::OnBnClickedTuredelete()
{
	UpdateData(TRUE);
	WCHAR   NameDel[MAX_PATH] = { 0 };
	wcscpy_s(NameDel, CT2CW(DelName));
	DelUser(NameDel);
	CDialogEx::OnOK();
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
