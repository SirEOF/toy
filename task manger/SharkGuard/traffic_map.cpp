#include "stdafx.h"
#include "traffic_map.h"

void TRAFFIC_MAP_DATA::init()
{
	memset(mData, 0, MAX_NUM_TMD*sizeof(double));

	mDataLast = 0;//���һ������λ��
	mDataNum = 0;//��Ч���ݸ���

	mMaxData = 0;//��ʼ���������ڵķ�ֵ

	mTrafficTotal = 0;//������	
	mTotaltime = 0;
};
TRAFFIC_MAP_DATA::TRAFFIC_MAP_DATA()
{
	init();
};
TRAFFIC_MAP_DATA::~TRAFFIC_MAP_DATA(){};

void TRAFFIC_MAP_DATA::Clear()
{
	init();
};//��գ����¿�ʼ
void TRAFFIC_MAP_DATA::AddData(double data, unsigned int timeStep)//����һ������
{
	if (data<0.0) data = 0;
	mTrafficTotal += data;

	data = (double)(data * (1000.0 / (double)timeStep)) / 1024.0;//�ٶ�	

	mDataLast++;
	mDataLast = mDataLast%MAX_NUM_TMD;
	mData[mDataLast] = data;

	mDataNum++;
	if (mDataNum>MAX_NUM_TMD) mDataNum = MAX_NUM_TMD;

	mMaxData = data > mMaxData ? data : mMaxData;

	mTotaltime += timeStep;

};

double TRAFFIC_MAP_DATA::GetFirst()//ȡ�����һ����ǰȡ -1������<0��
{
	if (mDataNum <= 0)
		return -1;

	mtemp = 1;//�Ѿ�ȡ�ߵĸ���
	return mData[mDataLast];//ȡ�ߵ�ǰ��
}
double TRAFFIC_MAP_DATA::GetNext()
{
	mtemp++;
	if (mtemp <= mDataNum)
	{
		int cur = (mDataLast - mtemp - 1);
		cur += MAX_NUM_TMD;
		cur = cur%MAX_NUM_TMD;
		return mData[cur];
	}
	else
		return -1;
}