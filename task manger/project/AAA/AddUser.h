#pragma once


// AddUser �Ի���

class AddUser : public CDialogEx
{
	DECLARE_DYNAMIC(AddUser)

public:
	AddUser(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~AddUser();

// �Ի�������
	enum { IDD = IDD_ADDuser };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString UserName;
	CString UserPassword;
	//afx_msg void OnBnClickedOk();
public:
	int Adduser(LPWSTR szUserName, LPWSTR szPassword);
	afx_msg void OnBnClickedAddUser();
	afx_msg void OnBnClickedExit();
	afx_msg void OnMpick();
};
