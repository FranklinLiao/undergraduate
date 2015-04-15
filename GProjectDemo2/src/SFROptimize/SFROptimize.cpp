#include "stdafx.h"
#include "SFROptimize.h"
bool SFROptimize::optimizeOld() {  //注意查看一下标志，特别是多次仿真中有些标志是否已经清零了！！！
	bool flag = false;
	//1.先计算经典算法
	/***********************************************
	从数据库中取出所有的小区
	*************************************************/
	vector<vector<string>> areaInfo = DBHelper::queryGridInfoFromDB();
	vector<OldArea> oldAreaSet;
	vector<vector<string>>::iterator iter = areaInfo.begin();
	while(iter!=areaInfo.end()) {
		Area area = Area(*iter++);
		OldArea oldArea = OldArea(area);
		oldAreaSet.push_back(oldArea);
	}
	/****************************************************
	给小区分配mainRBIndex
	******************************************************/
	vector<OldArea>::iterator iterArea0 = oldAreaSet.begin();
	while(iterArea0!=oldAreaSet.end()) {
		OldArea oldArea = *iterArea0;
		vector<int> adjArea = oldArea.getAdjAreaId();
		/****************************************************
		//根据邻区信息，确定MainRbIndex 1 2 3
		//便利邻区，判断它们使用了什么Index
		分配mainRbIndex
		******************************************************/
		vector<int>::iterator iterAdjAreaId = adjArea.begin();
		vector<int> adjMainRbIndexSet;
		while(iterAdjAreaId!=adjArea.end()) { //便利这个小区的邻区
			int adjMainRbIndex = 0;
			vector<OldArea>::iterator iterTmp = oldAreaSet.begin();
			while(iterTmp!=oldAreaSet.end()) { //找到对应的邻区
				if(iterTmp->area.AId==*iterAdjAreaId) {
					adjMainRbIndex = iterTmp->mainRbIndex;
					if(!((adjMainRbIndex > 0) && (adjMainRbIndex <= RBPARTS))) { ////判断是否有效 
						adjMainRbIndex = 0; //之前未分配就赋值为0
					} else {
						adjMainRbIndexSet.push_back(adjMainRbIndex);
					}
					break;
				}
				iterTmp++;
			}
			//找到了对应邻区的RBIndex
			iterAdjAreaId++;
		}
		//找到了邻区使用的mainRbIndex，并存放在mainRBIndexSet中
		for(int mainRbIndex = 1;mainRbIndex<=RBPARTS;mainRbIndex++) {
			vector<int>::iterator iterRBIndex = adjMainRbIndexSet.begin();
			bool isUsed = false;
			while(iterRBIndex!=adjMainRbIndexSet.end()) {
				if(*iterRBIndex == mainRbIndex) {
					isUsed = true;
					break; //如果有就退出
				}
				iterRBIndex++;
			}
			if(!isUsed) { //如果这一个没有使用
				iterArea0->mainRbIndex = mainRbIndex;
				break; //跳出for循环
			}
		}
		iterArea0++;
	}
	/****************************************************
	进行初始化操作 包括分配主副载波资源、随机生成用户，统计边缘和中心用户，计算RB的功率
	******************************************************/
	vector<OldArea>::iterator iterArea2 = oldAreaSet.begin();
	while(iterArea2!=oldAreaSet.end()) {
		iterArea2->init();
		iterArea2++;
	}
	/****************************************************
	通过调度算法给每个小区用户分配RB，此处应该是分配100次，每次都统计吞吐量
	******************************************************/
	double sumAllOutput=0; //100次累加的吞吐量
	double avgAllOutput=0; //平均吞吐量
	double sumEdgeOutput=0;
	double avgEdageOutput=0;
	for(int calcnt =0;calcnt<SIMCNT;calcnt++) {
		vector<OldArea>::iterator iterArea3 = oldAreaSet.begin();
		while(iterArea3!=oldAreaSet.end()) {
			iterArea3->allocateRb(); //调度算法在allocateRb中
			iterArea3++;
		}
		/****************************************************
		先得到这个小区的邻区的集合，便于计算干扰，然后计算吞吐量，
		******************************************************/
		vector<OldArea>::iterator iterArea4 = oldAreaSet.begin();
		while(iterArea4!=oldAreaSet.begin()) {  //便利每一个小区
			//查找这个小区的邻区的id
			vector<int>::iterator iter = iterArea4->adjAreaId.begin();
			while(iter!=iterArea4->adjAreaId.end()) {
				int id = *iter;
				//找到该id的小区，并把他加入到该小区的邻区集合中
				vector<OldArea>::iterator iterIn = oldAreaSet.begin();
				while(iterIn!=oldAreaSet.end()) {
					if(iterIn->area.AId==id) {
						(*iterArea4).adjArea.push_back(*iterIn);
					}
					iterIn++;
				}
				iter++;
			}
			iterArea4++;
		}
		vector<OldArea>::iterator iterArea5 = oldAreaSet.begin();
		while(iterArea5!=oldAreaSet.end()) {
			double edgeOutPut = iterArea5->getEdgeThroughPut(iterArea5->adjArea);
			double sumOutput = iterArea5->getAllThroughPut(iterArea5->adjArea);
			sumAllOutput += sumOutput;
			sumEdgeOutput += edgeOutPut;
			iterArea5++;
		}
	}
	avgAllOutput = sumAllOutput / SIMCNT;
	avgEdageOutput = sumEdgeOutput / SIMCNT;
	return flag;
}

bool SFROptimize::optimizeNew() {  //注意查看一下标志，特别是多次仿真中有些标志是否已经清零了！！！
	bool flag = false;
	//1.先计算改进后的算法
	/***********************************************
	从数据库中取出所有的小区
	*************************************************/
	vector<vector<string>> areaInfo = DBHelper::queryGridInfoFromDB();
	vector<NewArea> newAreaSet;
	vector<vector<string>>::iterator iter = areaInfo.begin();
	while(iter!=areaInfo.end()) {
		Area area = Area(*iter++);
		NewArea newArea = NewArea(area);
		newAreaSet.push_back(newArea);
	}
	/****************************************************
	给小区分配mainRBIndex
	******************************************************/
	vector<NewArea>::iterator iterArea0 = newAreaSet.begin();
	while(iterArea0!=newAreaSet.end()) {
		NewArea newArea = *iterArea0;
		vector<int> adjArea = newArea.getAdjAreaId();
		/****************************************************
		//根据邻区信息，确定MainRbIndex 1 2 3
		//便利邻区，判断它们使用了什么Index
		分配mainRbIndex
		******************************************************/
		vector<int>::iterator iterAdjAreaId = adjArea.begin();
		vector<int> adjMainRbIndexSet;
		while(iterAdjAreaId!=adjArea.end()) { //便利这个小区的邻区
			int adjMainRbIndex = 0;
			vector<NewArea>::iterator iterTmp = newAreaSet.begin();
			while(iterTmp!=newAreaSet.end()) { //找到对应的邻区
				if(iterTmp->area.AId==*iterAdjAreaId) {
					adjMainRbIndex = iterTmp->mainRbIndex;
					if(!((adjMainRbIndex > 0) && (adjMainRbIndex <= RBPARTS))) { ////判断是否有效 
						adjMainRbIndex = 0; //之前未分配就赋值为0
					} else {
						adjMainRbIndexSet.push_back(adjMainRbIndex);
					}
					break;
				}
				iterTmp++;
			}
			//找到了对应邻区的RBIndex
			iterAdjAreaId++;
		}
		//找到了邻区使用的mainRbIndex，并存放在mainRBIndexSet中
		for(int mainRbIndex = 1;mainRbIndex<=RBPARTS;mainRbIndex++) {
			vector<int>::iterator iterRBIndex = adjMainRbIndexSet.begin();
			bool isUsed = false;
			while(iterRBIndex!=adjMainRbIndexSet.end()) {
				if(*iterRBIndex == mainRbIndex) {
					isUsed = true;
					break; //如果有就退出
				}
				iterRBIndex++;
			}
			if(!isUsed) { //如果这一个没有使用
				iterArea0->mainRbIndex = mainRbIndex;
				break; //跳出for循环
			}
		}
		iterArea0++;
	}
	/****************************************************
	进行初始化操作 包括分配主副载波资源、随机生成用户，统计边缘和中心用户，计算RB的功率
	******************************************************/
	vector<NewArea>::iterator iterArea2 = newAreaSet.begin();
	while(iterArea2!=newAreaSet.end()) {
		iterArea2->init();
		iterArea2++;
	}
	/****************************************************
	通过调度算法给每个小区用户分配RB，此处应该是分配100次，每次都统计吞吐量
	******************************************************/
	double sumAllOutput=0; //100次累加的吞吐量
	double avgAllOutput=0; //平均吞吐量
	double sumEdgeOutput=0;
	double avgEdageOutput=0;
	for(int calcnt =0;calcnt<SIMCNT;calcnt++) {
		vector<NewArea>::iterator iterArea3 = newAreaSet.begin();
		while(iterArea3!=newAreaSet.end()) {
			iterArea3->allocateRb(); //调度算法在allocateRb中
			iterArea3++;
		}
		/****************************************************
		先得到这个小区的邻区的集合，便于计算干扰，然后计算吞吐量，
		******************************************************/
		vector<NewArea>::iterator iterArea4 = newAreaSet.begin();
		while(iterArea4!=newAreaSet.begin()) {  //便利每一个小区
			//查找这个小区的邻区的id
			vector<int>::iterator iter = iterArea4->adjAreaId.begin();
			while(iter!=iterArea4->adjAreaId.end()) {
				int id = *iter;
				//找到该id的小区，并把他加入到该小区的邻区集合中
				vector<NewArea>::iterator iterIn = newAreaSet.begin();
				while(iterIn!=newAreaSet.end()) {
					if(iterIn->area.AId==id) {
						(*iterArea4).adjArea.push_back(*iterIn);
					}
					iterIn++;
				}
				iter++;
			}
			iterArea4++;
		}
		vector<NewArea>::iterator iterArea5 = newAreaSet.begin();
		while(iterArea5!=newAreaSet.end()) {
			double edgeOutPut = iterArea5->getEdgeThroughPut(iterArea5->adjArea);
			double sumOutput = iterArea5->getAllThroughPut(iterArea5->adjArea);
			sumAllOutput += sumOutput;
			sumEdgeOutput += edgeOutPut;
			iterArea5++;
		}
	}
	avgAllOutput = sumAllOutput / SIMCNT;
	avgEdageOutput = sumEdgeOutput / SIMCNT;
	return flag;
}