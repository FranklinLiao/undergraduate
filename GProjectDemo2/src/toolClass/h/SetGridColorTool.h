#ifndef _RECORDGRID_H
#define _RECORDGRID_H
#include "stdafx.h"
#include "icrsint.h"
#include "DBHelper.h"
#include "Grid.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;
#define COLOR1 14211263
#define COLOR2 14408560
#define COLOR3 16776960
#define COLOR4 13612347
#define COLOR5 16744192
#define COLOR6 16720896
#define COLOR7 16711680
#define COLOR8 9315107
#define COLOR9 5123887

class SetGridColorTool
	/*  �½��ࣺRecordBuildingPoint
     *  �๦�ܣ���ȡ.MIF�ļ���Ϣ������������Ϣ¼�����ݿ��У����캯���н�������Ĭ���ļ�·��
     *  ����ʱ��: 2014.04.08
     *  �����ߣ�����*/
{
private:
	ifstream file;
	string FilePosition;
	int color[9];
public:
	SetGridColorTool(void);
	~SetGridColorTool(void);
	
	static bool SetColor(void);
};

#endif

