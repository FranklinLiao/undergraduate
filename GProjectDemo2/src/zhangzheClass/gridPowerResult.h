#ifndef _GRIDPOWERRESULT_H
#define _GRIDPOWERRESULT_H
#include "stdafx.h"
#include<iostream>
#include "complex.h"
#include<cmath>
#include<vector>
using namespace std;
class gridPowerResult
{
public:
	vector<complex> gridFinalPower;//������
	double gridFinalTotalPower;
	void findGridFinalTotalPower( float frequence);//���ÿ������Ĺ��ʣ���vector�еĹ������,Ƶ����mhzΪ��λ

};

#endif
