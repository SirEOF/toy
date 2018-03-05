#pragma once
#include "afxcmn.h"
#include <tlhelp32.h>
#include <vector>
#include "tchar.h"
#include "sViewHeap.h"
#include "afxwin.h"

// PageTwo 对话框
         //    new sViewHeap();




class PageTwo : public CDialogEx
{
	DECLARE_DYNAMIC(PageTwo)

public:
	PageTwo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~PageTwo();
	PQWORD hhnd;
	afx_msg LRESULT SendProcessID(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT SendProHeap(WPARAM wParam, LPARAM lParam);
// 对话框数据
	enum { IDD = IDD_P2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	int m_L2;
	CListCtrl m_L2;
        //DLL新线程注入
	public:
		HANDLE hfile;
		TCHAR  m_Path[MAX_PATH];
		DWORD m_PID;
		CString Path;
		TCHAR *TPath;
		BOOL pFlag;
		CString ProcessName;
		void ShowList();//列表插入
		//afx_msg void OnRclickProcessList(NMHDR *pNMHDR, LRESULT *pResult);
		BOOL GetProcessPath(DWORD dwPID);//获取文件路径
		BOOL BDTPath(LPTSTR BDPath, LPTSTR BTPath);//获取磁盘信息
		
		afx_msg void OnSeem();
		afx_msg void OnSeet();
		afx_msg void OnKissproc();

		afx_msg void OnReproc();
		afx_msg void OnResh();

		afx_msg void OnUpproc();

		afx_msg void OnHighmal();
		
		afx_msg void OnLowmal();
		afx_msg void OnMal();
		afx_msg void OnRt();
		afx_msg void OnTOPE();

		afx_msg void DLL();
		afx_msg void OnDropFiles(HDROP hDropInfo);
		afx_msg void Onyincang();



		afx_msg void KillPro();
		afx_msg void Openpos();
		afx_msg void RePro();
		afx_msg void Refreshlist();
		afx_msg void Viewmodel();
		afx_msg void ViewProcess();
	
		afx_msg void OnNMRClickLt2(NMHDR *pNMHDR, LRESULT *pResult);
		afx_msg void OnPickpro();  //挂起进程
		afx_msg void OnDllinJect(); //DLL注入
	
		afx_msg void OnInjectshellcode();
		void SetProcessPriority(int PriorityFlag);//判断优先级并设置
	
		 
		afx_msg void OnShishi();
		afx_msg void OnHighstd();
		afx_msg void OnStd();
		afx_msg void OnBelowstd();
		afx_msg void OnLow();
		afx_msg void OnHigh();
		afx_msg void OnViewheap();
		afx_msg void OnNMRClickItemprod(NMHDR *pNMHDR, LRESULT *pResult);
		afx_msg void OnHideProcess();
		virtual BOOL OnInitDialog();
};

