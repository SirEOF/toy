#pragma once

//#include "servicer.h"
#include "afxcmn.h"
#include <vector>
#include <winsvc.h>
using namespace std;
#define UPDATE_SERVICE_INFO		WM_USER+3			//���·�����Ϣ��Ϣ��
// ServicerDlg �Ի���


// PageThree �Ի���

class PageThree : public CDialogEx
{
	DECLARE_DYNAMIC(PageThree)

public:
	PageThree(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PageThree();

// �Ի�������
	enum { IDD = IDD_P3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnLvnItemchangedList3(NMHDR *pNMHDR, LRESULT *pResult);
	
	
	//��ѡ���������
	CString m_ServiceName;
	//List��Ա����
	servicer servicer_List;
	//������Ϣ����
	vector<ENUM_SERVICE_STATUS> m_vecSerInfo;
	//���ڴ�С
	afx_msg void OnSize(UINT nType, int cx, int cy);
	bool isInitEnd;
	//��ȡ������Ϣ
	void GetServiceInfo();
	//���ڳ�ʼ������
	virtual BOOL OnInitDialog();
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
	//����List�Ҽ���Ӧ����
	afx_msg void OnRclickList(NMHDR *pNMHDR, LRESULT *pResult);
	//��������
	afx_msg void qidong();
	//ֹͣ����
	afx_msg void tingzhi();
	//ˢ�·���
	afx_msg void shuaxin();
	
	
	afx_msg void OnStops();
};





