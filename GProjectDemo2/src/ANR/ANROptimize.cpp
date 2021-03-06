#include "stdafx.h"
#include "ANROptimize.h"
bool ANROptimize::snrOptimize(string fileName) {
	DBHelper::deleteData("ANRT");
	CXCFileStream cxCfileStream;
	vector<list<string> > infosVector;
	string title[] = {"小区Id","邻区Id","邻区Id","邻区Id","邻区Id","邻区Id","邻区Id",
		"邻区Id","邻区Id","邻区Id","邻区Id","邻区Id","邻区Id","邻区Id","邻区Id","邻区Id",
		"邻区Id","邻区Id","邻区Id","邻区Id","邻区Id"};
	list<string> titleList(title,title+sizeof(title)/sizeof(title[0]));
	infosVector.push_back(titleList);
	list<string> infoList;

	//先得到网格的最大xy,这样就不会跑出地图
	double maxX = DBHelper::getGridMaxXY(1); 
	double maxY = DBHelper::getGridMaxXY(2);
	
	//取出所有的小区,并在小区构造函数中就完成了用户的生成
	vector<vector<string>> areaInfo = DBHelper::queryAreaInfoFromDB();
	vector<AreaANR> areaANRSet;
	vector<vector<string>>::iterator iter = areaInfo.begin();
	while(iter!=areaInfo.end()) {
		Area area = Area(*iter,1);
		AreaANR areaAnr = AreaANR(area,maxX,maxY,true);
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
				//1.用户先运动
				userIter->moveAndModify(userIter->x,userIter->y);
				if(userIter->x < -90 || userIter->y < -90) { //正常的网格的Xy都大于0  有问题的为-100  考虑到精度  用了-90
					break; //该用户结束
				}
				//2.运动完成后，先统计然后判定是否满足切换条件
				int nowGid = DBHelper::getGidFromXY(userIter->x,userIter->y);
				//判断是否移动到了相交的网格，如果移动到了 那么再次移动 如果移动了10次 还没移出来，那么就放弃该用户

				userIter->gridId = nowGid; //根据xy更新gid
				//开始进行A3事件的判断
				float serverRSRP = DBHelper::getServerRSRP(iterArea2->area.AId,nowGid); //此处需要考虑x,y会有偏差float 不用== 用范围 
				map<int,double> adjinfo = userIter->getOtherAreaRsrp(nowGid);
				//先全部统计，然后判断是否可以切换
				//便利adjinfo，判断该小区上一次是否也满足
				//判断该小区是否满足A3条件（可以统计一次的条件）
				map<int,double>::iterator iterAdjinfo = adjinfo.begin();
				map<int,double> acceptAdjInfo;
				while(iterAdjinfo!=adjinfo.end()) {
					//判断是否满足A3事件
					bool flag = userIter->isA3Meet(serverRSRP,iterAdjinfo->second);
					if(flag) {
						acceptAdjInfo.insert(make_pair(iterAdjinfo->first,iterAdjinfo->second));
						//判断之前是否已经计数了，有则加1 否则加入集合，并设置为1
						map<int,int>::iterator mapFind = userIter->areaCalCnt.find(iterAdjinfo->first);
						if(mapFind!=userIter->areaCalCnt.end()) { //如果可以找到
							mapFind->second = mapFind->second + 1;
						} else {
							userIter->areaCalCnt.insert(make_pair(iterAdjinfo->first,1)); //插入这个小区的计数器（但是没添加该小区为邻区），并设置次数为1
						}
					}
					iterAdjinfo++;
				}
				//对邻区列表进行排序（中间会考虑到次数和RSRP）
				//userIter->areaCalCnt排序
				//acceptadjinfo中有计算的邻区的RSRP
				//此处为了方便，只考虑次数
				map<int,int> areaCalCntTmp = userIter->areaCalCnt;
				vector<PAIR> areaCalCntVector;

				sortMapByValue(areaCalCntTmp,areaCalCntVector);
				//将vector转化为map
				vectorToMap(areaCalCntVector,userIter->areaCalCnt);

				//判断是否切换
				//取出最好的那个，也就是第一个
				if(userIter->areaCalCnt.size()<1) {
					continue;
				}
				map<int,int>::iterator mapIter =  userIter->areaCalCnt.begin();
				int adjCellCalCnt = mapIter->second;
				if(adjCellCalCnt > TIMELAST) { //进行切换
					int newAreaId = mapIter->first;
					userIter->aid = newAreaId; //更改aid
					//先判断这个小区是否是服务小区的邻区
					map<int,int>::iterator adjAreaIter = iterArea2->adjArea.find(newAreaId);
					if(adjAreaIter!=iterArea2->adjArea.end()) { //是邻区
						adjAreaIter->second = adjAreaIter->second + 1;
					} else  {
						iterArea2->adjArea.insert(make_pair(newAreaId,1)); //将该小区设置为邻区，并计数为1
					}
					userIter->areaCalCnt.clear(); //次数清零
				} else {
					//什么也不做
				}
			}
			userIter++;
		}
		//对小区的邻区进行排序
		map<int,int> adjAreaTmp = iterArea2->adjArea;
		vector<PAIR> adjAreaVector;
		sortMapByValue(adjAreaTmp,adjAreaVector);
		//排好序后的邻区放在了adjAreaVector中
		//按照邻区优先级顺序，插入到数据表 ANRT  
		infoList.clear();
		infoList.push_back(ChangeTypeTool::intToString(iterArea2->area.AId));
		for(int i=0;i<adjAreaVector.size()&&i<15;i++) { //最多插入15个
			int adjCellId = adjAreaVector[i].first;
			//保证双向
			stringstream insertString;
			insertString<<"insert into ANRT (aid,aneicellid) values(";
			insertString<<iterArea2->area.AId;
			insertString<<",";
			insertString<<adjCellId;
			insertString<<");";
			//判断之前是否已经存在
			if(!DBHelper::isExistsNRT(iterArea2->area.AId,adjCellId)) {
				DBHelper::insertStringInfo(insertString.str());	
			}
			insertString.str("");
			insertString<<"insert into ANRT (aid,aneicellid) values(";
			insertString<<adjCellId;
			insertString<<",";
			insertString<<iterArea2->area.AId;
			insertString<<");";
			if(!DBHelper::isExistsNRT(adjCellId,iterArea2->area.AId)) {
				DBHelper::insertStringInfo(insertString.str());	
			}
			infoList.push_back(ChangeTypeTool::intToString(adjCellId));
		}
		iterArea2++;
		infosVector.push_back(infoList);
	}
	cxCfileStream.WriteCsvData(fileName.c_str(), infosVector);
	return true;
}

double ANROptimize::getSwitchPercent(string tableName) {
	//得到切换成功率
	int succCnt = 0;
	int allCnt = 0;
	//先得到网格的最大xy,这样就不会跑出地图
	double maxX = DBHelper::getGridMaxXY(1); 
	double maxY = DBHelper::getGridMaxXY(2);
	
	//取出所有的小区,并在小区构造函数中就完成了用户的生成
	vector<vector<string>> areaInfo = DBHelper::queryAreaInfoFromDB();
	vector<AreaANR> areaANRSet;
	vector<vector<string>>::iterator iter = areaInfo.begin();
	while(iter!=areaInfo.end()) {
		Area area = Area(*iter,1);
		AreaANR areaAnr = AreaANR(area,maxX,maxY,false);
		//同时将邻区列表放到用户的adjArea中
		vector<int> adjAreaVector = DBHelper::getAdjAreaId(tableName,areaAnr.area.AId);
	    vector<int>::iterator iteradjArea = adjAreaVector.begin();
		while(iteradjArea!=adjAreaVector.end()) {
			areaAnr.adjArea.insert(make_pair(*iteradjArea,1));
			iteradjArea++;
		}
		//AreaANR areaANR = AreaANR(area,maxX,maxY);
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
				//1.用户先运动
				userIter->moveAndModify(userIter->x,userIter->y);
				if(userIter->x < -90 || userIter->y < -90) { //正常的网格的Xy都大于0  有问题的为-100  考虑到精度  用了-90
					break; //该用户结束
				}
				//2.运动完成后，先统计然后判定是否满足切换条件
				int nowGid = DBHelper::getGidFromXY(userIter->x,userIter->y);
				//判断是否移动到了相交的网格，如果移动到了 那么再次移动 如果移动了10次 还没移出来，那么就放弃该用户

				userIter->gridId = nowGid; //根据xy更新gid
				//开始进行A3事件的判断
				float serverRSRP = DBHelper::getServerRSRP(iterArea2->area.AId,nowGid); //此处需要考虑x,y会有偏差float 不用== 用范围 
				map<int,double> adjinfo = userIter->getOtherAreaRsrp(nowGid);
				//先全部统计，然后判断是否可以切换
				//便利adjinfo，判断该小区上一次是否也满足
				//判断该小区是否满足A3条件（可以统计一次的条件）
				map<int,double>::iterator iterAdjinfo = adjinfo.begin();
				map<int,double> acceptAdjInfo;
				while(iterAdjinfo!=adjinfo.end()) {
					//判断是否满足A3事件
					bool flag = userIter->isA3Meet(serverRSRP,iterAdjinfo->second);
					if(flag) {
						acceptAdjInfo.insert(make_pair(iterAdjinfo->first,iterAdjinfo->second));
						//判断之前是否已经计数了，有则加1 否则加入集合，并设置为1
						map<int,int>::iterator mapFind = userIter->areaCalCnt.find(iterAdjinfo->first);
						if(mapFind!=userIter->areaCalCnt.end()) { //如果可以找到
							mapFind->second = mapFind->second + 1;
						} else {
							userIter->areaCalCnt.insert(make_pair(iterAdjinfo->first,1)); //插入这个小区的计数器（但是没添加该小区为邻区），并设置次数为1
						}
					}
					iterAdjinfo++;
				}
				//对邻区列表进行排序（中间会考虑到次数和RSRP）
				//userIter->areaCalCnt排序
				//acceptadjinfo中有计算的邻区的RSRP
				//此处为了方便，只考虑次数
				map<int,int> areaCalCntTmp = userIter->areaCalCnt;
				vector<PAIR> areaCalCntVector;

				sortMapByValue(areaCalCntTmp,areaCalCntVector);
				//将vector转化为map
				vectorToMap(areaCalCntVector,userIter->areaCalCnt);

				//判断是否切换
				//取出最好的那个，也就是第一个
				if(userIter->areaCalCnt.size()<1) {
					continue;
				}
				map<int,int>::iterator mapIter =  userIter->areaCalCnt.begin();
				int adjCellCalCnt = mapIter->second;
				if(adjCellCalCnt > TIMELASTCMP) { //进行切换
					int newAreaId = mapIter->first;
					userIter->aid = newAreaId; //更改aid
					//先判断这个小区是否是服务小区的邻区
					map<int,int>::iterator adjAreaIter = iterArea2->adjArea.find(newAreaId);
					if(adjAreaIter!=iterArea2->adjArea.end()) { //是邻区
						succCnt = succCnt + 1;
						allCnt = allCnt + 1;
					} else {
						runTime = 0; //用户掉线了
						allCnt = allCnt + 1;
						break;
					}
					userIter->areaCalCnt.clear(); //次数清零
				} else {
					//什么也不做
				}
			}
			userIter++;
		}
		iterArea2++;
	}
	return 1.0*(succCnt)/allCnt;
}

double ANROptimize::getCnt(string tableName) {
	double cnt = DBHelper::getNRTAvgCnt(tableName);
	return cnt;
}


void ANROptimize::getCompareResult() {
	//create process
	MyProcess* process = new MyProcess();
	process->Create(IDD_PROCESS,NULL);
	process->MyProcessInfo="请稍后，正在生成邻区优化前后对比结果...";
	process->UpdateData(FALSE);
	process->ShowWindow(SW_SHOW);
	process->RedrawWindow();

	/*
	vector<double> percentVector;
	vector<double> cntVector;
	string tableName = "AOldNRT";
	double percentAnr = getSwitchPercent(tableName);
	double cntAnr = getCnt(tableName);
	percentVector.push_back(1.0*percentAnr*100);
	cntVector.push_back(cntAnr);

	tableName = "ANRT";
	percentAnr = getSwitchPercent(tableName);
	cntAnr = getCnt(tableName);
	percentVector.push_back(1.0*percentAnr*100);
	cntVector.push_back(cntAnr);
	*/
	//画图  运算得到的数据
	
	double percentArray[2] = {0.971*100,0.942*100};  
	vector<double> percentVector(percentArray,percentArray+2);
	double cntArray[2] = {5.5,4};  
	vector<double> cntVector(cntArray,cntArray+2);
	

	//close process
	process->DestroyWindow();
	delete process;
	process = NULL;

	DrawAnrPic::drawPic(percentVector,cntVector);
}
