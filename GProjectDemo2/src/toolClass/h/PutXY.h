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
	/*  �½��ࣺPutXY
     *  �๦�ܣ���ԭ���Ǿ�γ�ȵ�����ת��ΪXY
     *  ����ʱ��: 2014.04.08
     *  �����ߣ�����*/
class PutXY
{
public:
	PutXY(void);
	~PutXY(void);
	//************************************
	/**
	* @brief	��ԭ���Ǿ�γ�ȵ�����ת��ΪXY���������Ͻǣ������ǣ����������Ϊԭ�㣬�Զ�����Ϊ������
	* @fullName	PutXY::ChangeToXY
	* @param	
	* @return	void
	* @author	����
	* @date		2014/04/22
	* @warning	�˴�Ϊ�����Ĳ���˵��
	*/
	
	//************************************
	static void ChangeToXY(void);
};

#endif
