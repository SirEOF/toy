#pragma once


// Rocket �Ի���
class Rocket : public CDialogEx
{
	DECLARE_DYNAMIC(Rocket)

public:
	Rocket(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Rocket();

// �Ի�������
	enum { IDD = IDD_Rocket };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	
	CBitmap bmp;
	virtual BOOL OnInitDialog();
	void SetStyle();
	void Draw(CDC *dc); /*ʹ�����쿽����ͼ*/

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void ClearMemory();
};
