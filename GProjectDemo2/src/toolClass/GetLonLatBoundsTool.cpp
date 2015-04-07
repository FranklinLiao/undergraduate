#include "stdafx.h"
#include "GetLonLatBoundsTool.h"
vector<double> GetLonLatBoundsTool::getLonLatBounds() { //得到建筑物的边界
	vector<double> lonLatBounds;
	DataBase db;
	lonLatBounds=db.getLonLatBounds();
	return lonLatBounds;
}

vector<double> GetLonLatBoundsTool::getGridLonLatBounds() { //得到网格的边界
	vector<double> lonLatBounds;
	DataBase db;
	lonLatBounds=db.getGridLonLatBounds();
	return lonLatBounds;
}