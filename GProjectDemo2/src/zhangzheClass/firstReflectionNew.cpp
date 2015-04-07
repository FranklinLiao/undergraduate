#include "stdafx.h"
#include "firstReflectionNew.h"
TwoDimPoint FirstReflection:: getCross(line line1, line line2)//求两条线段的交点
{
	
	TwoDimPoint CrossP;
	//y = a * x + b;
	if ((line1.point1.x - line1.point2.x) != 0 && (line2.point1.x - line2.point2.x) != 0)
	{
		float a1 = (line1.point1.y - line1.point2.y) / (line1.point1.x - line1.point2.x);
		float b1 = line1.point1.y - a1 * (line1.point1.x);

		float a2 = (line2.point1.y - line2.point2.y) / (line2.point1.x - line2.point2.x);
		float b2 = line2.point1.y - a2 * (line2.point1.x);

		if (a1 != a2)
		{
			CrossP.x = (b1 - b2) / (a2 - a1);
			CrossP.y = a1 * CrossP.x + b1;
		}
		else
		{
			CrossP.x = 9999999999999;
			CrossP.y = 9999999999999;
		}
	}
	else if ((line1.point1.x - line1.point2.x) == 0 && (line2.point1.x - line2.point2.x) != 0)
	{
		float a2 = (line2.point1.y - line2.point2.y) / (line2.point1.x - line2.point2.x);
		float b2 = line2.point1.y - a2 * (line2.point1.x);
		CrossP.x = line1.point1.x;
		CrossP.y = a2*CrossP.x + b2;
	}
	else if ((line1.point1.x - line1.point2.x) != 0 && (line2.point1.x - line2.point2.x) == 0)
	{
		float a1 = (line1.point1.y - line1.point2.y) / (line1.point1.x - line1.point2.x);
		float b1 = line1.point1.y - a1 * (line1.point1.x);
		CrossP.x = line2.point1.x;
		CrossP.y = a1*CrossP.x + b1;
	}
	else if ((line1.point1.x - line1.point2.x) == 0 && (line2.point1.x - line2.point2.x) == 0)
	{
		CrossP.x = 9999999999999;
		CrossP.y = 9999999999999;
	}
	return CrossP;
}

int FirstReflection::vertex_triangle(TwoDimPoint pa, TwoDimPoint pb, TwoDimPoint pc, TwoDimPoint vertex1)//判断点是否在三角形内
{
	float k1, b1,k2,b2,k3,b3;
	float result1,result2,result3;

	if(pb.x!=pc.x)
	{
		k1 = (pc.y - pb.y) / (pc.x - pb.x);
		b1 = pb.y - k1*pb.x;
		result1 = (k1*vertex1.x + b1 - vertex1.y)*(k1*pa.x+b1-pa.y);
	}
	else
	{
		result1=(pa.x-pb.x)*(vertex1.x-pb.x);
	}
	/*cout<<result1<<endl;*/
	if(pb.x!=pa.x)
	{
		k2 = (pb.y - pa.y) / (pb.x - pa.x);
		b2 = pa.y - k2*pa.x;
		result2 = (k2*vertex1.x + b2 - vertex1.y)*(k2*pc.x+b2-pc.y);
	}
	else
		result2=(pc.x-pa.x)*(vertex1.x-pa.x);
	/*cout<<result2<<endl;*/
	if(pc.x!=pa.x)
	{
		k3 = (pc.y - pa.y) / (pc.x - pa.x);
		b3= pc.y - k3*pc.x;
		result3 = (k3*vertex1.x + b3 - vertex1.y)*(k3*pb.x+b3-pb.y);
	}
	else
		result3=(pb.x-pc.x)*(vertex1.x-pc.x);
	/*cout<<result3<<endl;*/
	if (result1>=0&&result2>=0&&result3>=0)

		/*cout<<"in"<<endl;*/
		return 1;
	else
		/*cout<<"out"<<endl;*/
		return 0;

}

int FirstReflection::vertex_polygon(TwoDimPoint vertex0)                               //把多边形分解成多个三角形
{
	//TwoDimPoint vertex;
	int i;
	for (i = 0; i<polyPoint.size()-3; i++)
	{
		if (vertex_triangle(polyPoint[0], polyPoint[i + 1], polyPoint[i + 2], vertex0) == 1)
			return 1;
	}
	return 0;
}

void FirstReflection::buildingCross(float shootingStartX,float shootingStartY,float shootingStartZ,float shootingDirectionX,float shootingDirectionY,float shootingDirectionZ,vector<BuildingPoint> BPoint,float buildingHeight)
{
	line line1;
	line line2;
	TwoDimPoint CointP;
	TwoDimPoint vertex;

	int sideFlag=0;
	//int roofFlag;
	float X,Y,Z;
	float x,y,z;

	for(int k=0;k<BPoint.size();k++)
	{
		TwoDimPoint temp;
		temp.x=BPoint[k].getPx();
		temp.y=BPoint[k].getPy();
		polyPoint.push_back(temp);

	//polyPoint[k].x=BPoint[k].px;
	//polyPoint[k].y=BPoint[k].py;
	}
	line1.point1.x = shootingStartX;
	line1.point1.y = shootingStartY;
	line1.point2.x = shootingStartX + shootingDirectionX;
	line1.point2.y = shootingStartY + shootingDirectionY;

	//float buildingHeight=15;
/*
	printf("请输入建筑物高度:");                      //这里应该调用建筑物高度的vector
	scanf_s("%f", &h);
*/

	//求射线与建筑物侧面的交点
	refPolyPoint[0].x = 0;
	refPolyPoint[0].y = 0;
	refPolyPoint[1].x = 0;
	refPolyPoint[1].y = 0;
	float little = 9999999999;
	//因为给的点的向量中第一个点和最后一个点是重复的
	for (int i = 0; i < polyPoint.size()-1; i++)
	{
		if (i != polyPoint.size() - 2)
		{
			line2.point1.x = polyPoint[i].x;
			line2.point1.y = polyPoint[i].y;
			line2.point2.x = polyPoint[i + 1].x;
			line2.point2.y = polyPoint[i + 1].y;
		}
		else
		{
			line2.point1.x = polyPoint[i].x;
			line2.point1.y = polyPoint[i].y;
			line2.point2.x = polyPoint[0].x;
			line2.point2.y = polyPoint[0].y;
		}
		CointP = getCross(line1, line2);

			if (min(line2.point1.x, line2.point2.x) <= CointP.x && CointP.x <= max(line2.point1.x, line2.point2.x))
			{

				float distant;
				
				z = shootingStartZ + shootingDirectionZ / shootingDirectionX *(CointP.x - shootingStartX);
				if (z < buildingHeight)
				{
					sideFlag=1;
					distant = sqrt(pow(CointP.x - line1.point1.x, 2) + pow(CointP.y - line1.point1.y, 2) + pow(z - shootingStartZ, 2));
					if (distant <= little)
					{
						little = distant;
						X = CointP.x;
						Y = CointP.y;
						Z = z;

						refPolyPoint[0].x = line2.point1.x;
						refPolyPoint[0].y = line2.point1.y;
						refPolyPoint[1].x = line2.point2.x;
						refPolyPoint[1].y = line2.point2.y;
					}
				}
			}
		
	}

	//求射线与建筑物顶面的交点
	if (shootingDirectionZ != 0)
	{
		z = buildingHeight;
		float t = (z - shootingStartZ) / shootingDirectionZ;
		x = shootingStartX + shootingDirectionX*t;
		y = shootingStartY + shootingDirectionY*t;
		vertex.x = x;
		vertex.y = y;

		if (vertex_polygon(vertex) == 1)
		{
			//cout<<"射线与建筑物顶面交点为:"<< x<<'\t'<< y<<'\t'<< z<<endl;
			roofFlag=1;
			
		}

		else
		{
			//cout<<"射线与建筑物侧顶面无交点！"<<'\n';
			//sideFlag = 0;
			roofFlag=0;
		}
	}
	else
	{
		//cout<<"射线与建筑物顶面无交点！"<<'\n';
		//sideFlag = 0;
		roofFlag=0;
	}
	
	//综合侧面和顶面，判断射线与建筑物是否相交，若相交给出交点。同时给出标志位的值。

	if (sideFlag == 1 && roofFlag == 1)
	{
		float L1 = sqrt(pow((X - shootingStartX), 2) + pow((Y - shootingStartY), 2) + pow((Z - shootingStartZ), 2));
		float L2 = sqrt(pow((x - shootingStartX), 2) + pow((y - shootingStartY), 2) + pow((z - shootingStartZ), 2));
		if (L1 < L2)
		{
			crossX = X;
			crossY = Y;
			crossZ = Z;
			//cout<<"射线与建筑物的交点为:"<< crossX<<'\t'<< crossY<<'\t'<< crossZ<<endl;
			//cout<<refPolyPoint[0].x<<'\t'<<refPolyPoint[0].y<<'\t'<<refPolyPoint[1].x<<'\t'<<refPolyPoint[1].y<<endl;
			roofFlag=0;
			buildingCrossFlag=1;
		}
		else
		{
			crossX = x;
			crossY = y;
			crossZ = z;
			//cout<<"射线与建筑物的交点为:"<< crossX<<'\t'<< crossY<<'\t'<< crossZ<<endl;
			roofFlag=1;
			sideFlag=0;
			buildingCrossFlag=1;
		}
	}
	else if (sideFlag == 1 && roofFlag == 0)
	{
		crossX = X;
		crossY = Y;
		crossZ = Z;
		//cout<<"射线与建筑物的交点为:"<< crossX<<'\t'<< crossY<<'\t'<< crossZ<<endl;
		//cout<<refPolyPoint[0].x<<refPolyPoint[0].y<<refPolyPoint[1].x<<refPolyPoint[1].y<<endl;
		buildingCrossFlag=1;
	}

	else if (sideFlag == 0 && roofFlag == 1)
	{
		crossX = x;
		crossY = y;
		crossZ = z;
	//	cout<<"射线与建筑物的交点为:"<< crossX<<'\t'<< crossY<<'\t'<< crossZ<<endl;
		buildingCrossFlag=1;
	}
	else 
		{
	 		//cout<<"射线与建筑物无交点！"<<'\n';
	        buildingCrossFlag=0;
	    }

}