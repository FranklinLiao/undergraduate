#include "stdafx.h"
#include "OldArea.h"
/*
vector<OldArea> OldArea::getObjectSet(vector<vector<string>> param) {
	vector<OldArea> AreaSet;
	vector<vector<string>>::iterator iter = param.begin();
	while(iter!=param.end()) {
		OldArea area = OldArea(*iter++);
		AreaSet.push_back(area); 
	}
	return AreaSet;
}
*/
void OldArea::init() {
	getMainSubRb(); //�õ������ز��ķ��� ͨ��mainRbIndex��ѡ��ʹ���ĸ�Ƶ����Ϊ���ز�
	edgeUserIndex = 0;
	centerUserIndex = 0;
	mainRbOverFlag = false; //Ĭ�ϲ�����
	//sendPower = SENDPOWER;
	ratio = RATIO;
	generateUser(); //�����û�
	//rbCntReal = USERPERRB*(centerUsers.size() + edgeUsers.size()*1.0/ratio);  //�ܴ����Rb����
	getCenterEdgeUser(); //���ֱ�Ե�������û������ֱ�ͳ�Ƹ���
	setRbPower(); //�������ĺͱ�Ե�û������õ���Ե�û�ÿ��Rb�Ĺ���

}
vector<User> OldArea::generateUser() { 
	int areaId = this->area.AId;
	vector<User> users = DBHelper::getUser(areaId,this->userCnt); //�Ӹ�С�������������������ѡ��userCnt��������Ϊ���ѡ���˷ֲ��ڸ�С���е��û�
	this->users = users;
	return users;
}

vector<int> OldArea::getAdjAreaId() {  //�������಻�ܳ���6��
	int areaId = this->area.AId;
	vector<int> adjAreaId = DBHelper::getAdjAreaId(areaId);
	return adjAreaId;
}


//************************************  
// ��������: getCenterEdgeUser     
// ����˵���� ʶ�������Ե�û�   
// ����:Franklin     
// ���ڣ�2015/04/13     
// �� �� ֵ: void     
//************************************
void OldArea::getCenterEdgeUser() {
	vector<User> users = this->users;
	//����ÿ���û��ж������Ļ��Ǳ�Ե
	vector<User>::iterator iter = users.begin();
	while(iter != users.end()) {
		User user = *iter;
		double userX = user.x;
		double userY = user.y;
		double userRsrp = user.rsrp;
		if(isEdgeUser(userX,userY,userRsrp)) { //�Ǳ�Ե�û�
			(*iter).type = 2;
			edgeUsers.push_back(*iter);
		} else {
			(*iter).type = 1;
			centerUsers.push_back(*iter);
		}
		iter++;
	}
	edgeUserCnt = edgeUsers.size();
	centerUserCnt = centerUsers.size();
}


bool OldArea::isEdgeUser(double userX,double userY,double userRsrp) {
	double dist = sqrt(pow((this->area.aX-userX),2)+pow((this->area.aY-userY),2));
	if(dist<=distanceGate&&userRsrp>=rsrpGate) { //�����û�����
		return false;
	} else {
		return true;
	}
}

void OldArea::getMainSubRb() {
	Rbs rbs =  Rbs(mainRbIndex); //Ȼ����з���
	//����Ӧ�����ж����������Ǹ�RB����Ϊ��ԵС��ʹ��
	//�����ĸ�С�����ǽ�part1����Ϊ���ز� ��ͬС����1�᲻һ����Rbs������part1��һ����
	//���ز�
	mainRb = rbs.part1Rb;
	//���ز�

	subRb.insert(rbs.part2Rb.begin(),rbs.part2Rb.end());
	subRb.insert(rbs.part3Rb.begin(),rbs.part3Rb.end());
}

void OldArea::sortUser() {
	vector<User> users = users;
	//���յ����㷨��user��������
	//1.�ȿ�����ѯ�㷨
	//�ȶԱ�Ե�û���������
	int index = edgeUserIndex; //��ʼλ��
	//1.�Ƚ��������ӵ�edgeUsers��
	//2.��֮ǰ�������
	edgeUsers.clear();//������֮ǰ���û�
	vector<User>::iterator iter = users.begin()+index;
	while(iter != users.end()) {
		if(iter->type==2) {
			edgeUsers.insert(edgeUsers.end(),*iter);
		}
		iter++;
	}
	iter = users.begin();
	while(iter != users.begin()+index) {
		if(iter->type==2) {
			edgeUsers.insert(edgeUsers.end(),*iter);
		}
		iter++;
	}
	
	//�������û���������
	index = centerUserIndex;
	centerUsers.clear();
	iter = users.begin()+index;
	while(iter != users.end()) {
		if(iter->type==1) {
			centerUsers.insert(centerUsers.end(),*iter);
		}
		iter++;
	}
	iter = users.begin();
	while(iter != users.begin()+index) {
		if(iter->type==1) {
			centerUsers.insert(centerUsers.end(),*iter);
		}
		iter++;
	}
	
}

void OldArea::setRbPower() { //�˴���Ҫ������һ�£�����
	//��Ե�û�ʹ��mainRb ����ֻ����mainRb
	int edgeUserCnt = edgeUserCnt;
	int centerUserCnt = centerUserCnt;
	int edgeReal = 0;
	int centerReal = 0;
	if(edgeUserCnt*USERPERRB<=mainRb.size()) { //mainRb����
		//��Ե�û��������õ���Դ
		edgeReal = edgeUserCnt;
		if(centerUserCnt*USERPERRB<=subRb.size()) { //subRb����
			centerReal = centerUserCnt;
		} else { //subRb�����ã���ô��ʹ��һ���ֵ�mainRb
			int leftRb = mainRb.size() - edgeUserCnt * USERPERRB;
			int leftUser = centerUserCnt - subRb.size()/USERPERRB;
			//�ж�ʣ��mainRb�Ĺ�������
			if(leftRb >= leftUser*USERPERRB) { //ʣ��mainRb�Ĺ��ã�ʣ��������û������Է��䵽��Դ
				centerReal = centerUserCnt;
			} else { //��һ���������û�û����Դ
				centerReal = leftRb / USERPERRB + subRb.size()/USERPERRB;
			}
		}
	} else { //mainRb������
		edgeReal = mainRb.size()/USERPERRB;
		if(centerUserCnt*USERPERRB<=subRb.size()) { //���Ĺ���
			centerReal = centerUserCnt;
		} else { //���ĵĲ����ã����ڱ�Ե��Ҳ�����ã�mainRb��ʣ�࣬��ô��ֻ�ܷ���subRb�����������û���
			centerReal = subRb.size()/USERPERRB;
		}
	}
	edgePowerRatio = (edgeReal/ratio+centerReal)/ratio;
	/*
	if(centerUserCnt*USERPERRB < subRb.size()){ //��Ե����
		//ÿ���û�ʹ��Userperrb��rb����������ܵ��û���*ÿ���û�ʹ�õ�rb=ÿ�����ز�rb�ķ��书��  ��/ratio���͵õ����ز��ķ��书��
		//edgePower = (sendPower / USERPERRB*(edgeUserCnt/ratio+centerUserCnt))/ratio;
		//������˱�Ե�û�ռ���ܵĹ��ʵı���
		edgePowerRatio = 1.0/((edgeUserCnt/ratio+centerUserCnt)/ratio);
	} else { //������,�����û�ʹ�õ�rb����ࣨʹ��һЩmainRb)
		int mainRbLeft = mainRb.size() - edgeUserCnt*USERPERRB;
		int rbNeed = centerUserCnt*USERPERRB - subRb.size();
		if(mainRbLeft>=rbNeed) { //ʣ����rb�Ĺ���
			//edgePower = 1.0*(sendPower / USERPERRB*(edgeUserCnt/ratio+(rbNeed+centerUserCnt)))/ratio; 
			edgePowerRatio = 1.0 / ((edgeUserCnt/ratio+(rbNeed+centerUserCnt))/ratio); 
		} else {
			edgePowerRatio = 1.0/ ((edgeUserCnt/ratio+(mainRbLeft+centerUserCnt))/ratio); 
		}
	}
	*/
}
void OldArea::allocateRb() {
	mainRbOverFlag = false;
	//���Ƚ�User���е���
	sortUser();
	//�ȷ����Ե�û����ٷ��������û�
	//�ж����ز��Ƿ��� 
	if(edgeUserCnt*USERPERRB <= mainRb.size()){  //����
		mainRbOverFlag = true; //���ز�����
		vector<User>::iterator iter = edgeUsers.begin();
		map<int,int>::iterator iterMap = mainRb.begin();
		while(iter!=edgeUsers.end()) { //ÿ���û������Է��䵽
			//������õ�Rb
			int cnt = 0; //�����ÿ���û�
			while(iterMap!=mainRb.end()) {  //mainRb��ʣ�࣬break���Կ��Ʋ��������е�mainRb
				if(cnt<USERPERRB) { //��ÿ���û��������趨��Rb��  
					if(0==iterMap->second) { //�����ûʹ��
						iter->rbId.push_back(iterMap->first);
						iterMap->second = 1; //��ʾ�Ѿ�ʹ���� 
						cnt++;
					}
					iterMap++;
				} else {
					cnt = 0;
					break;  //�Ѿ���������û������Է�����һ���û�
				}
			}
			iter++;
		}
		edgeUserIndex = (iter-edgeUsers.begin())%edgeUsers.size(); //������ɺ󣬼�¼֮����ʼ������index
	} else { //���������  �ǾͰ�ȫ������������û�  ���º�����һ��
		map<int,int>::iterator iterMap = mainRb.begin();
		int cnt = 0;
		vector<User>::iterator iter = edgeUsers.begin();
		while(iterMap!=mainRb.end()) { 
			//ֻ�в����û����Է��䵽��Դ �����û�û��ͨ��while���б���
			//������õ�Rb
			if(cnt<USERPERRB) { //��ÿ���û��������趨��Rb��
				if(0==iterMap->second) { //�����ûʹ��
					iter->rbId.push_back(iterMap->first);
					iterMap->second = 1;
					cnt++;
				}
				iterMap++;
			} else { //������û��Ѿ���ɣ���ʼ������һ���û�
				cnt = 0;
				iter++; 
			}
		}
		edgeUserIndex = (iter-edgeUsers.begin())%edgeUsers.size(); //������ɺ󣬼�¼֮����ʼ������index  �����ز�

	}
	/*********************************************************
	*********************************************************/
	//���丱�ز�  �����û���������ز� �����õ͵ķ��书��
	if(centerUserCnt*USERPERRB<=subRb.size()) { //������ز�����
		vector<User>::iterator iter = centerUsers.begin();
		map<int,int>::iterator iterMap = subRb.begin();
		while(iter!=centerUsers.end()) {
			int cnt = 0;
			while(iterMap!=subRb.end()) {  //subRb��ʣ�࣬break���Կ��Ʋ��������е�subRb
				if(cnt<USERPERRB) { //��ÿ���û��������趨��Rb��
					if(0==iterMap->second) { //�����ûʹ��
						iter->rbId.push_back(iterMap->first);
						iterMap->second = 1;
						cnt++;
					}
					iterMap++;
				} else {
					cnt = 0;
					break;  //�Ѿ���������û������Է�����һ���û�
				}
			}
			iter++;
		}
		centerUserIndex = (iter-centerUsers.begin())%centerUsers.size(); //������ɺ󣬼�¼֮����ʼ������index
	} else { //���������  �ǾͰ�ȫ������������û�  ���º�����һ��
		map<int,int>::iterator iterMap = subRb.begin();
		int cnt = 0;
		vector<User>::iterator iter = centerUsers.begin();
		while(iterMap!=subRb.end()) { 
			//ֻ�в����û����Է��䵽��Դ �����û�û��ͨ��while���б���
			//������õ�Rb
			if(cnt<USERPERRB) { //��ÿ���û��������趨��Rb��
				if(0==iterMap->second) { //�����ûʹ��
					iter->rbId.push_back(iterMap->first);
					iterMap->second = 1;
					cnt++;
				}
				iterMap++;
			} else { //������û��Ѿ���ɣ���ʼ������һ���û�
				cnt = 0;
				iter++; 
			}
		}
		centerUserIndex = (iter-centerUsers.begin())%centerUsers.size(); //������ɺ󣬼�¼֮����ʼ������index  
		//�����ز��Ѿ�ȫ��������������û������濴�����ز����Ƿ��п����õ�
		if(mainRbOverFlag)  { //���ز����п��Է����
			//1.�ж�ʣ����Ƿ���
			int mainRbLeft = mainRb.size() - edgeUserCnt*USERPERRB;
			int rbNeed = centerUserCnt * USERPERRB - subRb.size();
			if(mainRbLeft >= rbNeed) { //���ʣ�µĹ���
				vector<User>::iterator userLeft = centerUsers.begin() + centerUserIndex; //��û�з�����û�������ʼ����
				map<int,int>::iterator rbLeft = mainRb.begin();  //����Ӧ�ô��ϴη������ʼ��ʼ�����ǲ������ôŪ ������ͷ��ʼ  ��Ϊʹ���˶����ǣ����Կ��Ա�֤ʹ�õĶ���û�����
				while(userLeft!=centerUsers.end()) { //�û��϶�����  �����û��϶���һֱ����
					cnt = 0;
					while(rbLeft!=mainRb.end()) {
						//������õ�Rb
						if(cnt<USERPERRB) { //��ÿ���û��������趨��Rb��
							if(0==rbLeft->second) { //�����ûʹ��
								userLeft->rbId.push_back(rbLeft->first);
								rbLeft->second = 1;
								cnt++;
							}
							rbLeft++; //������һ��rb
						} else { //������û��Ѿ����
							cnt = 0;
							break; 
						} 
					}
					userLeft++;   //��ʼ������һ���û�
				}
				centerUserIndex = (userLeft - centerUsers.begin()) % centerUsers.size(); //����һ�±��η�����ɵ������û���index
			} else {  //ʣ�����ز����������û���
				map<int,int>::iterator rbLeft = mainRb.begin(); //û�д��ϴη�������ĵط���ʼ ԭ��ͬ��
				int cnt = 0;
				vector<User>::iterator userLeft = centerUsers.begin()+centerUserIndex;
				while(rbLeft!=mainRb.end()) { 
					//ֻ�в����û����Է��䵽��Դ �����û�û��ͨ��while���б���
					//������õ�Rb
					if(cnt<USERPERRB) { //��ÿ���û��������趨��Rb��
						if(0==rbLeft->second) { //�����ûʹ��
							userLeft->rbId.push_back(rbLeft->first);
							rbLeft->second = 1;
							cnt++;
						}
						rbLeft++;
					} else { //������û��Ѿ���ɣ���ʼ������һ���û�
						cnt = 0;
						userLeft++; 
					}
				}
				centerUserIndex = (userLeft-centerUsers.begin())%centerUsers.size(); //������ɺ󣬼�¼֮����ʼ������index  
			}
		}
	}
}

double OldArea::getEdgeThroughPut() {
	vector<User>::iterator iter = edgeUsers.begin();
	double sumThroughPut=0.0;
	while(iter!=edgeUsers.end()) { //��������ÿ���û���������
		//1.�õ�sinr sinr���㶼����dbmΪ��λ ���Բ��ý��е�λ����  �õ���sinr��һ����ֵ
		//2.����������
		//�ȵõ��Լ��Ĺ���
		// 1.0/ratio * Userperrb���������û���RB����Ϊ��λ��������û����ܴ�����ռ�õ�RB��
		double percent = edgePowerRatio; //�õ����û���rb���ܵĴ�����ռ�õı���
		double selfPower = (iter->rsrp)*percent; //*1.0���ڲ���double������
		double noisePower = NOISE*(USERPERRB*RBFREQLEN);//һ��rb 180khz
		//������� �õ�ĳ���û��������ĸ���
		double otherPower = getAdjAreaPower(*iter); //�˴�Ӧ���Ǽ�������С��ʹ��ͬһRB�Ĺ���
		double sinr = selfPower / (otherPower + noisePower);  //����sinr
		double userThroughPut = powerToThroughPut(sinr);  //����������
		sumThroughPut += userThroughPut; //�ۼ��û���������
		iter++;
	}
	return sumThroughPut;
}

double OldArea::getCenterThroughPut() {
	vector<User>::iterator iter = centerUsers.begin();
	double sumThroughPut=0.0;
	while(iter!=centerUsers.end()) { //��������ÿ���û���������
		//1.�õ�sinr sinr���㶼����dbmΪ��λ ���Բ��ý��е�λ����  �õ���sinr��һ����ֵ
		//2.����������
		//�ȵõ��Լ��Ĺ���
		double percent = edgePowerRatio*ratio; //�õ����û���rb���ܵĴ�����ռ�õı���
		double selfPower = (iter->rsrp)*percent; //*1.0���ڲ���double������
		double noisePower = NOISE*(USERPERRB*RBFREQLEN);//һ��rb 180khz
		//������� �õ�ĳ���û��������ĸ���
		double otherPower = getAdjAreaPower(*iter); //�˴�Ӧ���Ǽ�������С��ʹ��ͬһRB�Ĺ���
		double sinr = selfPower / (otherPower + noisePower);  //����sinr
		double userThroughPut = powerToThroughPut(sinr);  //����������
		sumThroughPut += userThroughPut; //�ۼ��û���������
		iter++;
	}
	return sumThroughPut;
}

double OldArea::getAllThroughPut() {
	return getEdgeThroughPut()+getCenterThroughPut();
}

double OldArea::powerToThroughPut(double sinr) {
	//Blog(1+sinr) ��2Ϊ��  sinr�����ж�����  B:hzΪ��λ  C�ĵ�λ��bps
	double B = USERPERRB*180000.0;
	double throughPut = B*(1.0*log(1.0+sinr)/log(2.0));
	return throughPut;
}

double OldArea::getAdjAreaPower(User user) {
	//��������ȥ�������  �������Ӧ����ÿ��С�����Ѿ��ֲ������û����������RB
	double disturbPower = 0.0;
	int rbId = user.rbId.at(0); //ȡ����һ��rbId�ı��
	vector<OldArea> adjCell = adjArea;
	vector<OldArea>::iterator iter = adjCell.begin();
	while(iter!=adjCell.end()) { //��������
		//�ж�������Ե�û��ĸ��� ��Ȼ�Ա�Ե�û����ԣ������ı�Ե�û��޸��ţ�����Ϊ�˼򻯱�Ե�������û��ĳ��򣬾ͺ���һ����
		//������Ե�û��ĸ���
		vector<User>::iterator iterEdgeUser = iter->edgeUsers.begin();
		while(iterEdgeUser!=iter->edgeUsers.end()) { //���������ı�Ե�û�
			if(iterEdgeUser->rbId.at(0)==rbId) { //����С��Ҳ�����˸�RB
				//ȡ������С���ڸ��û��ĳ�ǿ��С*��rb��ռ���ʵı����͵õ�������С��ʹ�ø�RB�Ը��û��ĸ���
				//�����ڸ��û��ĳ�ǿ
				double powStrength = DBHelper::getAdjAreaGridStrength(iter->area.AId,user.gridId);
				//ȡ����Ӧrb��ǿ��ֵ
				double adjPower = powStrength*iter->edgePowerRatio;
				disturbPower += adjPower;
			}
			iterEdgeUser++;
		}
		//�ж����������û��ĸ���
		vector<User>::iterator iterCenterUser = iter->centerUsers.begin();
		while(iterCenterUser!=iter->centerUsers.end()) {
			if(iterCenterUser->rbId.at(0)==rbId) { //����С��Ҳ�����˸�RB
				//ȡ������С���ڸ��û��ĳ�ǿ��С*��rb��ռ���ʵı����͵õ�������С��ʹ�ø�RB�Ը��û��ĸ���
				double powStrength = DBHelper::getAdjAreaGridStrength(iter->area.AId,user.gridId);
				//ȡ����Ӧrb��ǿ��ֵ
				double adjPower = (iter->edgePowerRatio)*powStrength*ratio;
				disturbPower += adjPower;
			}
			iterCenterUser++;
		}
		iter++;
	}
	return disturbPower;
}