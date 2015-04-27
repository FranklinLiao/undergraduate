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
//整体偏移  -55    >-85 偏移  23（最大62  以85为分界线）
class SFROptimize {
public :
	static string optimizeOld(int simUserCnt);
	static string optimizeNew(int simUserCnt); 
	static bool opertion();
};
#endif