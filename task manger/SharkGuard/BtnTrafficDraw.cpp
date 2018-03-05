// BtnTrafficDraw.cpp : implementation file
//

#include "stdafx.h"
//#include "Traffic_watcher.h"
#include "BtnTrafficDraw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// BtnTrafficDraw

#define GRID_STEP 10 //网格宽度
#define TRAFFIC_STEP 3 //移动宽度宽度

BtnTrafficDraw::BtnTrafficDraw()
{
	mGridStartX = 6;//画网格竖开始位置
	mdata = NULL;
	mState = 0;
}

BtnTrafficDraw::~BtnTrafficDraw()
{
}


BEGIN_MESSAGE_MAP(BtnTrafficDraw, CButton)
	//{{AFX_MSG_MAP(BtnTrafficDraw)
	ON_CONTROL_REFLECT(BN_DOUBLECLICKED, OnDoubleclicked)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



void BtnTrafficDraw::PreSubclassWindow()
{
	CButton::PreSubclassWindow();

	// 这个函数确保这个button是用来绘制的而不是接收按下的消息的
	ModifyStyle(0, BS_OWNERDRAW);
}
void BtnTrafficDraw::gostep(TRAFFIC_MAP_DATA *data)
{
	mGridStartX -= TRAFFIC_STEP;
	if (mGridStartX <= 0)
		mGridStartX += GRID_STEP;
	mdata = data;

	// 绘制
	Invalidate(FALSE);

	//#define TRAFFIC_STEP 3 //移动宽度宽度
}
//#include "memdc.h"//GDI绘图
void BtnTrafficDraw::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	//return;
	//CButton::OnDrawItem(nIDCtl, lpDrawItemStruct);
	ASSERT(lpDrawItemStruct != NULL);

	CDC * pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rect = lpDrawItemStruct->rcItem;

	pDC->FillSolidRect(&rect, 0xffffffff);

	CPen pPen(PS_SOLID, 1, RGB(255, 255, 0));//255,255,0 画左方比例尺
	pDC->SelectObject(&pPen);

	POINT p; p.x = 30; p.y = 0;
	pDC->MoveTo(p); p.y = rect.bottom;
	pDC->LineTo(p);

	//网格
	CPen pPen2(PS_SOLID, 1, RGB(1, 128, 64));
	pDC->SelectObject(&pPen2);

	int step = rect.bottom / 6;
	for (int i = 0; i < 7; i++)
	{
		int cury = step*i;
		if (0 == i)cury = 0;
		if (6 == i)cury = rect.bottom;
		p.x = 30; p.y = cury; pDC->MoveTo(p); p.x = rect.right; pDC->LineTo(p);
	}

	//#define GRID_STEP 6 //网格宽度
	//BtnTrafficDraw::BtnTrafficDraw()
	//mGridStartX=6;//画网格竖开始位置
	int curX = 30 + mGridStartX;
	while (curX < rect.right)
	{
		p.x = curX; p.y = 0; pDC->MoveTo(p); p.y = rect.bottom; pDC->LineTo(p);
		curX += GRID_STEP;
	}
	//速度曲线
	if (mdata)
	{
		
		CPen pPen3(PS_SOLID, 1, RGB(84, 255, 159));
		pDC->SelectObject(&pPen3);

		double max = mdata->GetMax();
		if (max > 1e-20)
		{
			double cur = mdata->GetFirst();
			double scale = cur / max;

			p.y = (int)(rect.bottom*scale);
			if (p.y<1)p.y = 1;
			p.y = rect.bottom - p.y;

			p.x = rect.right;
			pDC->MoveTo(p);

			cur = mdata->GetNext();
			while (cur>-0.5)
			{
				scale = cur / max;
				p.y = (int)(rect.bottom*scale);
				if (p.y < 1)p.y = 1;
				p.y = rect.bottom - p.y;
				p.x -= TRAFFIC_STEP;
				if (p.x < 30)
					break;
				pDC->LineTo(p);
				cur = mdata->GetNext();
			}
		}

		TCHAR ss[32];

		pDC->SetTextColor(RGB(255, 255, 0));

		p.x = 0;
		p.y = rect.bottom;

		swprintf_s(ss, 32,L"%.1f", max);
		pDC->TextOut(0, 0, ss);
		swprintf_s(ss, 32,L"%.1f", max / 2);
		pDC->TextOut(0, p.y / 2 - 6, ss);
		//pDC->TextOut(0,p.y-12,"0");

	}
	else
	{
		p.x = 0;
		p.y = rect.bottom;

		pDC->SetTextColor(RGB(255, 255, 0));
		//		pDC->TextOut(0,0,"100%");
		//		pDC->TextOut(0,p.y/2-6,"50%");
		pDC->TextOut(0, 0, L"0");
		pDC->TextOut(0, p.y / 2 - 6, L"0");
		//pDC->TextOut(0,p.y-12,"0");
	}
	p.y = rect.bottom;

	pDC->TextOut(0, p.y - 12, L"0");
	pDC->TextOut(31, 0, L"KB/sec");
}

extern int g_Cur_Draw_State;//当前绘图状态 0：原始 1:all 2:in 3:out
extern void TrafficchangeDrawState();
void BtnTrafficDraw::OnDoubleclicked()
{
	if (0 == g_Cur_Draw_State) g_Cur_Draw_State = mState;
	else g_Cur_Draw_State = 0;

	TrafficchangeDrawState();
}
