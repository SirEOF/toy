#pragma once
#include "List.h"
#include <vector>
using namespace std;
#define Win32PATH _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall")
#define Win64PATH _T("SOFTWARE\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall")

typedef struct _SOFTINFO
{
	TCHAR szSoftName[50];				//�������
	TCHAR szSoftVer[50];				//����汾��
	TCHAR strSoftVenRel[50];			//�����������
	TCHAR szSoftData[20];				//�����װ����
	TCHAR strSoftInsPath[MAX_PATH];		//�����װ·��
	TCHAR strSoftUniPath[MAX_PATH];		//���ж��·��
}SOFTINFO, *PSOFTINFO;

class SoftMange : public CDialogEx
{
	DECLARE_DYNAMIC(SoftMange)

public:
	SoftMange(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~SoftMange();

// �Ի�������
	enum { IDD = IDD_Dlg_SoftMange };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
public:
	//���������Ϣ
	void GetSoftwareInfo();
	//������������Ϣ
	vector<SOFTINFO> m_vecSoftInfo;
	//�ж�ϵͳ�Ƿ���64λ
	BOOL Is64();
	List MFCList;
	//�˵�
	afx_msg void OnRclickNinthlist(NMHDR *pNMHDR, LRESULT *pResult);
	//��ѡ������
	int m_Select;
	CString strTemp;

	afx_msg void OnDownload();
	afx_msg void OnFresh();
	afx_msg void OnOpenpos();
	afx_msg void OnLvnItemchangedP3List(NMHDR *pNMHDR, LRESULT *pResult);
};
