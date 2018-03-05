#pragma once
#include "SerList.h"
#include "Qdshut.h"
#include <winsvc.h>
#include <vector>
#include "afxcmn.h"
using namespace std;

#define UPDATE_SERVICE_INFO		WM_USER+3			//���·�����Ϣ��Ϣ��

//��������Ϣ�ṹ��
typedef struct _BOOTINFO
{
	TCHAR szBootName[50];			//������
	TCHAR szBootOrder[255];			//����
	TCHAR szHKEY[50];				//������Ϣ
	TCHAR szBootPos[255];			//ɾ��ʱҪ�õ���
	TCHAR szBootPos_All[255];		//List��Ҫ��ʾ��
}BOOTINFO, *PBOOTINFO;



class SysServer : public CDialogEx
{
	DECLARE_DYNAMIC(SysServer)

public:
	SysServer(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~SysServer();

// �Ի�������
	enum { IDD = IDD_Dlg_SysServer };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	

public:
	

	//��ѡ���������
	CString m_ServiceName;
	//������Ϣ����
	vector<ENUM_SERVICE_STATUS> m_vecSerInfo;
	//��ȡ������Ϣ
	void GetServiceInfo();
	//���·���Ƶ��
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//���·�����Ϣ
	void UpDataSerInfo();
	//�Ƿ���Ҫ���½���
	BOOL m_IsUpDateSer;
	//���´���
	DWORD m_UpDataTimes;
	//��ѡ������List�е����
	DWORD m_SelectNum;
	// List����
	MyFourList MyFourthList;
	afx_msg void OnSeverstart();
	afx_msg void OnSeverstop();
	afx_msg void OnSeverfresh();
	afx_msg void OnNMRClickListSever(NMHDR *pNMHDR, LRESULT *pResult);
public:
	MyEighthList StartUp;
	//������������Ϣ
	vector<BOOTINFO> m_vecBootInfo;
	//��ȡ��������Ϣ
	void GetBootInfo();
	//��ѡ������
	int m_Select;
	CString strTemp;

	afx_msg void OnAddqd();
	afx_msg void OnBanqd();
	afx_msg void OnFreshqd();
	afx_msg void OnNMRClickListQd(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListQd(NMHDR *pNMHDR, LRESULT *pResult);
};


