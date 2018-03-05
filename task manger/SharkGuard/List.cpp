// MyNinthList.cpp : 实现文件
//

#include "stdafx.h"
#include "SharkGuard.h"
#include "List.h"


// MyNinthList

IMPLEMENT_DYNAMIC(List, CListCtrl)

List::List()
{

}

List::~List()
{
}


BEGIN_MESSAGE_MAP(List, CListCtrl)
END_MESSAGE_MAP()

void List::AddColumn(DWORD dwCount, ...)
{
	va_list vl;
	va_start(vl, dwCount);
	//名称
	TCHAR* pName = va_arg(vl, TCHAR*);
	InsertColumn(0, pName, 0, 350);
	//发布者
	pName = va_arg(vl, TCHAR*);
	InsertColumn(1, pName, 0, 200);
	//安装时间
	pName = va_arg(vl, TCHAR*);
	InsertColumn(2, pName, 0, 100);
	//版本
	pName = va_arg(vl, TCHAR*);
	InsertColumn(3, pName, 0, 200);
	va_end(vl);
}

void List::AddItem(int n, DWORD dwCount, ...)
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
	va_end(vl);
}



// MyNinthList 消息处理程序


