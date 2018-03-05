#pragma once
#include "afxcmn.h"


// PeZiYuan 对话框

class PeZiYuan : public CDialogEx
{
	DECLARE_DYNAMIC(PeZiYuan)

public:
	PeZiYuan(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~PeZiYuan();

// 对话框数据
	enum { IDD = IDD_PeZiYuan };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString mP_EDIT_ZY_1_1;
	CString mP_EDIT_ZY_1_2;
	CString mP_EDIT_ZY_2_1;
	CString mP_EDIT_ZY_2_2;
	CString mP_EDIT_ZY_3_1;
	CString mP_EDIT_ZY_3_2;
	CString mP_EDIT_ZY_3_3;
	CTreeCtrl mP_Tree_ReSouce;
	
	void ShowResourcesInfo();
	virtual BOOL OnInitDialog();
	afx_msg void OnNMClickTree1(NMHDR *pNMHDR, LRESULT *pResult);
};
