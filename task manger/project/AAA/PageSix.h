#pragma once
#include "afxcmn.h"

// PageSix �Ի���

class PageSix : public CDialogEx
{
	DECLARE_DYNAMIC(PageSix)

public:
	PageSix(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PageSix();

// �Ի�������
	enum { IDD = IDD_P6 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	
	DECLARE_MESSAGE_MAP()


	
public:
	CListCtrl m_list;
	virtual BOOL OnInitDialog();

public:
	//�û�
	void EnumUser1();
	//�û���
	int Listgroup();
	//�û���Ϣ
	int ShowUsersInfo(LPWSTR pszUserName);
	afx_msg void OnNMRClickLpagesix(NMHDR *pNMHDR, LRESULT *pResult);
};



