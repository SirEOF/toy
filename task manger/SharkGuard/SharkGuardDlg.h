
// SharkGuardDlg.h : ͷ�ļ�
//

#pragma once
#include <vector>
#include "BtnOne.h"
#include "BtnTwo.h"
#include "BtnThree.h"
#include "BtnFour.h"
#include "BtnFive.h"
#include "BtnSix.h"
#include "BtnSeven.h"
#include "Exit.h"
#include "Min.h"
#include "Head.h"
#include "LJClean.h"
#include "SoftMange.h"
#include "SysServer.h"
#include "NetMonitor.h"
#include "HackAv.h"
#include "Defend.h"
#include "Rocket.h"
#include "shellapi.h"
using namespace std;
// CSharkGuardDlg �Ի���
class CSharkGuardDlg : public CDialogEx
{
// ����
public:
	CSharkGuardDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MainPage };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	NOTIFYICONDATA Id;
	afx_msg LRESULT OnNcHitTest(CPoint point);
	BtnOne bOne;
	BtnTwo bTwo;
	BtnThree bThree;
	BtnFour  bFour;
	BtnFive bFive;
	BtnSix bSix;
	BtnSeven bSeven;
	Exit ei;
	Min mi;
	Head Top;
	afx_msg void OnBnClickedHackav();
	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedMin();
	afx_msg void OnBnClickedHead();
	vector<CDialogEx*> m_vecDlg;
	void ShowWindowDlg(CDialogEx* phwnd);
	afx_msg void OnBnClickedLjclean();
	afx_msg void OnBnClickedSoftmange();
	afx_msg void OnBnClickedVirsfuck();
	afx_msg void OnBnClickedSysserver();
	afx_msg void OnBnClickedNetmonitor();
	afx_msg void OnBnClickedSsdt();
	LJClean LjClear;
	SoftMange SfMange;
	SysServer Sys;
	NetMonitor Mitor;
	HackAv Av;
	Defend defend;
	Rocket rock;
	NOTIFYICONDATA m_nid;
	afx_msg LRESULT Hide(WPARAM wParam, LPARAM lParam);
};
