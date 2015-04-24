#ifndef _USERANR_H
#define _USERANR_H
#include "stdafx.h"
#include "stdlib.h"
#include "time.h"
#include "User.h"
#define DIRECTIONS 4
#define RUNTIME 100
#define RAND4 (rand()%DIRECTIONS)
class UserANR {
public:
	double maxX;
	double maxY;
	int gridId;
	double x;
	double y;
public:
	UserANR(int gridId,double x,double y){
		this->gridId = gridId;
		this->x = x;
		this->y = y;
	}
	void init(double maxX,double maxY) {
		this->maxX = maxX;
		this->maxY = maxY;
	}
	vector<double> move(double x,double y) {
		vector<double> nextPosition;
		srand((int)time(0)); //用当前时间生成随机数种子
		int randNum = RAND4;
		//定义 随机数为0,1,2,3时  分别为向上、下、左、右移动
		switch(randNum) {
		case 0: y = y -5;break;
		case 1: y = y +5;break;
		case 2: x = x -5;break;
		case 3: x = x +5;break;
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
		nextPosition.push_back(x);
		nextPosition.push_back(y);
	}
};
#endif