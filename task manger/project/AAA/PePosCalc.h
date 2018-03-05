#pragma once


// PePosCalc 对话框

class PePosCalc : public CDialogEx
{
	DECLARE_DYNAMIC(PePosCalc)

public:
	PePosCalc(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~PePosCalc();

// 对话框数据
	enum { IDD = IDD_PePosCalc };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
	//锁定信息框
	void  LockEdit(int EditId);
	//转换偏移
	DWORD SwitchOffset(DWORD Rva);
	afx_msg void OnEnChangePePosEditRa();
	afx_msg void OnEnChangePePosEditRva();
	afx_msg void OnEnChangePePosEditPianyi();
};
