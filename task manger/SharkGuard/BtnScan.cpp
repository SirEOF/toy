// BtnOne.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SharkGuard.h"
#include "BtnScan.h"
#include "afxdialogex.h"


// BtnOne �Ի���

IMPLEMENT_DYNAMIC(BtnScan, CButton)



BtnScan::BtnScan()
{
	m_btnState = NORMAL;
}

BtnScan::~BtnScan()
{
}


BEGIN_MESSAGE_MAP(BtnScan, CButton)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEHOVER()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


void BtnScan::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	//1.����ͼƬ
	CBitmap bitmap1, bitmap2, bitmap3;
	bitmap1.LoadBitmap(IDB_BITMAP43);										//����ʱ���ͼƬ����
	bitmap2.LoadBitmap(IDB_BITMAP44);										//��ͣʱ���ͼƬ����
	bitmap3.LoadBitmap(IDB_BITMAP44);										//����ʱ���ͼƬ����//2.��ȡDC���ڴ�DC
	//	2.1 ��ȡ��ͼDC
	//			�����ڣ����˺ܶ����ԣ�������һ��dc�ľ��
	//			ͨ������������ȡһ��cdc�࣬�����ϻ��ư�ťͼ��
	CDC * pDc = CDC::FromHandle(lpDrawItemStruct->hDC);
	//	2.2 �����ڴ�DC
	CDC cMemDc;
	cMemDc.CreateCompatibleDC(pDc);
	//3.ѡ��ͼƬ��Դ
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
	pDc->StretchBlt(0, 0, 135, 100, &cMemDc, 0, 0, 135, 100, SRCCOPY);
}


void BtnScan::OnMouseMove(UINT nFlags, CPoint point)
{
	//��Ҫ�ֶ�����TME_LEAVE��Ϣ��TME_HOVER��Ϣ
	TRACKMOUSEEVENT tme;
	tme.cbSize = sizeof(TRACKMOUSEEVENT);
	tme.dwFlags = TME_LEAVE | TME_HOVER;	// Ҫ��������Ϣ
	tme.hwndTrack = this->m_hWnd;			// ָ��Ϊ��ť����
	tme.dwHoverTime = 20;					// �Ҿ���Ӧ���Ǽ��ļ����ÿ20������һ��
	TrackMouseEvent(&tme);
	CButton::OnMouseMove(nFlags, point);
}


void BtnScan::OnMouseLeave()
{
	//�뿪�󴥷�
	m_bIsMouseHower = FALSE;
	m_btnState = NORMAL;					  //��ť״̬������״̬
	InvalidateRect(NULL, TRUE);
	CButton::OnMouseLeave();
}


void BtnScan::OnMouseHover(UINT nFlags, CPoint point)
{
	//һֱ�ڰ�ť�Ϸ������ظ�����
	if (m_bIsMouseHower == TRUE)
	{
		return;
	}
	//��һ������������
	m_bIsMouseHower = TRUE;

	m_btnState = MOUSEOVER;					//��ť״̬�������ͣ״̬
	InvalidateRect(NULL, TRUE);
	CButton::OnMouseHover(nFlags, point);
}

void BtnScan::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_bIsButtonDown = TRUE;
	m_btnState = BUTTONDOWN;					//��ť״̬�������״̬
	InvalidateRect(NULL, TRUE);
	CButton::OnLButtonDown(nFlags, point);
}


void BtnScan::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_bIsButtonDown = FALSE;
	m_btnState = MOUSEOVER;					//��ť״̬���ָ���ͣ״̬
	InvalidateRect(NULL, TRUE);
	CButton::OnLButtonUp(nFlags, point);
}