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
class gridPower//用于计算接收端的贡献
{
   
   public:
	   void findGroundGridPowerFirst(float groundCrossPointx,float groundCrossPointy,float shootingStartx,float shootingStarty,
		   float shootingStartz,float shootingDirectiona,float shootingDirectionb,float shootingDirectionc,float shootingLength,float antennaGain,gridPowerResult gridNumber[]);//射线刚开始就落地计算网格功率
	   //射线迭代时如果落到地面，计算对地面网格的贡献
	   void findGroundGridPowerSecond(float groundCrossPointx,float groundCrossPointy,float shootingStartx,float shootingStarty,float shootingStartz,float shootingDirectiona,float shootingDirectionb,float shootingDirectionc,float shootingLength,float antennaGain,float totalRefCoefficient,gridPowerResult gridNumber[]);
	   void gridAllPowerCalculate(rayPath raypath1,gridPowerResult gridNumber[],float rayInterval,float frequence);//用于计算射线对所有网格的贡献,最后一个参数代表射线间隔，便于计算接收球,频率以MHZ为单位
	 
};

#endif