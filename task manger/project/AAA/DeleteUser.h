#pragma once


// DeleteUser �Ի���

class DeleteUser : public CDialogEx
{
	DECLARE_DYNAMIC(DeleteUser)

public:
	DeleteUser(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DeleteUser();

// �Ի�������
	enum { IDD = IDD_DelUser };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString DelName;
public:
	int DelUser(LPWSTR szUserName);
	afx_msg void OnBnClickedExitdelete();
	afx_msg void OnBnClickedTuredelete();
};
