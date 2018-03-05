#pragma once


// DeleteUser 对话框

class DeleteUser : public CDialogEx
{
	DECLARE_DYNAMIC(DeleteUser)

public:
	DeleteUser(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DeleteUser();

// 对话框数据
	enum { IDD = IDD_DelUser };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString DelName;
public:
	int DelUser(LPWSTR szUserName);
	afx_msg void OnBnClickedExitdelete();
	afx_msg void OnBnClickedTuredelete();
};
