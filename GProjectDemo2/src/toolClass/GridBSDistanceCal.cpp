#include "stdafx.h"
#include "GridBSDistanceCal.h"

void GridBSDistanceCal::updateDistance() {
	//�õ�grid�ĸ���
	string tableName = "Grid";
	long rowCount = DBHelper::queryTableInfoNum(tableName);
	rowCount = 1000;
	int time = rowCount / 100;
	int left = rowCount % 100;
	int index = 0;
	while(index <time) {
		string sqlString = CreateSqlTool::createUpdateDistance(100,index*100+1);
		DataBase db;
		db.updateInfo(sqlString);
		index++;
	}
	//left����
	if(left!=0) {
		string sqlString = CreateSqlTool::createUpdateDistance(left,index*100+1);
		DataBase db;
		db.updateInfo(sqlString);
	}
}