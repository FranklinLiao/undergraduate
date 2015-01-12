#include "stdafx.h"
#include "BuildingBuildingPoint.h"

BuildingBuildingPoint BuildingBuildingPoint::getBuildingBuildingPoint(vector<string> param) {
	BuildingBuildingPoint buildingBuildingPoint = BuildingBuildingPoint(param);
	return buildingBuildingPoint;
}

vector<BuildingBuildingPoint> BuildingBuildingPoint::getBuildingBuildingPointSet(vector<vector<string>> param) {
	vector<BuildingBuildingPoint> buildingBuildingPointSet;
	BuildingBuildingPoint buildingBuildingPoint;
	vector<vector<string>>::iterator iter = param.begin();
	while(iter!=param.end()) {
		buildingBuildingPoint = BuildingBuildingPoint(*iter++);
		buildingBuildingPointSet.push_back(buildingBuildingPoint);
	}
	return buildingBuildingPointSet;
}