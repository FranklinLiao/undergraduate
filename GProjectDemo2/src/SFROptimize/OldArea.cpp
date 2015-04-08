#include "stdafx.h"
#include "OldArea.h"

vector<User> OldArea::generateUser(int userCnt) {
	int areaId = this->AId;
	vector<User> users = DBHelper::getUser(areaId,userCnt); //�Ӹ�С�������������������ѡ��userCnt��������Ϊ���ѡ���˷ֲ��ڸ�С���е��û�
	this->users = users;
	return users;
}

vector<int> OldArea::getAdjAreaId() {
	int areaId = this->AId;
	vector<int> adjAreaId = DBHelper::getAdjAreaId(areaId);
	return adjAreaId;
}


int OldArea::getEdgeUserCnt() {
	int cnt = 0; //��Ե�û�������
	vector<User> users = this->users;
	//����ÿ���û��ж������Ļ��Ǳ�Ե
	vector<User>::iterator iter = users.begin();
	while(iter != users.end()) {
		User user = *iter;
		double userX = user.x;
		double userY = user.y;
		double userRsrp = user.rsrp;
		if(isEdgeUser(userX,userY,userRsrp)) { //�Ǳ�Ե�û�
			cnt++;
			//�޸ĸ�user��type����
			user.type = 2; //��Ե�û�
		}
		users.erase(iter); //�Ƴ�֮ǰ���Ǹ�user
		users.push_back(user); //���޸���type��user��ӽ���
		iter++;
	}
}

bool OldArea::isEdgeUser(double userX,double userY,double userRsrp) {
	bool flag = true;
	double dist = sqrt(pow((this->aX-userX),2)+pow((this->aY-userY),2));
	if(dist<distanceGate&&userRsrp>rsrpGate) { //�����û�����
		return false;
	}
}

void OldArea::getMainSubRb() {
	Rbs rbs = new Rbs(); //Ȼ����з���
	//����Ӧ�����ж����������Ǹ�RB����Ϊ��ԵС��ʹ��
	//1.�ȼ����1����Ե
	//���ز�
	mainRb = rbs.part1Rb;
	//���ز�
	subRb.insert(rbs.part2Rb.begin(),rbs.part2Rb.end());
	subRb.insert(rbs.part3Rb.begin(),rbs.part3Rb.end());
}

void OldArea::allocateRb() {
	//�ȷ������ز����ٷ��丱�ز�  ��δ��������㷨
	int edgeUserCnt = getEdgeUserCnt();
	//�ж����ز��Ƿ��� 
	if(edgeUserCnt*USERPERRB < mainRb.size()){  //����
		vector<User> users = users;
		vector<User>::iterator iter = users.begin();
		while(iter!=users.end()) {
			User user = *iter;
			if(2==user.type) { //�Ǳ�Ե�û�
				 //������õ�Rb
				map<int,int>::iterator iterMap = mainRb.begin();
				int cnt = 0;
				while(iterMap!=mainRb.end()) { 
					if(cnt<USERPERRB) { //��ÿ���û��������趨��Rb��
						if(0==iterMap->second) { //�����ûʹ��
							iter->rbId.push_back(iterMap->first);
							iterMap->second = 1;
							cnt++;
						}
						iterMap++;
					} else {
						break; 
					}
				}
				
			}
			iter++;
		}
	}
}