#ifndef _AREAGRID_H
#define _AREAGRID_H
#include "stdafx.h"
#include "ChangeTypeTool.h"
#include <vector>
#include <string>
using namespace std;

class AreaGrid{
private:
	int id;
	int gridId;

public:
	AreaGrid();
	AreaGrid(vector<string> param) {
		vector<string>::iterator iter = param.begin();
		this->setId(ChangeTypeTool::stringToInt(*iter++));
		this->setGridId(ChangeTypeTool::stringToInt(*iter));
	}

	/**
	* @brief	由参数创建一个网格小区
	* @fullName	AreaGrid::getObject
	* @param	param
	* @return	AreaGrid
	* @author	Franklin
	* @date		2014/06/12
	* @warning	
	*/
	static AreaGrid getObject(vector<string> param);

	/**
	* @brief	由参数创建一个网格集
	* @fullName	AreaGrid::getObjectSet
	* @param	param
	* @return	vector<AreaGrid>
	* @author	Franklin
	* @date		2014/06/12
	* @warning	
	*/
	static vector<AreaGrid> getObjectSet(vector<vector<string>> param);

	//set方法
	void setId(int id) {
		this->id = id;
	}

	void setGridId(int gridId) {
		this->gridId = gridId;
	}

	//get方法
	int getId() {
		return this->id;
	}

	int getGridId() {
		return this->gridId;
	}
};

#endif