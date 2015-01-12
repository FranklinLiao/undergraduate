#ifndef _RECORDBUILDINGPOINTTOOL_H
#define _RECORDBUILDINGPOINTTOOL_H
#include "stdafx.h"
#include"DBConnPool.h"
#include"DataBase.h"
#include "DBHelper.h"
#include<iostream>
#include<fstream>
#include <sstream>
#include<string>
#include<cstring>
#include <icrsint.h>
#include<iomanip>

using namespace std;
extern CMapX m_ctrlMapX;
class RecordBuildingPointTool
	/*  新建类：RecordBuildingPointTool
     *  类功能：读取.MIF文件信息，并将建筑物折点信息录入数据库中，构造函数中仅放入了默认文件路径
     *  创建时间: 2014.04.08
     *  创建者：贾琦*/
{
	
public:
	ifstream file;
	string Bpoint;
	CString FilePosition;
	RecordBuildingPointTool(void);
	~RecordBuildingPointTool(void);
	bool RecordBuildingLayerInfoToDB();	//录入信息，返回是否成功录入

};

#endif