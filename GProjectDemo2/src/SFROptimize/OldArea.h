#ifndef _OLDAREA_H
#define _OLDAREA_H
#include "Area.h"
#include "User.h"
#include "Rbs.h"
#include <vector>
#include <math>
using namespace std;
#define DISTANCEGATE 100
#define RSRPGATE -80
class OldArea:public Area{
//�����ӵ�����
public:
	map<int,int> mainRb;
	map<int,int> subRb;
	vector<int> adjAreaId; //���������ڣ����������б������������
	int userCnt;
	vector<User> users; //�˴���Ϊ���ɵ��û�������ĳ��������
	double rsrpGate; 
	double distanceGate;
	double totalThroughput;
	double edgeThroughput;
public:
	OldArea(int userCnt,double rsrpGate,double distanceGate) {
		this->userCnt = userCnt;
		this->rsrpGate = rsrpGate;
		this->distanceGate = distanceGate;
		rsrpGate = DISTANCEGATE; //������������Ҫ��ֵ���ڵ�һ��ʹ�õ�ʱ��
		distanceGate = RSRPGATE;
	}
	
public:
	vector<User> generateUser(int userCnt);
	int getEdgeUserCnt();
	bool isEdgeUser(double userX,double userY,double userRsrp);
	vector<int> getAdjAreaId();
	//���������ز�
	void getMainSubRb();
	//���û����з���Rb
	void allocateRb();
};
#endif