#pragma once
#include "afxcmn.h"


// PeChongDW 对话框

class PeChongDW : public CDialogEx
{
	DECLARE_DYNAMIC(PeChongDW)

public:
	PeChongDW(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~PeChongDW();

// 对话框数据
	enum { IDD = IDD_PeChongDW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl mP_Cdw_L1;
	CListCtrl mP_Cdw_L2;
	void ShowRelocation();
	virtual BOOL OnInitDialog();
	
	afx_msg void OnNMClickPeCdwL1(NMHDR *pNMHDR, LRESULT *pResult);
};
