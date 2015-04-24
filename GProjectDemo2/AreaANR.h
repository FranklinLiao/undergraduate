#ifndef _AREAANR_H
#define _AREAANR_H
#include "stdafx.h"
#include "UserANR.h"
#include "User.h"
#include "Area.h"
#define AREAANRUSERCNT 40
class AreaANR {
public:
	vector<UserANR> users;
	Area area;
	int userCnt;
	map<int,int> adjArea;//第一位为邻区id，第二位为这个邻区被添加的次数
	AreaANR(Area area,double maxX,double maxY) {
		this->area = area;
		this->userCnt = AREAANRUSERCNT;
		generateUser();
		//设定每个用户的最大移动x,y
		vector<UserANR>::iterator iter = this->users.begin();
		while(iter!=this->users.end()) {
			iter->init(maxX,maxY);
		}
	}
	void generateUser() {
		int areaId = this->area.AId;
		vector<UserANR> users = DBHelper::getUserANR(areaId,this->userCnt); //从该小区所包括的网格中随机选择userCnt个，即认为随机选择了分布在该小区中的用户
		this->users = users;
	}
};
#endif