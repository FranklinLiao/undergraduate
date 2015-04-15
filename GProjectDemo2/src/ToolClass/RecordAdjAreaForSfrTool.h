#ifndef _RECORDADJAREAFORSFRTOOL_H
#define _RECORDADJAREAFORSFRTOOL_H
#include "stdafx.h"
#include "DBHelper.h"
#include "Area.h"
#include <vector>
#include <string>
#include <iterator>
using namespace std;
#define RSRPDIFF 6 //设定判断是否在两个小区重叠区的场强差的阈值  参考的数据来源：http://wenku.baidu.com/link?url=A20fv1AXF6AVhUYs86smVndgxWXa4yIoHrIlOV7R-AWMr0qzgNH5JrChUVwqIl66YMNhyz0g6SsU2vipCpJzxDcENibY1sIqyiu7kSRNJly
#define COVERAREAPERCENT 0.3 //这个比例是两个小区总面积的比例  dbm-30 就得到了db 
 class RecordAdjAreaForSfrTool {
 public:
	 static void recordAdjAreaForSfrTool();
};
#endif