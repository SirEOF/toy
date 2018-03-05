#pragma once


// PeMainIndex 对话框

class PeMainIndex : public CDialogEx
{
	DECLARE_DYNAMIC(PeMainIndex)

public:
	PeMainIndex(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~PeMainIndex();

// 对话框数据
	enum { IDD = IDD_PeMainIndex };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString Pe_1_RAV;
	CString Pe_1_SIZE;
	CString Pe_2_RAV;
	CString Pe_2_SIZE;
	CString Pe_3_RAV;
	CString Pe_3_SIZE;
	CString Pe_4_RAV;
	CString Pe_4_SIZE;
	CString Pe_5_RAV;
	CString Pe_5_SIZE;
	CString Pe_6_RAV;
	CString Pe_6_SIZE;
	CString Pe_7_RAV;
	CString Pe_7_SIZE;
	CString Pe_8_RAV;
	CString Pe_8_SIZE;
	CString Pe_9_RAV;
	CString Pe_9_SIZE;
	CString Pe_10_RAV;
	CString Pe_10_SIZE;
	CString Pe_11_RAV;
	CString Pe_11_SIZE;
	CString Pe_12_RAV;
	CString Pe_12_SIZE;
	CString Pe_13_RAV;
	CString Pe_13_SIZE;
	CString Pe_14_RAV;
	CString Pe_14_SIZE;
	CString Pe_15_RAV;
	CString Pe_15_SIZE;
	CString Pe_16_RAV;
	CString Pe_16_SIZE;
	PIMAGE_OPTIONAL_HEADER32 pOptional;
	PIMAGE_SECTION_HEADER pSection;
public:
	virtual BOOL OnInitDialog();
	void ShowInfo();
	void OutPutPeInfo(CString &m_RvaInfo, CString &m_SizeInfo, DWORD RvaValue, DWORD SizeValue);//输出PE相关信息
	
	afx_msg void OnBnClickedBtnDaochu();
	afx_msg void OnBnClickedBtnDaoru();
	afx_msg void OnBnClickedBtnZiyuan();
	afx_msg void OnBnClickedBtnChongdingwei();
	afx_msg void OnBnClickedBtnYanchishuru();
	afx_msg void OnBnClickedBtnPeTls();
};
