#ifndef _COVERTYPEDEFINE_H
#define _COVERTYPEDEFINE_H
#include "stdafx.h"
#include <string>
using namespace std;

class CoverTypeDefine {
public:
	/**
	* @brief	由区域所在的类型得到相应的天线发射增益
	* @fullName	CoverTypeDefine::getCoverTypeValue
	* @param	name
	* @return	double
	* @author	Franklin
	* @date		2014/06/12
	* @warning	
	*/
	static double getCoverTypeValue(string name);
};
#endif