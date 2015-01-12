#include "stdafx.h"
#include "RTData.h"

RTData  RTData::getObject(vector<string> param) {
	RTData rtData(param);
	return rtData;
}

vector<RTData> RTData::getObjectSet(vector<vector<string>> param) {
	vector<RTData> rtDataSet;
	vector<vector<string>>::iterator iter = param.begin();
	while(iter!=param.end()) {
		RTData rtData = RTData::getObject(*iter++);
		rtDataSet.push_back(rtData);
	}
	return rtDataSet;
}
