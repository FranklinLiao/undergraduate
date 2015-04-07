#include "stdafx.h"
#include "BuildingPoint.h"

BuildingPoint  BuildingPoint::getObject(vector<string> param) {
	BuildingPoint buildPoint(param);
	return buildPoint;
}

vector<BuildingPoint> BuildingPoint::getObjectSet(vector<vector<string>> param) {
	vector<BuildingPoint> buildingPointSet;
	vector<vector<string>>::iterator iter = param.begin();
	while(iter!=param.end()) {
		BuildingPoint buildingPoint = BuildingPoint::getObject(*iter++);
		buildingPointSet.push_back(buildingPoint);
	}
	return buildingPointSet;
}

BuildingPoint BuildingPoint::getMyself(int pId) {
	BuildingPoint buildingPoint;
	string tableName = "BuildingPoint";
	string key[1] = {"PId"};
	string keyValue[1] = {ChangeTypeTool::intToString(pId)};
	vector<BuildingPoint> buildingPointSet = BuildingPoint::getObjectSet(DBHelper::queryInfo(tableName,key,keyValue,sizeof(key)/sizeof(key[0])));
	vector<BuildingPoint>::iterator iter =  buildingPointSet.begin();
	buildingPoint = *iter;
	return buildingPoint;
}