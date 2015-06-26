#include "stdafx.h"
#include "ShowInfoMB.h"
bool ShowInfoMB::showInfo(string infoHead,string infoBody) {
	stringstream info;
	string infoString = "";
	info<<infoHead;  
	info<<infoBody;
	infoString = info.str();
	info.clear();
	MessageBox(NULL,infoString.c_str(),_T("Warnning"),MB_OK);
	return TRUE;
}