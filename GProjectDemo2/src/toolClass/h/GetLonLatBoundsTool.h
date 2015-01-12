#ifndef _GETLONLATBOUNDSTOOL_H
#define _GETLONLATBOUNDSTOOL_H
#include "stdafx.h"
#include "DataBase.h"
#include <vector>
using namespace std;

class GetLonLatBoundsTool{
private:
	static vector<double> LonLatBounds;
public:
	static vector<double> getLonLatBounds();
};

#endif