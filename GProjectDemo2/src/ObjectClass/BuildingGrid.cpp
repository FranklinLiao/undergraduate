#include "stdafx.h"
#include "BuildingGrid.h"

BuildingGrid BuildingGrid::getObject(vector<string> param) {
	BuildingGrid buildingGrid = BuildingGrid(param);
	return buildingGrid;
}

vector<BuildingGrid> BuildingGrid::getObjectSet(vector<vector<string>> param) {
	vector<BuildingGrid> buildingGridSet;
	vector<vector<string>>::iterator iter = param.begin();
	while(iter!=param.end()) {
		BuildingGrid buildingGrid = BuildingGrid::getObject(*iter++);
		buildingGridSet.push_back(buildingGrid);
	}
	return buildingGridSet;
}
