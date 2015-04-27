#ifndef _RB_H
#define _RB_H
#define RBCNT 100
#define USERPERRB 2
#define OLDRBPARTS 3
#include <map>
using namespace std;
class Rbs{ //假设100个Rb 载波进行3等分  考虑每个用户使用2个Rb
public: //0表示该RB未分配 1表示该RB已经分配
	map<int,int> part1Rb; //全部初始化为0
	map<int,int> part2Rb;
	map<int,int> part3Rb;
public:
	Rbs(int index){  //由于考虑到要能够把rb刚好分给一个用户（所以主副载波rb必须为偶数）  32 34 34 因此不是刚好平均分配
		//对part1,part2,part3进行初始化
		int part1Size = RBCNT/OLDRBPARTS-1; //用part1作为主载波 32个
		int otherPartSize = (RBCNT - part1Size) / 2; //
		//int otherPartSize2 = RBCNT - part1Size - otherPartSize; 
		int part1Start = 32*(index-1) + 2*index - 1;  //index=1 1-32  =2 35-66  =3 69-100
		//part1Start 1-69  part1Start+part1Size  33-101
		for(int i=0;i<part1Size;i++) { //分配32个
			part1Rb[part1Start]=0;
			part1Start++;
		}
		int part2Start = (part1Start) % RBCNT; 
		for(int i=0;i<otherPartSize;i++) {
			part2Rb[part2Start] = 0;
			part2Start=(part2Start++)%RBCNT;
		}
		int part3Start = (part2Start) % RBCNT;
		for(int i=0;i<otherPartSize;i++) {
			part3Rb[part3Start] = 0;
			part3Start=(part3Start++)%RBCNT;
		}
		
	}
	//当是改进型时 24 24 24 28的分配
};
#endif