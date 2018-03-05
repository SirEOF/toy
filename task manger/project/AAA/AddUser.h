#pragma once


// AddUser 对话框

class AddUser : public CDialogEx
{
	DECLARE_DYNAMIC(AddUser)

public:
	AddUser(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AddUser();

// 对话框数据
	enum { IDD = IDD_ADDuser };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
