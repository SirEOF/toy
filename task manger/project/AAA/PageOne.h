#pragma once
#include "afxcmn.h"
#include <vector>
using namespace std;

// PageOne 对话框

class PageOne : public CDialogEx
{
	DECLARE_DYNAMIC(PageOne)

public:
	PageOne(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~PageOne();

// 对话框数据
	enum { IDD = IDD_P1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	 CListCtrl m_L1;
	 CListCtrl Exelist;
	virtual BOOL OnInitDialog();
	BOOL isInitEnd;
	
	static BOOL CALLBACK PROC1(HWND hwnd, LPARAM lparam);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	static PageOne * m_myThis; //为了static回调函数使用成员变量。
	
	
	afx_msg void OnLvnItemchangedLt1(NMHDR *pNMHDR, LRESULT *pResult);


	afx_msg void OnBnClickServer();
};
