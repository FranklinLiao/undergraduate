#ifndef _RECORDADJAREAFORSFRTOOL_H
#define _RECORDADJAREAFORSFRTOOL_H
#include "stdafx.h"
#include "DBHelper.h"
#include "Area.h"
#include <vector>
#include <string>
#include <iterator>
using namespace std;
#define RSRPDIFF 6 //�趨�ж��Ƿ�������С���ص����ĳ�ǿ�����ֵ  �ο���������Դ��http://wenku.baidu.com/link?url=A20fv1AXF6AVhUYs86smVndgxWXa4yIoHrIlOV7R-AWMr0qzgNH5JrChUVwqIl66YMNhyz0g6SsU2vipCpJzxDcENibY1sIqyiu7kSRNJly
#define COVERAREAPERCENT 0.3 //�������������С��������ı���  dbm-30 �͵õ���db 
 class RecordAdjAreaForSfrTool {
 public:
	 static void recordAdjAreaForSfrTool();
};
#endif