#include "stdafx.h"
#include "GetLonLatBoundsTool.h"
vector<double> GetLonLatBoundsTool::getLonLatBounds() {
	vector<double> lonLatBounds;
	DataBase db;
	lonLatBounds=db.getLonLatBounds();
	return lonLatBounds;
}