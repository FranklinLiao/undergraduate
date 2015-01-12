#include "stdafx.h"
#include "GridStrengthObject.h"


GridStrengthObject GridStrengthObject::getGridStrengthObject(vector<string> param) {
	GridStrengthObject gridStrengthObject = GridStrengthObject(param);
	return gridStrengthObject;
}



vector<GridStrengthObject> GridStrengthObject::getGridStrengthObjectSet(vector<vector<string>> param) {
	vector<GridStrengthObject> gridStrengthObjectSet;
	GridStrengthObject gridStrengthObject;
	vector<vector<string>>::iterator iter = param.begin();
	while(iter!=param.end()) {
		gridStrengthObject=GridStrengthObject(*iter++);
		gridStrengthObjectSet.push_back(gridStrengthObject);
	}
	return gridStrengthObjectSet;
}
