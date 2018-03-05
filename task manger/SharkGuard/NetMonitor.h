#pragma once
#include "traffic_map.h"
#include "mTraffic.h"
#include "BtnTrafficDraw.h"


// NetMonitor 对话框

class NetMonitor : public CDialogEx
{
	/*DECLARE_DYNAMIC(NetMonitor)*/

public:
	BtnTrafficDraw	m_btnOutgoing;
	BtnTrafficDraw	m_btnIncoming;
	BtnTrafficDraw	m_btnTotalTraffic;
	void draw();

	NetMonitor(CWnd* pParent = NULL);   // 标准构造函数


// 对话框数据
	enum { IDD = IDD_Dlg_NetMonitor };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
public:
	void RefreshControl(UINT uCtlID);
	int SelectedInterface;

	MTraffic m_Traffic;
	MTraffic m_TrafficIn;
	MTraffic m_TrafficOut;

	TRAFFIC_MAP_DATA mDaraAll;
	TRAFFIC_MAP_DATA mDaraIn;
	TRAFFIC_MAP_DATA mDaraOut;
	afx_msg void OnBnClickedButtonIn();
	afx_msg void OnStnClickedStaticIn();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnStnClickedStaticOut();
};
