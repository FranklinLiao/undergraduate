#include "stdafx.h"
#include "AreaGrid.h"

AreaGrid AreaGrid::getObject(vector<string> param) {
	AreaGrid areaGrid = AreaGrid(param);
	return areaGrid;
}

vector<AreaGrid> AreaGrid::getObjectSet(vector<vector<string>> param) {
	vector<AreaGrid> areaGridSet;
	vector<vector<string>>::iterator iter = param.begin();
	while(iter!=param.end()) {
		AreaGrid building = AreaGrid::getObject(*iter++);
		areaGridSet.push_back(building);
	}
	return areaGridSet;
}
