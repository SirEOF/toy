#pragma once
#include "afxcmn.h"


// PeDaoChu �Ի���
class PeDaoChu : public CDialogEx
{
	DECLARE_DYNAMIC(PeDaoChu)

public:
	PeDaoChu(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PeDaoChu();

// �Ի�������
	enum { IDD = IDD_PeDaoChu };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	
	CString mP_Dc_1;
	CString mP_Dc_2;
	CString mP_Dc_3;
	CString mP_Dc_4;
	CString mP_Dc_5;
	CString mP_Dc_6;
	CString mP_Dc_7;
	CString mP_Dc_8;
	CString mP_Dc_9;
	CString mP_Dc_10;
public:
	CListCtrl mP_DC_List;
	virtual BOOL OnInitDialog();
	void PeDaoChu::ShowInfo();
	void  ShowLIST();
	
};
