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
	/*  �½��ࣺStaining
     *  �๦�ܣ�����ǿ��Ӧ����ɫ�༭�����ݿ���У��Ӷ�������ʾ
     *  ����ʱ��: 2014.04.08
     *  �����ߣ�����*/
class Staining
{
public:
	Staining(void);
	~Staining(void);
	//************************************
	/**
	* @brief	��������еĳ�ǿ��Ӧ����ɫ����easyloder�����ı��У�ʹ���ܹ���ͼ
	* @fullName	Staining::PutColor
	* @param	
	* @return	void
	* @author	����
	* @date		2014/04/22
	* @warning	�˴�Ϊ�����Ĳ���˵��
	*/
	
	//************************************
	void PutColor(void);
};

#endif
