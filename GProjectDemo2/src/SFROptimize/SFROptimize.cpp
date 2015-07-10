#include "stdafx.h"
#include "SFROptimize.h"
string SFROptimize::optimizeOld(int simUserCnt) {  //注意查看一下标志，特别是多次仿真中有些标志是否已经清零了！！！
	bool flag = true;
	//计算经典算法
	/***********************************************
	从数据库中取出所有的小区,并拼装成OldArea
	*************************************************/
	vector<vector<string>> areaInfo = DBHelper::queryAreaInfoFromDB();
	vector<OldArea> oldAreaSet;
	vector<vector<string>>::iterator iter = areaInfo.begin();
	int i = 1;
	while(iter!=areaInfo.end()) {
		Area area = Area(*iter,1); //1用来标识是SFR的Area
		
		//用于科技论文的结果  之后要删除
		//****************************************/
		/*
		switch(i) {
		case 1:
		case 4:
		case 9:simUserCnt = 80;break;
		default:simUserCnt = 10;break;
		}
		i++;
		*/
		OldArea oldArea = OldArea(area,simUserCnt);
		oldAreaSet.push_back(oldArea);
		iter++;
	}
	/****************************************************
	便利各个小区，给小区添加邻区的信息
	******************************************************/
	vector<OldArea>::iterator iterArea12 = oldAreaSet.begin();
	while(iterArea12!=oldAreaSet.end()) {
		string tableName = "ANRT";
		iterArea12->adjAreaId = DBHelper::getAdjAreaId(tableName,iterArea12->area.AId);
		/*
		vector<int>::iterator iterArea13 = iterArea12->adjAreaId.begin();
		while(iterArea13!=iterArea12->adjAreaId.end()) { //根据id，找到邻区
			vector<OldArea>::iterator iterArea14 = oldAreaSet.begin();
			while(iterArea14!=oldAreaSet.end()) {
				if(iterArea14->area.AId==*iterArea13) { //找到了对应的小区，那么添加为邻区
					iterArea12->adjArea.push_back(*iterArea14);
					break;
				}
				iterArea14++;
			}
			iterArea13++;
		}
		*/
		iterArea12++;
	}
	
	/****************************************************
	便利各个小区，给小区分配mainRBIndex
	******************************************************/
	vector<OldArea>::iterator iterArea0 = oldAreaSet.begin();
	while(iterArea0!=oldAreaSet.end()) {
		OldArea oldArea = *iterArea0;
		vector<int> adjArea = oldArea.getAdjAreaId(); //得到某个小区的邻区id
		/****************************************************
		//根据邻区信息，确定MainRbIndex 1 2 3
		//便利邻区，判断它们使用了什么Index
		//得到邻区使用的MainRbIndex，并把邻区使用的MainRbIndex存放到adjMainRbIndexSet中
		******************************************************/
		vector<int>::iterator iterAdjAreaId = adjArea.begin();
		vector<int> adjMainRbIndexSet;
		while(iterAdjAreaId!=adjArea.end()) { //便利这个小区的邻区id
			int adjMainRbIndex = 0;
			vector<OldArea>::iterator iterTmp = oldAreaSet.begin();
			while(iterTmp!=oldAreaSet.end()) { //便利小区集合，通过邻区的Id，找到对应的邻区
				if(iterTmp->area.AId==*iterAdjAreaId) {
					adjMainRbIndex = iterTmp->mainRbIndex; //取出该邻区的mainRbIndex
					if(!((adjMainRbIndex > 0) && (adjMainRbIndex <= OLDRBPARTS))) { ////判断是否有效,也就是判断是否已经分配了MainRbIndex
						adjMainRbIndex = 0; //之前未分配就赋值为0
					} else {
						adjMainRbIndexSet.push_back(adjMainRbIndex); //如果有效，那么就把邻区使用的mainRbIndex存放到set中
					}
					break; //如果找到了，那么就跳出这个小循环，开始查找下一个邻区iterAdjAreaId
				}
				iterTmp++;  //该小区iterTmp不是本小区的邻区，就从小区集合中，查找下一个小区
			}
			
			iterAdjAreaId++; //已经找到了对应邻区的mainRBIndex,继续查找下一个邻区的mainRbIndex
		}
		//找到了邻区使用的mainRbIndex，并存放在mainRBIndexSet中,开始根据这个set查看有哪些mainRbIndex可以用
		for(int mainRbIndex = 1;mainRbIndex<=OLDRBPARTS;mainRbIndex++) {
			vector<int>::iterator iterRBIndex = adjMainRbIndexSet.begin();
			bool isUsed = false; //每一次判定该mainRbIndex时，都要置位
			while(iterRBIndex!=adjMainRbIndexSet.end()) {
				if(*iterRBIndex == mainRbIndex) { //判断当前邻区是否使用了该Index:mainRbIndex
					isUsed = true;
					break; //如果有就退出这个循环， 查看下一个mainRbIndex
				}
				iterRBIndex++; //当前邻区没有使用，继续判断下一个邻区是否用了该Index
			}
			if(!isUsed) { //如果当前的mainRbIndex，没有邻区使用过，那么该小区就使用这个mainRbIndex
				iterArea0->mainRbIndex = mainRbIndex;
				break; //跳出for循环
			}
		}
		if(iterArea0->mainRbIndex==0) { //如果这个小区没有分配上，即邻区用了所有的mainRbIndex
			//1.查看生成邻区的方法，控制个数  
			//2.随机分配
			//此处是随机分配的例子
			srand( (unsigned)time(NULL)); //生成种子
			iterArea0->mainRbIndex = rand()%OLDRBPARTS + 1; //rand()%RBPARTS  0 ~ RBPARTS-1
		}
		iterArea0++; //该小区的mainRbIndex分配结束，可以分配下一个小区了
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
		//便利小区，给小区中的用户分配Rb
		vector<OldArea>::iterator iterArea3 = oldAreaSet.begin();
		while(iterArea3!=oldAreaSet.end()) {
			iterArea3->allocateRb(); //调度算法在allocateRb中
			iterArea3++;
		}
		
		//先分配RB，然后添加邻区信息  方便进行计算sinr
		vector<OldArea>::iterator iterArea12 = oldAreaSet.begin();
		while(iterArea12!=oldAreaSet.end()) {
			//iterArea12->adjAreaId = DBHelper::getAdjAreaId(iterArea12->area.AId);
			iterArea12->adjArea.clear(); //先清除上次的
			vector<int>::iterator iterArea13 = iterArea12->adjAreaId.begin();
			while(iterArea13!=iterArea12->adjAreaId.end()) { //根据id，找到邻区
				vector<OldArea>::iterator iterArea14 = oldAreaSet.begin();
				while(iterArea14!=oldAreaSet.end()) {
					if(iterArea14->area.AId==*iterArea13) { //找到了对应的小区，那么添加为邻区
						iterArea12->adjArea.push_back(*iterArea14);
						break;
					}
					iterArea14++;
				}
				iterArea13++;
			}

			iterArea12++;
		}
		vector<OldArea>::iterator iterArea5 = oldAreaSet.begin();
		while(iterArea5!=oldAreaSet.end()) {
			double edgeOutPut = iterArea5->getEdgeThroughPut();
			iterArea5->edgeThroughput += edgeOutPut; //存储每次的边缘吞吐量
			double sumOutput = iterArea5->getCenterThroughPut()+edgeOutPut;
			sumAllOutput += 1.0*sumOutput/1000;  //kbs
			sumEdgeOutput += 1.0*edgeOutPut/1000; //kbs
			//TRACE("the oldedgeput :%s\n",edgeOutPut);
			//TRACE("the oldsumput :%s\n",sumOutput);
			iterArea5++;
		}
	}
	//将结果求平均
	vector<OldArea>::iterator iterArea5 = oldAreaSet.begin();
	while(iterArea5!=oldAreaSet.end()) {
		double edgeOutPut = iterArea5->edgeThroughput;
		iterArea5->edgeThroughput = 1.0*edgeOutPut / SIMCNT; //存储每次的边缘吞吐量
		iterArea5++;
	}
	avgAllOutput = 1.0*sumAllOutput / SIMCNT / 1000; //mbps
	avgEdageOutput = 1.0*sumEdgeOutput / SIMCNT /1000; //mbps
	edgeOldVector.push_back(avgEdageOutput);
	allOldVector.push_back(avgAllOutput);
	cout<<"old avgall"<<avgAllOutput;
	cout<<"old avgedge"<<avgEdageOutput;
	stringstream ss;
	ss<<avgAllOutput;
	ss<<",";
	ss<<avgEdageOutput;
	return ss.str();
}

string SFROptimize::optimizeNew(int simUserCnt) {  //注意查看一下标志，特别是多次仿真中有些标志是否已经清零了！！！
	bool flag = true;
	//1.先计算改进后的算法
	/***********************************************
	从数据库中取出所有的小区
	*************************************************/
	vector<vector<string>> areaInfo = DBHelper::queryAreaInfoFromDB();
	vector<NewArea> newAreaSet;
	vector<vector<string>>::iterator iter = areaInfo.begin();
	//int i = 1;
	while(iter!=areaInfo.end()) {
		Area area = Area(*iter++,1);
		//用于科技论文的结果  之后要删除
		//****************************************/
		/*
		switch(i) {
		case 1:
		case 4:
		case 9:simUserCnt = 80;break;
		default:simUserCnt = 10;break;
		}
		i++;
		*/
		NewArea newArea = NewArea(area,simUserCnt);
		newAreaSet.push_back(newArea);
	}
	/****************************************************
	便利各个小区，给小区添加邻区的信息
	******************************************************/
	vector<NewArea>::iterator iterArea12 = newAreaSet.begin();
	while(iterArea12!=newAreaSet.end()) {
		string tableName = "ANRT";
		iterArea12->adjAreaId = DBHelper::getAdjAreaId(tableName,iterArea12->area.AId);
		/*
		vector<int>::iterator iterArea13 = iterArea12->adjAreaId.begin();
		while(iterArea13!=iterArea12->adjAreaId.end()) { //根据id，找到邻区
			vector<NewArea>::iterator iterArea14 = newAreaSet.begin();
			while(iterArea14!=newAreaSet.end()) {
				if(iterArea14->area.AId==*iterArea13) { //找到了对应的小区，那么添加为邻区
					iterArea12->adjArea.push_back(*iterArea14);
					break;
				}
				iterArea14++;
			}
			iterArea13++;
		}
		*/
		iterArea12++;
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
					if(!((adjMainRbIndex > 0) && (adjMainRbIndex <= NEWRBPARTS))) { ////判断是否有效 
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
		for(int mainRbIndex = 1;mainRbIndex<=NEWRBPARTS;mainRbIndex++) {
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
		if(iterArea0->mainRbIndex==0) { //如果这个小区没有分配上，即邻区用了所有的mainRbIndex
			//1.查看生成邻区的方法，控制个数  
			//2.随机分配
			//此处是随机分配的例子
			srand( (unsigned)time(NULL)); //生成种子
			iterArea0->mainRbIndex = rand()%NEWRBPARTS + 1; //rand()%RBPARTS  0 ~ RBPARTS-1
		}
		iterArea0++; //该小区的mainRbIndex分配结束，可以分配下一个小区了
	//	iterArea0++;
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
	便利各个小区，给小区添加邻区的信息
	******************************************************/
	vector<NewArea>::iterator iterArea12 = newAreaSet.begin();
	while(iterArea12!=newAreaSet.end()) {
		//iterArea12->adjAreaId = DBHelper::getAdjAreaId(iterArea12->area.AId);
		
		vector<int>::iterator iterArea13 = iterArea12->adjAreaId.begin();
		while(iterArea13!=iterArea12->adjAreaId.end()) { //根据id，找到邻区
			vector<NewArea>::iterator iterArea14 = newAreaSet.begin();
			while(iterArea14!=newAreaSet.end()) {
				if(iterArea14->area.AId==*iterArea13) { //找到了对应的小区，那么添加为邻区
					iterArea12->adjArea.push_back(*iterArea14);
					break;
				}
				iterArea14++;
			}
			iterArea13++;
		}
		
		iterArea12++;
	}
		/****************************************************
		先得到这个小区的邻区的集合，便于计算干扰，然后计算吞吐量，  取出小区后就添加了 所以不用这一块 20150425
		******************************************************/
		/*
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
		*/
		vector<NewArea>::iterator iterArea5 = newAreaSet.begin();
		while(iterArea5!=newAreaSet.end()) {
			double edgeOutPut = iterArea5->getEdgeThroughPut();
			iterArea5->edgeThroughput += edgeOutPut; //存储每次的边缘吞吐量
			double sumOutput = iterArea5->getCenterThroughPut()+edgeOutPut;
			sumAllOutput += 1.0*sumOutput/1000; //kbs
			sumEdgeOutput += 1.0*edgeOutPut/1000; //kbs
			iterArea5++;
		}
	}
	//仿真100次后 将100次的结果求平均
	vector<NewArea>::iterator iterArea5 = newAreaSet.begin();
	while(iterArea5!=newAreaSet.end()) {
		double edgeOutPut = iterArea5->edgeThroughput;
		iterArea5->edgeThroughput = 1.0*edgeOutPut / SIMCNT; //存储每次的边缘吞吐量
		iterArea5++;
	}
	
	avgAllOutput = 1.0*sumAllOutput / SIMCNT /1000; //mbps
	avgEdageOutput = 1.0* sumEdgeOutput / SIMCNT / 1000; //mbps
	edgeNewVector.push_back(avgEdageOutput);
	allNewVector.push_back(avgAllOutput);
	cout<<"new avgall"<<avgAllOutput;
	cout<<"new avgedge"<<avgEdageOutput;
	stringstream ss;
	ss<<avgAllOutput;
	ss<<",";
	ss<<avgEdageOutput;
	return ss.str();
}

bool SFROptimize::opertion() {
	/*
	int userarray[9] = {0,10,20,30,40,50,60,70,80};  
	vector<int> userCnt(userarray , userarray+9); 
	vector<int>::iterator userCntIter = userCnt.begin();
	while(userCntIter!=userCnt.end()) {
		optimizeOld(*userCntIter);
		optimizeNew(*userCntIter);
		userCntIter++;
	}
	*/
	
	//计算得到的吞吐量
	double edgeOldSfrArray[9] = {0,0.314,1.141,1.718,2.150,2.641,2.965,3.573,4.032};  
	vector<double> edgeOldSfrVector(edgeOldSfrArray,edgeOldSfrArray+9);
	double edgeNewSfrArray[9] = {0,0.366,0.919,1.824,2.511,2.857,3.243,3.873,4.549};  
	vector<double> edgeNewSfrVector(edgeNewSfrArray,edgeNewSfrArray+9);
	double allOldSfrArray[9] = {0,5.918,12.804,19.302,20.451,21.639,23.550,24.375,24.917};  
	vector<double> allOldSfrVector(allOldSfrArray,allOldSfrArray+9);
	double allNewSfrArray[9] = {0,5.825,12.609,18.750,19.947,21.019,23.093,23.939,24.426};  
	vector<double> allNewSfrVector(allNewSfrArray,allNewSfrArray+9);

	//为了方便演示，使用了之前计算的数据
	edgeOldVector.clear();
	edgeOldVector.assign(edgeOldSfrVector.begin(), edgeOldSfrVector.end());
	edgeNewVector.clear();
	edgeNewVector.assign(edgeNewSfrVector.begin(), edgeNewSfrVector.end());
	allOldVector.clear();
	allOldVector.assign(allOldSfrVector.begin(), allOldSfrVector.end());
	allNewVector.clear();
	allNewVector.assign(allNewSfrVector.begin(), allNewSfrVector.end());
	
	
	return true;
}
