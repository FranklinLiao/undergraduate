#ifndef _SHOOTINGRAY_H
#define _SHOOTINGRAY_H
#include "stdafx.h"
#include<iostream>
#include<math.h>
using namespace std;
#define pi 3.14
#define gainMax 17.7

class shootingRay{
public:
	float x[2000], y[2000], z[2000],gain[2000];
	void shootingGain(float directionAngle,float downInclineAngle,float horizonDivision,float verticalDivision);
	void shootingGainAllDirection(float directionAngle,float downInclineAngle,float horizonRange, float verticalRange,
		float horizonDivision,float verticalDivision);//射线发射是全向的

	
};

#endif