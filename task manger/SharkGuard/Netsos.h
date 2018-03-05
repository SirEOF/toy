#pragma once
#include <afxtempl.h>
class Netsos
{
public:
	enum TrafficType //��������
	{
		AllTraffic = 388,//�ܵ�����
		IncomingTraffic = 264,//��������
		OutGoingTraffic = 506 //�������
	};
	void	SetTrafficType(int trafficType);		//������������
	DWORD	GetInterfaceTotalTraffic(int index);	//�õ�index�����ӿڵ�������
	BOOL	GetNetworkInterfaceName(CString *InterfaceName, int index);//�õ�����ӿ�����
	int		GetNetworkInterfacesCount();			//�õ��ӿڵ���Ŀ
	double	GetTraffic(int interfaceNumber);		//�õ�����
	DWORD	GetInterfaceBandwidth(int index);		//�õ�index�����ӿڵĴ���
	Netsos();
	virtual ~Netsos();

private:
	BOOL		GetInterfaces();
	double		lasttraffic;
	CStringList Interfaces;
	CList < DWORD, DWORD &>		Bandwidths;	//����
	CList < DWORD, DWORD &>		TotalTraffics;//�ܵ�����
	int CurrentInterface;
	int CurrentTrafficType;
};

