#ifndef _USERANR_H
#define _USERANR_H
#include "stdafx.h"
#include "stdlib.h"
#include "time.h"
#include "User.h"
#include "CreateSqlTool.h"
#include "DBHelper.h"
//A3�¼�����ֵ
//���� 4db
//ƫ�� 0-6db
#define HYST   4 //���Ͳ���
#define CELLOFFSET 2 //ƫ�ò���
#define TIMELAST 4
#define AREARSRPGATE   -90 //A2�¼�   ����С�����źŵ�ƽ����ĳһֵ  �˴���ȷ������Ҫ�ٺú��˽�A3
//�û����ƶ�����
#define DIRECTIONS 4
#define RAND4 (rand()%DIRECTIONS)
class UserANR {
public:
	double maxX;
	double maxY;
	int gridId;
	int aid;
	double x;
	double y;
	map<int,double> otherAreaRsrp;
	map<int,int> areaCalCnt;// �������С����A3�¼���������  �����ж�����С���Ƿ���Խ����л�
public:
	UserANR(int gridId,int aid,double x,double y){
		this->gridId = gridId;
		this->aid = aid;
		this->x = x;
		this->y = y;
		setOtherAreaRsrp(gridId);
	}
	void init(double maxX,double maxY) {
		this->maxX = maxX;
		this->maxY = maxY;
	}
	void move(double x,double y) {
		vector<double> nextPosition;
		srand((int)time(0)); //�õ�ǰʱ���������������
		int randNum = RAND4;
		//���� �����Ϊ0,1,2,3ʱ  �ֱ�Ϊ���ϡ��¡������ƶ�
		switch(randNum) {
		case 0: y = y -GRIDSIZE;break;
		case 1: y = y +GRIDSIZE;break;
		case 2: x = x -GRIDSIZE;break;
		case 3: x = x +GRIDSIZE;break;
		}
		//�ж�xy�Ƿ��ڵ�ͼ������
		if(x<0) {
			x = 0;
		} 
		if(y<0) {
			y = 0;
		}
		if(x>maxX) {
			x = maxX;
		}
		if(y>maxY) {
			y = maxY;
		}
	}

	void setOtherAreaRsrp(int gid) {
		otherAreaRsrp.clear(); //�ڲ���֮ǰ��ɾ�������õ�
		vector<vector<string>> vectorString = DBHelper::getGridAllRsrp(gid);
		vector<vector<string>>::iterator iterout = vectorString.begin();
		while(iterout!=vectorString.end()) {
			vector<string>::iterator iterin = (*iterout++).begin();
			int aId = ChangeTypeTool::stringToInt(*iterin++);
			double rsrp = ChangeTypeTool::stringToDouble(*iterin++);
			otherAreaRsrp.insert(map<int,double>::value_type(aId,rsrp)); //���������������Ϣ���
		}
	}

	map<int,double> getOtherAreaRsrp(int gid) {
		setOtherAreaRsrp(gid);
		return otherAreaRsrp;
	}


	bool isA3Meet(double serverAreaRsrp,double adjAreaRsrp) {
		bool flag = false;
		//��������+����ƫ��-���Ͳ���>�������+����ƫ��+A3ƫ�ò���
		//�˴�����С��ƫ�ö�Ϊ0
		double temp = adjAreaRsrp - HYST - (serverAreaRsrp + CELLOFFSET);
		//bool flag_temp = serverAreaRsrp < AREARSRPGATE;
		if(temp>0 /*&& flag_temp*/) {
			flag = true;
		} else {
			flag = false;
		}
		return flag;
	}
};
#endif