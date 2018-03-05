#pragma once
#include "MDFive.h"
#include "resource.h"


class PageFive : public CDialogEx
{
	DECLARE_DYNAMIC(PageFive)

public:
	PageFive(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PageFive();
	
// �Ի�������
	enum { IDD = IDD_P5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit6();
	//**************************************************************//pehead
	CString P_EOP;
	CString P_IMAGEBASE;
	CString P_SIZEOFIMAGE;
	CString P_BASEOFCODE;
	CString P_BASEOFDATA;
	CString P_SECTIONALIGNMENT;
	CString P_MAGIC;
	CString P_SUBSYSYSTEM;
	CString P_NUMBEROFSECTIONS;
	CString P_TIMEDATASTAMP;
	CString P_SIZEOFHEADERS;
	CString P_CHARACTERISTICS;
	CString P_CHECKSUM;
	CString P_SIZEOFOPTIONALHEADER;
	CString P_FILEALIGNMENT;
	CString P_NUMBEROFRVAANDSIZE;
	//****************************************************************//fileinfo
	CString P_FILENAME;
	CString P_SIZEOFFILE;
	CString P_MDFIVE;
	CString P_BUILDTIME;
	CString P_LASTINCORTIME;
	//********************************************
	// �ļ���	
	TCHAR Path[MAX_PATH];
	void GetMD5message();																//��ȡMD5��Ϣ
	CMD5 *MD5;																			//����һ������ָ��
	void TcharToChar(const TCHAR * tchar, char * _char);							//MD5�ֽ�ת��
	void ShowPeInfo();																	//��ʾPE�����Ϣ
	 void OnDropPE();																		//��ק��ʾ��PE
	//void ProToPE();																			//����ת��PE
	void OutPutPeInfo(CString &m_PeInfo, DWORD PeValue);					//���PE�����Ϣ
	
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnBnClickedPQuduan();
	afx_msg void OnBnClickedPMulu();
	afx_msg void OnBnClickedPBaocun();
	afx_msg void OnBnClickedPPosclac();

};



	