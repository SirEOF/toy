//////////////////////////////////////////////////////////////////////
#if !defined MTRAFFIC_H
#define MTRAFFIC_H


#include <afxtempl.h>

#define Traffic_AllTraffic  388 //流量类型//总的流量
#define Traffic_IncomingTraffic 264 //流量类型//输入流量
#define Traffic_OutGoingTraffic 506 //流量类型//输出流量

class MTraffic
{
public:
	void	SetTrafficType(int trafficType);		//设置流量类型
	DWORD	GetInterfaceTotalTraffic(int index);	//得到index索引接口的总流量
	BOOL	GetNetworkInterfaceName(CString *InterfaceName, int index);//得到网络接口名字
	int		GetNetworkInterfacesCount();			//得到接口的数目
	double	GetTraffic(int interfaceNumber);		//得到流量

	DWORD	GetInterfaceBandwidth(int index);		//得到index索引接口的带宽
	MTraffic();
	virtual ~MTraffic();
private:
	BOOL		GetInterfaces();
	double		lasttraffic;
	CStringList Interfaces;
	CList < DWORD, DWORD &>		Bandwidths;	//带宽
	CList < DWORD, DWORD &>		TotalTraffics;//总的流量
	int CurrentInterface;
	int CurrentTrafficType;
};

#endif 
