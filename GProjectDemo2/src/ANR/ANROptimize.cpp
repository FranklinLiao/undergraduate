#include "stdafx.h"
#include "ANROptimize.h"
bool ANROptimize::snrOptimize(string fileName) {
	DBHelper::deleteData("ANRT");
	CXCFileStream cxCfileStream;
	vector<list<string> > infosVector;
	string title[] = {"С��Id","����Id","����Id","����Id","����Id","����Id","����Id",
		"����Id","����Id","����Id","����Id","����Id","����Id","����Id","����Id","����Id",
		"����Id","����Id","����Id","����Id","����Id"};
	list<string> titleList(title,title+sizeof(title)/sizeof(title[0]));
	infosVector.push_back(titleList);
	list<string> infoList;

	//�ȵõ���������xy,�����Ͳ����ܳ���ͼ
	double maxX = DBHelper::getGridMaxXY(1); 
	double maxY = DBHelper::getGridMaxXY(2);
	
	//ȡ�����е�С��,����С�����캯���о�������û�������
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
	��ʼ����ÿ��С��
	******************************************************/
	
	vector<AreaANR>::iterator iterArea2 = areaANRSet.begin();
	while(iterArea2!=areaANRSet.end()) {
		//AreaANR areaANR = *iterArea2;
		//ע���С���Ĵ�������ڶ�iterArea2
		//ȡ��С���е��û�
		vector<UserANR>::iterator userIter = iterArea2->users.begin();
		while(userIter!=iterArea2->users.end()) {
			//�Ե����û�
			//1.�û��Ƿ��˶����㹻��ʱ��
			int runTime = RUNTIME;
			while(runTime--) {
				//1.�û����˶�
				userIter->moveAndModify(userIter->x,userIter->y);
				if(userIter->x < -90 || userIter->y < -90) { //�����������Xy������0  �������Ϊ-100  ���ǵ�����  ����-90
					break; //���û�����
				}
				//2.�˶���ɺ���ͳ��Ȼ���ж��Ƿ������л�����
				int nowGid = DBHelper::getGidFromXY(userIter->x,userIter->y);
				//�ж��Ƿ��ƶ������ཻ����������ƶ����� ��ô�ٴ��ƶ� ����ƶ���10�� ��û�Ƴ�������ô�ͷ������û�

				userIter->gridId = nowGid; //����xy����gid
				//��ʼ����A3�¼����ж�
				float serverRSRP = DBHelper::getServerRSRP(iterArea2->area.AId,nowGid); //�˴���Ҫ����x,y����ƫ��float ����== �÷�Χ 
				map<int,double> adjinfo = userIter->getOtherAreaRsrp(nowGid);
				//��ȫ��ͳ�ƣ�Ȼ���ж��Ƿ�����л�
				//����adjinfo���жϸ�С����һ���Ƿ�Ҳ����
				//�жϸ�С���Ƿ�����A3����������ͳ��һ�ε�������
				map<int,double>::iterator iterAdjinfo = adjinfo.begin();
				map<int,double> acceptAdjInfo;
				while(iterAdjinfo!=adjinfo.end()) {
					//�ж��Ƿ�����A3�¼�
					bool flag = userIter->isA3Meet(serverRSRP,iterAdjinfo->second);
					if(flag) {
						acceptAdjInfo.insert(make_pair(iterAdjinfo->first,iterAdjinfo->second));
						//�ж�֮ǰ�Ƿ��Ѿ������ˣ������1 ������뼯�ϣ�������Ϊ1
						map<int,int>::iterator mapFind = userIter->areaCalCnt.find(iterAdjinfo->first);
						if(mapFind!=userIter->areaCalCnt.end()) { //��������ҵ�
							mapFind->second = mapFind->second + 1;
						} else {
							userIter->areaCalCnt.insert(make_pair(iterAdjinfo->first,1)); //�������С���ļ�����������û��Ӹ�С��Ϊ�������������ô���Ϊ1
						}
					}
					iterAdjinfo++;
				}
				//�������б���������м�ῼ�ǵ�������RSRP��
				//userIter->areaCalCnt����
				//acceptadjinfo���м����������RSRP
				//�˴�Ϊ�˷��㣬ֻ���Ǵ���
				map<int,int> areaCalCntTmp = userIter->areaCalCnt;
				vector<PAIR> areaCalCntVector;

				sortMapByValue(areaCalCntTmp,areaCalCntVector);
				//��vectorת��Ϊmap
				vectorToMap(areaCalCntVector,userIter->areaCalCnt);

				//�ж��Ƿ��л�
				//ȡ����õ��Ǹ���Ҳ���ǵ�һ��
				if(userIter->areaCalCnt.size()<1) {
					continue;
				}
				map<int,int>::iterator mapIter =  userIter->areaCalCnt.begin();
				int adjCellCalCnt = mapIter->second;
				if(adjCellCalCnt > TIMELAST) { //�����л�
					int newAreaId = mapIter->first;
					userIter->aid = newAreaId; //����aid
					//���ж����С���Ƿ��Ƿ���С��������
					map<int,int>::iterator adjAreaIter = iterArea2->adjArea.find(newAreaId);
					if(adjAreaIter!=iterArea2->adjArea.end()) { //������
						adjAreaIter->second = adjAreaIter->second + 1;
					} else  {
						iterArea2->adjArea.insert(make_pair(newAreaId,1)); //����С������Ϊ������������Ϊ1
					}
					userIter->areaCalCnt.clear(); //��������
				} else {
					//ʲôҲ����
				}
			}
			userIter++;
		}
		//��С����������������
		map<int,int> adjAreaTmp = iterArea2->adjArea;
		vector<PAIR> adjAreaVector;
		sortMapByValue(adjAreaTmp,adjAreaVector);
		//�ź���������������adjAreaVector��
		//�����������ȼ�˳�򣬲��뵽���ݱ� ANRT  
		infoList.clear();
		infoList.push_back(ChangeTypeTool::intToString(iterArea2->area.AId));
		for(int i=0;i<adjAreaVector.size()&&i<15;i++) { //������15��
			int adjCellId = adjAreaVector[i].first;
			//��֤˫��
			stringstream insertString;
			insertString<<"insert into ANRT (aid,aneicellid) values(";
			insertString<<iterArea2->area.AId;
			insertString<<",";
			insertString<<adjCellId;
			insertString<<");";
			//�ж�֮ǰ�Ƿ��Ѿ�����
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
	//�õ��л��ɹ���
	int succCnt = 0;
	int allCnt = 0;
	//�ȵõ���������xy,�����Ͳ����ܳ���ͼ
	double maxX = DBHelper::getGridMaxXY(1); 
	double maxY = DBHelper::getGridMaxXY(2);
	
	//ȡ�����е�С��,����С�����캯���о�������û�������
	vector<vector<string>> areaInfo = DBHelper::queryAreaInfoFromDB();
	vector<AreaANR> areaANRSet;
	vector<vector<string>>::iterator iter = areaInfo.begin();
	while(iter!=areaInfo.end()) {
		Area area = Area(*iter,1);
		AreaANR areaAnr = AreaANR(area,maxX,maxY,false);
		//ͬʱ�������б�ŵ��û���adjArea��
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
	��ʼ����ÿ��С��
	******************************************************/
	
	vector<AreaANR>::iterator iterArea2 = areaANRSet.begin();
	while(iterArea2!=areaANRSet.end()) {
		//AreaANR areaANR = *iterArea2;
		//ע���С���Ĵ�������ڶ�iterArea2
		//ȡ��С���е��û�
		vector<UserANR>::iterator userIter = iterArea2->users.begin();
		while(userIter!=iterArea2->users.end()) {
			//�Ե����û�
			//1.�û��Ƿ��˶����㹻��ʱ��
			int runTime = RUNTIME;
			while(runTime--) {
				//1.�û����˶�
				userIter->moveAndModify(userIter->x,userIter->y);
				if(userIter->x < -90 || userIter->y < -90) { //�����������Xy������0  �������Ϊ-100  ���ǵ�����  ����-90
					break; //���û�����
				}
				//2.�˶���ɺ���ͳ��Ȼ���ж��Ƿ������л�����
				int nowGid = DBHelper::getGidFromXY(userIter->x,userIter->y);
				//�ж��Ƿ��ƶ������ཻ����������ƶ����� ��ô�ٴ��ƶ� ����ƶ���10�� ��û�Ƴ�������ô�ͷ������û�

				userIter->gridId = nowGid; //����xy����gid
				//��ʼ����A3�¼����ж�
				float serverRSRP = DBHelper::getServerRSRP(iterArea2->area.AId,nowGid); //�˴���Ҫ����x,y����ƫ��float ����== �÷�Χ 
				map<int,double> adjinfo = userIter->getOtherAreaRsrp(nowGid);
				//��ȫ��ͳ�ƣ�Ȼ���ж��Ƿ�����л�
				//����adjinfo���жϸ�С����һ���Ƿ�Ҳ����
				//�жϸ�С���Ƿ�����A3����������ͳ��һ�ε�������
				map<int,double>::iterator iterAdjinfo = adjinfo.begin();
				map<int,double> acceptAdjInfo;
				while(iterAdjinfo!=adjinfo.end()) {
					//�ж��Ƿ�����A3�¼�
					bool flag = userIter->isA3Meet(serverRSRP,iterAdjinfo->second);
					if(flag) {
						acceptAdjInfo.insert(make_pair(iterAdjinfo->first,iterAdjinfo->second));
						//�ж�֮ǰ�Ƿ��Ѿ������ˣ������1 ������뼯�ϣ�������Ϊ1
						map<int,int>::iterator mapFind = userIter->areaCalCnt.find(iterAdjinfo->first);
						if(mapFind!=userIter->areaCalCnt.end()) { //��������ҵ�
							mapFind->second = mapFind->second + 1;
						} else {
							userIter->areaCalCnt.insert(make_pair(iterAdjinfo->first,1)); //�������С���ļ�����������û��Ӹ�С��Ϊ�������������ô���Ϊ1
						}
					}
					iterAdjinfo++;
				}
				//�������б���������м�ῼ�ǵ�������RSRP��
				//userIter->areaCalCnt����
				//acceptadjinfo���м����������RSRP
				//�˴�Ϊ�˷��㣬ֻ���Ǵ���
				map<int,int> areaCalCntTmp = userIter->areaCalCnt;
				vector<PAIR> areaCalCntVector;

				sortMapByValue(areaCalCntTmp,areaCalCntVector);
				//��vectorת��Ϊmap
				vectorToMap(areaCalCntVector,userIter->areaCalCnt);

				//�ж��Ƿ��л�
				//ȡ����õ��Ǹ���Ҳ���ǵ�һ��
				if(userIter->areaCalCnt.size()<1) {
					continue;
				}
				map<int,int>::iterator mapIter =  userIter->areaCalCnt.begin();
				int adjCellCalCnt = mapIter->second;
				if(adjCellCalCnt > TIMELASTCMP) { //�����л�
					int newAreaId = mapIter->first;
					userIter->aid = newAreaId; //����aid
					//���ж����С���Ƿ��Ƿ���С��������
					map<int,int>::iterator adjAreaIter = iterArea2->adjArea.find(newAreaId);
					if(adjAreaIter!=iterArea2->adjArea.end()) { //������
						succCnt = succCnt + 1;
						allCnt = allCnt + 1;
					} else {
						runTime = 0; //�û�������
						allCnt = allCnt + 1;
						break;
					}
					userIter->areaCalCnt.clear(); //��������
				} else {
					//ʲôҲ����
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
	process->MyProcessInfo="���Ժ��������������Ż�ǰ��ԱȽ��...";
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
	//��ͼ  ����õ�������
	
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
