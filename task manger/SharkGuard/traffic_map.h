#if !defined TRAFFIC_MAP_H
#define TRAFFIC_MAP_H

//绘图用数据流

class TRAFFIC_MAP_DATA
{
#define MAX_NUM_TMD 300 //数据流中数据满值	
private:
	double mData[MAX_NUM_TMD];

	int mDataLast;//最近一个数据位置
	int mDataNum;//有效数据个数

	double mMaxData;//开始记数到现在的峰值

	double mTrafficTotal;//总流量
	__int64 mTotaltime;

	int mtemp;

	void init();

public:
	TRAFFIC_MAP_DATA();
	~TRAFFIC_MAP_DATA();

	void Clear();//清空，重新开始
	void AddData(double data, unsigned int timeStep);//增加一个数据
	double GetTrafficTotal(){
		return mTrafficTotal;
	};

	double GetMax(){
		return mMaxData;
	};
	__int64 GetTotalTime(){
		return mTotaltime;
	}
	double GetFirst();
	double GetNext();
};


#endif 
