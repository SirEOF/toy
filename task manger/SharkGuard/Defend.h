#pragma once
#include "afxcmn.h"


// Defend �Ի���

class Defend : public CDialogEx
{
	DECLARE_DYNAMIC(Defend)

public:
	Defend(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Defend();

// �Ի�������
	enum { IDD = IDD_SSDT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_csDirPath;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	CListCtrl M_Monlist;
	
};
