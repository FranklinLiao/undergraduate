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
	//��������
	 void insertInfo(string insertString);
	//��������
	 void updateInfo(string updateString);
	 //�õ����ݵĽ����
	 vector<vector<string>> getObjectInfo(string queryString);
	 //�õ���ȡ�Ľ������۵�ľ�γ�ȷ�Χ
	 vector<double> getLonLatBounds();
};

#endif