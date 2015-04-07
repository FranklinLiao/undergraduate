/*function: ¹ý¸²¸ÇÅÐ¶Ï
  author: YuanMan
  date: 2014/09/25
*/
#ifndef _OVERLAY_H
#define _OVERLAY_H
#include "stdafx.h"
#include "ChangeTypeTool.h"
#include <stdarg.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <iterator>
using namespace std;

class OverLay{
public:
	static string ojudge(long gid);
	static string ajudge(long minaid,long maxaid,double percent);
};
#endif