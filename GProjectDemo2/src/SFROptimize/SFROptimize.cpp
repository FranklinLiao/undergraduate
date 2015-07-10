#include "stdafx.h"
#include "SFROptimize.h"
string SFROptimize::optimizeOld(int simUserCnt) {  //ע��鿴һ�±�־���ر��Ƕ�η�������Щ��־�Ƿ��Ѿ������ˣ�����
	bool flag = true;
	//���㾭���㷨
	/***********************************************
	�����ݿ���ȡ�����е�С��,��ƴװ��OldArea
	*************************************************/
	vector<vector<string>> areaInfo = DBHelper::queryAreaInfoFromDB();
	vector<OldArea> oldAreaSet;
	vector<vector<string>>::iterator iter = areaInfo.begin();
	int i = 1;
	while(iter!=areaInfo.end()) {
		Area area = Area(*iter,1); //1������ʶ��SFR��Area
		
		//���ڿƼ����ĵĽ��  ֮��Ҫɾ��
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
	��������С������С�������������Ϣ
	******************************************************/
	vector<OldArea>::iterator iterArea12 = oldAreaSet.begin();
	while(iterArea12!=oldAreaSet.end()) {
		string tableName = "ANRT";
		iterArea12->adjAreaId = DBHelper::getAdjAreaId(tableName,iterArea12->area.AId);
		/*
		vector<int>::iterator iterArea13 = iterArea12->adjAreaId.begin();
		while(iterArea13!=iterArea12->adjAreaId.end()) { //����id���ҵ�����
			vector<OldArea>::iterator iterArea14 = oldAreaSet.begin();
			while(iterArea14!=oldAreaSet.end()) {
				if(iterArea14->area.AId==*iterArea13) { //�ҵ��˶�Ӧ��С������ô���Ϊ����
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
	��������С������С������mainRBIndex
	******************************************************/
	vector<OldArea>::iterator iterArea0 = oldAreaSet.begin();
	while(iterArea0!=oldAreaSet.end()) {
		OldArea oldArea = *iterArea0;
		vector<int> adjArea = oldArea.getAdjAreaId(); //�õ�ĳ��С��������id
		/****************************************************
		//����������Ϣ��ȷ��MainRbIndex 1 2 3
		//�����������ж�����ʹ����ʲôIndex
		//�õ�����ʹ�õ�MainRbIndex����������ʹ�õ�MainRbIndex��ŵ�adjMainRbIndexSet��
		******************************************************/
		vector<int>::iterator iterAdjAreaId = adjArea.begin();
		vector<int> adjMainRbIndexSet;
		while(iterAdjAreaId!=adjArea.end()) { //�������С��������id
			int adjMainRbIndex = 0;
			vector<OldArea>::iterator iterTmp = oldAreaSet.begin();
			while(iterTmp!=oldAreaSet.end()) { //����С�����ϣ�ͨ��������Id���ҵ���Ӧ������
				if(iterTmp->area.AId==*iterAdjAreaId) {
					adjMainRbIndex = iterTmp->mainRbIndex; //ȡ����������mainRbIndex
					if(!((adjMainRbIndex > 0) && (adjMainRbIndex <= OLDRBPARTS))) { ////�ж��Ƿ���Ч,Ҳ�����ж��Ƿ��Ѿ�������MainRbIndex
						adjMainRbIndex = 0; //֮ǰδ����͸�ֵΪ0
					} else {
						adjMainRbIndexSet.push_back(adjMainRbIndex); //�����Ч����ô�Ͱ�����ʹ�õ�mainRbIndex��ŵ�set��
					}
					break; //����ҵ��ˣ���ô���������Сѭ������ʼ������һ������iterAdjAreaId
				}
				iterTmp++;  //��С��iterTmp���Ǳ�С�����������ʹ�С�������У�������һ��С��
			}
			
			iterAdjAreaId++; //�Ѿ��ҵ��˶�Ӧ������mainRBIndex,����������һ��������mainRbIndex
		}
		//�ҵ�������ʹ�õ�mainRbIndex���������mainRBIndexSet��,��ʼ�������set�鿴����ЩmainRbIndex������
		for(int mainRbIndex = 1;mainRbIndex<=OLDRBPARTS;mainRbIndex++) {
			vector<int>::iterator iterRBIndex = adjMainRbIndexSet.begin();
			bool isUsed = false; //ÿһ���ж���mainRbIndexʱ����Ҫ��λ
			while(iterRBIndex!=adjMainRbIndexSet.end()) {
				if(*iterRBIndex == mainRbIndex) { //�жϵ�ǰ�����Ƿ�ʹ���˸�Index:mainRbIndex
					isUsed = true;
					break; //����о��˳����ѭ���� �鿴��һ��mainRbIndex
				}
				iterRBIndex++; //��ǰ����û��ʹ�ã������ж���һ�������Ƿ����˸�Index
			}
			if(!isUsed) { //�����ǰ��mainRbIndex��û������ʹ�ù�����ô��С����ʹ�����mainRbIndex
				iterArea0->mainRbIndex = mainRbIndex;
				break; //����forѭ��
			}
		}
		if(iterArea0->mainRbIndex==0) { //������С��û�з����ϣ��������������е�mainRbIndex
			//1.�鿴���������ķ��������Ƹ���  
			//2.�������
			//�˴���������������
			srand( (unsigned)time(NULL)); //��������
			iterArea0->mainRbIndex = rand()%OLDRBPARTS + 1; //rand()%RBPARTS  0 ~ RBPARTS-1
		}
		iterArea0++; //��С����mainRbIndex������������Է�����һ��С����
	}
	/****************************************************
	���г�ʼ������ �������������ز���Դ����������û���ͳ�Ʊ�Ե�������û�������RB�Ĺ���
	******************************************************/
	vector<OldArea>::iterator iterArea2 = oldAreaSet.begin();
	while(iterArea2!=oldAreaSet.end()) {
		iterArea2->init();
		iterArea2++;
	}
	/****************************************************
	ͨ�������㷨��ÿ��С���û�����RB���˴�Ӧ���Ƿ���100�Σ�ÿ�ζ�ͳ��������
	******************************************************/
	double sumAllOutput=0; //100���ۼӵ�������
	double avgAllOutput=0; //ƽ��������
	double sumEdgeOutput=0;
	double avgEdageOutput=0;
	for(int calcnt =0;calcnt<SIMCNT;calcnt++) {
		//����С������С���е��û�����Rb
		vector<OldArea>::iterator iterArea3 = oldAreaSet.begin();
		while(iterArea3!=oldAreaSet.end()) {
			iterArea3->allocateRb(); //�����㷨��allocateRb��
			iterArea3++;
		}
		
		//�ȷ���RB��Ȼ�����������Ϣ  ������м���sinr
		vector<OldArea>::iterator iterArea12 = oldAreaSet.begin();
		while(iterArea12!=oldAreaSet.end()) {
			//iterArea12->adjAreaId = DBHelper::getAdjAreaId(iterArea12->area.AId);
			iterArea12->adjArea.clear(); //������ϴε�
			vector<int>::iterator iterArea13 = iterArea12->adjAreaId.begin();
			while(iterArea13!=iterArea12->adjAreaId.end()) { //����id���ҵ�����
				vector<OldArea>::iterator iterArea14 = oldAreaSet.begin();
				while(iterArea14!=oldAreaSet.end()) {
					if(iterArea14->area.AId==*iterArea13) { //�ҵ��˶�Ӧ��С������ô���Ϊ����
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
			iterArea5->edgeThroughput += edgeOutPut; //�洢ÿ�εı�Ե������
			double sumOutput = iterArea5->getCenterThroughPut()+edgeOutPut;
			sumAllOutput += 1.0*sumOutput/1000;  //kbs
			sumEdgeOutput += 1.0*edgeOutPut/1000; //kbs
			//TRACE("the oldedgeput :%s\n",edgeOutPut);
			//TRACE("the oldsumput :%s\n",sumOutput);
			iterArea5++;
		}
	}
	//�������ƽ��
	vector<OldArea>::iterator iterArea5 = oldAreaSet.begin();
	while(iterArea5!=oldAreaSet.end()) {
		double edgeOutPut = iterArea5->edgeThroughput;
		iterArea5->edgeThroughput = 1.0*edgeOutPut / SIMCNT; //�洢ÿ�εı�Ե������
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

string SFROptimize::optimizeNew(int simUserCnt) {  //ע��鿴һ�±�־���ر��Ƕ�η�������Щ��־�Ƿ��Ѿ������ˣ�����
	bool flag = true;
	//1.�ȼ���Ľ�����㷨
	/***********************************************
	�����ݿ���ȡ�����е�С��
	*************************************************/
	vector<vector<string>> areaInfo = DBHelper::queryAreaInfoFromDB();
	vector<NewArea> newAreaSet;
	vector<vector<string>>::iterator iter = areaInfo.begin();
	//int i = 1;
	while(iter!=areaInfo.end()) {
		Area area = Area(*iter++,1);
		//���ڿƼ����ĵĽ��  ֮��Ҫɾ��
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
	��������С������С�������������Ϣ
	******************************************************/
	vector<NewArea>::iterator iterArea12 = newAreaSet.begin();
	while(iterArea12!=newAreaSet.end()) {
		string tableName = "ANRT";
		iterArea12->adjAreaId = DBHelper::getAdjAreaId(tableName,iterArea12->area.AId);
		/*
		vector<int>::iterator iterArea13 = iterArea12->adjAreaId.begin();
		while(iterArea13!=iterArea12->adjAreaId.end()) { //����id���ҵ�����
			vector<NewArea>::iterator iterArea14 = newAreaSet.begin();
			while(iterArea14!=newAreaSet.end()) {
				if(iterArea14->area.AId==*iterArea13) { //�ҵ��˶�Ӧ��С������ô���Ϊ����
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
	��С������mainRBIndex
	******************************************************/
	vector<NewArea>::iterator iterArea0 = newAreaSet.begin();
	while(iterArea0!=newAreaSet.end()) {
		NewArea newArea = *iterArea0;
		vector<int> adjArea = newArea.getAdjAreaId();
		/****************************************************
		//����������Ϣ��ȷ��MainRbIndex 1 2 3
		//�����������ж�����ʹ����ʲôIndex
		����mainRbIndex
		******************************************************/
		vector<int>::iterator iterAdjAreaId = adjArea.begin();
		vector<int> adjMainRbIndexSet;
		while(iterAdjAreaId!=adjArea.end()) { //�������С��������
			int adjMainRbIndex = 0;
			vector<NewArea>::iterator iterTmp = newAreaSet.begin();
			while(iterTmp!=newAreaSet.end()) { //�ҵ���Ӧ������
				if(iterTmp->area.AId==*iterAdjAreaId) {
					adjMainRbIndex = iterTmp->mainRbIndex;
					if(!((adjMainRbIndex > 0) && (adjMainRbIndex <= NEWRBPARTS))) { ////�ж��Ƿ���Ч 
						adjMainRbIndex = 0; //֮ǰδ����͸�ֵΪ0
					} else {
						adjMainRbIndexSet.push_back(adjMainRbIndex);
					}
					break;
				}
				iterTmp++;
			}
			//�ҵ��˶�Ӧ������RBIndex
			iterAdjAreaId++;
		}
		//�ҵ�������ʹ�õ�mainRbIndex���������mainRBIndexSet��
		for(int mainRbIndex = 1;mainRbIndex<=NEWRBPARTS;mainRbIndex++) {
			vector<int>::iterator iterRBIndex = adjMainRbIndexSet.begin();
			bool isUsed = false;
			while(iterRBIndex!=adjMainRbIndexSet.end()) {
				if(*iterRBIndex == mainRbIndex) {
					isUsed = true;
					break; //����о��˳�
				}
				iterRBIndex++;
			}
			if(!isUsed) { //�����һ��û��ʹ��
				iterArea0->mainRbIndex = mainRbIndex;
				break; //����forѭ��
			}
		}
		if(iterArea0->mainRbIndex==0) { //������С��û�з����ϣ��������������е�mainRbIndex
			//1.�鿴���������ķ��������Ƹ���  
			//2.�������
			//�˴���������������
			srand( (unsigned)time(NULL)); //��������
			iterArea0->mainRbIndex = rand()%NEWRBPARTS + 1; //rand()%RBPARTS  0 ~ RBPARTS-1
		}
		iterArea0++; //��С����mainRbIndex������������Է�����һ��С����
	//	iterArea0++;
	}
	/****************************************************
	���г�ʼ������ �������������ز���Դ����������û���ͳ�Ʊ�Ե�������û�������RB�Ĺ���
	******************************************************/
	vector<NewArea>::iterator iterArea2 = newAreaSet.begin();
	while(iterArea2!=newAreaSet.end()) {
		iterArea2->init();
		iterArea2++;
	}
	/****************************************************
	ͨ�������㷨��ÿ��С���û�����RB���˴�Ӧ���Ƿ���100�Σ�ÿ�ζ�ͳ��������
	******************************************************/
	double sumAllOutput=0; //100���ۼӵ�������
	double avgAllOutput=0; //ƽ��������
	double sumEdgeOutput=0;
	double avgEdageOutput=0;
	for(int calcnt =0;calcnt<SIMCNT;calcnt++) {
		vector<NewArea>::iterator iterArea3 = newAreaSet.begin();
		while(iterArea3!=newAreaSet.end()) {
			iterArea3->allocateRb(); //�����㷨��allocateRb��
			iterArea3++;
		}
			/****************************************************
	��������С������С�������������Ϣ
	******************************************************/
	vector<NewArea>::iterator iterArea12 = newAreaSet.begin();
	while(iterArea12!=newAreaSet.end()) {
		//iterArea12->adjAreaId = DBHelper::getAdjAreaId(iterArea12->area.AId);
		
		vector<int>::iterator iterArea13 = iterArea12->adjAreaId.begin();
		while(iterArea13!=iterArea12->adjAreaId.end()) { //����id���ҵ�����
			vector<NewArea>::iterator iterArea14 = newAreaSet.begin();
			while(iterArea14!=newAreaSet.end()) {
				if(iterArea14->area.AId==*iterArea13) { //�ҵ��˶�Ӧ��С������ô���Ϊ����
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
		�ȵõ����С���������ļ��ϣ����ڼ�����ţ�Ȼ�������������  ȡ��С���������� ���Բ�����һ�� 20150425
		******************************************************/
		/*
		vector<NewArea>::iterator iterArea4 = newAreaSet.begin();
		while(iterArea4!=newAreaSet.begin()) {  //����ÿһ��С��
			//�������С����������id
			vector<int>::iterator iter = iterArea4->adjAreaId.begin();
			while(iter!=iterArea4->adjAreaId.end()) {
				int id = *iter;
				//�ҵ���id��С�������������뵽��С��������������
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
			iterArea5->edgeThroughput += edgeOutPut; //�洢ÿ�εı�Ե������
			double sumOutput = iterArea5->getCenterThroughPut()+edgeOutPut;
			sumAllOutput += 1.0*sumOutput/1000; //kbs
			sumEdgeOutput += 1.0*edgeOutPut/1000; //kbs
			iterArea5++;
		}
	}
	//����100�κ� ��100�εĽ����ƽ��
	vector<NewArea>::iterator iterArea5 = newAreaSet.begin();
	while(iterArea5!=newAreaSet.end()) {
		double edgeOutPut = iterArea5->edgeThroughput;
		iterArea5->edgeThroughput = 1.0*edgeOutPut / SIMCNT; //�洢ÿ�εı�Ե������
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
	
	//����õ���������
	double edgeOldSfrArray[9] = {0,0.314,1.141,1.718,2.150,2.641,2.965,3.573,4.032};  
	vector<double> edgeOldSfrVector(edgeOldSfrArray,edgeOldSfrArray+9);
	double edgeNewSfrArray[9] = {0,0.366,0.919,1.824,2.511,2.857,3.243,3.873,4.549};  
	vector<double> edgeNewSfrVector(edgeNewSfrArray,edgeNewSfrArray+9);
	double allOldSfrArray[9] = {0,5.918,12.804,19.302,20.451,21.639,23.550,24.375,24.917};  
	vector<double> allOldSfrVector(allOldSfrArray,allOldSfrArray+9);
	double allNewSfrArray[9] = {0,5.825,12.609,18.750,19.947,21.019,23.093,23.939,24.426};  
	vector<double> allNewSfrVector(allNewSfrArray,allNewSfrArray+9);

	//Ϊ�˷�����ʾ��ʹ����֮ǰ���������
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
