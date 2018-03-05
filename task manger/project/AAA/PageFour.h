#pragma once
#include "afxwin.h"


// PageFour 对话框

class PageFour : public CDialogEx
{
	DECLARE_DYNAMIC(PageFour)

public:
	PageFour(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~PageFour();
	LRESULT OnRePaint(WPARAM wParam, LPARAM lParam);
// 对话框数据
	enum { IDD = IDD_P4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void RefreshControl(UINT uCtlID);
	afx_msg void OnBnClickedZyjsq();
	afx_msg void OnBnClickedWulineicun();
	CString S_KeYongMem;
	CString S_AddressMem;
	CString S_FreeMem;
	afx_msg void OnStnClickedAddressmem();
	afx_msg void OnStnClickedFreeaddress();
	afx_msg void OnStnClickedWulimem();
	CStatic M_AddMem;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	
	CStatic S_AddFreeMem;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedCleanmemry();
	afx_msg void ClearMemory();
	CString m_SsFree;
	CStatic FuckDog;
};



