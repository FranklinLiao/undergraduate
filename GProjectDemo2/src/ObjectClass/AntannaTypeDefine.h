#ifndef _ANTANNATYPEDEFINE_H
#define _ANTANNATYPEDEFINE_H
#include "stdafx.h"

class AntannaTypeDefine{
public:
	/**
	* @brief	由天线的类型来判定天线的编号 
	* @fullName	AntannaTypeDefine::getAntanaTypeDefineValue
	* @param	typeName
	* @return	int
	* @author	Franklin
	* @date		2014/06/12
	* @warning	
	*/
	static int getAntanaTypeDefineValue(CString typeName);
};

#endif