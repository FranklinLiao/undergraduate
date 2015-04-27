#include "stdafx.h"
#include "ANROptimize.h"
void ANROptimize::snrOptimize() {
	
	//先得到网格的最大xy,这样就不会跑出地图
	double maxX = DBHelper::getGridMaxXY(1); 
	double maxY = DBHelper::getGridMaxXY(2);
	
	//取出所有的小区,并在小区构造函数中就完成了用户的生成
	vector<vector<string>> areaInfo = DBHelper::queryAreaInfoFromDB();
	vector<AreaANR> areaANRSet;
	vector<vector<string>>::iterator iter = areaInfo.begin();
	while(iter!=areaInfo.end()) {
		Area area = Area(*iter,1);
		AreaANR areaAnr = AreaANR(area,maxX,maxY);
	//	AreaANR areaANR = AreaANR(area,maxX,maxY);
		areaANRSet.push_back(areaAnr);
		iter++;
	}
	
	/****************************************************
	开始遍历每个小区
	******************************************************/
	
	vector<AreaANR>::iterator iterArea2 = areaANRSet.begin();
	while(iterArea2!=areaANRSet.end()) {
		//AreaANR areaANR = *iterArea2;
		//注意对小区的处理必须在对iterArea2
		//取出小区中的用户
		vector<UserANR>::iterator userIter = iterArea2->users.begin();
		while(userIter!=iterArea2->users.end()) {
			//对单个用户
			//1.用户是否运动了足够的时间
			int runTime = RUNTIME;
			while(runTime--) {
				//2.用户判断是否要添加邻区
				//3.用户移动
				int nowGid = DBHelper::getGidFromXY(userIter->x,userIter->y);
				float serverRSRP = DBHelper::getServerRSRP(iterArea2->area.AId,nowGid); //此处需要考虑x,y会有偏差float 不用== 用范围 
				//vector<map<int,float>> adjinfo = ;//

			}
			userIter++;
		}
		iterArea2++;
	}
	
}