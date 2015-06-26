#ifndef __SHOWGRIDAREA_H
#define __SHOWGRIDAREA_H
#include "stdafx.h"
#include "SetGridColorTool.h"
#include "MakeGridFileTool.h"
#include "Mif2Tab.h"
#include "ShowInfoMB.h"
#include <string>
using namespace std;
class ShowGridArea {
public:
	static void showGridArea(CString title);
	static void showAreaMb(string infoHead,string infoBody);
};
#endif