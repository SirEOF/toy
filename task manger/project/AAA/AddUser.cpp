// AddUser.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AAA.h"
#include "AddUser.h"
#include "afxdialogex.h"
#include <Lmaccess.h>
#include <stdlib.h>
#include <lm.h>
#include <assert.h>

// AddUser �Ի���
#pragma comment(lib, "Netapi32.lib")
IMPLEMENT_DYNAMIC(AddUser, CDialogEx)

AddUser::AddUser(CWnd* pParent /*=NULL*/)
	: CDialogEx(AddUser::IDD, pParent)
	, UserName(_T(""))
	, UserPassword(_T(""))
{

}

AddUser::~AddUser()
{
}

void AddUser::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, UserName);
	DDX_Text(pDX, IDC_EDIT2, UserPassword);
}


BEGIN_MESSAGE_MAP(AddUser, CDialogEx)
	//ON_BN_CLICKED(IDOK, &AddUser::OnBnClickedOk)
	ON_BN_CLICKED(IDC_Add, &AddUser::OnBnClickedAddUser)
	ON_BN_CLICKED(IDC_Exit, &AddUser::OnBnClickedExit)
	ON_COMMAND(ID_Mpick, &AddUser::OnMpick)
END_MESSAGE_MAP()





/************************************************************************************
*����û�
*szUserName�û��� szPassword����
**************************************************************************************/
int AddUser::Adduser(LPWSTR szUserName, LPWSTR szPassword){
	USER_INFO_1 ui;
	DWORD dwLevel = 1;
	DWORD dwError = 0;
	NET_API_STATUS nSatatus;
	//���USER_INFO_1
	ui.usri1_name = szUserName;//�û���
	ui.usri1_password = szPassword;//����
	ui.usri1_priv = USER_PRIV_USER;//����
	ui.usri1_home_dir = NULL;
	ui.usri1_comment = NULL;
	ui.usri1_flags = UF_SCRIPT;
	ui.usri1_script_path = NULL;
	//�����û�
	nSatatus = NetUserAdd(NULL, dwLevel, (LPBYTE)&ui, &dwError);
	//�жϽ��
	if (nSatatus == NERR_Success){
		MessageBox(L"��ӳɹ�!");
	}
	else
	{
		MessageBox(L"���ʧ��!");
	}
	return 0;
}


















void AddUser::OnBnClickedAddUser()
{
	UpdateData(TRUE);
	WCHAR   Name[MAX_PATH] = { 0 };
	WCHAR	Password[MAX_PATH] = { 0 };
	wcscpy_s(Name, CT2CW(UserName));
	wcscpy_s(Password, CT2CW(Password));
	Adduser(Name, Password);
	CDialogEx::OnOK();
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void AddUser::OnBnClickedExit()
{
	//AfxGetMainWnd()->SendMessage(WM_CLOSE);
	//DestroyWindow();
	EndDialog(0);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void AddUser::OnMpick()
{
	// TODO:  �ڴ���������������
}
