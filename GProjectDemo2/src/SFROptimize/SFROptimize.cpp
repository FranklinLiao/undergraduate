#include "stdafx.h"
#include "SFROptimize.h"
bool SFROptimize::optimizeOld() {  //ע��鿴һ�±�־���ر��Ƕ�η�������Щ��־�Ƿ��Ѿ������ˣ�����
	bool flag = true;
	//���㾭���㷨
	/***********************************************
	�����ݿ���ȡ�����е�С��,��ƴװ��OldArea
	*************************************************/
	vector<vector<string>> areaInfo = DBHelper::queryAreaInfoFromDB();
	vector<OldArea> oldAreaSet;
	vector<vector<string>>::iterator iter = areaInfo.begin();
	while(iter!=areaInfo.end()) {
		Area area = Area(*iter);
		OldArea oldArea = OldArea(area);
		oldAreaSet.push_back(oldArea);
		iter++;
	}
	/****************************************************
	��������С������С�������������Ϣ
	******************************************************/
	vector<OldArea>::iterator iterArea12 = oldAreaSet.begin();
	while(iterArea12!=oldAreaSet.end()) {
		iterArea12->adjAreaId = DBHelper::getAdjAreaId(iterArea12->area.AId);
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
					if(!((adjMainRbIndex > 0) && (adjMainRbIndex <= RBPARTS))) { ////�ж��Ƿ���Ч,Ҳ�����ж��Ƿ��Ѿ�������MainRbIndex
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
		for(int mainRbIndex = 1;mainRbIndex<=RBPARTS;mainRbIndex++) {
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
			iterArea0->mainRbIndex = rand()%RBPARTS + 1; //rand()%RBPARTS  0 ~ RBPARTS-1
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
		
		/****************************************************
		�ȵõ�����С���������ļ��ϣ����ڼ�����ţ�Ȼ����������� ȡ��С���������� ���Բ�����һ�� 20150425
		******************************************************/
		/*
		vector<OldArea>::iterator iterArea4 = oldAreaSet.begin();
		while(iterArea4!=oldAreaSet.begin()) {  //����ÿһ��С��
			//�������С����������id
			vector<int>::iterator iter = iterArea4->adjAreaId.begin(); //�ҵ����С��������
			while(iter!=iterArea4->adjAreaId.end()) {
				int id = *iter; //�õ�ĳ��������Id
				//�ҵ���id��С�������������뵽��С��������������
				vector<OldArea>::iterator iterIn = oldAreaSet.begin();
				while(iterIn!=oldAreaSet.end()) {
					if(iterIn->area.AId==id) { //��С���������ҵ����������
						(*iterArea4).adjArea.push_back(*iterIn);
					}
					iterIn++;
				}
				iter++;
			}
			iterArea4++;
		}
		*/
		vector<OldArea>::iterator iterArea5 = oldAreaSet.begin();
		while(iterArea5!=oldAreaSet.end()) {
			double edgeOutPut = iterArea5->getEdgeThroughPut();
			double sumOutput = iterArea5->getAllThroughPut();
			sumAllOutput += sumOutput;
			sumEdgeOutput += edgeOutPut;
			iterArea5++;
		}
	}
	avgAllOutput = sumAllOutput / SIMCNT;
	avgEdageOutput = sumEdgeOutput / SIMCNT;
	cout<<"old avgall"<<avgAllOutput;
	cout<<"old avgedge"<<avgEdageOutput;
	return flag;
}

bool SFROptimize::optimizeNew() {  //ע��鿴һ�±�־���ر��Ƕ�η�������Щ��־�Ƿ��Ѿ������ˣ�����
	bool flag = true;
	//1.�ȼ���Ľ�����㷨
	/***********************************************
	�����ݿ���ȡ�����е�С��
	*************************************************/
	vector<vector<string>> areaInfo = DBHelper::queryAreaInfoFromDB();
	vector<NewArea> newAreaSet;
	vector<vector<string>>::iterator iter = areaInfo.begin();
	while(iter!=areaInfo.end()) {
		Area area = Area(*iter++);
		NewArea newArea = NewArea(area);
		newAreaSet.push_back(newArea);
	}
	/****************************************************
	��������С������С�������������Ϣ
	******************************************************/
	vector<NewArea>::iterator iterArea12 = newAreaSet.begin();
	while(iterArea12!=newAreaSet.end()) {
		iterArea12->adjAreaId = DBHelper::getAdjAreaId(iterArea12->area.AId);
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
					if(!((adjMainRbIndex > 0) && (adjMainRbIndex <= RBPARTS))) { ////�ж��Ƿ���Ч 
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
		for(int mainRbIndex = 1;mainRbIndex<=RBPARTS;mainRbIndex++) {
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
			iterArea0->mainRbIndex = rand()%RBPARTS + 1; //rand()%RBPARTS  0 ~ RBPARTS-1
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
			double sumOutput = iterArea5->getAllThroughPut();
			sumAllOutput += sumOutput;
			sumEdgeOutput += edgeOutPut;
			iterArea5++;
		}
	}
	avgAllOutput = sumAllOutput / SIMCNT;
	avgEdageOutput = sumEdgeOutput / SIMCNT;
	cout<<"new avgall"<<avgAllOutput;
	cout<<"new avgedge"<<avgEdageOutput;
	return flag;
}