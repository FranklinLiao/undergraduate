#ifndef _NEWAREA_H
#define _NEWAREA_H
#include "stdafx.h"
#include "NewRbs.h"
#include "OldArea.h"
#include "User.h"
#include "Area.h"
#include <vector>
#include <iterator>
using namespace std;
class NewArea : public OldArea{
public:
	map<int,int> optRb;
	bool optRbOverFlag;
	NewArea(Area area,int simUserCnt):OldArea(area,simUserCnt) {
		
	}
	void init();
	void getMainSubRb();
	void setRbPower();
	void sortUserAndClearRBMap();
	void allocateRb();
};

#endif