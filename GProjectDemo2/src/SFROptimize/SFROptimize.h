#ifndef _SFROPTIMIZE_H
#define _SFROPTIMIZE_H
#include "stdafx.h"
#include "DBHelper.h"
#include "OldArea.h"
#include "NewArea.h"
#include "time.h"
#include "stdlib.h"
#include <vector>
#include <string>
using namespace std;
#define SIMCNT 1
//����ƫ��  -55    >-85 ƫ��  23�����62  ��85Ϊ�ֽ��ߣ�
class SFROptimize {
public :
	static string optimizeOld(int simUserCnt);
	static string optimizeNew(int simUserCnt); 
	static bool opertion();
};
#endif