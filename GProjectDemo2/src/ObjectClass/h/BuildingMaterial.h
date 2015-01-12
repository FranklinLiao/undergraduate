#ifndef _BUILDINGMATERIAL_H
#define _BUILDINGMATERIAL_H
#include "stdafx.h"
#include "ChangeTypeTool.h"
#include <vector>
using namespace std;

class BuildingMaterial {
private:
	int id;
	double dielectricConstant;
	double conductivity;

public:
	//构造方法
	BuildingMaterial(){};
	BuildingMaterial(vector<string> param) {
		vector<string>::iterator iter = param.begin();
		this->setId(ChangeTypeTool::stringToInt(*iter++));
		this->setDielectricConstant(ChangeTypeTool::stringToDouble(*iter++));
		this->setConductivity(ChangeTypeTool::stringToDouble(*iter));
	}
		
	/**
	* @brief	由参数得到一个建筑物材质实例
	* @fullName	BuildingMaterial::getObject
	* @param	param
	* @return	BuildingMaterial
	* @author	Franklin
	* @date		2014/06/12
	* @warning	
	*/
	static BuildingMaterial getObject(vector<string> param);

	/**
	* @brief	由参数得到一个建筑物材质实例集
	* @fullName	BuildingMaterial::getObjectSet
	* @param	param
	* @return	vector<BuildingMaterial>
	* @author	Franklin
	* @date		2014/06/12
	* @warning	
	*/
	static vector<BuildingMaterial> BuildingMaterial::getObjectSet(vector<vector<string>> param);
	
	//set方法
	void setId(int id) {
		this->id = id;
	}

	void setDielectricConstant(double dielectricConstant) {
		this->dielectricConstant = dielectricConstant;
	}

	void setConductivity(double conductivity) {
		this->conductivity = conductivity;
	}

	//get方法
	int getid() {
		return this->id;
	}
	
	double getDielectricConstant() {
		return this->dielectricConstant;
	}

	double getConductivity() {
		return this->conductivity;
	}
};

#endif