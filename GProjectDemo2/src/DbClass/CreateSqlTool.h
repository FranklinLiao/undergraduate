#ifndef _CREATESQLTOOL_H
#define _CREATESQLTOOL_H
#include "stdafx.h"
#include "ChangeTypeTool.h"
#include <stdarg.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <iterator>
#include <sstream>
using namespace std;

class CreateSqlTool {
public:
	static string queryAllGridString;
	static string updateGridSNRString;
	static string getNotNullSNRGridString;
	static string getLonLatBoundString;
	static string getGridLonLatBoundString;
	static string queryAllAreaString;
	static string getTableInfoNum;
	static string getMaxXY;
	static string getRTDataXY;
public:
	//insert into product1(productNum,productName,productSale,productBank) values(1,'ŵ����N97','4499','12');
	//t
	//static string createInsertSql(string tableName,string sqlInfo);

	//UPDATE SendMsg SET sendstatus = 1 WHERE teacherid=1001;
	//tableName   sendstatus = 1 WHERE teacherid=1001
	//static string createUpdateSql(string tableName,string sqlInfo);

	//select name from sysobjects where xtype='U';
	//tableName   where xtype='U'
	//static string createAllQuerySql(string tableName,string sqlInfo);
	//static string createPartQuerySql(string tableName,vector<string> param,string sqlInfo);
	//static string createGetIdSql(string tableName,string sqlInfo);
	//ƴ���ַ���   countΪ�����ĸ���     ����Ĳ�������Ϊstring,intʲô��ҲҪת����string�ٴ���
	//static string getString(int count,...);

	//����������Ϣ��ȡ�����ݿ���
	//static string insertBuildingInfo(string tableName,string sqlInfoParts);

	//������Ҫ�������Ϣ����
	//static string createBuildingSqlInfoPart(int bId,double longitude,double latitude);
	//static string createBuildingPointSqlInfoPart(int pId,double longitude,double latitude,int bId);
	//static string createGridSqlInfoPart(int gId,double longitude,double latitude);
	//����Ҫ����Ľ�����ͽ������۵�Ķ�Ӧ��ϵ
	//static string createSqlLinkInfoPart(int bId,int pId);
	//����������������ཻ�Ķ�Ӧ��ϵ
	//static string createGridBuildingSqlInfoPart(int id,int bId,int gId);
	//�����������۵�������ཻ�Ķ�Ӧ��ϵ
	//static string createGridBuildingPointSqlInfoPart(int PId,int pGridId);
	//����Ҫ����Ļ�վ��Ϣ����
	//static string createBaseStationSqlInfoPart(int AId,double ALongitude,double ALatitude,double AHeight,double AAspectAngle,double ADeclineAngle,double ALength,int AType,int ABaseStationAttr);
	//static string createBaseStationSqlInfoPart(int AId,double ALongitude,double ALatitude,double AHeight,int ABaseStationAttr,double coverTypeValue);
	//������վ������Ķ�Ӧ��ϵ
	//static string createBSGridSqlInfoPart(int Id,int AId,int AGridId);

	//ֱ�Ӵ������ӵ��ַ���
	//static string createQueryGridInfo();  //Gid,GRealSNR,GRTSNR

	//static string createUpdateGridSNRSqlInfoPart(int gid,double GRealSNR); 

	//����֮ǰ����
	static string createInsertKeyValueSql(string tableName,string* key,string* value,int count);
	static string createUpdateKeyValueSql(string tableName,string* key,string* value,int count,string* whereKey,string* whereValue,int whereCount);
	static string createQueryWhereKeyValueSql(string tableName,string* whereKey,string* whereValue,int whereCount);
	static string createGetSpecialGridId(string tableName,double minLongitude,double maxLongitude,double minLatitude,double maxLatitude);
	static string creategetRTDataId(string tablename,double x,double y);
	static string createUpdateDistance(int size,int start);
	//�����Ż�
	static string getRandonUser(string tableName,int areaId,int userCnt);
	static string getAdjAreaId(string tableName,int areaId);
	static string getAdjAreaGridStrength(int aid,int gridId);
};

#endif