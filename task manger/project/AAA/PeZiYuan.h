#pragma once
#include "afxcmn.h"


// PeZiYuan �Ի���

class PeZiYuan : public CDialogEx
{
	DECLARE_DYNAMIC(PeZiYuan)

public:
	PeZiYuan(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PeZiYuan();

// �Ի�������
	enum { IDD = IDD_PeZiYuan };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString mP_EDIT_ZY_1_1;
	CString mP_EDIT_ZY_1_2;
	CString mP_EDIT_ZY_2_1;
	CString mP_EDIT_ZY_2_2;
	CString mP_EDIT_ZY_3_1;
	CString mP_EDIT_ZY_3_2;
	CString mP_EDIT_ZY_3_3;
	CTreeCtrl mP_Tree_ReSouce;
	
	void ShowResourcesInfo();
	virtual BOOL OnInitDialog();
	afx_msg void OnNMClickTree1(NMHDR *pNMHDR, LRESULT *pResult);
};
