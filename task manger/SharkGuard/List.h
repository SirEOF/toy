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
	//�ܹ���̬����Ӷ���
	void AddColumn(DWORD dwCount, ...);
	//�ܹ���̬���һ���е�����
	void AddItem(int n, DWORD dwCount, ...);
};


