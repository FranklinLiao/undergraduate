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
	/*  �½��ࣺRecordBuildingPointTool
     *  �๦�ܣ���ȡ.MIF�ļ���Ϣ�������������۵���Ϣ¼�����ݿ��У����캯���н�������Ĭ���ļ�·��
     *  ����ʱ��: 2014.04.08
     *  �����ߣ�����*/
{
	
public:
	ifstream file;
	string Bpoint;
	CString FilePosition;
	RecordBuildingPointTool(void);
	~RecordBuildingPointTool(void);
	bool RecordBuildingLayerInfoToDB();	//¼����Ϣ�������Ƿ�ɹ�¼��

};

#endif