/*function: »ı∏≤∏«≈–∂œ
  author: YuanMan
  date: 2014/09/25
*/
#ifndef _WEAKLAY_H
#define _WEAKLAY_H
#include "stdafx.h"
#include "ChangeTypeTool.h"
#include <stdarg.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <iterator>
using namespace std;

class WeakLay{
public:
	
	static string Max(string tableName,string columnName);
	static string Min(string tableName,string columnName);
	static string UpdateInfo(string tableName, string columnName1,string columnName2,long id,double distance);
	static string  GetGAId(long gid);
	//static string Count(string tableName,string key, string* whereKey, string* whereKeyValue, int whereCount);
	static string WJudge(long Gid,double threshold);
	static string AJudge(long minaid,long maxaid,double percent);
};
#endif