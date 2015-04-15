#ifndef _NEWRBS_H
#define _NEWRBS_H
#define RBCNT 100
#define USERPERRB 2
#define RBPARTS 4
#include <map>
using namespace std;
class NewRbs{
public: //0表示该RB未分配 1表示该RB已经分配
	map<int,int> part1Rb; //全部初始化为0
	map<int,int> part2Rb;
	map<int,int> part3Rb;
	map<int,int> part4Rb;
public:
	//当是改进型时 24 24 24 28的分配 main sub sub opt
	NewRbs(int mainIndex){  //由于考虑到要能够把rb刚好分给一个用户（所以主副载波rb必须为偶数）  32 34 34 因此不是刚好平均分配
		//对part1,part2,part3进行初始化
		int part1Size = RBCNT/RBPARTS-1; //用part1作为主载波 32个
		int optSize = part1Size + 4;
		int otherPartSize = (RBCNT - part1Size - optSize) / 2;
		int part1Start = 1;
		switch(mainIndex) {
		case 1: part1Start = 1;break;
		case 2: part1Start = 29;break;
		case 3: part1Start = 53;break;
		case 4: part1Start = 77;break;
		}
		//mainRb
		for(int i=0;i<part1Size;i++) { //分配24个
			part1Rb[part1Start]=0;
			part1Start++;
		}
		int part2Start = (part1Start+part1Size) % RBCNT; 
		for(int i=0;i<otherPartSize;i++) {
			part2Rb[part2Start] = 0;
			part2Start++;
		}
		int part3Start = (part2Start+otherPartSize) % RBCNT;
		for(int i=0;i<otherPartSize;i++) {
			part3Rb[part3Start] = 0;
			part3Start++;
		}
		//optRb
		int part4Start = (part3Start + otherPartSize) % RBCNT;
		for(int i=0;i<optSize;i++) {
			part4Rb[part4Start] = 0;
			part4Start++;
		}
	}
};
#endif