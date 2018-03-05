#pragma once


// Rocket 对话框
class Rocket : public CDialogEx
{
	DECLARE_DYNAMIC(Rocket)

public:
	Rocket(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Rocket();

// 对话框数据
	enum { IDD = IDD_Rocket };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	
	CBitmap bmp;
	virtual BOOL OnInitDialog();
	void SetStyle();
	void Draw(CDC *dc); /*使用拉伸拷贝画图*/

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void ClearMemory();
};
