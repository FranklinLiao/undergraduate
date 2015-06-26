#include "stdafx.h"
#include "GridBSDistanceCal.h"
#define COUNTSIZE 100
void GridBSDistanceCal::updateDistance() {
	//得到grid的个数
	string tableName = "GridFieldStrenth";
	long rowCount = DBHelper::queryTableInfoNum(tableName);
	//rowCount = 1000;
	int time = rowCount / (COUNTSIZE);
	int left = rowCount % (COUNTSIZE);
	int index = 0;
	while(index <time) {
		string sqlString = CreateSqlTool::createUpdateDistance((COUNTSIZE),(index*(COUNTSIZE))+1);
		DataBase db;
		db.updateInfo(sqlString);
		index++;
	}
	//left插入
	if(left!=0) {
		string sqlString = CreateSqlTool::createUpdateDistance(left,(index*(COUNTSIZE))+1);
		DataBase db;
		db.updateInfo(sqlString);
	}
}