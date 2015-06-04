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
				//1.�û����˶�
				userIter->move(userIter->x,userIter->y);
				//2.�˶���ɺ���ͳ��Ȼ���ж��Ƿ������л�����
				int nowGid = DBHelper::getGidFromXY(userIter->x,userIter->y);
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
				map<int,int>::iterator mapIter =  userIter->areaCalCnt.begin();
				int adjCellCalCnt = mapIter->second;
				if(adjCellCalCnt > TIMELAST) { //�����л�
					userIter->areaCalCnt.clear(); //��������
					int newAreaId = mapIter->first;
					userIter->aid = newAreaId; //����aid
					//���ж����С���Ƿ��Ƿ���С��������
					map<int,int>::iterator adjAreaIter = iterArea2->adjArea.find(newAreaId);
					if(adjAreaIter!=iterArea2->adjArea.end()) { //������
						adjAreaIter->second = adjAreaIter->second + 1;
					} else  {
						iterArea2->adjArea.insert(make_pair(newAreaId,1)); //����С������Ϊ������������Ϊ1
					}
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
		for(int i=0;i<adjAreaVector.size();i++) {
			int adjCellId = adjAreaVector[i].first;
			stringstream insertString;
			insertString<<"insert into ANRT (aid,aneicellid) values(";
			insertString<<iterArea2->area.AId;
			insertString<<",";
			insertString<<adjCellId;
			insertString<<");";
			DBHelper::insertStringInfo(insertString.str());
		}
		iterArea2++;
	}
	
}

