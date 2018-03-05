#pragma once
#include "afxcmn.h"
#include "PageTwo.h"
#include "afxcmn.h"
#include <vector>
#include <tlhelp32.h>
extern PQWORD hhnd;

// sViewHeap 对话框


class sViewHeap : public CDialogEx
{
	DECLARE_DYNAMIC(sViewHeap)

public:
	sViewHeap(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~sViewHeap();
	LRESULT GetHeapProID(WPARAM wParam, LPARAM lParam);
// 对话框数据
	enum { IDD = IDD_ViewHeap };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	CListCtrl m_Heap;
	BOOL flag;
	DWORD hhnd;
	afx_msg void SetEnvironment();
	afx_msg void ShowHeap(UINT);

	UINT m_HeapId;
	void Show();
	static sViewHeap* pthis;
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	CListCtrl m_Heap;
	afx_msg void OnLvnItemchangedViewheap(NMHDR *pNMHDR, LRESULT *pResult);
};
