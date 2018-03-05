#if !defined TRAFFIC_MAP_H
#define TRAFFIC_MAP_H

//��ͼ��������

class TRAFFIC_MAP_DATA
{
#define MAX_NUM_TMD 300 //��������������ֵ	
private:
	double mData[MAX_NUM_TMD];

	int mDataLast;//���һ������λ��
	int mDataNum;//��Ч���ݸ���

	double mMaxData;//��ʼ���������ڵķ�ֵ

	double mTrafficTotal;//������
	__int64 mTotaltime;

	int mtemp;

	void init();

public:
	TRAFFIC_MAP_DATA();
	~TRAFFIC_MAP_DATA();

	void Clear();//��գ����¿�ʼ
	void AddData(double data, unsigned int timeStep);//����һ������
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
