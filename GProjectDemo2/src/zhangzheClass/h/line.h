#ifndef _LINE_H
#define _LINE_H
#include "stdafx.h"
#include <vector>
using namespace std;

class TwoDimPoint{
public:
	float x;
	float y;
};
class line
{
public:
	TwoDimPoint point1;
	TwoDimPoint point2;
};
#endif
