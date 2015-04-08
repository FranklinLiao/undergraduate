#ifndef _USER_H
#define _USER_H
#include <vector>
using namespace std;
class User {
public:
		int areaId;
		vector<int> rbId;
		int gridId;
		double rsrp;
		double sinr;
		double x;
		double y;
		int type=1;//1:中心用户  2：边缘用户  默认是中心用户
	//构造方法
public:
	User(int gridId,double rsrp,double x,double y){
		this->gridId = gridId;
		this->rsrp = rsrp;
		this->x = x;
		this->y = y;
	}
public:
	bool isEdgeUser();
};
#endif