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
	double gHeight;
	int gAId;
	double gRealSNR;
	double gRTSNR;
	float gX;
	float gY;
	float gZ;
	int gColor;
public:
	//���캯��
	Grid(){};
	Grid(vector<string> param) {
		vector<string>::iterator iter = param.begin();
		while(iter!=param.end()) {
			this->setGId(ChangeTypeTool::stringToInt(*iter++));
			this->setGLongtitude(ChangeTypeTool::stringToDouble(*iter++));
			this->setGLatitude(ChangeTypeTool::stringToDouble(*iter++));
			this->setGHeight(ChangeTypeTool::stringToDouble(*iter++));
			this->setGAId(ChangeTypeTool::stringToInt(*iter++));
			this->setGRealSNR(ChangeTypeTool::stringToDouble(*iter++));
			this->setGRTSNR(ChangeTypeTool::stringToDouble(*iter++));
			this->setGX(ChangeTypeTool::stringToDouble(*iter++));
			this->setGY(ChangeTypeTool::stringToDouble(*iter++));
			this->setGZ(ChangeTypeTool::stringToDouble(*iter++));
			this->setGColor(ChangeTypeTool::stringToInt(*iter));
		}
	}
	~Grid() {}
	//��ö���
	static Grid getObject(vector<string> param);
	static vector<Grid> getObjectSet(vector<vector<string>> param);
	
	//�õ��������ཻ�Ľ��������Ϣ
	static vector<Building>  getGridBuilding(int bGridId);
	
	//�õ��Լ�
	static Grid getMyself(int gId);
	static Grid getMyselfByXY(double gX,double gY);
	//�õ�ȫ��
	static vector<Grid> getAllGrid();
	//set����
	void setGId(int gId) {
		this->gId = gId;
	}

	void setGLongtitude(double gLongitude) {
		this->gLongitude = gLongitude;
	}

	void setGLatitude(double gLatitude) {
		this->gLatitude = gLatitude;
	}

	void setGHeight(double gHeight) {
		this->gHeight=gHeight;
	}

	void setGAId(int gAId) {
		this->gAId=gAId;
	}

	void setGRealSNR(double gRealSNR) {
		this->gRealSNR = gRealSNR;
	}
	
	void setGRTSNR(double gRTSNR) {
		this->gRTSNR=gRTSNR;
	}
	
	void setGX(float gX) {
		this->gX = gX;
	}

	void setGY(float gY) {
		this->gY = gY;
	}

	void setGZ(float gZ) {
		this->gZ = gZ;
	}

	void setGColor(int gColor) {
		this->gColor = gColor;
	}
	//get����
	int getGId() {
		return this->gId;
	}
	double getGLongtitude() {
		return this->gLongitude;
	}

	double getGLatitude() {
		return this->gLatitude;
	}

	int getGHeight() {
		return this->gHeight;
	}

	int getGAid() {
		return this->gAId;
	}

	double getGRealSNR() {
		return this->gRealSNR;
	}

	double getGRTSNR() {
		return this->gRTSNR;
	}
	
	float getGX() {
		return this->gX;
	}

	float getGY() {
		return this->gY;
	}
	
	float getGZ() {
		return this->gZ;
	}

	int getGColor() {
		return this->gColor;
	}
	/**
	* @brief	ʹ��ʱ�ṩ����ID�������ݿ�����ȡ�����й���Grid����Ϣ
	* @fullName	Grid::GetThisGirdRecord
	* @param	GId
	* @return	void
	* @author	����
	* @date		2014/04/22
	* @warning  ��ע��˴���������
	*/	
	//void GetThisGirdRecord(int GId);

	/**
	* @brief	ʹ��ʱ�ṩ����ĺ���XY���꣬�����ݿ�����ȡ�����й���Grid����Ϣ
	* @fullName	Grid::GetThisGirdRecord
	* @param	GX
	* @param	GY
	* @return	void
	* @author	����
	* @date		2014/04/22
	* @warning	�˴�Ϊ�����Ĳ���˵��
	*/
	//void GetThisGirdRecord(double GX, double GY);
};

#endif