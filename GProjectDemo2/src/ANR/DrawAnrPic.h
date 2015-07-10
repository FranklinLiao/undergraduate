#ifndef __DRAWPIC_H
#define __DRAWPIC_H

#include "stdafx.h"
#include "engine.h"
#include <vector>
#include <iostream>
#include <iterator>
using namespace std;
#pragma  comment(lib,"libeng.lib")
#pragma  comment(lib,"libmx.lib")
class DrawAnrPic {
public:
	static void drawPic(vector<double> nrtPercent,vector<double> nrtCnt);
};
#endif