#ifndef _USER_H
#define _USER_H
#include "stdafx.h"
#include <vector>
using namespace std;

class User {
public:
		vector<int> rbId;  //����������ʱ����Ҫ�ж�ʵ�ʷ����˼���Rb
		int gridId;
		double rsrp;
		double sinr;
		double x;
		double y;
		int type;//1:�����û�  2����Ե�û�  
	//���췽��
public:
	User(int gridId,double rsrp,double x,double y){
		this->gridId = gridId;
		this->rsrp = rsrp;
		this->x = x;
		this->y = y;
		this->type = 1; //Ĭ���������û�
	}
};
#endif