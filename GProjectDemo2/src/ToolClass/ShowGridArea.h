#ifndef __SHOWGRIDAREA_H
#define __SHOWGRIDAREA_H
#include "stdafx.h"
#include "SetGridColorTool.h"
#include "MakeGridFileTool.h"
#include "Mif2Tab.h"
#include "ShowInfoMB.h"
#include "MyProcess.h"
#include <string>
using namespace std;
class ShowGridArea {
public:
	void showGridArea(CString title,CString name);
	void showAreaMb(string infoHead,string infoBody);
	//static void openProcess();
	//static void closeProcess();
	MyProcess* process;
	void openProcess();
	void closeProcess();
};
#endif