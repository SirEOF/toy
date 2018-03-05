// BtnOne.cpp : 实现文件
//

#include "stdafx.h"
#include "SharkGuard.h"
#include "Head.h"
#include "afxdialogex.h"


// BtnOne 对话框

IMPLEMENT_DYNAMIC(Head, CButton)



Head::Head()
{
	m_btnState = NORMAL;
}

Head::~Head()
{
}


BEGIN_MESSAGE_MAP(Head, CButton)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEHOVER()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


void Head::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	//1.加载图片
	CBitmap bitmap1, bitmap2, bitmap3;
	bitmap1.LoadBitmap(IDB_BITMAP21);										//正常时候的图片样子
	bitmap2.LoadBitmap(IDB_BITMAP23);										//悬停时候的图片样子
	bitmap3.LoadBitmap(IDB_BITMAP23);										//按下时候的图片样子//2.获取DC和内存DC
	//	2.1 获取绘图DC
	//			参数内，带了很多属性，其中有一个dc的句柄
	//			通过这个句柄，获取一个cdc类，在其上绘制按钮图案
	CDC * pDc = CDC::FromHandle(lpDrawItemStruct->hDC);
	//	2.2 创建内存DC
	CDC cMemDc;
	cMemDc.CreateCompatibleDC(pDc);
	//3.选入图片资源
	CBitmap * pOld;
	switch (m_btnState)
	{
	case NORMAL:
		pOld = cMemDc.SelectObject(&bitmap1);
		break;
	case MOUSEOVER:
		pOld = cMemDc.SelectObject(&bitmap2);
		break;
	case BUTTONDOWN:
		pOld = cMemDc.SelectObject(&bitmap3);
		break;
	}
//	pDc->StretchBlt(0, 0, 96, 96, &cMemDc, 0, 0, 96, 96, SRCCOPY);
	pDc->StretchBlt(0, 0, 250, 96, &cMemDc, 0, 0, 250, 96, SRCCOPY);
}


void Head::OnMouseMove(UINT nFlags, CPoint point)
{
	//需要手动触发TME_LEAVE消息和TME_HOVER消息
	TRACKMOUSEEVENT tme;
	tme.cbSize = sizeof(TRACKMOUSEEVENT);
	tme.dwFlags = TME_LEAVE | TME_HOVER;	// 要触发的消息
	tme.hwndTrack = this->m_hWnd;			// 指定为按钮窗口
	tme.dwHoverTime = 20;					// 我觉得应该是检测的间隔，每20毫秒检测一次
	TrackMouseEvent(&tme);
	CButton::OnMouseMove(nFlags, point);
}


void Head::OnMouseLeave()
{
	//离开后触发
	m_bIsMouseHower = FALSE;
	m_btnState = NORMAL;					  //按钮状态，正常状态
	InvalidateRect(NULL, TRUE);
	CButton::OnMouseLeave();
}


void Head::OnMouseHover(UINT nFlags, CPoint point)
{
	//一直在按钮上方，则不重复触发
	if (m_bIsMouseHower == TRUE)
	{
		return;
	}
	//第一次上来，触发
	m_bIsMouseHower = TRUE;

	m_btnState = MOUSEOVER;					//按钮状态，鼠标悬停状态
	InvalidateRect(NULL, TRUE);
	CButton::OnMouseHover(nFlags, point);
}

void Head::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_bIsButtonDown = TRUE;
	m_btnState = BUTTONDOWN;					//按钮状态，被点击状态
	InvalidateRect(NULL, TRUE);
	CButton::OnLButtonDown(nFlags, point);
}


void Head::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_bIsButtonDown = FALSE;
	m_btnState = MOUSEOVER;					//按钮状态，恢复悬停状态
	InvalidateRect(NULL, TRUE);
	CButton::OnLButtonUp(nFlags, point);
}
