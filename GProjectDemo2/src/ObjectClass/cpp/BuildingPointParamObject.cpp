#include "stdafx.h" 
#include "BuildingPointParamObject.h"
#include <vector>
#include <string>
#include <iterator>
using namespace std;

BuildingPointParamObject BuildingPointParamObject::getBuildingPointParamObject(vector<string> param) {
	BuildingPointParamObject buildingPointParamObject = BuildingPointParamObject(param);
	return buildingPointParamObject;
}

vector<BuildingPointParamObject> BuildingPointParamObject::getBuildingPointParamObjectSet(vector<vector<string>> param) {
	vector<BuildingPointParamObject> buildingPointParamObjectSet;
	BuildingPointParamObject buildingPointParamObject;
	vector<vector<string>>::iterator iter = param.begin();
	while(iter!=param.end()) {
		buildingPointParamObject = BuildingPointParamObject(*iter++);
		buildingPointParamObjectSet.push_back(buildingPointParamObject);
	}
	return buildingPointParamObjectSet;
}
