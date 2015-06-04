#ifndef _ANROPTIMIZE_H
#define _ANROPTIMIZE_H
#include "stdafx.h"
#include "Area.h"
#include "UserANR.h"
#include "AreaANR.h"
#include <iterator>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int,int> PAIR;//
#define RUNTIME 100  //·ÂÕæ´ÎÊý
class ANROptimize {
public:
	static void snrOptimize();
	static int mapCmp(const PAIR& x,const PAIR& y) {
		return x.second > y.second;
	}

	static void sortMapByValue(map<int,int> &mapAdjArea,vector<PAIR> &vectorAdjArea) {
		vectorAdjArea.clear();
		for(map<int,int>::iterator adjAreaTmpIter = mapAdjArea.begin();adjAreaTmpIter!=mapAdjArea.end();++adjAreaTmpIter) {
			vectorAdjArea.push_back(make_pair(adjAreaTmpIter->first,adjAreaTmpIter->second));
		}
		sort(vectorAdjArea.begin(),vectorAdjArea.end(),mapCmp);
	}

	static void vectorToMap(vector<PAIR> &vectorAdjArea,map<int,int> &mapAdjArea) {
		mapAdjArea.clear();
		for(vector<PAIR>::iterator adjAreaTmpIter = vectorAdjArea.begin();adjAreaTmpIter!=vectorAdjArea.end();++adjAreaTmpIter) {
			mapAdjArea.insert(make_pair(adjAreaTmpIter->first,adjAreaTmpIter->second));
		}
	}
};
#endif