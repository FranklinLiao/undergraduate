#ifndef _AREA_H
#define _AREA_H
#include "stdafx.h"
#include "ChangeTypeTool.h"
#include "CreateSqlTool.h"
#include "DBHelper.h"
#include "AreaGrid.h"
#include <vector>
using namespace std;


class Area {
public:
	int AId;
	double ASendPower;
	double ALongtitude;
	double ALatitude;
	double AHeight;  
	double AFreq;
	double AAspectAngle;
	double ADeclineAngle;
	double ALength;
	int AType;
	double APower;
	int ABaseStationAttr;
	float aX;
	float aY;
	float aZ;
public:
	//构造函数
	Area() {

	}
	
	Area(vector<string> param){
		vector<string>::iterator iter = param.begin();
		this->setAId(ChangeTypeTool::stringToInt(*iter++));
		this->setASendPower(ChangeTypeTool::stringToDouble(*iter++));
		this->setALongtitude(ChangeTypeTool::stringToDouble(*iter++));
		this->setALatitude(ChangeTypeTool::stringToDouble(*iter++));
		this->setAHeight(ChangeTypeTool::stringToDouble(*iter++));
		this->setAFreq(ChangeTypeTool::stringToDouble(*iter++));
		this->setAAspectAngle(ChangeTypeTool::stringToDouble(*iter++));
		this->setADeclineAngle(ChangeTypeTool::stringToDouble(*iter++));
		this->setALength(ChangeTypeTool::stringToDouble(*iter++));
		this->setAType(ChangeTypeTool::stringToInt(*iter++));
		this->setAPower(ChangeTypeTool::stringToDouble(*iter++));
		this->setABaseStationAttr(ChangeTypeTool::stringToInt(*iter++));
		this->setAX(ChangeTypeTool::stringToDouble(*iter++));
		this->setAY(ChangeTypeTool::stringToDouble(*iter++));
		this->setAZ(ChangeTypeTool::stringToDouble(*iter));
	}
	
	Area(vector<string> param, int flag){
		vector<string>::iterator iter = param.begin();
		this->setAId(ChangeTypeTool::stringToInt(*iter++));
		this->setASendPower(ChangeTypeTool::stringToDouble(*iter++));
		this->setALongtitude(ChangeTypeTool::stringToDouble(*iter++));
		this->setALatitude(ChangeTypeTool::stringToDouble(*iter++));
		this->setAHeight(ChangeTypeTool::stringToDouble(*iter++));
		this->setAAspectAngle(ChangeTypeTool::stringToDouble(*iter++));
		this->setADeclineAngle(ChangeTypeTool::stringToDouble(*iter++));
		this->setALength(ChangeTypeTool::stringToDouble(*iter++));
		this->setAPower(ChangeTypeTool::stringToDouble(*iter++));
		this->setABaseStationAttr(ChangeTypeTool::stringToInt(*iter++));
		this->setAX(ChangeTypeTool::stringToDouble(*iter++));
		this->setAY(ChangeTypeTool::stringToDouble(*iter++));
		this->setAZ(ChangeTypeTool::stringToDouble(*iter));
	}
	
	/**
	* @brief	得到Area的对象集
	* @fullName	Area::getObjectSet
	* @param	param
	* @return	vector<Area>
	* @author	Franklin
	* @date		2014/06/12
	* @warning	
	*/
	static vector<Area> getObjectSet(vector<vector<string>> param);

	/**
	* @brief	得到编号为aId的小区中的网格数
	* @fullName	Area::getAreaGridCount
	* @param	aId
	* @return	int
	* @author	Franklin
	* @date		2014/06/12
	* @warning	
	*/
	static int getAreaGridCount(int aId);
	
	/**
	* @brief	得到编号为aId的小区
	* @fullName	Area::getMyself
	* @param	aId
	* @return	Area
	* @author	Franklin
	* @date		2014/06/12
	* @warning	
	*/
	static Area getMyself(int aId);

	//set方法
	void setAId(int AId) {
		this->AId = AId;
	}
	void setASendPower(double ASendPower) {
		this->ASendPower=ASendPower;
	}

	void setALongtitude(double ALongtitude) {
		this->ALongtitude=ALongtitude;
	}

	void setALatitude(double ALatitude) {
		this->ALatitude = ALatitude;
	}

	void setAHeight(double AHeight) {
		this->AHeight = AHeight;
	}

	void setAFreq(double AFreq) {
		this->AFreq = AFreq;
	}

	void setAAspectAngle(double AAspectAngle) {
		this->AAspectAngle=AAspectAngle;
	}

	void setADeclineAngle(double ADeclineAngle) {
		this->ADeclineAngle=ADeclineAngle;
	}

	void setALength(double ALength) {
		this->ALength=ALength;
	}

	void setAType(int AType) {
		this->AType=AType;
	}

	void setAPower(double transmitPower) {
		this->APower = APower;
	}

	void setABaseStationAttr(int ABaseStationAttr) {
		this->ABaseStationAttr=ABaseStationAttr;
	}

	void setAX(float aX) {
		this->aX = aX;
	}

	void setAY(float aY) {
		this->aY = aY;
	}

	void setAZ(float aZ) {
		this->aZ = aZ;
	}
	//get方法
	int getAId() {
		return this->AId;
	}

	double getASendPower() {
		return this->ASendPower;
	}

	double getALongtitude() {
		return ALongtitude;
	}

	double getALatitude() {
		return this->ALatitude;
	}
	
	double getAHeight() {
		return this->AHeight;
	}
	
	double getAFreq() {
		return this->AFreq;
	}

	double getAAspectAngle() {
		return this->AAspectAngle;
	}

	double getADeclineAngle() {
		return this->ADeclineAngle;
	}

	double getALength() {
		return this->ALength;
	}

	int getAType() {
		return this->AType;
	}

	double getAPower() {
		return this->APower;
	}

	int getABaseStationAttr() {
		return this->ABaseStationAttr;
	}

	float getAX() {
		return this->aX;
	}

	float getAY() {
		return this->aY;
	}

	float getAZ() {
		return this->aZ;
	}
};

#endif
