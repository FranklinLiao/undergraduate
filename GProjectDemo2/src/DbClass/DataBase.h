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
	void clearOneCol(string TableName,string col);
	//插入数据
	 void insertInfo(string insertString);
	//更新数据
	 void updateInfo(string updateString);
	 //得到数据的结果集
	 vector<vector<string>> getObjectInfo(string queryString);
	 //得到读取的建筑物折点的经纬度范围
	 vector<double> getLonLatBounds();
	 vector<double> getGridLonLatBounds();
	 //覆盖优化中弱覆盖的方法
	 long MaxId(string maxidString);
	 long MinId(string minidString);
	 vector<int> getLayOptimizeAreaIdFromDb(string sqlInfo);
	 void setWeakLay();//将没有收到场强的网格判定为弱覆盖
	 vector<float> getCellInfo(int cellId);

	 //干扰优化的方法
	 vector<vector<string>> getUserFromDb(string tableName,int areaId,int userCnt);
	 vector<int> getAdjAreaIdFromDb(string tableName,int areaId);

	 //SFR优化
	 int getAreaCnt();
	 int getGridCnt();
	 double getAdjAreaGridStrength(int aid,int gridId);

	 //ANR优化
	 double getServerRSRPFromDB(int aid,int gid);
	 double getMaxGridXY(int flag);
	 vector<vector<string>> getUserANRFromDb(string tableName,int areaId,int userCnt);
	 int getGidFromXY(double x,double y);
	 vector<vector<string>> getGridAllRsrpInfo(int gridId);
};

#endif