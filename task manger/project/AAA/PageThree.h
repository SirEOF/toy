#pragma once

//#include "servicer.h"
#include "afxcmn.h"
#include <vector>
#include <winsvc.h>
using namespace std;
#define UPDATE_SERVICE_INFO		WM_USER+3			//更新服务信息消息宏
// ServicerDlg 对话框


// PageThree 对话框

class PageThree : public CDialogEx
{
	DECLARE_DYNAMIC(PageThree)

public:
	PageThree(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~PageThree();

// 对话框数据
	enum { IDD = IDD_P3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnLvnItemchangedList3(NMHDR *pNMHDR, LRESULT *pResult);
	
	
	//所选服务的名字
	CString m_ServiceName;
	//List成员变量
	servicer servicer_List;
	//服务信息容器
	vector<ENUM_SERVICE_STATUS> m_vecSerInfo;
	//窗口大小
	afx_msg void OnSize(UINT nType, int cx, int cy);
	bool isInitEnd;
	//获取服务信息
	void GetServiceInfo();
	//窗口初始化函数
	virtual BOOL OnInitDialog();
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
	//服务List右键响应函数
	afx_msg void OnRclickList(NMHDR *pNMHDR, LRESULT *pResult);
	//启动服务
	afx_msg void qidong();
	//停止服务
	afx_msg void tingzhi();
	//刷新服务
	afx_msg void shuaxin();
	
	
	afx_msg void OnStops();
};





