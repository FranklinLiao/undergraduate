#ifndef _CREATEGRID_H
#define _CREATEGRID_H
#include "MAPX.H"
#include "DBConnect.h"
#include "DBConnPool.h"
#include "Grid.h"
#include<iostream>
#include<fstream>
#include <sstream>
#include<string>
#include <icrsint.h>
#include<iomanip>
using namespace std;
#import "C:\\program files\\common files\\system\\ado\\msado15.dll"  no_namespace rename("EOF", "EndOfFile")

#define UNIT_LONG 0.000029
#define UNIT_LAT 0.000023
extern CMapX m_ctrlMapX;


class MakeGridFileTool
{
public:
	
	/**
	* @brief	从数据库中提取出网格数据，生成带有颜色属性的mif文件
	* @fullName	MakeGridFileTool::makeGridFile
	* @param	
	* @return	bool
	* @author	Franklin
	* @date		2014/06/12
	* @warning	
	*/
	static bool makeGridFile(string fileNameString);
};

#endif

