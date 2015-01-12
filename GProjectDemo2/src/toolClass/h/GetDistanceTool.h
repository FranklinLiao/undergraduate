#ifndef _GETDISTANCETOOL_H
#define _GETDISTANCETOOL_H
#include "stdafx.h"
#include <math.h>
#include <vector>
using namespace std;

class GetDistanceTool{
private:
	double MyEarthRadius;
	double gridDistance;

public:
	GetDistanceTool() {
		MyEarthRadius= 6378.137;
		gridDistance = 0.005;
	}
	vector<double> boundingCoordinates(double longi,double lati);

};
#endif