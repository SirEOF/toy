#pragma once


// PePosCalc �Ի���

class PePosCalc : public CDialogEx
{
	DECLARE_DYNAMIC(PePosCalc)

public:
	PePosCalc(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PePosCalc();

// �Ի�������
	enum { IDD = IDD_PePosCalc };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedPePosRa();
	afx_msg void OnBnClickedPePosRva();
	afx_msg void OnBnClickedPePosPianyi();
	CString mP_Pos_Edit_RA;
	CString mP_Pos_Edit_RVA;
	CString mP_Pos_Edit_PianYi;
	CString mP_Pos_Edit_QuDuan;
	CString mP_Pos_Edit_ZiJie;
	afx_msg void OnBnClickedPeposwork();
public:
	//������Ϣ��
	void  LockEdit(int EditId);
	//ת��ƫ��
	DWORD SwitchOffset(DWORD Rva);
	afx_msg void OnEnChangePePosEditRa();
	afx_msg void OnEnChangePePosEditRva();
	afx_msg void OnEnChangePePosEditPianyi();
};
