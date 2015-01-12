#ifndef _BUILDINGAREA_H
#define _BUILDINGAREA_H
#include "stdafx.h"
#include "ChangeTypeTool.h"
#include <vector>
#include <string>
#include <iterator>
using namespace std;
class BuildingArea {
private:
	int bId;
	int bGridId;
public:
	BuildingArea() {};
	BuildingArea(vector<string> param) {
		vector<string>::iterator iter = param.begin();
		this->setBId(ChangeTypeTool::stringToInt(*iter++));
		this->setBGridId(ChangeTypeTool::stringToInt(*iter));
	}

	/**
	* @brief	由参数创建一个建筑物网格
	* @fullName	BuildingArea::getBuildingArea
	* @param	param
	* @return	BuildingArea
	* @author	Franklin
	* @date		2014/06/12
	* @warning	
	*/
	static BuildingArea getBuildingArea(vector<string> param);

	/**
	* @brief	由参数创建一个建筑物网格集
	* @fullName	BuildingArea::getBuildingAreaSet
	* @param	param
	* @return	vector<BuildingArea>
	* @author	Franklin
	* @date		2014/06/12
	* @warning	
	*/
	static vector<BuildingArea> getBuildingAreaSet(vector<vector<string>> param);

	//set 方法
	void setBId(int bId) {
		this->bId = bId;
	}

	void setBGridId(int bGridId) {
		this->bGridId = bGridId;
	}

	//get方法
	int getBId() {
		return this->bId;
	}

	int getBGridId() {
		return this->bGridId;
	}
};

#endif