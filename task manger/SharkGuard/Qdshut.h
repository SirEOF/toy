#pragma once


// MyEighthList

class MyEighthList : public CListCtrl
{
	DECLARE_DYNAMIC(MyEighthList)

public:
	MyEighthList();
	virtual ~MyEighthList();


protected:
	DECLARE_MESSAGE_MAP()
public:
	void AddColumn(DWORD dwCount, ...);
	void AddItem(int n, DWORD dwCount, ...);
};


