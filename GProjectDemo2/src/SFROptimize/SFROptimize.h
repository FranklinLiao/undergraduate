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
#define SIMCNT 100
class SFROptimize {
public :
	static bool optimizeOld();
	static bool optimizeNew();
};
#endif