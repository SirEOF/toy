
// x64toolDlg.h : 头文件
//

#pragma once


// Cx64toolDlg 对话框
class Cx64toolDlg : public CDialogEx
{
// 构造
public:
	Cx64toolDlg(CWnd* pParent = NULL);	// 标准构造函数
	LRESULT OnControlPrint(WPARAM wParam, LPARAM lParam);
// 对话框数据
	enum { IDD = IDD_X64TOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void GetProcessId(int);
	DECLARE_MESSAGE_MAP()
};
