#ifndef _USER_H
#define _USER_H
#include <vector>
using namespace std;
class User {
	private int areaId;
	private vector<int> rbId;
	private int gridId;
	private double rsrp;
	private double sinr;
	private double x;
	private double y;
	private int type;//1:中心用户  2：边缘用户
	//构造方法
	User(int areaId,vector<int> rbId,int gridId,double rsrp,double sinr,double x,double y,int type) {
		this->areaId = areaId;
		this->rbId = rbId;
		this->gridId = gridId;
		this->rsrp = rsrp;
		this->sinr = sinr;
		this->x = x;
		this->y = y;
		this->type = type;
	}

};
#endif