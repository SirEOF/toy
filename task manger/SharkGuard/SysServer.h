#pragma once
#include "SerList.h"
#include "Qdshut.h"
#include <winsvc.h>
#include <vector>
#include "afxcmn.h"
using namespace std;

#define UPDATE_SERVICE_INFO		WM_USER+3			//更新服务信息消息宏

//启动项信息结构体
typedef struct _BOOTINFO
{
	TCHAR szBootName[50];			//启动项
	TCHAR szBootOrder[255];			//命令
	TCHAR szHKEY[50];				//主键信息
	TCHAR szBootPos[255];			//删除时要用到的
	TCHAR szBootPos_All[255];		//List中要显示的
}BOOTINFO, *PBOOTINFO;



class SysServer : public CDialogEx
{
	DECLARE_DYNAMIC(SysServer)

public:
	SysServer(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~SysServer();

// 对话框数据
	enum { IDD = IDD_Dlg_SysServer };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	

public:
	

	//所选服务的名字
	CString m_ServiceName;
	//服务信息容器
	vector<ENUM_SERVICE_STATUS> m_vecSerInfo;
	//获取服务信息
	void GetServiceInfo();
	//更新服务频率
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//更新服务信息
	void UpDataSerInfo();
	//是否需要更新进程
	BOOL m_IsUpDateSer;
	//更新次数
	DWORD m_UpDataTimes;
	//所选服务在List中的序号
	DWORD m_SelectNum;
	// List变量
	MyFourList MyFourthList;
	afx_msg void OnSeverstart();
	afx_msg void OnSeverstop();
	afx_msg void OnSeverfresh();
	afx_msg void OnNMRClickListSever(NMHDR *pNMHDR, LRESULT *pResult);
public:
	MyEighthList StartUp;
	//保存软件相关信息
	vector<BOOTINFO> m_vecBootInfo;
	//获取启动项信息
	void GetBootInfo();
	//所选则的软件
	int m_Select;
	CString strTemp;

	afx_msg void OnAddqd();
	afx_msg void OnBanqd();
	afx_msg void OnFreshqd();
	afx_msg void OnNMRClickListQd(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListQd(NMHDR *pNMHDR, LRESULT *pResult);
};


