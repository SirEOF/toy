#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#define WM_SHOWWINDOWS WM_USER+103
// CEnumWindow �Ի���

// DlgView �Ի���

class DlgView : public CDialogEx
{
	DECLARE_DYNAMIC(DlgView)

public:
	DlgView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DlgView();

// �Ի�������
	enum { IDD = IDD_Dlgview };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg LRESULT OnProcName(WPARAM wParam, LPARAM lParam);
	static BOOL CALLBACK WndEnumProc1(HWND, LPARAM);
	//	static WCHAR szClass[MAXBYTE][MAXBYTE];
	virtual BOOL OnInitDialog();
	void ShowWindows();
	static int flag;
	CListCtrl m_EnumWindow;
};


