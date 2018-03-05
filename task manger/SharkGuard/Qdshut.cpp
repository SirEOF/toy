// MyEighthList.cpp : ʵ���ļ�
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
	//����
	TCHAR* pName = va_arg(vl, TCHAR*);
	InsertColumn(0, pName, 0, 150);
	//������
	pName = va_arg(vl, TCHAR*);
	InsertColumn(1, pName, 0, 350);
	//��װʱ��
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

// MyEighthList ��Ϣ�������


