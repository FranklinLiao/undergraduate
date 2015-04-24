#include "stdafx.h"
#include "NewArea.h"
//����init�ķ���
void NewArea::init() {
	getMainSubRb(); //�õ������ز��ķ��� ͨ��mainRbIndex��ѡ��ʹ���ĸ�Ƶ����Ϊ���ز�
	edgeUserIndex = 0;
	centerUserIndex = 0;
	mainRbOverFlag = false; //Ĭ�ϲ�����
	optRbOverFlag = false;
	//sendPower = SENDPOWER;
	ratio = RATIO;
	generateUser(); //�����û�
	//rbCntReal = USERPERRB*(centerUsers.size() + edgeUsers.size()*1.0/ratio);  //�ܴ����Rb����
	getCenterEdgeUser(); //���ֱ�Ե�������û������ֱ�ͳ�Ƹ���
	setRbPower(); //�������ĺͱ�Ե�û������õ���Ե�û�ÿ��Rb�Ĺ���
}

void NewArea::getMainSubRb() {
	NewRbs newRbs =  NewRbs(mainRbIndex); //Ȼ����з���
	//����Ӧ�����ж����������Ǹ�RB����Ϊ��ԵС��ʹ��
	//�����ĸ�С�����ǽ�part1����Ϊ���ز� ��ͬС����1�᲻һ����Rbs������part1��һ����
	//���ز�
	mainRb = newRbs.part1Rb;
	//���ز�
	subRb.insert(newRbs.part2Rb.begin(),newRbs.part2Rb.end());
	subRb.insert(newRbs.part3Rb.begin(),newRbs.part3Rb.end());
	//optRb
	optRb = newRbs.part4Rb;

}

void NewArea::setRbPower() {
	//��Ե�û�ʹ��mainRb ����ֻ����mainRb
	int edgeUserCnt = this->edgeUserCnt;
	int centerUserCnt = this->userCnt - this->edgeUserCnt;
	int edgeReal = 0;
	int centerReal = 0;
	if(edgeUserCnt*USERPERRB<=mainRb.size()) { //��Ե�û����ã����Ը�һ���ָ������û�
		//��Ե�û��������õ���Դ
		edgeReal = edgeUserCnt;
		if(centerUserCnt*USERPERRB<=subRb.size()) { //���Ĺ���
			centerReal = centerUserCnt;
		} else { //���ĵĲ����ã���ô��ʹ��һ���ֵ�mainRb
			int leftRb = mainRb.size() - edgeUserCnt * USERPERRB;
			int leftUser = centerUserCnt - subRb.size()/USERPERRB;
			//�ж�ʣ��mainRb�Ĺ�������
			if(leftRb >= leftUser*USERPERRB) { //ʣ��Ĺ��ã�ʣ��������û������Է��䵽��Դ
				centerReal = centerUserCnt;
			} else { //��һ���������û�û�з��䵽mainRb����ô����optRb
				leftUser = centerUserCnt - subRb.size()/USERPERRB - leftRb / USERPERRB;
				if(optRb.size() >= leftUser*USERPERRB) { //optrb����
					centerReal = centerUserCnt; 
				} else { //optrbҲ������
					centerReal = subRb.size()/USERPERRB + leftRb /USERPERRB + optRb.size()/USERPERRB;
				}
			}
		}
	} else { //��Ե�û�������
		int leftEdgeUser = edgeUserCnt - mainRb.size()/USERPERRB;
		if(optRb.size() >= leftEdgeUser*USERPERRB) { //optrb����Ե�û���
			edgeReal = edgeUserCnt;
			if(centerUserCnt*USERPERRB<=subRb.size()) { //���������û������Ĺ���
				centerReal = centerUserCnt;
			} else { //���ĵĲ����ã����ڱ�Ե���Ѿ��������ˣ�mainRbû���ˣ����Դ�optRb����
				int optRbLeft = optRb.size() - leftEdgeUser*USERPERRB;
				int centerUserLeft = centerUserCnt - subRb.size()/USERPERRB; 
				if(optRbLeft >= centerUserLeft*USERPERRB) { //���optLeft����Ե�û���
					centerReal = centerUserCnt;
				} else { //
					centerReal = subRb.size()/USERPERRB+optRbLeft/USERPERRB;
				}
				//centerReal = subRb.size()/USERPERRB;
			}
		} else { //optRb�����������û���
			edgeReal = mainRb.size()/USERPERRB + optRb.size()/USERPERRB;
			if(centerUserCnt*USERPERRB<=subRb.size()) { //���Ĺ���
				centerReal = centerUserCnt;
			} else { //���ĵĲ����ã����ڱ�Ե��Ҳ�����ã�mainRb��ʣ��,optRbҲûʣ�࣬��ô��ֻ�ܷ���subRb�����������û���
				centerReal = subRb.size()/USERPERRB;
			}
		}
		
	}

	//edgePowerRatio = (edgeReal/ratio+centerReal)/ratio;
	//��ʦ�ֽ���Ӧ����
	edgePowerRatio = 1.0*USERPERRB/RBCNT/ratio; //��Ϊ�е�RB���Ƿ����˹��ʣ�����û���ã�
}
void NewArea::sortUser() {
	vector<User> users = this->users;
	//���յ����㷨��user��������
	//1.�ȿ�����ѯ�㷨
	//�ȶԱ�Ե�û���������
	int index = edgeUserIndex; //��ʼλ��
	//1.�Ƚ��������ӵ�edgeUsers��
	//2.��֮ǰ�������
	vector<User> temp = edgeUsers;
	edgeUsers.clear();//������֮ǰ���û�
	vector<User>::iterator iter = temp.begin()+index;
	while(iter != temp.end()) {
		if(iter->type==2) {
			edgeUsers.push_back(*iter);
		}
		iter++;
	}
	iter = temp.begin();
	while(iter != temp.begin()+index) {
		if(iter->type==2) {
			edgeUsers.push_back(*iter);
		}
		iter++;
	}

	//�������û���������
	index = centerUserIndex;
	temp = centerUsers;
	centerUsers.clear();
	iter = temp.begin()+index;
	while(iter != temp.end()) {
		if(iter->type==1) {
			centerUsers.push_back(*iter);
		}
		iter++;
	}
	iter = temp.begin();
	while(iter != temp.begin()+index) {
		if(iter->type==1) {
			centerUsers.push_back(*iter);
		}
		iter++;
	}

}

void NewArea::allocateRb() { //δ���
	mainRbOverFlag = false;
	optRbOverFlag = false;
	int optRbUsed = 0;
	//���Ƚ�User���е���
	sortUser();
	//�ȷ����Ե�û����ٷ��������û� 
	//�ж����ز��Ƿ��� 
	if(edgeUserCnt*USERPERRB <= mainRb.size()){  //����
		mainRbOverFlag = true; //���ز�����
		optRbOverFlag = true;
		vector<User>::iterator iter = edgeUsers.begin();
		map<int,int>::iterator iterMap = mainRb.begin();
		while(iter!=edgeUsers.end()) { //ÿ���û������Է��䵽
			//������õ�Rb
			int cnt = 0;
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
		
		//Ȼ���ж�optRb�Ƿ���
		int edgeUserLeft = edgeUserCnt - mainRb.size()/USERPERRB;
		if(optRb.size()>=edgeUserLeft*USERPERRB) { //optRb����
			optRbOverFlag = true;
			vector<User>::iterator edgeUserLeftIter = edgeUsers.begin()+edgeUserIndex;
			map<int,int>::iterator optRbIter = optRb.begin();
			while(edgeUserLeftIter!=edgeUsers.end()) {
				int cnt =0;
				while(optRbIter!=optRb.end()) {
					if(cnt<USERPERRB) { //��ÿ���û��������趨��Rb��  
						if(0==optRbIter->second) { //�����ûʹ��
							edgeUserLeftIter->rbId.push_back(optRbIter->first);
							optRbIter->second = 1; //��ʾ�Ѿ�ʹ���� 
							cnt++;
						}
						optRbIter++;
					} else {
						cnt = 0;
						break;  //�Ѿ���������û������Է�����һ���û�
					}
				}
				edgeUserLeftIter++;
			}
			optRbUsed = USERPERRB*(edgeUserCnt-mainRb.size()/USERPERRB);
			edgeUserIndex = (edgeUserLeftIter-edgeUsers.begin())%edgeUsers.size(); //������ɺ󣬼�¼֮����ʼ������index  ��opt�ز�
		} else { //optRb������
			vector<User>::iterator edgeUserLeftIter = edgeUsers.begin()+edgeUserIndex;
			map<int,int>::iterator optRbIter = optRb.begin();
			int cnt =0;
			while(optRbIter!=optRb.end()) {
				if(cnt<USERPERRB) { //��ÿ���û��������趨��Rb��  
					if(0==optRbIter->second) { //�����ûʹ��
						edgeUserLeftIter->rbId.push_back(optRbIter->first);
						optRbIter->second = 1; //��ʾ�Ѿ�ʹ���� 
						cnt++;
					}
					optRbIter++;
				} else {
					cnt = 0;
					edgeUserLeftIter++;  //�Ѿ���������û������Է�����һ���û�
				}
			}
			edgeUserIndex = (edgeUserLeftIter-edgeUsers.begin())%edgeUsers.size(); //������ɺ󣬼�¼֮����ʼ������index  ��opt�ز�
		}
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
		if(centerUsers.size()>0) {
			centerUserIndex = (iter-centerUsers.begin())%centerUsers.size(); //������ɺ󣬼�¼֮����ʼ������index
		} else {
			centerUserIndex = 0;
		}
		//centerUserIndex = (iter-centerUsers.begin())%centerUsers.size(); //������ɺ󣬼�¼֮����ʼ������index
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
		/**********************************
		�����ز��Ѿ�ȫ��������������û������濴�����ز����Ƿ��п����õ�
		****************************************/
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
				/**********************************
					��ʣ������ز��Ѿ�ȫ��������������û������濴��opt�ز����Ƿ��п����õ�
				****************************************/
				//��δ������û���
				int leftCenterUserCnt = centerUserCnt - subRb.size()/USERPERRB - mainRbLeft/USERPERRB;
				if(optRbOverFlag) {
					//�жϹ�����
					int optRbLeft = optRb.size() - optRbUsed;
					if(optRbLeft>=leftCenterUserCnt*USERPERRB) { //����
						vector<User>::iterator centeruserLeft = centerUsers.begin() + centerUserIndex; //��û�з�����û�������ʼ����
						map<int,int>::iterator rbLeft = optRb.begin();  //����Ӧ�ô��ϴη������ʼ��ʼ�����ǲ������ôŪ ������ͷ��ʼ  ��Ϊʹ���˶����ǣ����Կ��Ա�֤ʹ�õĶ���û�����
						while(centeruserLeft!=centerUsers.end()) { //�û��϶�����  �����û��϶���һֱ����
							cnt = 0;
							while(rbLeft!=optRb.end()) {
								//������õ�Rb
								if(cnt<USERPERRB) { //��ÿ���û��������趨��Rb��
									if(0==rbLeft->second) { //�����ûʹ��
										centeruserLeft->rbId.push_back(rbLeft->first);
										rbLeft->second = 1;
										cnt++;
									}
									rbLeft++; //������һ��rb
								} else { //������û��Ѿ����
									cnt = 0;
									break; 
								} 
							}
							centeruserLeft++;   //��ʼ������һ���û�
						}
						centerUserIndex = (centeruserLeft - centerUsers.begin()) % centerUsers.size(); //����һ�±��η�����ɵ������û���index
					} else {
						map<int,int>::iterator rbLeft = optRb.begin(); //û�д��ϴη�������ĵط���ʼ ԭ��ͬ��
						int cnt = 0;
						vector<User>::iterator centeruserLeft = centerUsers.begin()+centerUserIndex;
						while(rbLeft!=mainRb.end()) { 
							//ֻ�в����û����Է��䵽��Դ �����û�û��ͨ��while���б���
							//������õ�Rb
							if(cnt<USERPERRB) { //��ÿ���û��������趨��Rb��
								if(0==rbLeft->second) { //�����ûʹ��
									centeruserLeft->rbId.push_back(rbLeft->first);
									rbLeft->second = 1;
									cnt++;
								}
								rbLeft++;
							} else { //������û��Ѿ���ɣ���ʼ������һ���û�
								cnt = 0;
								centeruserLeft++; 
							}
						}
						centerUserIndex = (centeruserLeft-centerUsers.begin())%centerUsers.size(); //������ɺ󣬼�¼֮����ʼ������index  
					}
					//int optRbLeft = optRb.size() - edgeUserCnt*USERPERRB;
				} else {
					//û��optrb�ˣ���ô��ʲôҲ����
				}
			}
		}
	}
}