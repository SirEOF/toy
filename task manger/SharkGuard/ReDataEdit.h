#pragma once
#include "md5.h"

// ReDataEdit 对话框

class ReDataEdit : public CDialogEx
{
	DECLARE_DYNAMIC(ReDataEdit)

public:
	ReDataEdit(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ReDataEdit();

// 对话框数据
	enum { IDD = IDD_Dlg_ReData };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString v_id;
	CString v_name;
	CString v_md5;
	CString v_time;
	CString v_path;
	virtual BOOL OnInitDialog();
	BOOL m_isUpdate = FALSE;
	void doUpdate(CString id);
	afx_msg void OnBnClickedResave();
	afx_msg void OnBnClickedExitedit();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	void TcharToChar(const TCHAR * tchar, char * _char);
	CMD5 *MD5;
	// 文件名	
	TCHAR Path[MAX_PATH];
};
