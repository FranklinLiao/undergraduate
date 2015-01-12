#ifndef _DATABASE_H
#define _DATABASE_H
#include "stdafx.h"
#include "DBConnPool.h"
#include "CreateSqlTool.h"
#include <iostream>
#include <iomanip> //for setw()
#include <string>
#include <vector>
#include <cstring>
using namespace std;

class DataBase{
public:
	 _bstr_t sqlString;
public:
	//删除数据
	void deletAllInfo(string TableName);
	//插入数据
	 void insertInfo(string insertString);
	//更新数据
	 void updateInfo(string updateString);
	 //得到数据的结果集
	 vector<vector<string>> getObjectInfo(string queryString);
	 //得到读取的建筑物折点的经纬度范围
	 vector<double> getLonLatBounds();
};

#endif