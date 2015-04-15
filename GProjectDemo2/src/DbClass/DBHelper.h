#ifndef _DBHELPER_H
#define _DBHELPER_H
#include "stdafx.h"
//#include "Grid.h"
#include "CreateSqlTool.h"
#include "DataBase.h"
#include "User.h"
#include <vector>
#include <string>
using namespace std;

class DBHelper{
public:
	static void deleteAllTable();
	static void deleteData(string tableName);
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
	

	//������  ������������
	static void insertInfo(string tableName,string* key,string* value,int count);
	static void updateInfo(string tableName,string* key,string* value,int count,string* whereKey,string* whereValue,int whereCount);
	static vector<vector<string>>  queryInfo(string tableName,string* whereKey,string* whereValue,int whereCount);
	
	//����sql���ֱ�ӵ���
	static void insertStringInfo(string SqlString);
	static void updateStringInfo(string SqlString);
	static vector<vector<string>> queryStringInfo(string SqlString);
	//��ĳһ�򼸸���������ȡ
	static double getLargestStrength();
	//�����ѡ�����
	static vector<vector<string>> queryGridInfoFromDB();
	static vector<vector<string>> queryAreaInfoFromDB();
	static int queryTableInfoNum(string tableName);
	static vector<int> queryGridMaxXY();
	static vector<double> queryGridXY(int id);
	static vector<double> queryRTDataXY(int id);
	static int getRTDataId(string tableName,double x,double y);
//�����Ż�
public:
	static vector<User> getUser(int areaId,int userCnt);
	static vector<int> getAdjAreaId(int areaId);
	static double getAdjAreaGridStrength(int aid,int gridId);
};

#endif
