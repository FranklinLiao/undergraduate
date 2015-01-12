#ifndef _BUILDINGGRID_H
#define _BUILDINGGRID_H
#include "stdafx.h"
#include "ChangeTypeTool.h"
#include <vector>
#include <string>
using namespace std;

class BuildingGrid{
private:
	int bId;
	int bGridId;

public:
	BuildingGrid();
	BuildingGrid(vector<string> param) {
		vector<string>::iterator iter = param.begin();
		this->setBId(ChangeTypeTool::stringToInt(*iter++));
		this->setBGridId(ChangeTypeTool::stringToInt(*iter));
	}

	/**
	* @brief	�ɲ����õ�һ������������ʵ��
	* @fullName	BuildingGrid::getObject
	* @param	param
	* @return	BuildingGrid
	* @author	Franklin
	* @date		2014/06/12
	* @warning	
	*/
	static BuildingGrid getObject(vector<string> param);

	/**
	* @brief	�ɲ����õ�һ������������ʵ����
	* @fullName	BuildingGrid::getObjectSet
	* @param	param
	* @return	vector<BuildingGrid>
	* @author	Franklin
	* @date		2014/06/12
	* @warning	
	*/
	static vector<BuildingGrid> getObjectSet(vector<vector<string>> param);

	//set����
	void setBId(int bId) {
		this->bId = bId;
	}

	void setBGridId(int bGridId) {
		this->bGridId = bGridId;
	}

	//get����
	int getBId() {
		return this->bId;
	}

	int getBGridId() {
		return this->bGridId;
	}
};
#endif