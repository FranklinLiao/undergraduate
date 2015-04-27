#ifndef _RB_H
#define _RB_H
#define RBCNT 100
#define USERPERRB 2
#define OLDRBPARTS 3
#include <map>
using namespace std;
class Rbs{ //����100��Rb �ز�����3�ȷ�  ����ÿ���û�ʹ��2��Rb
public: //0��ʾ��RBδ���� 1��ʾ��RB�Ѿ�����
	map<int,int> part1Rb; //ȫ����ʼ��Ϊ0
	map<int,int> part2Rb;
	map<int,int> part3Rb;
public:
	Rbs(int index){  //���ڿ��ǵ�Ҫ�ܹ���rb�պ÷ָ�һ���û������������ز�rb����Ϊż����  32 34 34 ��˲��Ǹպ�ƽ������
		//��part1,part2,part3���г�ʼ��
		int part1Size = RBCNT/OLDRBPARTS-1; //��part1��Ϊ���ز� 32��
		int otherPartSize = (RBCNT - part1Size) / 2; //
		//int otherPartSize2 = RBCNT - part1Size - otherPartSize; 
		int part1Start = 32*(index-1) + 2*index - 1;  //index=1 1-32  =2 35-66  =3 69-100
		//part1Start 1-69  part1Start+part1Size  33-101
		for(int i=0;i<part1Size;i++) { //����32��
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
	//���ǸĽ���ʱ 24 24 24 28�ķ���
};
#endif