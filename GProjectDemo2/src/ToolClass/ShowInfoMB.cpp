#include "stdafx.h"
#include "ShowInfoMB.h"
bool ShowInfoMB::showInfo(string infoHead,string infoBody) {
	stringstream info;
	string infoString = "";
	info<<infoHead;  
	info<<infoBody;
	infoString = info.str();
	info.clear();
	//只有这个文件的 中文才乱码  打开该文件，选择文件->高级保存选项  然后改为unicode -1200
	MessageBox(NULL,infoString.c_str(),_T("通知"),MB_OK);
	return TRUE;
}