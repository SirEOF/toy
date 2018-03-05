//////////////////////////////////////////////////////////////////////
#if !defined MTRAFFIC_H
#define MTRAFFIC_H


#include <afxtempl.h>

#define Traffic_AllTraffic  388 //��������//�ܵ�����
#define Traffic_IncomingTraffic 264 //��������//��������
#define Traffic_OutGoingTraffic 506 //��������//�������

class MTraffic
{
public:
	void	SetTrafficType(int trafficType);		//������������
	DWORD	GetInterfaceTotalTraffic(int index);	//�õ�index�����ӿڵ�������
	BOOL	GetNetworkInterfaceName(CString *InterfaceName, int index);//�õ�����ӿ�����
	int		GetNetworkInterfacesCount();			//�õ��ӿڵ���Ŀ
	double	GetTraffic(int interfaceNumber);		//�õ�����

	DWORD	GetInterfaceBandwidth(int index);		//�õ�index�����ӿڵĴ���
	MTraffic();
	virtual ~MTraffic();
private:
	BOOL		GetInterfaces();
	double		lasttraffic;
	CStringList Interfaces;
	CList < DWORD, DWORD &>		Bandwidths;	//����
	CList < DWORD, DWORD &>		TotalTraffics;//�ܵ�����
	int CurrentInterface;
	int CurrentTrafficType;
};

#endif 
