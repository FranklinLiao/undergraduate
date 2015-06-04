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
	map<int,int> adjArea;//��һλΪ����id���ڶ�λΪ�����������ӵĴ���
	AreaANR(Area area,double maxX,double maxY) {
		this->area = area;
		this->userCnt = AREAANRUSERCNT;
		generateUser();
		//�趨ÿ���û�������ƶ�x,y
		vector<UserANR>::iterator iter = this->users.begin();
		while(iter!=this->users.end()) {
			iter->init(maxX,maxY);
			iter++;
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