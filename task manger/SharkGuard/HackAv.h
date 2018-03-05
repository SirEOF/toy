#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "BtnDeclear.h"
#include "BtnScan.h"
#include "md5.h"
#include <vector>
using namespace std;
#define WM_MYUPDATEDATA				WM_USER+100 

// 病毒信息结构体
typedef struct _VIRINFO
{
	TCHAR szVirName[50];
	TCHAR szVirPath[MAX_PATH];
	TCHAR szVirSize[50];
}VIRINFO, *PVIRINFO;


class HackAv : public CDialogEx
{
	DECLARE_DYNAMIC(HackAv)

public:
	HackAv(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~HackAv();

// 对话框数据
	enum { IDD = IDD_Dlg_HackAv };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	CListCtrl listAv;
	afx_msg void OnBnClickedHackgo();
	afx_msg void OnBnClickedHackout();


public:

	//杀毒选项是否被选中
	BOOL IsSelect[6];
	//初始化查杀选项设置
	BOOL IsSingleScan;	//是否为单个文件查杀	否则为全路径
	BOOL IsMD5;			//是否为MD5查杀		否则为白名单
	BOOL IsLocal;		//是否为本地查杀		否则为云端
	void InitSelect();
	//查杀路径保存
	CString m_SinglePath;
	CString BrowseFolder(HWND hWnd, LPCTSTR lpTitle);
	CString m_AllPath;
	//单个文件查杀
	void Scan_Single(LPCTSTR szPath);
	//全路径查杀
	void Scam_All(LPCTSTR szPath);;
	//开始查杀
	void StartScan();
	//获取病毒大小
	CString m_szTemp;
	CString GetShowSize(DOUBLE dwSize);
	//响应子线程更新状态消息
	LRESULT OnUpdateMyData(WPARAM wParam, LPARAM lParam)
	{
		return UpdateData(wParam);
	}
	//MD5查杀
	BOOL MD5Scan(LPCTSTR szPath);
	CString m_szMD5;
	//白名单查杀
	BOOL WhiteScan(LPCTSTR szPath);
	CMD5 QQMD5;
	void TchartoChar(const TCHAR * tchar, char * _char);
	//保存病毒信息Vector，病毒库加载信息
	vector<VIRINFO> m_vecVirInfo;
	vector<CString> m_LocalMD5;		//本地MD5库
	vector<CString> m_LocalWhite;	//本地白名单库
	vector<CString> m_ServerMD5;	//云端MD5库
	vector<CString> m_ServerWhite;	//云端白名单库
	//云查杀
	void ServerScan();
	afx_msg void OnStnClickedPathdisk();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	void RefreshControl(UINT uCtlID);
	//***********************************************************************
	//
	//       数据库 Demo
	//************************************************************************
	CListCtrl list_virsDb;
	afx_msg void OnDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMenu_Del();
	void Show();
	CString m_id;
	CString m_name;
	BOOL m_isSelect = FALSE;
	void doSelect(CString id, CString name);
	afx_msg void OnDeletevirs();
	afx_msg void OnAddvirs();
	afx_msg void OnReshow();
	BtnDeclear Bclear;
	BtnScan Bscan;
};




