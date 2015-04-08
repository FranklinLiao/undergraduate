#include "stdafx.h"
#include "OldArea.h"

vector<User> OldArea::generateUser(int userCnt) {
	int areaId = this->AId;
	vector<User> users = DBHelper::getUser(areaId,userCnt); //从该小区所包括的网格中随机选择userCnt个，即认为随机选择了分布在该小区中的用户
	this->users = users;
	return users;
}

vector<int> OldArea::getAdjAreaId() {
	int areaId = this->AId;
	vector<int> adjAreaId = DBHelper::getAdjAreaId(areaId);
	return adjAreaId;
}


int OldArea::getEdgeUserCnt() {
	int cnt = 0; //边缘用户计数器
	vector<User> users = this->users;
	//便利每个用户判断是中心还是边缘
	vector<User>::iterator iter = users.begin();
	while(iter != users.end()) {
		User user = *iter;
		double userX = user.x;
		double userY = user.y;
		double userRsrp = user.rsrp;
		if(isEdgeUser(userX,userY,userRsrp)) { //是边缘用户
			cnt++;
			//修改该user的type参数
			user.type = 2; //边缘用户
		}
		users.erase(iter); //移除之前的那个user
		users.push_back(user); //将修改了type的user添加进来
		iter++;
	}
}

bool OldArea::isEdgeUser(double userX,double userY,double userRsrp) {
	bool flag = true;
	double dist = sqrt(pow((this->aX-userX),2)+pow((this->aY-userY),2));
	if(dist<distanceGate&&userRsrp>rsrpGate) { //中心用户条件
		return false;
	}
}

void OldArea::getMainSubRb() {
	Rbs rbs = new Rbs(); //然后进行分配
	//这里应该先判断邻区用了那个RB段作为边缘小区使用
	//1.先假设把1给边缘
	//主载波
	mainRb = rbs.part1Rb;
	//副载波
	subRb.insert(rbs.part2Rb.begin(),rbs.part2Rb.end());
	subRb.insert(rbs.part3Rb.begin(),rbs.part3Rb.end());
}

void OldArea::allocateRb() {
	//先分配主载波，再分配副载波  还未加入调度算法
	int edgeUserCnt = getEdgeUserCnt();
	//判断主载波是否够用 
	if(edgeUserCnt*USERPERRB < mainRb.size()){  //够用
		vector<User> users = users;
		vector<User>::iterator iter = users.begin();
		while(iter!=users.end()) {
			User user = *iter;
			if(2==user.type) { //是边缘用户
				 //分配可用的Rb
				map<int,int>::iterator iterMap = mainRb.begin();
				int cnt = 0;
				while(iterMap!=mainRb.end()) { 
					if(cnt<USERPERRB) { //给每个用户分配了设定的Rb数
						if(0==iterMap->second) { //如果还没使用
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