#ifndef _BUILDING_H
#define _BUILDING_H
#include "stdafx.h"
#include "BuildingPoint.h"
#include "BuildingBuildingPoint.h"
#include "ChangeTypeTool.h"
#include "DBHelper.h"
#include <vector>
#include <string>
using namespace std;

class Building{
private:
	int id;
	double longitude;
	double latitude;
	double height;

public:
	//构造函数
	Building(){};
	Building(vector<string> param) {
		vector<string>::iterator iter = param.begin();
		this->setId(ChangeTypeTool::stringToInt(*iter++));
		this->setLongitude(ChangeTypeTool::stringToDouble(*iter++));
		this->setLatitude(ChangeTypeTool::stringToDouble(*iter++));
		this->setHeight(ChangeTypeTool::stringToDouble(*iter));
	}
	~Building(){};
	
	/**
	* @brief	由参数创建一个建筑物
	* @fullName	Building::getObject
	* @param	param
	* @return	Building
	* @author	Franklin
	* @date		2014/06/12
	* @warning	
	*/
	static Building getObject(vector<string> param);

	/**
	* @brief	由参数创建一个建筑物集
	* @fullName	Building::getObjectSet
	* @param	param
	* @return	vector<Building>
	* @author	Franklin
	* @date		2014/06/12
	* @warning	
	*/
	static vector<Building> Building::getObjectSet(vector<vector<string>> param);
	
	/**
	* @brief	得到编号为bId的建筑物
	* @fullName	Building::getMyself
	* @param	bId
	* @return	Building
	* @author	Franklin
	* @date		2014/06/12
	* @warning	
	*/
	static Building getMyself(int bId);

	/**
	* @brief	得到编号为bId的建筑物所包含的的建筑物折点
	* @fullName	Building::getBuildingBuildingPoint
	* @param	bId
	* @return	vector<BuildingPoint>
	* @author	Franklin
	* @date		2014/06/12
	* @warning	
	*/
	static vector<BuildingPoint> getBuildingBuildingPoint(int bId);

	//set方法
	void setId(int id) {
		this->id =id;
	}
	
	void setLongitude(double longitude) {
		this->longitude=longitude;
	}
	
	void setLatitude(double latitude) {
		this->latitude = latitude;
	}
	
	void setHeight(double height) {
		this->height = height;
	}
	// get方法

	int getId() {
		return id;
	}
	
	double  getLongitude() {
		return this->longitude;
	}
	
	double getLatitude() {
		return this->latitude;
	}

	double getHeight() {
		return this->height;
	}
};

#endif
