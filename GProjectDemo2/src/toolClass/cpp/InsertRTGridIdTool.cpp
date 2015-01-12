#include "stdafx.h"
#include "InsertRTGridIdTool.h"

void InsertRTGridIdTool::insertRTGridIdTool() {
	int count = DBHelper::queryTableInfoNum("RTData");
	double x=0,y=0;
	for(int id = 1;id <= count;id++) {
		//遍历获得每条rtdata记录
		//vector<double> xy = DBHelper::queryGridXY(id);
		vector<double> xy = DBHelper::queryRTDataXY(id);
		x = xy.at(0);
		y = xy.at(1);
		string tableName = "Grid";
		int gridId = DBHelper::getRTDataId(tableName,x,y);
		tableName = "RTData";
		string key[]={"RGridId"};
		string keyValue[]={ChangeTypeTool::intToString(gridId)};
		string whereKey[]={"RId"};
		string whereValue[]= {ChangeTypeTool::intToString(id)};
		DBHelper::updateInfo(tableName,key,keyValue,sizeof(key)/sizeof(key[0]),whereKey,whereValue,sizeof(whereKey)/sizeof(whereKey[0]));
	}
}