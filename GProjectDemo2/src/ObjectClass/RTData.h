#ifndef _RTDATA_H
#define _RTDATA_H
#include "stdafx.h"
#include "ChangeTypeTool.h"
#include <vector>
#include <string>
#include <iterator>
using namespace std;

class RTData{
private:
	int id;
	double longitude;
	double latitude;
	int areaId;
	int gridId;
	double voltage;
	double snr;

public:
	RTData();
	RTData(vector<string> param) {
		vector<string>::iterator iter = param.begin();
		this->setId(ChangeTypeTool::stringToInt(*iter++));
		this->setLongitude(ChangeTypeTool::stringToDouble(*iter++));
		this->setLatitude(ChangeTypeTool::stringToDouble(*iter));
	}

	//其他函数
	static RTData getObject(vector<string> param);
	static vector<RTData> RTData::getObjectSet(vector<vector<string>> param);
	//set方法
	void setId(int id) {
		this->id=id;
	}

	void setLongitude(double longitude) {
		this->longitude=longitude;
	}

	void setLatitude(double latitude) {
		this->latitude = latitude;
	}

	void setAreaId(int areaId) {
		this->areaId = areaId;
	}
	
	void setGridId(int gridId) {
		this->gridId = gridId;
	}
	void setVoltage(double voltage) {
		this->voltage=voltage;
	}

	void setSnr(double snr) {
		this->snr = snr;
	}

	//get方法
	int getId() {
		return id;
	}

	double getLongitude() {
		return this->longitude;
	}

	double getLatitude() {
		return this->latitude;
	}

	int  getAreaId() {
		return this->areaId;
	}

	int getGridId() {
		return this->gridId;
	}
	double getVoltage() {
		return this->voltage;
	}

	double getSnr() {
		return snr;
	}
};
#endif