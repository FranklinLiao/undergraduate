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
class DrawPic {
public:
	static void drawPic(vector<double> edgeOldSfr,vector<double> edgeNewSfr,vector<double> allOldSfr,vector<double> allNewSfr);
};
#endif