#pragma once
#include "MDFive.h"
#include "resource.h"


class PageFive : public CDialogEx
{
	DECLARE_DYNAMIC(PageFive)

public:
	PageFive(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~PageFive();
	
// 对话框数据
	enum { IDD = IDD_P5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
	// 文件名	
	TCHAR Path[MAX_PATH];
	void GetMD5message();																//获取MD5信息
	CMD5 *MD5;																			//声明一个类型指针
	void TcharToChar(const TCHAR * tchar, char * _char);							//MD5字节转换
	void ShowPeInfo();																	//显示PE相关信息
	 void OnDropPE();																		//拖拽显示的PE
	//void ProToPE();																			//进程转到PE
	void OutPutPeInfo(CString &m_PeInfo, DWORD PeValue);					//输出PE相关信息
	
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnBnClickedPQuduan();
	afx_msg void OnBnClickedPMulu();
	afx_msg void OnBnClickedPBaocun();
	afx_msg void OnBnClickedPPosclac();

};



	