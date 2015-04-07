#ifndef _BUILDINGPOINT_H
#define _BUILDINGPOINT_H
#include "stdafx.h"
#include "ChangeTypeTool.h"
#include "DBHelper.h"
#include <vector>
#include <string>
using namespace std;

class BuildingPoint {
private:
	int id;
	double longitude;
	double latitude;
	double height;
	int gridId;
	int buildingId;
	double px;
	double py;
	double pz;
public:
	//���캯��
	BuildingPoint(){};
	BuildingPoint(vector<string> param) {
		vector<string>::iterator iter = param.begin();
		this->setId(ChangeTypeTool::stringToInt(*iter++));
		this->setLongtitude(ChangeTypeTool::stringToDouble(*iter++));
		this->setLatitude(ChangeTypeTool::stringToDouble(*iter++));
		this->setHeight(ChangeTypeTool::stringToDouble(*iter++));
		this->setGridId(ChangeTypeTool::stringToInt(*iter++));
		this->setBuildingId(ChangeTypeTool::stringToInt(*iter++));
		this->setPx(ChangeTypeTool::stringToDouble(*iter++));
		this->setPy(ChangeTypeTool::stringToDouble(*iter++));
		this->setPz(ChangeTypeTool::stringToDouble(*iter));
	}

	/**
	* @brief	�ɲ����õ�һ���������۵�ʵ��
	* @fullName	BuildingPoint::getObject
	* @param	param
	* @return	BuildingPoint
	* @author	Franklin
	* @date		2014/06/12
	* @warning	
	*/
	static BuildingPoint  getObject(vector<string> param);

	/**
	* @brief	�ɲ����õ�һ���������۵�ʵ����
	* @fullName	BuildingPoint::getObjectSet
	* @param	param
	* @return	vector<BuildingPoint>
	* @author	Franklin
	* @date		2014/06/12
	* @warning	
	*/
	static vector<BuildingPoint> getObjectSet(vector<vector<string>> param);
	
	/**
	* @brief	�ô���ΪpId�Ľ������۵�
	* @fullName	BuildingPoint::getMyself
	* @param	pId
	* @return	BuildingPoint
	* @author	Franklin
	* @date		2014/06/12
	* @warning	
	*/
	static BuildingPoint getMyself(int pId);

	//set����
	void setId(int id) {
		this->id = id;
	}

	void setLongtitude(double longitude) {
		this->longitude = longitude;
	}

	void setLatitude(double latitude) {
		this->latitude = latitude;
	}

	void setHeight(double height) {
		this->height = height;
	}
	
	void setGridId(int gridId) {
		this->gridId = gridId;
	}

	void setBuildingId(int buildingId) {
		this->buildingId = buildingId;
	}

	void setPx(double px) {
		this->px=px;
	}

	void setPy(double py) {
		this->py=py;
	}

	void setPz(double pz) {
		this->pz = pz;
	}
	//get����
	int getId() {
		return this->id;
	}

	double getLongtitude() {
		return this->longitude;
	}

	double getLatitude() {
		return this->latitude;
	}

	double getHeight() {
		return this->height;
	}

	int getGridId() {
		return this->gridId;
	}
	
	int getBuildingId() {
		return this->buildingId;
	}

	double getPx() {
		return this->px;
	}

	double getPy() {
		return this->py;
	}

	double getPz() {
		return this->pz;
	}
};

#endif
