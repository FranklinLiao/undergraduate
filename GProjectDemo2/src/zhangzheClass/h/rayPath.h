#ifndef _RAYPATH_H
#define _RAYPATH_H
#include "stdafx.h"
#include "complex.h"
#include<iostream>
#include<vector>
using namespace std;

class rayPath                //����·����
{
public:
	float  firstPointx,firstPointy,firstPointz;//������ʼ�������
	float  firstDirectiona,firstDirectionb,firstDirectionc;
	float  rayGain;
public:
	vector<float>reflecttDirectiona;
	vector<float>reflecttDirectionb;
	vector<float>reflecttDirectionc;
	vector<float>reflecttAngle;
	vector<float>reflecttCoefficient;
	vector<float>crossPointx;
	vector<float>crossPointy;
	vector<float>crossPointz;
	vector<float>rayLength;
	vector<int>searchGridNumberTrue;//��¼ÿ����ģ������ʵ�ʾ���������ĸ���
	vector<int>searchGridTrueX;//��¼ÿ����ģ������ʵ�ʾ����������ˮƽ���
	vector<int>searchGridTrueY;//��¼ÿ����ģ������ʵ�ʾ���������Ĵ�ֱ���
	vector<int>positioniState;
	vector<complex>reflectComplexCoefficient;//���븴�ķ���ϵ��

	//rayPath(float a,float b,float c,float d,float e,float f,float g);





};


#endif
/*rayPath::rayPath(float a,float b,float c,float d,float e,float f,float g)
{
	firstPointx=a;
	firstPointy=b;
	firstPointz=c;
	firstDirectiona=d;
	firstDirectionb=e;
	firstDirectionc=f;
	rayGain=g;
}
*/
