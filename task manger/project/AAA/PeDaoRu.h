#pragma once
#include "afxcmn.h"


// PeDaoRu �Ի���

class PeDaoRu : public CDialogEx
{
	DECLARE_DYNAMIC(PeDaoRu)

public:
	PeDaoRu(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PeDaoRu();

// �Ի�������
	enum { IDD = IDD_PeDaoRu };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl mP_DR_List;
	CListCtrl mP_DR_List2;
	virtual BOOL OnInitDialog();
	void ShowImportList();		//��ʾ�������Ϣ
	afx_msg void OnNMClickPeDrList1(NMHDR *pNMHDR, LRESULT *pResult);
};
