#ifndef _AREAANR_H
#define _AREAANR_H
#include "stdafx.h"
#include "UserANR.h"
#include "User.h"
#include "Area.h"
#define AREAANRUSERCNT 80
//给直接相邻的小区设置一个较大的数 以便排在前几位
#define ANEIGHBOURCNT 65530 
class AreaANR {
public:
	vector<UserANR> users;
	Area area;
	int userCnt;
	map<int,int> adjArea;//第一位为邻区id，第二位为这个邻区被添加的次数
	AreaANR(Area area,double maxX,double maxY,bool flag) { //flag 为true 说明是添加邻区  false 说明为对两个邻区列表进行比较
		this->area = area;
		this->userCnt = AREAANRUSERCNT;
		generateUser();
		//设定每个用户的最大移动x,y
		vector<UserANR>::iterator iter = this->users.begin();
		while(iter!=this->users.end()) {
			iter->init(maxX,maxY);
			iter++;
		}
		//添加该小区的直接相邻小区为邻区，并设置添加次数为ANEIGHBOURCNT
		if(flag) {
			vector<int> neighArea = DBHelper::getDirectNeighArea(this->area.aX,this->area.aY);
			if(neighArea.size()>0) {
				vector<int>::iterator iter = neighArea.begin();
				while(iter!=neighArea.end()) {
					if(*iter!=this->area.AId) {
						this->adjArea.insert(make_pair(*iter,ANEIGHBOURCNT));
					}
					iter++;
				}
			}
		}
	}
	void generateUser() {
		int areaId = this->area.AId;
		vector<vector<string>> userInfos = DBHelper::getUserANR(areaId,this->userCnt);
		vector<vector<string>>::iterator iterout = userInfos.begin();
		while(iterout!=userInfos.end()) {
			vector<string>::iterator iterin = (*iterout++).begin();
			int gridId = ChangeTypeTool::stringToInt(*iterin++);
			int aId = ChangeTypeTool::stringToInt(*iterin++);
			double x = ChangeTypeTool::stringToDouble(*iterin++);
			double y = ChangeTypeTool::stringToDouble(*iterin++);
			UserANR userANR = UserANR(gridId,aId,x,y);
			this->users.push_back(userANR);
		}

	}

};
#endif