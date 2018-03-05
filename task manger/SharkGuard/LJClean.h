
#pragma once


//#pragma once


#include "SysClean.h"
#include "recentFile.h"
#include "bwn.h"
#include "Cookie.h"
#include "Delete.h"
#include "afxcmn.h"
#include "Wininet.h"
#include "MemoryCleanBtn.h"
#include "VsClear.h"
#include "VsSelect.h"
#include "afxwin.h"
#include <vector>
using std::vector;
enum DEL_CACHE_TYPE
{
	FILES = 0, COOKIES
};
//清理项ID枚举
enum DEL_RUBBISH_TYPE
{
	CLEAN_SYSTEM_TEMP = 0,
	CLEAN_DOCUMENT_HISTORY,
	CLEAN_INTERNET_TEMP, CLEAN_INTERNET_COOKIE
};

class LJClean : public CDialogEx
{
	DECLARE_DYNAMIC(LJClean)

public:
	LJClean(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~LJClean();

// 对话框数据
	enum { IDD = IDD_Dlg_LJClean };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	vector<CString> m_vecPath;
	SysClean sys;
	recentFile file;
	bwn bWn;
	Cookie cookie;
	Delete deLete;
	VsClear vsClear;
	VsSelect vsSelect;
	MemoryCleanBtn MemClear;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedP2sysfile();
	afx_msg void OnBnClickedP2record();

	afx_msg void OnBnClickedDelete();
	CListCtrl Cl1;
	BOOL  FirstShow(LPCTSTR szPath, BOOL bDeleteDesktopIni = FALSE, BOOL bWipeIndexDat = FALSE);
	CString ShowSize(DOUBLE dwSize);						  DOUBLE m_AllFileSize;
	bool WipeShow(LPCTSTR szDir, LPCTSTR szFile);
	BOOL IsScanFile;
	BOOL DeleteUrlCache(DEL_CACHE_TYPE type);
	//DWORD WINAPI NewThread(LPVOID lpVoid);
	afx_msg void OnHdnGetdispinfoP2L1(NMHDR *pNMHDR, LRESULT *pResult);
	
	afx_msg void OnBnClickedNewfile();
	afx_msg void OnBnClickedCookies();
	afx_msg void OnLvnItemchangedP2L1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedMemoryclean();
	afx_msg void ClearMemory();
	CListBox vsPath;
	afx_msg void OnBnClickedSelectfile();
	afx_msg void OnBnClickedVsclear();
	void ErgodicFile(TCHAR szPath[MAX_PATH]);
	afx_msg void OnLbnSelchangeVspath();
};
