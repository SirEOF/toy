#pragma once


// MyNinthList

class List : public CListCtrl
{
	DECLARE_DYNAMIC(List)

public:
	List();
	virtual ~List();

protected:
	DECLARE_MESSAGE_MAP()
public:
	//能够动态的添加多列
	void AddColumn(DWORD dwCount, ...);
	//能够动态添加一整行的内容
	void AddItem(int n, DWORD dwCount, ...);
};


