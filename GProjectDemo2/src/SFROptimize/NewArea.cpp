#include "stdafx.h"
#include "NewArea.h"
//覆盖init的方法
void NewArea::init() {
	getMainSubRb(); //得到主副载波的分配 通过mainRbIndex来选择使用哪个频段作为主载波
	edgeUserIndex = 0;
	centerUserIndex = 0;
	mainRbOverFlag = false; //默认不够用
	optRbOverFlag = false;
	//sendPower = SENDPOWER;
	ratio = RATIO;
	generateUser(); //生成用户
	//rbCntReal = USERPERRB*(centerUsers.size() + edgeUsers.size()*1.0/ratio);  //总带宽的Rb个数
	getCenterEdgeUser(); //区分边缘和中心用户，并分别统计个数
	setRbPower(); //根据中心和边缘用户数，得到边缘用户每个Rb的功率
}

void NewArea::getMainSubRb() {
	NewRbs newRbs =  NewRbs(mainRbIndex); //然后进行分配
	//这里应该先判断邻区用了那个RB段作为边缘小区使用
	//不管哪个小区都是将part1给作为主载波 不同小区的1会不一样（Rbs中生成part1不一样）
	//主载波
	mainRb = newRbs.part1Rb;
	//副载波
	subRb.insert(newRbs.part2Rb.begin(),newRbs.part2Rb.end());
	subRb.insert(newRbs.part3Rb.begin(),newRbs.part3Rb.end());
	//optRb
	optRb = newRbs.part4Rb;

}

void NewArea::setRbPower() {
	//边缘用户使用mainRb 并且只能用mainRb
	int edgeUserCnt = this->edgeUserCnt;
	int centerUserCnt = this->userCnt - this->edgeUserCnt;
	int edgeReal = 0;
	int centerReal = 0;
	if(edgeUserCnt*USERPERRB<=mainRb.size()) { //边缘用户够用，可以给一部分给中心用户
		//边缘用户都可以拿到资源
		edgeReal = edgeUserCnt;
		if(centerUserCnt*USERPERRB<=subRb.size()) { //中心够用
			centerReal = centerUserCnt;
		} else { //中心的不够用，那么就使用一部分的mainRb
			int leftRb = mainRb.size() - edgeUserCnt * USERPERRB;
			int leftUser = centerUserCnt - subRb.size()/USERPERRB;
			//判断剩余mainRb的够不够用
			if(leftRb >= leftUser*USERPERRB) { //剩余的够用，剩余的中心用户都可以分配到资源
				centerReal = centerUserCnt;
			} else { //有一部分中心用户没有分配到mainRb，那么分配optRb
				leftUser = centerUserCnt - subRb.size()/USERPERRB - leftRb / USERPERRB;
				if(optRb.size() >= leftUser*USERPERRB) { //optrb够用
					centerReal = centerUserCnt; 
				} else { //optrb也不够用
					centerReal = subRb.size()/USERPERRB + leftRb /USERPERRB + optRb.size()/USERPERRB;
				}
			}
		}
	} else { //边缘用户不够用
		int leftEdgeUser = edgeUserCnt - mainRb.size()/USERPERRB;
		if(optRb.size() >= leftEdgeUser*USERPERRB) { //optrb够边缘用户用
			edgeReal = edgeUserCnt;
			if(centerUserCnt*USERPERRB<=subRb.size()) { //分配中心用户，中心够用
				centerReal = centerUserCnt;
			} else { //中心的不够用，由于边缘的已经不够用了，mainRb没有了，所以从optRb中拿
				int optRbLeft = optRb.size() - leftEdgeUser*USERPERRB;
				int centerUserLeft = centerUserCnt - subRb.size()/USERPERRB; 
				if(optRbLeft >= centerUserLeft*USERPERRB) { //如果optLeft够边缘用户用
					centerReal = centerUserCnt;
				} else { //
					centerReal = subRb.size()/USERPERRB+optRbLeft/USERPERRB;
				}
				//centerReal = subRb.size()/USERPERRB;
			}
		} else { //optRb不够给中心用户用
			edgeReal = mainRb.size()/USERPERRB + optRb.size()/USERPERRB;
			if(centerUserCnt*USERPERRB<=subRb.size()) { //中心够用
				centerReal = centerUserCnt;
			} else { //中心的不够用，由于边缘的也不够用，mainRb无剩余,optRb也没剩余，那么就只能分配subRb给部分中心用户了
				centerReal = subRb.size()/USERPERRB;
			}
		}
		
	}

	//edgePowerRatio = (edgeReal/ratio+centerReal)/ratio;
	//按师兄建议应该是
	edgePowerRatio = 1.0*USERPERRB/RBCNT/ratio; //因为有的RB就是分配了功率，但是没人用！
}
void NewArea::sortUser() {
	vector<User> users = this->users;
	//按照调度算法对user进行排序
	//1.先考虑轮询算法
	//先对边缘用户进行排序
	int index = edgeUserIndex; //起始位置
	//1.先将后面的添加到edgeUsers中
	//2.将之前的再添加
	vector<User> temp = edgeUsers;
	edgeUsers.clear();//先清理之前的用户
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

	//对中心用户进行排序
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

void NewArea::allocateRb() { //未完成
	mainRbOverFlag = false;
	optRbOverFlag = false;
	int optRbUsed = 0;
	//首先将User进行调度
	sortUser();
	//先分配边缘用户，再分配中心用户 
	//判断主载波是否够用 
	if(edgeUserCnt*USERPERRB <= mainRb.size()){  //够用
		mainRbOverFlag = true; //主载波够用
		optRbOverFlag = true;
		vector<User>::iterator iter = edgeUsers.begin();
		map<int,int>::iterator iterMap = mainRb.begin();
		while(iter!=edgeUsers.end()) { //每个用户都可以分配到
			//分配可用的Rb
			int cnt = 0;
			while(iterMap!=mainRb.end()) {  //mainRb有剩余，break可以控制不分配所有的mainRb
				if(cnt<USERPERRB) { //给每个用户分配了设定的Rb数  
					if(0==iterMap->second) { //如果还没使用
						iter->rbId.push_back(iterMap->first);
						iterMap->second = 1; //表示已经使用了 
						cnt++;
					}
					iterMap++;
				} else {
					cnt = 0;
					break;  //已经分配完该用户，可以分配下一个用户
				}
			}
			iter++;
		}
		edgeUserIndex = (iter-edgeUsers.begin())%edgeUsers.size(); //遍历完成后，记录之后起始遍历的index
	} else { //如果不够用  那就把全部分配给部分用户  大致和上面一样
		map<int,int>::iterator iterMap = mainRb.begin();
		int cnt = 0;
		vector<User>::iterator iter = edgeUsers.begin();
		while(iterMap!=mainRb.end()) { 
			//只有部分用户可以分配到资源 所以用户没有通过while进行遍历
			//分配可用的Rb
			if(cnt<USERPERRB) { //给每个用户分配了设定的Rb数
				if(0==iterMap->second) { //如果还没使用
					iter->rbId.push_back(iterMap->first);
					iterMap->second = 1;
					cnt++;
				}
				iterMap++;
			} else { //分配该用户已经完成，开始分配下一个用户
				cnt = 0;
				iter++; 
			}
		}
		edgeUserIndex = (iter-edgeUsers.begin())%edgeUsers.size(); //遍历完成后，记录之后起始遍历的index  对主载波
		
		//然后判断optRb是否够用
		int edgeUserLeft = edgeUserCnt - mainRb.size()/USERPERRB;
		if(optRb.size()>=edgeUserLeft*USERPERRB) { //optRb够用
			optRbOverFlag = true;
			vector<User>::iterator edgeUserLeftIter = edgeUsers.begin()+edgeUserIndex;
			map<int,int>::iterator optRbIter = optRb.begin();
			while(edgeUserLeftIter!=edgeUsers.end()) {
				int cnt =0;
				while(optRbIter!=optRb.end()) {
					if(cnt<USERPERRB) { //给每个用户分配了设定的Rb数  
						if(0==optRbIter->second) { //如果还没使用
							edgeUserLeftIter->rbId.push_back(optRbIter->first);
							optRbIter->second = 1; //表示已经使用了 
							cnt++;
						}
						optRbIter++;
					} else {
						cnt = 0;
						break;  //已经分配完该用户，可以分配下一个用户
					}
				}
				edgeUserLeftIter++;
			}
			optRbUsed = USERPERRB*(edgeUserCnt-mainRb.size()/USERPERRB);
			edgeUserIndex = (edgeUserLeftIter-edgeUsers.begin())%edgeUsers.size(); //遍历完成后，记录之后起始遍历的index  对opt载波
		} else { //optRb不够用
			vector<User>::iterator edgeUserLeftIter = edgeUsers.begin()+edgeUserIndex;
			map<int,int>::iterator optRbIter = optRb.begin();
			int cnt =0;
			while(optRbIter!=optRb.end()) {
				if(cnt<USERPERRB) { //给每个用户分配了设定的Rb数  
					if(0==optRbIter->second) { //如果还没使用
						edgeUserLeftIter->rbId.push_back(optRbIter->first);
						optRbIter->second = 1; //表示已经使用了 
						cnt++;
					}
					optRbIter++;
				} else {
					cnt = 0;
					edgeUserLeftIter++;  //已经分配完该用户，可以分配下一个用户
				}
			}
			edgeUserIndex = (edgeUserLeftIter-edgeUsers.begin())%edgeUsers.size(); //遍历完成后，记录之后起始遍历的index  对opt载波
		}
	}
	/*********************************************************
	*********************************************************/
	//分配副载波  中心用户如果用主载波 必须用低的发射功率
	if(centerUserCnt*USERPERRB<=subRb.size()) { //如果副载波够用
		vector<User>::iterator iter = centerUsers.begin();
		map<int,int>::iterator iterMap = subRb.begin();
		while(iter!=centerUsers.end()) {
			int cnt = 0;
			while(iterMap!=subRb.end()) {  //subRb有剩余，break可以控制不分配所有的subRb
				if(cnt<USERPERRB) { //给每个用户分配了设定的Rb数
					if(0==iterMap->second) { //如果还没使用
						iter->rbId.push_back(iterMap->first);
						iterMap->second = 1;
						cnt++;
					}
					iterMap++;
				} else {
					cnt = 0;
					break;  //已经分配完该用户，可以分配下一个用户
				}
			}
			iter++;
		}
		if(centerUsers.size()>0) {
			centerUserIndex = (iter-centerUsers.begin())%centerUsers.size(); //遍历完成后，记录之后起始遍历的index
		} else {
			centerUserIndex = 0;
		}
		//centerUserIndex = (iter-centerUsers.begin())%centerUsers.size(); //遍历完成后，记录之后起始遍历的index
	} else { //如果不够用  那就把全部分配给部分用户  大致和上面一样
		map<int,int>::iterator iterMap = subRb.begin();
		int cnt = 0;
		vector<User>::iterator iter = centerUsers.begin();
		while(iterMap!=subRb.end()) { 
			//只有部分用户可以分配到资源 所以用户没有通过while进行遍历
			//分配可用的Rb
			if(cnt<USERPERRB) { //给每个用户分配了设定的Rb数
				if(0==iterMap->second) { //如果还没使用
					iter->rbId.push_back(iterMap->first);
					iterMap->second = 1;
					cnt++;
				}
				iterMap++;
			} else { //分配该用户已经完成，开始分配下一个用户
				cnt = 0;
				iter++; 
			}
		}
		centerUserIndex = (iter-centerUsers.begin())%centerUsers.size(); //遍历完成后，记录之后起始遍历的index  
		/**********************************
		将副载波已经全部分配给了中心用户，下面看看主载波中是否还有可以用的
		****************************************/
		if(mainRbOverFlag)  { //主载波还有可以分配的
			//1.判断剩余的是否够用
			int mainRbLeft = mainRb.size() - edgeUserCnt*USERPERRB;
			int rbNeed = centerUserCnt * USERPERRB - subRb.size();
			if(mainRbLeft >= rbNeed) { //如果剩下的够用
				vector<User>::iterator userLeft = centerUsers.begin() + centerUserIndex; //从没有分配的用户继续开始分配
				map<int,int>::iterator rbLeft = mainRb.begin();  //本来应该从上次分配的起始开始，但是不清楚怎么弄 所以重头开始  因为使用了都会标记，所以可以保证使用的都是没分配的
				while(userLeft!=centerUsers.end()) { //用户肯定够了  所以用户肯定会一直迭代
					cnt = 0;
					while(rbLeft!=mainRb.end()) {
						//分配可用的Rb
						if(cnt<USERPERRB) { //给每个用户分配了设定的Rb数
							if(0==rbLeft->second) { //如果还没使用
								userLeft->rbId.push_back(rbLeft->first);
								rbLeft->second = 1;
								cnt++;
							}
							rbLeft++; //分配下一个rb
						} else { //分配该用户已经完成
							cnt = 0;
							break; 
						} 
					}
					userLeft++;   //开始分配下一个用户
				}
				centerUserIndex = (userLeft - centerUsers.begin()) % centerUsers.size(); //更新一下本次分配完成的中心用户的index
			} else {  //剩下主载波不够中心用户用
				map<int,int>::iterator rbLeft = mainRb.begin(); //没有从上次分配结束的地方开始 原因同上
				int cnt = 0;
				vector<User>::iterator userLeft = centerUsers.begin()+centerUserIndex;
				while(rbLeft!=mainRb.end()) { 
					//只有部分用户可以分配到资源 所以用户没有通过while进行遍历
					//分配可用的Rb
					if(cnt<USERPERRB) { //给每个用户分配了设定的Rb数
						if(0==rbLeft->second) { //如果还没使用
							userLeft->rbId.push_back(rbLeft->first);
							rbLeft->second = 1;
							cnt++;
						}
						rbLeft++;
					} else { //分配该用户已经完成，开始分配下一个用户
						cnt = 0;
						userLeft++; 
					}
				}
				centerUserIndex = (userLeft-centerUsers.begin())%centerUsers.size(); //遍历完成后，记录之后起始遍历的index  
				/**********************************
					将剩余的主载波已经全部分配给了中心用户，下面看看opt载波中是否还有可以用的
				****************************************/
				//还未分配的用户数
				int leftCenterUserCnt = centerUserCnt - subRb.size()/USERPERRB - mainRbLeft/USERPERRB;
				if(optRbOverFlag) {
					//判断够不够
					int optRbLeft = optRb.size() - optRbUsed;
					if(optRbLeft>=leftCenterUserCnt*USERPERRB) { //够用
						vector<User>::iterator centeruserLeft = centerUsers.begin() + centerUserIndex; //从没有分配的用户继续开始分配
						map<int,int>::iterator rbLeft = optRb.begin();  //本来应该从上次分配的起始开始，但是不清楚怎么弄 所以重头开始  因为使用了都会标记，所以可以保证使用的都是没分配的
						while(centeruserLeft!=centerUsers.end()) { //用户肯定够了  所以用户肯定会一直迭代
							cnt = 0;
							while(rbLeft!=optRb.end()) {
								//分配可用的Rb
								if(cnt<USERPERRB) { //给每个用户分配了设定的Rb数
									if(0==rbLeft->second) { //如果还没使用
										centeruserLeft->rbId.push_back(rbLeft->first);
										rbLeft->second = 1;
										cnt++;
									}
									rbLeft++; //分配下一个rb
								} else { //分配该用户已经完成
									cnt = 0;
									break; 
								} 
							}
							centeruserLeft++;   //开始分配下一个用户
						}
						centerUserIndex = (centeruserLeft - centerUsers.begin()) % centerUsers.size(); //更新一下本次分配完成的中心用户的index
					} else {
						map<int,int>::iterator rbLeft = optRb.begin(); //没有从上次分配结束的地方开始 原因同上
						int cnt = 0;
						vector<User>::iterator centeruserLeft = centerUsers.begin()+centerUserIndex;
						while(rbLeft!=mainRb.end()) { 
							//只有部分用户可以分配到资源 所以用户没有通过while进行遍历
							//分配可用的Rb
							if(cnt<USERPERRB) { //给每个用户分配了设定的Rb数
								if(0==rbLeft->second) { //如果还没使用
									centeruserLeft->rbId.push_back(rbLeft->first);
									rbLeft->second = 1;
									cnt++;
								}
								rbLeft++;
							} else { //分配该用户已经完成，开始分配下一个用户
								cnt = 0;
								centeruserLeft++; 
							}
						}
						centerUserIndex = (centeruserLeft-centerUsers.begin())%centerUsers.size(); //遍历完成后，记录之后起始遍历的index  
					}
					//int optRbLeft = optRb.size() - edgeUserCnt*USERPERRB;
				} else {
					//没有optrb了，那么就什么也不做
				}
			}
		}
	}
}