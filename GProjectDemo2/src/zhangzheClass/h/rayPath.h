#ifndef _RAYPATH_H
#define _RAYPATH_H
#include "stdafx.h"
#include "complex.h"
#include<iostream>
#include<vector>
using namespace std;

class rayPath                //射线路径类
{
public:
	float  firstPointx,firstPointy,firstPointz;//射线起始点的坐标
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
	vector<int>searchGridNumberTrue;//记录每次求交模块射线实际经过的网格的个数
	vector<int>searchGridTrueX;//记录每次求交模块射线实际经过的网格的水平编号
	vector<int>searchGridTrueY;//记录每次求交模块射线实际经过的网格的垂直编号
	vector<int>positioniState;
	vector<complex>reflectComplexCoefficient;//存入复的反射系数

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
