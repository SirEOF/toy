// LabelItem.h: interface for the CLabelItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LABELITEM_H__AD63D692_F1DC_11D4_9414_00C04F68EB57__INCLUDED_)
#define AFX_LABELITEM_H__AD63D692_F1DC_11D4_9414_00C04F68EB57__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLabelItem : public CObject
{
public:
	DWORD m_Addr;
	CString m_strText;
	CLabelItem();
	CLabelItem(const CLabelItem& ci);
	const CLabelItem& operator=(const CLabelItem& stringSrc);
	virtual ~CLabelItem();

};

#endif // !defined(AFX_LABELITEM_H__AD63D692_F1DC_11D4_9414_00C04F68EB57__INCLUDED_)
