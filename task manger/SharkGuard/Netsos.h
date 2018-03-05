#pragma once
#include <afxtempl.h>
class Netsos
{
public:
	enum TrafficType //流量类型
	{
		AllTraffic = 388,//总的流量
		IncomingTraffic = 264,//输入流量
		OutGoingTraffic = 506 //输出流量
	};
	void	SetTrafficType(int trafficType);		//设置流量类型
	DWORD	GetInterfaceTotalTraffic(int index);	//得到index索引接口的总流量
	BOOL	GetNetworkInterfaceName(CString *InterfaceName, int index);//得到网络接口名字
	int		GetNetworkInterfacesCount();			//得到接口的数目
	double	GetTraffic(int interfaceNumber);		//得到流量
	DWORD	GetInterfaceBandwidth(int index);		//得到index索引接口的带宽
	Netsos();
	virtual ~Netsos();

private:
	BOOL		GetInterfaces();
	double		lasttraffic;
	CStringList Interfaces;
	CList < DWORD, DWORD &>		Bandwidths;	//带宽
	CList < DWORD, DWORD &>		TotalTraffics;//总的流量
	int CurrentInterface;
	int CurrentTrafficType;
};

