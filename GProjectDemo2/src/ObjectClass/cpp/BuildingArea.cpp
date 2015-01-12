#include "stdafx.h"
#include "BuildingArea.h"

BuildingArea BuildingArea::getBuildingArea(vector<string> param) {
	BuildingArea buildingArea = BuildingArea(param);
	return buildingArea;
}

vector<BuildingArea> BuildingArea::getBuildingAreaSet(vector<vector<string>> param) {
	vector<BuildingArea> buildingAreaSet;
	BuildingArea buildingArea;
	vector<vector<string>>::iterator iter = param.begin();
	while(iter!=param.end()) {
		buildingArea = BuildingArea(*iter++);
		buildingAreaSet.push_back(buildingArea);
	}
	return buildingAreaSet;
}
