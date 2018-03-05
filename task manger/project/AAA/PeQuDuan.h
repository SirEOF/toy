#pragma once
#include "afxcmn.h"


// PeQuDuan 对话框

class PeQuDuan : public CDialogEx
{
	DECLARE_DYNAMIC(PeQuDuan)

public:
	PeQuDuan(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~PeQuDuan();

// 对话框数据
	enum { IDD = IDD_PeQUDUAN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl mP_QD_list;
	//区段表头
	virtual BOOL OnInitDialog();
	//区段表内容
	void ShowQuDuan();

};
