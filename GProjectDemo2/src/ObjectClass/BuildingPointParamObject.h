#ifndef _BUILDINGPOINTPARAMOBJECT_H
#define _BUILDINGPOINTPARAMOBJECT_H
#include "stdafx.h"
#include "ChangeTypeTool.h"
#include <vector>
#include <iterator>
#include <string>
using namespace std;

class BuildingPointParamObject{
private:
	int bId;
	int bStartPointId;
	int bEndPointId;
	double bParam1;
	double bParam2;
	double bParam3;
public:
	BuildingPointParamObject() {};
	BuildingPointParamObject(vector<string> param) {
		vector<string>::iterator iter = param.begin();
		this->setBId(ChangeTypeTool::stringToInt(*iter++));
		this->setBStartPointId(ChangeTypeTool::stringToInt(*iter++));
		this->setBEndPointId(ChangeTypeTool::stringToInt(*iter++));
		this->setBParam1(ChangeTypeTool::stringToDouble(*iter++));
		this->setBParam2(ChangeTypeTool::stringToDouble(*iter++));
		this->setBParam3(ChangeTypeTool::stringToDouble(*iter));
	}
	
	/**
	* @brief	由参数得到一个建筑物折点参数实例
	* @fullName	BuildingPointParamObject::getBuildingPointParamObject
	* @param	param
	* @return	BuildingPointParamObject
	* @author	Franklin
	* @date		2014/06/12
	* @warning	
	*/
	static BuildingPointParamObject getBuildingPointParamObject(vector<string> param);
	
	/**
	* @brief	由参数得到一个建筑物折点实例集
	* @fullName	BuildingPointParamObject::getBuildingPointParamObjectSet
	* @param	param
	* @return	vector<BuildingPointParamObject>
	* @author	Franklin
	* @date		2014/06/12
	* @warning	
	*/
	static vector<BuildingPointParamObject> getBuildingPointParamObjectSet(vector<vector<string>> param);
	
	//set方法
	void setBId(int bId) {
		this->bId = bId;
	}

	void setBStartPointId(int bStartPointId) {
		this->bStartPointId=bStartPointId;
	}

	void setBEndPointId(int bEndPointId) {
		this->bEndPointId = bEndPointId;
	}

	void setBParam1(double bParam1) {
		this->bParam1 = bParam1;
	}

	void setBParam2(double bParam2) {
		this->bParam2 = bParam2;
	}

	void setBParam3(double bParam3) {
		this->bParam3 = bParam3;
	}

	//get方法
	int getBId() {
		return this->bId;
	}

	int getBStartPointId() {
		return this->bStartPointId;
	}

	int getBEndPointId() {
		return this->bEndPointId;
	}

	double getBParam1() {
		return this->bParam1;
	}

	double getBParam2() {
		return this->bParam2;
	}

	double getBParam3() {
		return this->bParam3;
	}
};

#endif