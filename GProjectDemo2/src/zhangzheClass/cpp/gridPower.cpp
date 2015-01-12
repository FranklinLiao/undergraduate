
#include "stdafx.h"
#include "gridPower.h"
 

void gridPower::findGroundGridPowerFirst(float groundCrossPointx,float groundCrossPointy,float shootingStartx,float shootingStarty,float shootingStartz,
	float shootingDirectiona,float shootingDirectionb,float shootingDirectionc,float shootingLength,float antennaGain,gridPowerResult gridNumber[])//射线刚开始就落地计算网格功率
{
	findGrid findgrid1;
	int q1,q2;
	q1=findgrid1.findpointgridx(groundCrossPointx,shootingDirectiona);
	q2=findgrid1.findpointgridy(groundCrossPointy,shootingDirectionb);
	float gridCenterX, gridCenterY;
	rayManage raymanage1;
	gridCenterX=raymanage1.findGridCenterxy(q1);//求出网格中心点的横坐标
	gridCenterY=raymanage1.findGridCenterxy(q2);//求出网格中心点的纵坐标
	float receiveBallR;
	receiveBallR=3.14*shootingLength*3/(180*sqrt(3.0));
	float pointDistance;//点到直线的距离
	pointDistance=raymanage1.findPointToLineDistance(shootingStartx,shootingStarty,shootingStartz,shootingDirectiona,shootingDirectionb,shootingDirectionc,gridCenterX,gridCenterY,0);
	if(pointDistance<receiveBallR)
	{
		float antennaPower=46;//基站发射的起始功率为46dbm，这里是个参数，是可调的
		float baseStationloss=0;//基站的损耗，这里先考虑为0
		float receivePower;//接收功率
		receivePower=antennaPower-10.9921-20*log10( shootingLength)+antennaGain;//10.9921代表10log4pai
		receivePower=exp(log(10.0)*(receivePower/10));
		int gridId;
		//Grid grid1;
		//gridId=grid1.findGridId(gridCenterX,gridCenterY);
		 //gridId=3;//暂时赋值，需要改的
		//只有在贾其所给的地图范围内才可以向网格中存取功率
		//这个是需要根据地图的大小而改变的
		if(gridCenterX>0&&gridCenterX<55&&gridCenterY>0&&gridCenterY<75)
		{
			Grid grid1;
		//grid1.GetThisGirdRecord(gridCenterX,gridCenterY);
			grid1 = Grid::getMyselfByXY(gridCenterX,gridCenterY);
			gridId=grid1.getGId();
		//cout<<gridId<<endl;
		 

//		gridNumber[gridId].gridFinalPower.push_back(receivePower);//将射线落地后的网格功率放入到向量中，以便最后求和
		}
		
	}
	


}
//射线迭代时如果落到地面，计算对地面网格的贡献
void gridPower::findGroundGridPowerSecond(float groundCrossPointx,float groundCrossPointy,float shootingStartx,float shootingStarty,float shootingStartz,
	float shootingDirectiona,float shootingDirectionb,float shootingDirectionc,float shootingLength,float antennaGain,float totalRefCoefficient,gridPowerResult gridNumber[])
{
	
	findGrid findgrid1;
	int q1,q2;
	q1=findgrid1.findpointgridx(groundCrossPointx,shootingDirectiona);
	q2=findgrid1.findpointgridy(groundCrossPointy,shootingDirectionb);
	float gridCenterX, gridCenterY;
	rayManage raymanage1;
	gridCenterX=raymanage1.findGridCenterxy(q1);//求出网格中心点的横坐标
	gridCenterY=raymanage1.findGridCenterxy(q2);//求出网格中心点的纵坐标
	float receiveBallR;
	receiveBallR=3.14*shootingLength*3/(180*sqrt(3.0));
	float pointDistance;//点到直线的距离
	pointDistance=raymanage1.findPointToLineDistance(shootingStartx,shootingStarty,shootingStartz,shootingDirectiona,shootingDirectionb,shootingDirectionc,gridCenterX,gridCenterY,0);
	if(pointDistance<receiveBallR)
	{
		float antennaPower=46;//基站发射的起始功率为46dbm，这里是个参数，是可调的
		float baseStationloss=0;//基站的损耗，这里先考虑为0
		float receivePower;//接收功率
		receivePower=antennaPower-10.9921-20*log10(shootingLength)+antennaGain+20*log10(totalRefCoefficient);//10.9921代表10log4pai
		receivePower=exp(log(10.0)*(receivePower/10));
		int gridId;
		//只有在贾其所给的地图范围内才可以向网格中存取功率
		//这个是需要根据地图的大小而改变的
		if(gridCenterX>0&&gridCenterX<55&&gridCenterY>0&&gridCenterY<75)
		{
		Grid grid1;
		grid1 = Grid::getMyselfByXY(gridCenterX,gridCenterY);
		//grid1.GetThisGirdRecord(gridCenterX,gridCenterY);
		gridId=grid1.getGId();
		//cout<<gridId<<endl;
//		gridNumber[gridId].gridFinalPower.push_back(receivePower);//将射线落地后的网格功率放入到向量中，以便最后求和
		}
	}
	 


}

void gridPower::gridAllPowerCalculate(rayPath raypath1,gridPowerResult gridNumber[],float rayInterval,float frequence)//计算射线对所有网格的功率
{
	int lineNumber;//一条射线的线段数
	lineNumber=raypath1.searchGridNumberTrue.size();
	for(int i=1;i<=lineNumber;i++)
	{
		int lineGridNumber;//一个线段包含的网格数
		lineGridNumber=raypath1.searchGridNumberTrue[i-1];
		float lineLengthBefore=0;//在计算接收球半径时用于计算之前的路径长度
		int totalNumber;
		int lineGridNumberBefore=0;//在搜索网格编号时能够保证从线段编号处运行
		complex totalCoefficienrt={1,0};//用来记录复的反射系数,初始值设置为1
		totalNumber=i-1;
		for(int q=1;q<=totalNumber;q++)
		{
			lineLengthBefore=lineLengthBefore+raypath1.rayLength[q-1];
			complexCalculate complexcalculate2;
			complexcalculate2.findComplexMulComplex(totalCoefficienrt,raypath1.reflectComplexCoefficient[q-1]);
			totalCoefficienrt=complexcalculate2.consequence;
			lineGridNumberBefore=lineGridNumberBefore+raypath1.searchGridNumberTrue[q-1];
		}
		for(int j=1;j<=lineGridNumber;j++)
		{
			int gridX,gridY;//用于记录网格编号
			gridX=raypath1.searchGridTrueX[lineGridNumberBefore+j-1];
			gridY=raypath1.searchGridTrueY[lineGridNumberBefore+j-1];
			rayManage raymanage3;
			float gridCenterX, gridCenterY;
			gridCenterX=raymanage3.findGridCenterxy(gridX);//求出网格中心点的横坐标
			gridCenterY=raymanage3.findGridCenterxy(gridY);//求出网格中心点的纵坐标
			float pointDistance;//点到直线的距离
			pointDistance=raymanage3.findPointToLineDistance(raypath1.crossPointx[i-1],raypath1.crossPointy[i-1],raypath1.crossPointz[i-1],
				raypath1.reflecttDirectiona[i-1],raypath1.reflecttDirectionb[i-1],raypath1.reflecttDirectionc[i-1],gridCenterX,gridCenterY,1.5);
			float lineLengthAfter;//针对本段射线的长度
			lineLengthAfter=raymanage3.findShootingLineLength(raypath1.crossPointx[i-1],raypath1.crossPointy[i-1],raypath1.crossPointz[i-1],
				raypath1.reflecttDirectiona[i-1],raypath1.reflecttDirectionb[i-1],raypath1.reflecttDirectionc[i-1],gridCenterX,gridCenterY,1.5);
			float lineLengthFinal;//射线路径的总长度
			lineLengthFinal=lineLengthAfter+lineLengthBefore;
			float receiveBallR;
			receiveBallR=3.14*lineLengthFinal*rayInterval/(180*sqrt(3.0));
			if(pointDistance<receiveBallR)
			{
				/*
				float antennaPower=46;//基站发射的起始功率为46dbm，这里是个参数，是可调的
				float baseStationloss=0;//基站的损耗，这里先考虑为0
				float receivePower;//接收功率
				receivePower=antennaPower-10.9921-20*log10( lineLengthFinal)+raypath1.rayGain;//10.9921代表10log4pai
				receivePower=exp(log(10.0)*(receivePower/10));				
				*/
				//Grid grid1;
				//gridId=grid1.findGridId(gridCenterX,gridCenterY);
				//gridId=3;//暂时赋值，需要改的
				//只有在贾其所给的地图范围内才可以向网格中存取功率
				//这个是需要根据地图的大小而改变的
				//if(gridCenterX>0&&gridCenterX<55&&gridCenterY>0&&gridCenterY<75)
				float waveLength;//定义波长
				waveLength=300/frequence;//频率以MHZ为单位
				complex receiveElecFiledStrength;//得到接收到的电场强度值，发射功率仍然以46dbm为参考，这里的单位换成w,39.8w
				receiveElecFiledStrength.real=(sqrt(30*39.8))*cos(6.28*lineLengthFinal/waveLength)/lineLengthFinal;
				receiveElecFiledStrength.img=(-1)*(sqrt(30*39.8))*sin(6.28*lineLengthFinal/waveLength)/lineLengthFinal;
				complexCalculate complexcalculate3;
				complexcalculate3.findComplexMulComplex(receiveElecFiledStrength,totalCoefficienrt);//接收到的电场强度乘以反射系数
				receiveElecFiledStrength=complexcalculate3.consequence;//得到最终的电场强度
				    int gridId;
					Grid grid1;
					grid1 = Grid::getMyselfByXY(gridCenterX,gridCenterY);
					//grid1.GetThisGirdRecord(gridCenterX,gridCenterY);
					gridId=grid1.getGId();
					//cout<<gridId<<endl;
	    		gridNumber[gridId].gridFinalPower.push_back(receiveElecFiledStrength);//将射线落地后的网格功率放入到向量中，以便最后求和
				

			}
		}
	}
}
