// MyNinthList.cpp : ʵ���ļ�
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
	//����
	TCHAR* pName = va_arg(vl, TCHAR*);
	InsertColumn(0, pName, 0, 350);
	//������
	pName = va_arg(vl, TCHAR*);
	InsertColumn(1, pName, 0, 200);
	//��װʱ��
	pName = va_arg(vl, TCHAR*);
	InsertColumn(2, pName, 0, 100);
	//�汾
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



// MyNinthList ��Ϣ�������


