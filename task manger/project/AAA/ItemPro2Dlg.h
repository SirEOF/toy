#pragma once
#include "afxcmn.h"
#include <tlhelp32.h>
#include <vector>
#include "afxcmn.h"
using namespace std;



// CItemPro2Dlg �Ի���

class CItemPro2Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CItemPro2Dlg)

public:
	CItemPro2Dlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CItemPro2Dlg();

// �Ի�������
	enum { IDD = IDD_ItemProDlg1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	UINT m_FuckPid;
	afx_msg void OnNMRClickItemprod(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl M_FuckThread;
	static void ShowThread(void *temp);
	static CItemPro2Dlg * pthis;
	virtual BOOL OnInitDialog();
//	afx_msg void OnNMClickItemprod(NMHDR *pNMHDR, LRESULT *pResult);
};
