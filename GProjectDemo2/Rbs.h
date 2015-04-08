#ifndef _RB_H
#define _RB_H
#define RBCNT 100
#define USERPERRB 2
#include <map>
using namespace std;
class Rbs{ //����100��Rb ���ز�����3�ȷ�  ����ÿ���û�ʹ��2��Rb
public: //0��ʾ��RBδ���� 1��ʾ��RB�Ѿ�����
	map<int,int> part1Rb; //ȫ����ʼ��Ϊ0
	map<int,int> part2Rb;
	map<int,int> part3Rb;
public:
	Rbs(){
		//��part1,part2,part3���г�ʼ��
		int part1iEnd = RBCNT/3+1;
		int part2iEnd = 2*(RBCNT/3)+1;
		for(int part1i=1;part1i<part1iEnd;part1i++) {
			part1Rb[part1i]=0;
			//mapStudent.insert(pair<int, string>(1, ��student_one��));
		}
		for(int part2i=part1iEnd;part2i<part2iEnd;part2i++) {
			part2Rb[part2i] = 0;
		}
		for(int part3i=part2iEnd;part3i<RBCNT+1;part3i++) {
			part3Rb[part3i] = 0;
		}
	}
};
#endif