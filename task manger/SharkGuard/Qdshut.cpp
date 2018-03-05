// MyEighthList.cpp : 实现文件
//

#include "stdafx.h"
#include "SharkGuard.h"
#include "Qdshut.h"


// MyEighthList

IMPLEMENT_DYNAMIC(MyEighthList, CListCtrl)

MyEighthList::MyEighthList()
{

}

MyEighthList::~MyEighthList()
{
}


BEGIN_MESSAGE_MAP(MyEighthList, CListCtrl)
END_MESSAGE_MAP()

void MyEighthList::AddColumn(DWORD dwCount, ...)
{
	va_list vl;
	va_start(vl, dwCount);
	//名称
	TCHAR* pName = va_arg(vl, TCHAR*);
	InsertColumn(0, pName, 0, 150);
	//发布者
	pName = va_arg(vl, TCHAR*);
	InsertColumn(1, pName, 0, 350);
	//安装时间
	pName = va_arg(vl, TCHAR*);
	InsertColumn(2, pName, 0, 350);
}

void MyEighthList::AddItem(int n, DWORD dwCount, ...)
{
	va_list vl;
	va_start(vl, dwCount);
	TCHAR* pName = va_arg(vl, TCHAR*);
	InsertItem(n, pName);
	for (DWORD i = 1; i < dwCount; i++)
	{
		TCHAR* pName = va_arg(vl, TCHAR*);
		SetItemText(n, i, pName);
	}

}

// MyEighthList 消息处理程序


