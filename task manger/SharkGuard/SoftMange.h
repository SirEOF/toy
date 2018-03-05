#pragma once
#include "List.h"
#include <vector>
using namespace std;
#define Win32PATH _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall")
#define Win64PATH _T("SOFTWARE\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall")

typedef struct _SOFTINFO
{
	TCHAR szSoftName[50];				//软件名称
	TCHAR szSoftVer[50];				//软件版本号
	TCHAR strSoftVenRel[50];			//软件发布厂商
	TCHAR szSoftData[20];				//软件安装日期
	TCHAR strSoftInsPath[MAX_PATH];		//软件安装路径
	TCHAR strSoftUniPath[MAX_PATH];		//软件卸载路径
}SOFTINFO, *PSOFTINFO;

class SoftMange : public CDialogEx
{
	DECLARE_DYNAMIC(SoftMange)

public:
	SoftMange(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~SoftMange();

// 对话框数据
	enum { IDD = IDD_Dlg_SoftMange };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
public:
	//遍历软件信息
	void GetSoftwareInfo();
	//保存软件相关信息
	vector<SOFTINFO> m_vecSoftInfo;
	//判断系统是否是64位
	BOOL Is64();
	List MFCList;
	//菜单
	afx_msg void OnRclickNinthlist(NMHDR *pNMHDR, LRESULT *pResult);
	//所选则的软件
	int m_Select;
	CString strTemp;

	afx_msg void OnDownload();
	afx_msg void OnFresh();
	afx_msg void OnOpenpos();
	afx_msg void OnLvnItemchangedP3List(NMHDR *pNMHDR, LRESULT *pResult);
};
