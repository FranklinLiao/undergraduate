#ifndef _BUILDINGBUILDINGPOINT_H
#define _BUILDINGBUILDINGPOINT_H
#include "stdafx.h"
#include "ChangeTypeTool.h"
#include <vector>
#include <string>
#include <iterator>
using namespace std;

class BuildingBuildingPoint{
private:
	int bId;
	int bPointId;
public:
	BuildingBuildingPoint() {};
	BuildingBuildingPoint(vector<string> param) {
		vector<string>::iterator iter = param.begin();
		this->setBId(ChangeTypeTool::stringToInt(*iter++));
		this->setBPointId(ChangeTypeTool::stringToInt(*iter));
	}

	/**
	* @brief	由参数创建一个建筑物建筑物折点实例
	* @fullName	BuildingBuildingPoint::getBuildingBuildingPoint
	* @param	param
	* @return	BuildingBuildingPoint
	* @author	Franklin
	* @date		2014/06/12
	* @warning	
	*/
	static BuildingBuildingPoint getBuildingBuildingPoint(vector<string> param);

	/**
	* @brief	由参数创建一个建筑物建筑物折点实例集
	* @fullName	BuildingBuildingPoint::getBuildingBuildingPointSet
	* @param	param
	* @return	vector<BuildingBuildingPoint>
	* @author	Franklin
	* @date		2014/06/12
	* @warning	
	*/
	static vector<BuildingBuildingPoint> getBuildingBuildingPointSet(vector<vector<string>> param);
	
	//set方法
	void setBId(int bId) {
		this->bId = bId;
	}

	void setBPointId(int bPointId) {
		this->bPointId = bPointId;
	}

	//get方法
	int getBId() {
		return this->bId;
	}

	int getBPointId() {
		return this->bPointId;
	}
};

#endif

