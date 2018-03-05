#pragma once
#include "afxcmn.h"

// PageSix 对话框

class PageSix : public CDialogEx
{
	DECLARE_DYNAMIC(PageSix)

public:
	PageSix(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~PageSix();

// 对话框数据
	enum { IDD = IDD_P6 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	
	DECLARE_MESSAGE_MAP()


	
public:
	CListCtrl m_list;
	virtual BOOL OnInitDialog();

public:
	//用户
	void EnumUser1();
	//用户组
	int Listgroup();
	//用户信息
	int ShowUsersInfo(LPWSTR pszUserName);
	afx_msg void OnNMRClickLpagesix(NMHDR *pNMHDR, LRESULT *pResult);
};



