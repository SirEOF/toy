
// AAADlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "DlgView.h"
#include "PageOne.h"
#include "PageTwo.h"
#include "PageThree.h"
#include "PageFour.h"
#include "PageFive.h"
#include "PageSix.h"
#include "afxwin.h"
static UINT cpuDef(LPVOID);
static CStatusBar m_Status;
// CAAADlg 对话框
class CAAADlg : public CDialogEx
{
// 构造
public:
	CAAADlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_AAA_DIALOG };
	
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	
// 实现
	
protected:
	
	HICON m_hIcon;
	PageOne m_L1;
	PageTwo m_L2;
	PageThree m_L3;
	PageFour m_L4;
	PageFive m_L5;
	PageSix m_L6;
	
	//PageOne m_L3;
	//PageOne m_L4;
	//PageOne m_L5;
	//PageOne m_L6;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	
	//void InitMenu();
public:
	 CTabCtrl m_tab;
	 CListCtrl m_MoudleList;
	 bool m_IsWindowHide;
//	afx_msg void OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);

	

	afx_msg void OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickedD2endprocess();
	afx_msg void OnBnClickedP3server();
	
	afx_msg void OnClickedEndprocess();
	//void getState();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	afx_msg void OnTopMenuStart();
	afx_msg void OnExitTaskManger();
	afx_msg void On32788();
	afx_msg void OnWideSpread();
	afx_msg void OnListSpread();
	afx_msg void OnSetMin();
	afx_msg void OnSetMax();
	afx_msg void OnCengD();
	afx_msg void OnForeSet();
	afx_msg void OnFreshRightOnce();
	afx_msg void InitStaus();
	afx_msg void TabInsert();
	afx_msg void OnBnClickedNewServer();

	afx_msg void OnBnClickedTurnto();
	afx_msg void OnBnClickedLogout();
	afx_msg void OnBnClickedZhuxiao();
	afx_msg void OnBnClickedSendmes();
	CButton m_SendMes;

	afx_msg void OnSysrise();
	afx_msg void OnViewwindow();
	afx_msg void OnClose();
	NOTIFYICONDATA m_nid;
protected:
	
	afx_msg LRESULT OnTuoPan(WPARAM wParam, LPARAM lParam);

};

class CCPUUseRate
{
public:


public:
	BOOL Initialize()
	{
		FILETIME ftIdle, ftKernel, ftUser;
		BOOL flag = FALSE;
		if (flag = GetSystemTimes(&ftIdle, &ftKernel, &ftUser))
		{
			m_fOldCPUIdleTime = FileTimeToDouble(ftIdle);
			m_fOldCPUKernelTime = FileTimeToDouble(ftKernel);
			m_fOldCPUUserTime = FileTimeToDouble(ftUser);

		}
		return flag;
	}
	//调用Initialize后要等待1秒再调用此函数  
	int GetCPUUseRate()
	{
		int nCPUUseRate = -1;
		FILETIME ftIdle, ftKernel, ftUser;
		if (GetSystemTimes(&ftIdle, &ftKernel, &ftUser))
		{
			double fCPUIdleTime = FileTimeToDouble(ftIdle);
			double fCPUKernelTime = FileTimeToDouble(ftKernel);
			double fCPUUserTime = FileTimeToDouble(ftUser);
			nCPUUseRate = (int)(100.0 - (fCPUIdleTime - m_fOldCPUIdleTime)
				/ (fCPUKernelTime - m_fOldCPUKernelTime + fCPUUserTime - m_fOldCPUUserTime)
				*100.0);
			m_fOldCPUIdleTime = fCPUIdleTime;
			m_fOldCPUKernelTime = fCPUKernelTime;
			m_fOldCPUUserTime = fCPUUserTime;
		}
		return nCPUUseRate;
	}
private:
	double FileTimeToDouble(FILETIME &filetime)
	{
		return (double)(filetime.dwHighDateTime * 4.294967296E9) + (double)filetime.dwLowDateTime;
	}
private:
	double m_fOldCPUIdleTime;
	double m_fOldCPUKernelTime;
	double m_fOldCPUUserTime;
};