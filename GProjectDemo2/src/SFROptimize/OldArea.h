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
//新增加的属性
public:
	map<int,int> mainRb;
	map<int,int> subRb;
	vector<int> adjAreaId; //物理上相邻（不是邻区列表的那种邻区）
	int userCnt;
	vector<User> users; //此处认为生成的用户就是在某个网格中
	double rsrpGate; 
	double distanceGate;
	double totalThroughput;
	double edgeThroughput;
public:
	OldArea(int userCnt,double rsrpGate,double distanceGate) {
		this->userCnt = userCnt;
		this->rsrpGate = rsrpGate;
		this->distanceGate = distanceGate;
		rsrpGate = DISTANCEGATE; //这两个参数需要赋值，在第一次使用的时候
		distanceGate = RSRPGATE;
	}
	
public:
	vector<User> generateUser(int userCnt);
	int getEdgeUserCnt();
	bool isEdgeUser(double userX,double userY,double userRsrp);
	vector<int> getAdjAreaId();
	//分配主副载波
	void getMainSubRb();
	//对用户进行分配Rb
	void allocateRb();
};
#endif