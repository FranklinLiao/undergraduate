#ifndef  _RECORDRTDATA_H
#define _RECORDRTDATA_H

#include "stdafx.h"
#include "DBHelper.h"

#include "OperateExcelFileTool.h"
#include "AntannaTypeDefine.h"
#include "ChangeTypeTool.h"
#include "DBHelper.h"
#include "CoverTypeDefine.h"

#include "Area.h"
#include "GetLonLatBoundsTool.h"
#include "Grid.h"

#include<iostream>
#include<fstream>
#include <sstream>
#include<string>
#include <icrsint.h>
#include<iomanip>
#include<ctime>
#include<cstdlib>
#include <vector>
using namespace std;







class RecordRTData {
public:
	static bool recordRTData(CString FileName);
};

#endif