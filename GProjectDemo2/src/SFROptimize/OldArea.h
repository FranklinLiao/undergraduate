#ifndef _OLDAREA_H
#define _OLDAREA_H
#include "Area.h"
#include "User.h"
#include "Rbs.h"
#include <vector>
#include <math.h>
#include <cmath>
using namespace std;
#define DISTANCEGATE 200  //不应该用绝对数值
#define RSRPGATE -70 //不应该用绝对数值 应该用相对  
#define SENDPOWER 43 //dBm  2w 此处需要问张喆 了解计算时使用的功率
#define RATIO (1/3.0)
#define NOISE -174 //	dbm/hz
#define RBFREQLEN 180000.0
#define USERCNT  60
class OldArea {
//新增加的属性
public:
	Area area;
public:
	int mainRbIndex;
	map<int,int> mainRb;
	map<int,int> subRb;
	vector<int> adjAreaId; //物理上相邻（不是邻区列表的那种邻区）
	vector<OldArea> adjArea;
	int userCnt;
	vector<User> users; //此处认为生成的用户就是在某个网格中
	vector<User> edgeUsers;
	vector<User> centerUsers;
	double rsrpGate; 
	double distanceGate;
	double totalThroughput;
	double edgeThroughput;
	int edgeUserCnt;
	int centerUserCnt;
	int edgeUserIndex;//记录当前分配到RB的边缘用户index
	int centerUserIndex;//记录当前分配到RB的中心用户index
	bool mainRbOverFlag; //主载波是否都用
	//double sendPower;
	double edgePowerRatio;
	double ratio;
	//double rbCntReal; //以中心用户的RB功率为单位 应该有多少个RB
	OldArea(Area area) {
		this->area = area;
		this->userCnt = USERCNT;
		this->rsrpGate = RSRPGATE;
		this->distanceGate = DISTANCEGATE;
		this->edgeUserIndex = 0; //初始从0开始进行分配
		this->centerUserIndex = 0; //初始从0开始分配
		this->mainRbIndex = 0; //分配一个不存在的RbIndex
	}
public:
	vector<int> getAdjAreaId();
	void getCenterEdgeUser();
	bool isEdgeUser(double userX,double userY,double userRsrp);

	void init();
	vector<User> generateUser();
	//分配主副载波
	void getMainSubRb();
	void setRbPower(); //根据用户使用的RB数，分配功率
	//对用户进行排序（调度算法），之后再按顺序分配Rb就可以
	void sortUser();
	//对用户进行分配Rb
	void allocateRb();
	//计算小区边缘用户的吞吐量
	double getEdgeThroughPut();
	//计算小区中心的用户的吞吐量
	double getCenterThroughPut();
	//计算小区总的用户的吞吐量
	double getAllThroughPut();
	double powerToThroughPut(double sinr);
	//计算某个用户在邻区的干扰
	double getAdjAreaPower(User user);
};
#endif