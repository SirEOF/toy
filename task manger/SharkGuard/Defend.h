#pragma once
#include "afxcmn.h"


// Defend 对话框

class Defend : public CDialogEx
{
	DECLARE_DYNAMIC(Defend)

public:
	Defend(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Defend();

// 对话框数据
	enum { IDD = IDD_SSDT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_csDirPath;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	CListCtrl M_Monlist;
	
};
