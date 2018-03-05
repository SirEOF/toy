#if !defined(AFX_BTNTRAFFICDRAW_H__03353773_A3F0_4EB2_A8C3_AB680586BC46__INCLUDED_)
#define AFX_BTNTRAFFICDRAW_H__03353773_A3F0_4EB2_A8C3_AB680586BC46__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BtnTrafficDraw.h : header file
//
#include "traffic_map.h"

/////////////////////////////////////////////////////////////////////////////
// BtnTrafficDraw window

class BtnTrafficDraw : public CButton
{
	// Construction
public:
	BtnTrafficDraw();

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(BtnTrafficDraw)
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

	// Implementation
public:
	virtual ~BtnTrafficDraw();

	// Generated message map functions
	void BtnTrafficDraw::gostep(TRAFFIC_MAP_DATA *data);
	void setState(int state){
		mState = state;
	}
protected:
	//{{AFX_MSG(BtnTrafficDraw)
	afx_msg void OnDoubleclicked();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	int mGridStartX;
	TRAFFIC_MAP_DATA *mdata;

	int mState;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BTNTRAFFICDRAW_H__03353773_A3F0_4EB2_A8C3_AB680586BC46__INCLUDED_)
