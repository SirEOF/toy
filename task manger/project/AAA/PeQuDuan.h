#pragma once
#include "afxcmn.h"


// PeQuDuan �Ի���

class PeQuDuan : public CDialogEx
{
	DECLARE_DYNAMIC(PeQuDuan)

public:
	PeQuDuan(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PeQuDuan();

// �Ի�������
	enum { IDD = IDD_PeQUDUAN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl mP_QD_list;
	//���α�ͷ
	virtual BOOL OnInitDialog();
	//���α�����
	void ShowQuDuan();

};
