/*function: µº∆µŒ€»æ
  author: YuanMan
  date: 2014/09/28
*/
#ifndef _POLLUTION_H
#define _POLLUTION_H
#include "stdafx.h"
#include "ChangeTypeTool.h"
#include <stdarg.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <iterator>
using namespace std;

class pollution {
public:
	static string PJudge(long gid,int count, double threshold,double difference );
	static string APJudge(double percent,long minaid,long maxaid);
};
#endif