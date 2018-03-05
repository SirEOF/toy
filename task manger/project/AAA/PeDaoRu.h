#pragma once
#include "afxcmn.h"


// PeDaoRu 对话框

class PeDaoRu : public CDialogEx
{
	DECLARE_DYNAMIC(PeDaoRu)

public:
	PeDaoRu(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~PeDaoRu();

// 对话框数据
	enum { IDD = IDD_PeDaoRu };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl mP_DR_List;
	CListCtrl mP_DR_List2;
	virtual BOOL OnInitDialog();
	void ShowImportList();		//显示输入表信息
	afx_msg void OnNMClickPeDrList1(NMHDR *pNMHDR, LRESULT *pResult);
};
