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
	vector<complex> gridFinalPower;//向量名
	double gridFinalTotalPower;
	void findGridFinalTotalPower( float frequence);//求出每个网格的功率，将vector中的功率相加,频率以mhz为单位

};

#endif
