#ifndef _GRIDPOWER_H
#define _GRIDPOWER_H
#include "stdafx.h"
#include<iostream>
#include "findGrid.h"
#include "rayManage.h"
#include"gridPowerResult.h"
#include "Grid.h"
#include "rayPath.h"
#include "complex.h"
#include<cmath>
using namespace std;
class gridPower//���ڼ�����ն˵Ĺ���
{
   
   public:
	   void findGroundGridPowerFirst(float groundCrossPointx,float groundCrossPointy,float shootingStartx,float shootingStarty,
		   float shootingStartz,float shootingDirectiona,float shootingDirectionb,float shootingDirectionc,float shootingLength,float antennaGain,gridPowerResult gridNumber[]);//���߸տ�ʼ����ؼ���������
	   //���ߵ���ʱ����䵽���棬����Ե�������Ĺ���
	   void findGroundGridPowerSecond(float groundCrossPointx,float groundCrossPointy,float shootingStartx,float shootingStarty,float shootingStartz,float shootingDirectiona,float shootingDirectionb,float shootingDirectionc,float shootingLength,float antennaGain,float totalRefCoefficient,gridPowerResult gridNumber[]);
	   void gridAllPowerCalculate(rayPath raypath1,gridPowerResult gridNumber[],float rayInterval,float frequence);//���ڼ������߶���������Ĺ���,���һ�������������߼�������ڼ��������,Ƶ����MHZΪ��λ
	 
};

#endif