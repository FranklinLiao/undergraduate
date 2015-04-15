#ifndef _USER_H
#define _USER_H
#include "stdafx.h"
#include <vector>
using namespace std;

class User {
public:
		vector<int> rbId;  //计算吞吐量时，需要判断实际分配了几个Rb
		int gridId;
		double rsrp;
		double sinr;
		double x;
		double y;
		int type;//1:中心用户  2：边缘用户  
	//构造方法
public:
	User(int gridId,double rsrp,double x,double y){
		this->gridId = gridId;
		this->rsrp = rsrp;
		this->x = x;
		this->y = y;
		this->type = 1; //默认是中心用户
	}
};
#endif