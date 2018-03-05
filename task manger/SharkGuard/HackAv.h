#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "BtnDeclear.h"
#include "BtnScan.h"
#include "md5.h"
#include <vector>
using namespace std;
#define WM_MYUPDATEDATA				WM_USER+100 

// ������Ϣ�ṹ��
typedef struct _VIRINFO
{
	TCHAR szVirName[50];
	TCHAR szVirPath[MAX_PATH];
	TCHAR szVirSize[50];
}VIRINFO, *PVIRINFO;


class HackAv : public CDialogEx
{
	DECLARE_DYNAMIC(HackAv)

public:
	HackAv(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~HackAv();

// �Ի�������
	enum { IDD = IDD_Dlg_HackAv };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	CListCtrl listAv;
	afx_msg void OnBnClickedHackgo();
	afx_msg void OnBnClickedHackout();


public:

	//ɱ��ѡ���Ƿ�ѡ��
	BOOL IsSelect[6];
	//��ʼ����ɱѡ������
	BOOL IsSingleScan;	//�Ƿ�Ϊ�����ļ���ɱ	����Ϊȫ·��
	BOOL IsMD5;			//�Ƿ�ΪMD5��ɱ		����Ϊ������
	BOOL IsLocal;		//�Ƿ�Ϊ���ز�ɱ		����Ϊ�ƶ�
	void InitSelect();
	//��ɱ·������
	CString m_SinglePath;
	CString BrowseFolder(HWND hWnd, LPCTSTR lpTitle);
	CString m_AllPath;
	//�����ļ���ɱ
	void Scan_Single(LPCTSTR szPath);
	//ȫ·����ɱ
	void Scam_All(LPCTSTR szPath);;
	//��ʼ��ɱ
	void StartScan();
	//��ȡ������С
	CString m_szTemp;
	CString GetShowSize(DOUBLE dwSize);
	//��Ӧ���̸߳���״̬��Ϣ
	LRESULT OnUpdateMyData(WPARAM wParam, LPARAM lParam)
	{
		return UpdateData(wParam);
	}
	//MD5��ɱ
	BOOL MD5Scan(LPCTSTR szPath);
	CString m_szMD5;
	//��������ɱ
	BOOL WhiteScan(LPCTSTR szPath);
	CMD5 QQMD5;
	void TchartoChar(const TCHAR * tchar, char * _char);
	//���没����ϢVector�������������Ϣ
	vector<VIRINFO> m_vecVirInfo;
	vector<CString> m_LocalMD5;		//����MD5��
	vector<CString> m_LocalWhite;	//���ذ�������
	vector<CString> m_ServerMD5;	//�ƶ�MD5��
	vector<CString> m_ServerWhite;	//�ƶ˰�������
	//�Ʋ�ɱ
	void ServerScan();
	afx_msg void OnStnClickedPathdisk();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	void RefreshControl(UINT uCtlID);
	//***********************************************************************
	//
	//       ���ݿ� Demo
	//************************************************************************
	CListCtrl list_virsDb;
	afx_msg void OnDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMenu_Del();
	void Show();
	CString m_id;
	CString m_name;
	BOOL m_isSelect = FALSE;
	void doSelect(CString id, CString name);
	afx_msg void OnDeletevirs();
	afx_msg void OnAddvirs();
	afx_msg void OnReshow();
	BtnDeclear Bclear;
	BtnScan Bscan;
};




