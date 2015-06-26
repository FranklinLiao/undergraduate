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
	//ɾ������
	void deletAllInfo(string TableName);
	void clearOneCol(string TableName,string col);
	//��������
	 void insertInfo(string insertString);
	//��������
	 void updateInfo(string updateString);
	 //�õ����ݵĽ����
	 vector<vector<string>> getObjectInfo(string queryString);
	 //�õ���ȡ�Ľ������۵�ľ�γ�ȷ�Χ
	 vector<double> getLonLatBounds();
	 vector<double> getGridLonLatBounds();
	 //�����Ż��������ǵķ���
	 long MaxId(string maxidString);
	 long MinId(string minidString);
	 vector<int> getLayOptimizeAreaIdFromDb(string sqlInfo);
	 void setWeakLay();//��û���յ���ǿ�������ж�Ϊ������
	 vector<float> getCellInfo(int cellId);

	 //�����Ż��ķ���
	 vector<vector<string>> getUserFromDb(string tableName,int areaId,int userCnt);
	 vector<int> getAdjAreaIdFromDb(string tableName,int areaId);

	 //SFR�Ż�
	 int getAreaCnt();
	 int getGridCnt();
	 double getAdjAreaGridStrength(int aid,int gridId);

	 //ANR�Ż�
	 double getServerRSRPFromDB(int aid,int gid);
	 double getMaxGridXY(int flag);
	 vector<vector<string>> getUserANRFromDb(string tableName,int areaId,int userCnt);
	 int getGidFromXY(double x,double y);
	 vector<vector<string>> getGridAllRsrpInfo(int gridId);
};

#endif