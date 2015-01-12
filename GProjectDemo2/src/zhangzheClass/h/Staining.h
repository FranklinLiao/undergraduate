#ifndef _STAINING_H
#define _STAINING_H
#include "stdafx.h"
#include "DBConnPool.h"
#include "DataBase.h"
#include "icrsint.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;
	/*  新建类：Staining
     *  类功能：将场强对应的颜色编辑在数据库表中，从而进行显示
     *  创建时间: 2014.04.08
     *  创建者：贾琦*/
class Staining
{
public:
	Staining(void);
	~Staining(void);
	//************************************
	/**
	* @brief	将网格表中的场强对应的颜色放入easyloder导出的表中，使得能够绘图
	* @fullName	Staining::PutColor
	* @param	
	* @return	void
	* @author	贾琦
	* @date		2014/04/22
	* @warning	此处为函数的补充说明
	*/
	
	//************************************
	void PutColor(void);
};

#endif
