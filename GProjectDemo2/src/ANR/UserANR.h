#ifndef _USERANR_H
#define _USERANR_H
#include "stdafx.h"
#include "stdlib.h"
#include "time.h"
#include "User.h"
#include "CreateSqlTool.h"
#include "DBHelper.h"
//A3事件的阈值
//迟滞 4db
//偏置 0-6db
#define HYST   4 //迟滞参数
#define CELLOFFSET 2 //偏置参数
#define TIMELAST 4
#define AREARSRPGATE   -90 //A2事件   服务小区的信号电平低于某一值  此处不确定，需要再好好了解A3
//用户的移动方向
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
	map<int,int> areaCalCnt;// 存放相邻小区的A3事件成立次数  用于判断相邻小区是否可以进行切换
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
		srand((int)time(0)); //用当前时间生成随机数种子
		int randNum = RAND4;
		//定义 随机数为0,1,2,3时  分别为向上、下、左、右移动
		switch(randNum) {
		case 0: y = y -GRIDSIZE;break;
		case 1: y = y +GRIDSIZE;break;
		case 2: x = x -GRIDSIZE;break;
		case 3: x = x +GRIDSIZE;break;
		}
		//判断xy是否在地图坐标内
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
		otherAreaRsrp.clear(); //在插入之前先删除掉不用的
		vector<vector<string>> vectorString = DBHelper::getGridAllRsrp(gid);
		vector<vector<string>>::iterator iterout = vectorString.begin();
		while(iterout!=vectorString.end()) {
			vector<string>::iterator iterin = (*iterout++).begin();
			int aId = ChangeTypeTool::stringToInt(*iterin++);
			double rsrp = ChangeTypeTool::stringToDouble(*iterin++);
			otherAreaRsrp.insert(map<int,double>::value_type(aId,rsrp)); //将该网格的邻区信息添加
		}
	}

	map<int,double> getOtherAreaRsrp(int gid) {
		setOtherAreaRsrp(gid);
		return otherAreaRsrp;
	}


	bool isA3Meet(double serverAreaRsrp,double adjAreaRsrp) {
		bool flag = false;
		//邻区测量+邻区偏置-迟滞参数>服务测量+服务偏置+A3偏置参数
		//此处考虑小区偏置都为0
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