#include "stdafx.h"
#include "shootingRay.h"
void shootingRay::shootingGain(float directionAngle,float downInclineAngle,float horizonDivision,float verticalDivision)
{  
	memset(x,0,sizeof(x));
    memset(y,0,sizeof(y));
	memset(z,0,sizeof(z));
	memset(gain,0,sizeof(gain));
	float verticalAngle=downInclineAngle+90;
	float angleX, angleZ;
	int count,countTemp,countTemp1,countTemp2;
	//float x[5000], y[5000], z[5000],gain[5000];
	count=0;

	//把发射的射线空间上分成四部分，分别用for循环求出每条射线的方向向量和增益
	for(angleX=directionAngle;angleX<directionAngle+60;angleX=angleX+horizonDivision)
		for(angleZ=verticalAngle;angleZ<verticalAngle+15;angleZ=angleZ+verticalDivision)
		{
			x[count] = sin(angleZ*pi/180)*cos(angleX*pi/180);
			y[count] = sin(angleZ*pi/180)*sin(angleX*pi/180);
			z[count] = cos(angleZ*pi/180);
			gain[count]=gainMax-0.1*(angleX-directionAngle)-0.1*(angleZ-verticalAngle);

			//cout<<x[count]<<'\n'<<y[count]<<'\n'<<z[count]<<'\n'<<gain[count]<<endl;
			count = count + 1;
		}
		countTemp=count;

	for(angleX=directionAngle;angleX<directionAngle+60;angleX=angleX+horizonDivision)
		for(angleZ=verticalAngle;angleZ>verticalAngle-15;angleZ=angleZ-verticalDivision)
		{
			x[countTemp] = sin(angleZ*pi/180)*cos(angleX*pi/180);
			y[countTemp] = sin(angleZ*pi/180)*sin(angleX*pi/180);
			z[countTemp] = cos(angleZ*pi/180);
			gain[countTemp]=gainMax-0.1*(angleX-directionAngle)-0.1*(verticalAngle-angleZ);

			//cout<<x[countTemp]<<'\n'<<y[countTemp]<<'\n'<<z[countTemp]<<'\n'<<gain[countTemp]<<endl;
			countTemp = countTemp + 1; 
		}
		countTemp1=countTemp;

	for(angleX=directionAngle;angleX>directionAngle-60;angleX=angleX-horizonDivision)
		for(angleZ=verticalAngle;angleZ<verticalAngle+15;angleZ=angleZ+verticalDivision)
		{
			x[countTemp1] = sin(angleZ*pi/180)*cos(angleX*pi/180);
			y[countTemp1] = sin(angleZ*pi/180)*sin(angleX*pi/180);
			z[countTemp1] = cos(angleZ*pi/180);
			gain[countTemp1]=gainMax-0.1*(directionAngle-angleX)-0.1*(angleZ-verticalAngle);

		//	cout<<x[countTemp1]<<'\n'<<y[countTemp1]<<'\n'<<z[countTemp1]<<'\n'<<gain[countTemp1]<<endl;
			countTemp1 = countTemp1 + 1; 
		}
		countTemp2=countTemp1;

	for(angleX=directionAngle;angleX>directionAngle-60;angleX=angleX-horizonDivision)
		for(angleZ=verticalAngle;angleZ>verticalAngle-15;angleZ=angleZ-verticalDivision)
		{
			x[countTemp2] = sin(angleZ*pi/180)*cos(angleX*pi/180);
			y[countTemp2] = sin(angleZ*pi/180)*sin(angleX*pi/180);
			z[countTemp2] = cos(angleZ*pi/180);
			gain[countTemp2]=gainMax-0.1*(directionAngle-angleX)-0.1*(verticalAngle-angleZ);

			//cout<<x[countTemp2]<<'\n'<<y[countTemp2]<<'\n'<<z[countTemp2]<<'\n'<<gain[countTemp2]<<endl;
			countTemp2 = countTemp2 + 1; 
		}
}
void shootingRay::shootingGainAllDirection(float directionAngle,float downInclineAngle,float horizonRange, float verticalRange,
	float horizonDivision,float verticalDivision) 
{
	float verticalAngle=downInclineAngle+90;
	float angleX, angleZ;
	
	int count=0;

	for(angleX=directionAngle-horizonRange/2;angleX<=directionAngle+horizonRange/2;angleX=angleX+horizonDivision)
		for(angleZ=verticalAngle-verticalRange/2;angleZ<=verticalAngle+verticalRange/2;angleZ=angleZ+verticalDivision)
		{
			x[count] = sin(angleZ*pi/180)*cos(angleX*pi/180);
			y[count] = sin(angleZ*pi/180)*sin(angleX*pi/180);
			z[count] = cos(angleZ*pi/180);
			gain[count]=17.7;
		//	cout<<x[count]<<'\t'<<y[count]<<'\t'<<z[count]<<'\t'<<gain[count]<<endl;
			count=count+1;
		}

		//cout<<count<<endl;
}