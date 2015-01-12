#ifndef _PUTXY_H
#define _PUTXY_H
#include "stdafx.h"
#include "icrsint.h"
#include "DBConnPool.h"
#include "DataBase.h"
#include "InsertRTGridIdTool.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include<math.h>
using namespace std;
	/*  新建类：PutXY
     *  类功能：将原来是经纬度的坐标转换为XY
     *  创建时间: 2014.04.08
     *  创建者：贾琦*/
class PutXY
{
public:
	PutXY(void);
	~PutXY(void);
	//************************************
	/**
	* @brief	将原来是经纬度的坐标转换为XY，以最左上角（西北角）的网格起点为原点，以东和南为增量轴
	* @fullName	PutXY::ChangeToXY
	* @param	
	* @return	void
	* @author	贾琦
	* @date		2014/04/22
	* @warning	此处为函数的补充说明
	*/
	
	//************************************
	static void ChangeToXY(void);
};

#endif
