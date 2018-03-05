#pragma once


// BtnOne ¶Ô»°¿ò

class BtnTwo : public CButton
{
	DECLARE_DYNAMIC(BtnTwo)

public:
	BtnTwo();
	virtual ~BtnTwo();


protected:

	DECLARE_MESSAGE_MAP()
public:
	enum BUTTONSTATE
	{
		NORMAL, MOUSEOVER, BUTTONDOWN
	};
	BUTTONSTATE m_btnState;					//°´Å¥×´Ì¬
	bool m_bIsButtonDown;
	bool m_bIsMouseHower;
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};




