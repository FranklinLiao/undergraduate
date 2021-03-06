#ifndef _GRID_H
#define _GRID_H
#include "stdafx.h"
#include "ChangeTypeTool.h"
#include "Building.h"
#include "BuildingGrid.h"
#include "DBHelper.h"
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

class Grid {
public:
	int gId;
	double gLongitude;
	double gLatitude;
	int gAId;
	double gRealRSRP;
	float gX;
	float gY;
	int gColor;
public:
	//构造函数
	Grid(){};
	Grid(vector<string> param) {
		vector<string>::iterator iter = param.begin();
		while(iter!=param.end()) {
			this->setGId(ChangeTypeTool::stringToInt(*iter++));
			this->setGLongtitude(ChangeTypeTool::stringToDouble(*iter++));
			this->setGLatitude(ChangeTypeTool::stringToDouble(*iter++));
			
			this->setGAId(ChangeTypeTool::stringToInt(*iter++));
			this->setGRealRSRP(ChangeTypeTool::stringToDouble(*iter++));
		
			this->setGX(ChangeTypeTool::stringToDouble(*iter++));
			this->setGY(ChangeTypeTool::stringToDouble(*iter++));
		
			this->setGColor(ChangeTypeTool::stringToInt(*iter));
		}
	}
	~Grid() {}
	//获得对象
	static Grid getObject(vector<string> param);
	static vector<Grid> getObjectSet(vector<vector<string>> param);
	
	//得到和网格相交的建筑物的信息
	static vector<Building>  getGridBuilding(int bGridId);
	
	//得到自己
	static Grid getMyself(int gId);
	static Grid getMyselfByXY(double gX,double gY);
	//得到全部
	static vector<Grid> getAllGrid();
	//set方法
	void setGId(int gId) {
		this->gId = gId;
	}

	void setGLongtitude(double gLongitude) {
		this->gLongitude = gLongitude;
	}

	void setGLatitude(double gLatitude) {
		this->gLatitude = gLatitude;
	}

	

	void setGAId(int gAId) {
		this->gAId=gAId;
	}

	void setGRealRSRP(double gRealRSRP) {
		this->gRealRSRP = gRealRSRP;
	}
	

	
	void setGX(float gX) {
		this->gX = gX;
	}

	void setGY(float gY) {
		this->gY = gY;
	}



	void setGColor(int gColor) {
		this->gColor = gColor;
	}
	//get方法
	int getGId() {
		return this->gId;
	}
	double getGLongtitude() {
		return this->gLongitude;
	}

	double getGLatitude() {
		return this->gLatitude;
	}

	

	int getGAid() {
		return this->gAId;
	}

	double getGRealRSRP() {
		return this->gRealRSRP;
	}

	
	
	float getGX() {
		return this->gX;
	}

	float getGY() {
		return this->gY;
	}
	
	

	int getGColor() {
		return this->gColor;
	}
	/**
	* @brief	使用时提供网格ID，从数据库中提取出所有关于Grid的信息
	* @fullName	Grid::GetThisGirdRecord
	* @param	GId
	* @return	void
	* @author	贾琦
	* @date		2014/04/22
	* @warning  请注意此处函数重载
	*/	
	//void GetThisGirdRecord(int GId);

	/**
	* @brief	使用时提供网格的横纵XY坐标，从数据库中提取出所有关于Grid的信息
	* @fullName	Grid::GetThisGirdRecord
	* @param	GX
	* @param	GY
	* @return	void
	* @author	贾琦
	* @date		2014/04/22
	* @warning	此处为函数的补充说明
	*/
	//void GetThisGirdRecord(double GX, double GY);
};

#endif