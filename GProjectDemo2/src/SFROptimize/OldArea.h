#ifndef _OLDAREA_H
#define _OLDAREA_H
#include "Area.h"
#include "User.h"
#include "Rbs.h"
#include <vector>
#include <math.h>
#include <cmath>
using namespace std;
#define DISTANCEGATE 200  //��Ӧ���þ�����ֵ
#define RSRPGATE -70 //��Ӧ���þ�����ֵ Ӧ�������  
#define SENDPOWER 43 //dBm  2w �˴���Ҫ���ņ� �˽����ʱʹ�õĹ���
#define RATIO (1/3.0)
#define NOISE -174 //	dbm/hz
#define RBFREQLEN 180000.0
#define USERCNT  60
class OldArea {
//�����ӵ�����
public:
	Area area;
public:
	int mainRbIndex;
	map<int,int> mainRb;
	map<int,int> subRb;
	vector<int> adjAreaId; //���������ڣ����������б������������
	vector<OldArea> adjArea;
	int userCnt;
	vector<User> users; //�˴���Ϊ���ɵ��û�������ĳ��������
	vector<User> edgeUsers;
	vector<User> centerUsers;
	double rsrpGate; 
	double distanceGate;
	double totalThroughput;
	double edgeThroughput;
	int edgeUserCnt;
	int centerUserCnt;
	int edgeUserIndex;//��¼��ǰ���䵽RB�ı�Ե�û�index
	int centerUserIndex;//��¼��ǰ���䵽RB�������û�index
	bool mainRbOverFlag; //���ز��Ƿ���
	//double sendPower;
	double edgePowerRatio;
	double ratio;
	//double rbCntReal; //�������û���RB����Ϊ��λ Ӧ���ж��ٸ�RB
	OldArea(Area area) {
		this->area = area;
		this->userCnt = USERCNT;
		this->rsrpGate = RSRPGATE;
		this->distanceGate = DISTANCEGATE;
		this->edgeUserIndex = 0; //��ʼ��0��ʼ���з���
		this->centerUserIndex = 0; //��ʼ��0��ʼ����
		this->mainRbIndex = 0; //����һ�������ڵ�RbIndex
	}
public:
	vector<int> getAdjAreaId();
	void getCenterEdgeUser();
	bool isEdgeUser(double userX,double userY,double userRsrp);

	void init();
	vector<User> generateUser();
	//���������ز�
	void getMainSubRb();
	void setRbPower(); //�����û�ʹ�õ�RB�������书��
	//���û��������򣨵����㷨����֮���ٰ�˳�����Rb�Ϳ���
	void sortUser();
	//���û����з���Rb
	void allocateRb();
	//����С����Ե�û���������
	double getEdgeThroughPut();
	//����С�����ĵ��û���������
	double getCenterThroughPut();
	//����С���ܵ��û���������
	double getAllThroughPut();
	double powerToThroughPut(double sinr);
	//����ĳ���û��������ĸ���
	double getAdjAreaPower(User user);
};
#endif