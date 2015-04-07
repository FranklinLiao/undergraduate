#ifndef _GRIDSTRENGTHOBJECT_H
#define _GRIDSTRENGTHOBEJCT_H
#include "stdafx.h"
#include "ChangeTypeTool.h"
#include <vector>
using namespace std;

class GridStrengthObject{
private:
	int gId;
	int aId;
	double freq;
	double fieldStrength;
public:
	GridStrengthObject() {};
	GridStrengthObject(vector<string> param) {
		vector<string>::iterator iter = param.begin();
		this->setGId(ChangeTypeTool::stringToInt(*iter++));
		this->setAId(ChangeTypeTool::stringToInt(*iter++));
		this->setFreq(ChangeTypeTool::stringToDouble(*iter++));
		this->setFieldStrenth(ChangeTypeTool::stringToDouble(*iter));
	}

	//其他函数
	static GridStrengthObject getGridStrengthObject(vector<string> param);
	static vector<GridStrengthObject> getGridStrengthObjectSet(vector<vector<string>> param);

	//set方法
	void setGId(int gId) {
		this->gId = gId;
	}

	void setAId(int aId) {
		this->aId = aId;
	}

	void setFreq(double freq) {
		this->freq =freq;
	}

	void setFieldStrenth(double fieldStrength) {
		this->fieldStrength = fieldStrength;
	}

	//get方法
	int getGId() {
		return this->gId;
	}

	int getAId() {
		return this->aId;
	}

	double getFreq() {
		return this->freq;
	}

	double getFieldStrength() {
		return this->fieldStrength;
	}
}; 

#endif