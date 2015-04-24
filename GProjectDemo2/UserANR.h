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
		srand((int)time(0)); //�õ�ǰʱ���������������
		int randNum = RAND4;
		//���� �����Ϊ0,1,2,3ʱ  �ֱ�Ϊ���ϡ��¡������ƶ�
		switch(randNum) {
		case 0: y = y -5;break;
		case 1: y = y +5;break;
		case 2: x = x -5;break;
		case 3: x = x +5;break;
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
		nextPosition.push_back(x);
		nextPosition.push_back(y);
	}
};
#endif