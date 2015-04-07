#ifndef _OLDAREA_H
#define _OLDAREA_H
class OldArea:public Area{
//新增加的属性
private:
	vector<int> mainRbId;
	vector<int> subRbId;
	vector<int> adjAreaId;
	int userCnt;
	vector<User> users;
	double rsrpGate;
	double distanceGate;
	double totalThroughput;
	double edgeThroughput;
public:
	OldArea(int userCnt,double rsrpGate,double distanceGate) {
		this->userCnt = userCnt;
		this->rsrpGate = rsrpGate;
		this->distanceGate = distanceGate;
	}
	vector<int> getMainRbId() {
		return mainRbId;
	}

	vector<User> generateUser(int userCnt);
};
#endif