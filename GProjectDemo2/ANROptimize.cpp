#include "stdafx.h"
#include "ANROptimize.h"
void ANROptimize::snrOptimize() {
	
	//�ȵõ���������xy,�����Ͳ����ܳ���ͼ
	double maxX = DBHelper::getGridMaxXY(1); 
	double maxY = DBHelper::getGridMaxXY(2);
	
	//ȡ�����е�С��,����С�����캯���о�������û�������
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
				//2.�û��ж��Ƿ�Ҫ�������
				//3.�û��ƶ�
				int nowGid = DBHelper::getGidFromXY(userIter->x,userIter->y);
				float serverRSRP = DBHelper::getServerRSRP(iterArea2->area.AId,nowGid); //�˴���Ҫ����x,y����ƫ��float ����== �÷�Χ 
				//vector<map<int,float>> adjinfo = ;//

			}
			userIter++;
		}
		iterArea2++;
	}
	
}