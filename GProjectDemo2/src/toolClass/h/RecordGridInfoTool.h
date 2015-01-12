#ifndef _RECORDGRIDINFOTOOL_H
#define _RECORDGRIDINFOTOOL_H
#include "stdafx.h"
#include "DBConnPool.h"
#include "DataBase.h"
#include "DBHelper.h"
#include <iostream>
#include <string>
using namespace std;
extern CMapX m_ctrlMapX;

class RecordGridInfoTool {
public:
	static bool recordGridInfoToDB();
};

#endif