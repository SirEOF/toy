
// x64toolDlg.h : ͷ�ļ�
//

#pragma once


// Cx64toolDlg �Ի���
class Cx64toolDlg : public CDialogEx
{
// ����
public:
	Cx64toolDlg(CWnd* pParent = NULL);	// ��׼���캯��
	LRESULT OnControlPrint(WPARAM wParam, LPARAM lParam);
// �Ի�������
	enum { IDD = IDD_X64TOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void GetProcessId(int);
	DECLARE_MESSAGE_MAP()
};
