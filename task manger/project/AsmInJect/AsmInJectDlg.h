
// AsmInJectDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "AsmKernel.h"

// CAsmInJectDlg 对话框
class CAsmInJectDlg : public CDialogEx
{
// 构造
public:
	CAsmInJectDlg(CWnd* pParent = NULL);	// 标准构造函数
	afx_msg LRESULT MsgASm(WPARAM wParam, LPARAM lParam);
// 对话框数据
	enum { IDD = IDD_ASMINJECT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:


	CString GetProPath();
	void InjectBin(DWORD pid);
	XASM m_asm;
	BOOL AdjustPr();

	CEdit m_Asm;
	CEdit m_Pid;
	afx_msg void OnBnClickedBtnAsm();
	afx_msg void OnBnClickedBtnexit();
};
