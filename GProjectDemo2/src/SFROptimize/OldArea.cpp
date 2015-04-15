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
	getMainSubRb(); //得到主副载波的分配 通过mainRbIndex来选择使用哪个频段作为主载波
	edgeUserIndex = 0;
	centerUserIndex = 0;
	mainRbOverFlag = false; //默认不够用
	//sendPower = SENDPOWER;
	ratio = RATIO;
	generateUser(); //生成用户
	//rbCntReal = USERPERRB*(centerUsers.size() + edgeUsers.size()*1.0/ratio);  //总带宽的Rb个数
	getCenterEdgeUser(); //区分边缘和中心用户，并分别统计个数
	setRbPower(); //根据中心和边缘用户数，得到边缘用户每个Rb的功率

}
vector<User> OldArea::generateUser() { 
	int areaId = this->area.AId;
	vector<User> users = DBHelper::getUser(areaId,this->userCnt); //从该小区所包括的网格中随机选择userCnt个，即认为随机选择了分布在该小区中的用户
	this->users = users;
	return users;
}

vector<int> OldArea::getAdjAreaId() {  //这个数最多不能超过6个
	int areaId = this->area.AId;
	vector<int> adjAreaId = DBHelper::getAdjAreaId(areaId);
	return adjAreaId;
}


//************************************  
// 函数名称: getCenterEdgeUser     
// 函数说明： 识别出主边缘用户   
// 作者:Franklin     
// 日期：2015/04/13     
// 返 回 值: void     
//************************************
void OldArea::getCenterEdgeUser() {
	vector<User> users = this->users;
	//便利每个用户判断是中心还是边缘
	vector<User>::iterator iter = users.begin();
	while(iter != users.end()) {
		User user = *iter;
		double userX = user.x;
		double userY = user.y;
		double userRsrp = user.rsrp;
		if(isEdgeUser(userX,userY,userRsrp)) { //是边缘用户
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
	if(dist<=distanceGate&&userRsrp>=rsrpGate) { //中心用户条件
		return false;
	} else {
		return true;
	}
}

void OldArea::getMainSubRb() {
	Rbs rbs =  Rbs(mainRbIndex); //然后进行分配
	//这里应该先判断邻区用了那个RB段作为边缘小区使用
	//不管哪个小区都是将part1给作为主载波 不同小区的1会不一样（Rbs中生成part1不一样）
	//主载波
	mainRb = rbs.part1Rb;
	//副载波

	subRb.insert(rbs.part2Rb.begin(),rbs.part2Rb.end());
	subRb.insert(rbs.part3Rb.begin(),rbs.part3Rb.end());
}

void OldArea::sortUser() {
	vector<User> users = users;
	//按照调度算法对user进行排序
	//1.先考虑轮询算法
	//先对边缘用户进行排序
	int index = edgeUserIndex; //起始位置
	//1.先将后面的添加到edgeUsers中
	//2.将之前的再添加
	edgeUsers.clear();//先清理之前的用户
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
	
	//对中心用户进行排序
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

void OldArea::setRbPower() { //此处需要重新理一下！！！
	//边缘用户使用mainRb 并且只能用mainRb
	int edgeUserCnt = edgeUserCnt;
	int centerUserCnt = centerUserCnt;
	int edgeReal = 0;
	int centerReal = 0;
	if(edgeUserCnt*USERPERRB<=mainRb.size()) { //mainRb够用
		//边缘用户都可以拿到资源
		edgeReal = edgeUserCnt;
		if(centerUserCnt*USERPERRB<=subRb.size()) { //subRb够用
			centerReal = centerUserCnt;
		} else { //subRb不够用，那么就使用一部分的mainRb
			int leftRb = mainRb.size() - edgeUserCnt * USERPERRB;
			int leftUser = centerUserCnt - subRb.size()/USERPERRB;
			//判断剩余mainRb的够不够用
			if(leftRb >= leftUser*USERPERRB) { //剩余mainRb的够用，剩余的中心用户都可以分配到资源
				centerReal = centerUserCnt;
			} else { //有一部分中心用户没有资源
				centerReal = leftRb / USERPERRB + subRb.size()/USERPERRB;
			}
		}
	} else { //mainRb不够用
		edgeReal = mainRb.size()/USERPERRB;
		if(centerUserCnt*USERPERRB<=subRb.size()) { //中心够用
			centerReal = centerUserCnt;
		} else { //中心的不够用，由于边缘的也不够用，mainRb无剩余，那么就只能分配subRb给部分中心用户了
			centerReal = subRb.size()/USERPERRB;
		}
	}
	edgePowerRatio = (edgeReal/ratio+centerReal)/ratio;
	/*
	if(centerUserCnt*USERPERRB < subRb.size()){ //边缘够用
		//每个用户使用Userperrb个rb，这样算出总的用户数*每个用户使用的rb=每个副载波rb的发射功率  再/ratio：就得到主载波的发射功率
		//edgePower = (sendPower / USERPERRB*(edgeUserCnt/ratio+centerUserCnt))/ratio;
		//计算出了边缘用户占的总的功率的比例
		edgePowerRatio = 1.0/((edgeUserCnt/ratio+centerUserCnt)/ratio);
	} else { //不够用,中心用户使用的rb会更多（使用一些mainRb)
		int mainRbLeft = mainRb.size() - edgeUserCnt*USERPERRB;
		int rbNeed = centerUserCnt*USERPERRB - subRb.size();
		if(mainRbLeft>=rbNeed) { //剩下主rb的够用
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
	//首先将User进行调度
	sortUser();
	//先分配边缘用户，再分配中心用户
	//判断主载波是否够用 
	if(edgeUserCnt*USERPERRB <= mainRb.size()){  //够用
		mainRbOverFlag = true; //主载波够用
		vector<User>::iterator iter = edgeUsers.begin();
		map<int,int>::iterator iterMap = mainRb.begin();
		while(iter!=edgeUsers.end()) { //每个用户都可以分配到
			//分配可用的Rb
			int cnt = 0; //分配给每个用户
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
		centerUserIndex = (iter-centerUsers.begin())%centerUsers.size(); //遍历完成后，记录之后起始遍历的index
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
		//将副载波已经全部分配给了中心用户，下面看看主载波中是否还有可以用的
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
			}
		}
	}
}

double OldArea::getEdgeThroughPut() {
	vector<User>::iterator iter = edgeUsers.begin();
	double sumThroughPut=0.0;
	while(iter!=edgeUsers.end()) { //便利计算每个用户的吞吐量
		//1.得到sinr sinr计算都是用dbm为单位 所以不用进行单位换算  得到的sinr是一个比值
		//2.计算吞吐量
		//先得到自己的功率
		// 1.0/ratio * Userperrb是以中心用户的RB功率为单位，计算该用户在总带宽上占用的RB数
		double percent = edgePowerRatio; //得到该用户的rb在总的带宽中占用的比例
		double selfPower = (iter->rsrp)*percent; //*1.0用于产生double型数据
		double noisePower = NOISE*(USERPERRB*RBFREQLEN);//一个rb 180khz
		//计算干扰 得到某个用户在邻区的干扰
		double otherPower = getAdjAreaPower(*iter); //此处应该是计算相邻小区使用同一RB的功率
		double sinr = selfPower / (otherPower + noisePower);  //计算sinr
		double userThroughPut = powerToThroughPut(sinr);  //计算吞吐量
		sumThroughPut += userThroughPut; //累计用户的吞吐量
		iter++;
	}
	return sumThroughPut;
}

double OldArea::getCenterThroughPut() {
	vector<User>::iterator iter = centerUsers.begin();
	double sumThroughPut=0.0;
	while(iter!=centerUsers.end()) { //便利计算每个用户的吞吐量
		//1.得到sinr sinr计算都是用dbm为单位 所以不用进行单位换算  得到的sinr是一个比值
		//2.计算吞吐量
		//先得到自己的功率
		double percent = edgePowerRatio*ratio; //得到该用户的rb在总的带宽中占用的比例
		double selfPower = (iter->rsrp)*percent; //*1.0用于产生double型数据
		double noisePower = NOISE*(USERPERRB*RBFREQLEN);//一个rb 180khz
		//计算干扰 得到某个用户在邻区的干扰
		double otherPower = getAdjAreaPower(*iter); //此处应该是计算相邻小区使用同一RB的功率
		double sinr = selfPower / (otherPower + noisePower);  //计算sinr
		double userThroughPut = powerToThroughPut(sinr);  //计算吞吐量
		sumThroughPut += userThroughPut; //累计用户的吞吐量
		iter++;
	}
	return sumThroughPut;
}

double OldArea::getAllThroughPut() {
	return getEdgeThroughPut()+getCenterThroughPut();
}

double OldArea::powerToThroughPut(double sinr) {
	//Blog(1+sinr) 以2为底  sinr计算中都是用  B:hz为单位  C的单位是bps
	double B = USERPERRB*180000.0;
	double throughPut = B*(1.0*log(1.0+sinr)/log(2.0));
	return throughPut;
}

double OldArea::getAdjAreaPower(User user) {
	//遍历邻区去计算干扰  这个操作应该是每个小区都已经分布好了用户，分配好了RB
	double disturbPower = 0.0;
	int rbId = user.rbId.at(0); //取出第一个rbId的编号
	vector<OldArea> adjCell = adjArea;
	vector<OldArea>::iterator iter = adjCell.begin();
	while(iter!=adjCell.end()) { //便利邻区
		//判断邻区边缘用户的干扰 虽然对边缘用户而言，邻区的边缘用户无干扰，但是为了简化边缘和中心用户的程序，就合在一起了
		//邻区边缘用户的干扰
		vector<User>::iterator iterEdgeUser = iter->edgeUsers.begin();
		while(iterEdgeUser!=iter->edgeUsers.end()) { //便利邻区的边缘用户
			if(iterEdgeUser->rbId.at(0)==rbId) { //相邻小区也是用了该RB
				//取出相邻小区在该用户的场强大小*该rb所占功率的比例就得到了相邻小区使用该RB对该用户的干扰
				//邻区在该用户的场强
				double powStrength = DBHelper::getAdjAreaGridStrength(iter->area.AId,user.gridId);
				//取出对应rb的强度值
				double adjPower = powStrength*iter->edgePowerRatio;
				disturbPower += adjPower;
			}
			iterEdgeUser++;
		}
		//判断邻区中心用户的干扰
		vector<User>::iterator iterCenterUser = iter->centerUsers.begin();
		while(iterCenterUser!=iter->centerUsers.end()) {
			if(iterCenterUser->rbId.at(0)==rbId) { //相邻小区也是用了该RB
				//取出相邻小区在该用户的场强大小*该rb所占功率的比例就得到了相邻小区使用该RB对该用户的干扰
				double powStrength = DBHelper::getAdjAreaGridStrength(iter->area.AId,user.gridId);
				//取出对应rb的强度值
				double adjPower = (iter->edgePowerRatio)*powStrength*ratio;
				disturbPower += adjPower;
			}
			iterCenterUser++;
		}
		iter++;
	}
	return disturbPower;
}