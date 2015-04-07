#include "stdafx.h"
#include "Area.h"
/*
Area Area::getPartObject(vector<string> param) {
	Area area;
	vector<string>::iterator iter = param.begin();
	area.setAId(ChangeTypeTool::stringToInt(*iter++));
	area.setALongtitude(ChangeTypeTool::stringToDouble(*iter++));
	area.setALatitude(ChangeTypeTool::stringToDouble(*iter++));
	return area;
}

Area Area::getFullOject(vector<string> param) {
	Area area = Area(param);
	return area;
}
*/
//
vector<Area> Area::getObjectSet(vector<vector<string>> param) {
	vector<Area> AreaSet;
	vector<vector<string>>::iterator iter = param.begin();
	while(iter!=param.end()) {
		Area area = Area(*iter++);
		AreaSet.push_back(area); 
	}
	return AreaSet;
}


int Area::getAreaGridCount(int aId) {
	int count=0;
	string tableName = "AreaGridId"; 
	string key[1] = {"AId"};
	string keyValue[1] = {ChangeTypeTool::intToString(aId)};
	vector<AreaGrid> areaGridSet = AreaGrid::getObjectSet(DBHelper::queryInfo(tableName,key,keyValue,sizeof(key)/sizeof(key[0])));
	count = areaGridSet.size();
	return count;
}

Area Area::getMyself(int aId) {
	Area area;
	string tableName = "Area"; 
	string key[1] = {"AId"};
	string keyValue[1] = {ChangeTypeTool::intToString(aId)};
	vector<Area> areaSet = Area::getObjectSet(DBHelper::queryInfo(tableName,key,keyValue,sizeof(key)/sizeof(key[0])));
	vector<Area>::iterator iter =  areaSet.begin();
	//考虑到只有一个所以不循环迭代
	area = *iter;
	return area;
}