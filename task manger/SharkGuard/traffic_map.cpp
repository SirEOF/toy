#include "stdafx.h"
#include "traffic_map.h"

void TRAFFIC_MAP_DATA::init()
{
	memset(mData, 0, MAX_NUM_TMD*sizeof(double));

	mDataLast = 0;//最近一个数据位置
	mDataNum = 0;//有效数据个数

	mMaxData = 0;//开始记数到现在的峰值

	mTrafficTotal = 0;//总流量	
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
};//清空，重新开始
void TRAFFIC_MAP_DATA::AddData(double data, unsigned int timeStep)//增加一个数据
{
	if (data<0.0) data = 0;
	mTrafficTotal += data;

	data = (double)(data * (1000.0 / (double)timeStep)) / 1024.0;//速度	

	mDataLast++;
	mDataLast = mDataLast%MAX_NUM_TMD;
	mData[mDataLast] = data;

	mDataNum++;
	if (mDataNum>MAX_NUM_TMD) mDataNum = MAX_NUM_TMD;

	mMaxData = data > mMaxData ? data : mMaxData;

	mTotaltime += timeStep;

};

double TRAFFIC_MAP_DATA::GetFirst()//取最近的一个向前取 -1结束（<0）
{
	if (mDataNum <= 0)
		return -1;

	mtemp = 1;//已经取走的个数
	return mData[mDataLast];//取走当前的
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