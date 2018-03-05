#pragma once
#include "afxwin.h"

// PeDelay 对话框

class PeDelay : public CDialogEx
{
	DECLARE_DYNAMIC(PeDelay)

public:
	PeDelay(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~PeDelay();

// 对话框数据
	enum { IDD = IDD_PeDelay };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString mP_EDIT_Pe_Delat_1;
	CString mP_EDIT_Pe_Delat_2;
	CString mP_EDIT_Pe_Delat_3;
	CString mP_EDIT_Pe_Delat_4;
	CString mP_EDIT_Pe_Delat_5;
	CString mP_EDIT_Pe_Delat_6;
	PIMAGE_DELAYLOAD_DESCRIPTOR  pDelay;
	virtual BOOL OnInitDialog();
};
