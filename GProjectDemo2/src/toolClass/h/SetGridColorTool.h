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
	/*  新建类：RecordBuildingPoint
     *  类功能：读取.MIF文件信息，并将网格信息录入数据库中，构造函数中仅放入了默认文件路径
     *  创建时间: 2014.04.08
     *  创建者：贾琦*/
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

