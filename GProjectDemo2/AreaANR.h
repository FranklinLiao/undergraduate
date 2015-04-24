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
		}
	}
	void generateUser() {
		int areaId = this->area.AId;
		vector<UserANR> users = DBHelper::getUserANR(areaId,this->userCnt); //�Ӹ�С�������������������ѡ��userCnt��������Ϊ���ѡ���˷ֲ��ڸ�С���е��û�
		this->users = users;
	}
};
#endif