#pragma once
#include "afxcmn.h"
#include <vector>
#include <tlhelp32.h>

using namespace std;

// ModelPro �Ի���

class ModelPro : public CDialogEx
{
	DECLARE_DYNAMIC(ModelPro)

public:
	ModelPro(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ModelPro();

// �Ի�������
	enum { IDD = IDD_ModelProDlg };

public:
	//UINT m_dwPID;
	
	vector<MODULEENTRY32> m_VecModList;
	TCHAR *m_StrMoudle;
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	virtual BOOL OnInitDialog();
	BOOL isInitEnd;
	UINT m_dwPID;
	
	CListCtrl m_MoudleList;
	afx_msg void KillMoudle();
	afx_msg void initMoudle();
	void ReMoudleList();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
};
