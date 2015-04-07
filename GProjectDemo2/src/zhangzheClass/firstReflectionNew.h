// F.cpp : �������̨Ӧ�ó������ڵ㡣
//
#pragma  once
#include "stdafx.h"

#include <iostream>
#include<vector>
#include <windows.h>
#include <math.h>
#include "BuildingPoint.h"
#include "line.h"
using namespace std;

//ȫ�ֱ�����ò�Ҫ���壬���࣬���Զ���һ������
/*struct TwoDimPoint{
	float x;
	float y;
};
 struct line
{
	TwoDimPoint point1;
	TwoDimPoint point2;
};
 vector<TwoDimPoint> polyPoint;

 */

class FirstReflection
{
	public:
		vector<TwoDimPoint> polyPoint;
		float crossX;
		float crossY;
		float crossZ;
		TwoDimPoint	refPolyPoint[2];
		int buildingCrossFlag;
		int roofFlag;
		void buildingCross(float shootingStartX,float shootingStartY,float shootingStartZ,float shootingDirectionX,float shootingDirectionY,float shootingDirectionZ,vector<BuildingPoint>BPoint,float buildingHeight);
		
	private:
		TwoDimPoint getCross(line line1, line line2);
		int vertex_triangle(TwoDimPoint pa, TwoDimPoint pb, TwoDimPoint pc, TwoDimPoint vertex0);	
		int vertex_polygon(TwoDimPoint vertex0);                               //�Ѷ���ηֽ�ɶ��������		
};



/*
int main()
{
	FirstReflection temp;
	vector<BuildingPoint> BPoint;
	BuildingPoint h1,h2,h3,h4;
	h1.px=2;
	h1.py=2;
	BPoint.push_back(h1);
	h2.px=4;
	h2.py=2;
	BPoint.push_back(h2);
	h3.px=4;
	h3.py=8;
	BPoint.push_back(h3);
	h4.px=2;
	h4.py=8;
	BPoint.push_back(h4);
	temp.buildingCross(0,4,30,1,0,-5,BPoint,15);
	
	cout<<temp.crossX<<endl;
	cout<<temp.crossY<<endl;
	cout<<temp.crossZ<<endl;
	cout<<temp.buildingCrossFlag<<endl;
	cout<<temp.roofFlag<<endl;
	int hh;
	cin>>hh;

}
*/
