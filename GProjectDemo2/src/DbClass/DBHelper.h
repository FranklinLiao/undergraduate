#ifndef _DBHELPER_H
#define _DBHELPER_H
#include "stdafx.h"
//#include "Grid.h"
#include "CreateSqlTool.h"
#include "DataBase.h"
#include <vector>
#include <string>
using namespace std;

class DBHelper{
public:
	static void deleteAllTable();
	static void deleteData(string tableName);
	static void clearOneCol(string tableName,string col);
public:
	//static void insertBuildingInfoToDB(string tableName,int bId,double longitude,double latitude);
	//static void insertBuildingPointToDB(string tableName,int pId,double longitude,double latitude,int BId);
	//static void insertBuildingPointLinkToDB(string tableName,int bId,int pId);
	//static void insertGridToDB(string tableName,int gId,double longitude,double latitude);
	//static void insertGridBuildingIntersectionToDB(string tableName,int id,int bId,int gId);
	static void updateGridBuildingPointIntersectionToDB(string tableName,int PId,int PGridId);
	//static void insertBaseStationToDB(string tableName,int AId,double ALongitude,double ALatitude,double AHeight,double AAspectAngle,double ADeclineAngle,double ALength,int AType,int ABaseStationAttr);
	//static void insertBaseStationToDB(string tableName,int AId,double ALongitude,double ALatitude,double AHeight,int ABaseStationAttr,double coverTypeValue);
	//static void insertBSGridLinkToDB(string tableName,int Id,int AId,int AGridId);
public:
	

	//调整后  三个基本操作
	static void insertInfo(string tableName,string* key,string* value,int count);
	static void updateInfo(string tableName,string* key,string* value,int count,string* whereKey,string* whereValue,int whereCount);
	static vector<vector<string>>  queryInfo(string tableName,string* whereKey,string* whereValue,int whereCount);
	//传入sql语句直接调用
	static void insertStringInfo(string SqlString);
	static void updateStringInfo(string SqlString);
	static vector<vector<string>> queryStringInfo(string SqlString);
	//对某一或几个参数的提取
	static double getLargestStrength();
	//特殊的选择语句
	static vector<vector<string>> queryGridInfoFromDB();
	static vector<vector<string>> queryAreaInfoFromDB();
	static int queryTableInfoNum(string tableName);
	static vector<int> queryGridMaxXY();
	static vector<double> queryGridXY(int id);
	static vector<double> queryRTDataXY(int id);
	static int getRTDataId(string tableName,double x,double y);

//覆盖优化
public:
	static vector<int> getLayOptimizeAreaId(string colum);
	static void setWeakLay();//将没有收到场强的网格判定为弱覆盖
	static vector<float> getCellInfo(int cellId);
	static void resetGridColor();
//干扰优化
public:
	static vector<vector<string>> getUser(int areaId,int userCnt);
	static vector<int> getAdjAreaId(string tableName,int areaId);
	static double getAdjAreaGridStrength(int aid,int gridId);

//ANR
public:
	static double getServerRSRP(int aid,int gid);
	static double getGridMaxXY(int flag);
	static vector<vector<string>> getUserANR(int areaId,int userCnt);
	static int getGidFromXY(double x,double y);
	static vector<vector<string>> getGridAllRsrp(int gridId);
	static vector<int> getDirectNeighArea(double x,double y);
	static bool judgeGrid(double x,double y);
	static bool isExistsNRT(int aid,int adjCellId);
	static double getNRTAvgCnt(string tableName);
};

#endif
