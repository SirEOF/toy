#pragma once


// PeTls �Ի���

class PeTls : public CDialogEx
{
	DECLARE_DYNAMIC(PeTls)

public:
	PeTls(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PeTls();

// �Ի�������
	enum { IDD = IDD_PeTls };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString mP_EDIT_Pe_TSL_1;
	CString mP_EDIT_Pe_TSL_2;
	CString mP_EDIT_Pe_TSL_3;
	CString mP_EDIT_Pe_TSL_4;
	CString mP_EDIT_Pe_TSL_5;
	CString mP_EDIT_Pe_TSL_6;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnPeTsl();
};
