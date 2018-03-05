
// AsmInJectDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "AsmKernel.h"

// CAsmInJectDlg �Ի���
class CAsmInJectDlg : public CDialogEx
{
// ����
public:
	CAsmInJectDlg(CWnd* pParent = NULL);	// ��׼���캯��
	afx_msg LRESULT MsgASm(WPARAM wParam, LPARAM lParam);
// �Ի�������
	enum { IDD = IDD_ASMINJECT_DIALOG };

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


	CString GetProPath();
	void InjectBin(DWORD pid);
	XASM m_asm;
	BOOL AdjustPr();

	CEdit m_Asm;
	CEdit m_Pid;
	afx_msg void OnBnClickedBtnAsm();
	afx_msg void OnBnClickedBtnexit();
};
