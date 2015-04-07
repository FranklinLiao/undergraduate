#ifndef _RECORDBSINFOTOOL_H
#define _RECORDBSINFOTOOL_H
#include "stdafx.h"

#include "AntannaTypeDefine.h"
#include "ChangeTypeTool.h"
#include "DBHelper.h"
#include "CoverTypeDefine.h"
#include "FreqTypeDefine.h"
#include "Area.h"
#include "GetLonLatBoundsTool.h"
//#include "StringParser.h"
#include "OperateExcelFileTool.h"
#include "Grid.h"
#include <string>
#include <vector>
using namespace std;

class RecordAreaInfoTool {
public:
	static bool insertAreaInfo(CString fileName);
	static bool isValid(double longitude,double latitude,int height,int aspectAngle,int declineAngle,int aPCI);

};

#endif