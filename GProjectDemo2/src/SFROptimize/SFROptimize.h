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
#define SIMCNT 2
class SFROptimize {
public :
	string optimizeOld(int simUserCnt);
	string optimizeNew(int simUserCnt); 
	bool opertion();
public:
	vector<double> edgeOldVector;
	vector<double> edgeNewVector;
	vector<double> allOldVector;
	vector<double> allNewVector;
public:

};
#endif