#pragma once
#include "afxcmn.h"


// PeChongDW �Ի���

class PeChongDW : public CDialogEx
{
	DECLARE_DYNAMIC(PeChongDW)

public:
	PeChongDW(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PeChongDW();

// �Ի�������
	enum { IDD = IDD_PeChongDW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl mP_Cdw_L1;
	CListCtrl mP_Cdw_L2;
	void ShowRelocation();
	virtual BOOL OnInitDialog();
	
	afx_msg void OnNMClickPeCdwL1(NMHDR *pNMHDR, LRESULT *pResult);
};
