
#include "stdafx.h"
#include "gridPower.h"
 

void gridPower::findGroundGridPowerFirst(float groundCrossPointx,float groundCrossPointy,float shootingStartx,float shootingStarty,float shootingStartz,
	float shootingDirectiona,float shootingDirectionb,float shootingDirectionc,float shootingLength,float antennaGain,gridPowerResult gridNumber[])//���߸տ�ʼ����ؼ���������
{
	findGrid findgrid1;
	int q1,q2;
	q1=findgrid1.findpointgridx(groundCrossPointx,shootingDirectiona);
	q2=findgrid1.findpointgridy(groundCrossPointy,shootingDirectionb);
	float gridCenterX, gridCenterY;
	rayManage raymanage1;
	gridCenterX=raymanage1.findGridCenterxy(q1);//����������ĵ�ĺ�����
	gridCenterY=raymanage1.findGridCenterxy(q2);//����������ĵ��������
	float receiveBallR;
	receiveBallR=3.14*shootingLength*3/(180*sqrt(3.0));
	float pointDistance;//�㵽ֱ�ߵľ���
	pointDistance=raymanage1.findPointToLineDistance(shootingStartx,shootingStarty,shootingStartz,shootingDirectiona,shootingDirectionb,shootingDirectionc,gridCenterX,gridCenterY,0);
	if(pointDistance<receiveBallR)
	{
		float antennaPower=46;//��վ�������ʼ����Ϊ46dbm�������Ǹ��������ǿɵ���
		float baseStationloss=0;//��վ����ģ������ȿ���Ϊ0
		float receivePower;//���չ���
		receivePower=antennaPower-10.9921-20*log10( shootingLength)+antennaGain;//10.9921����10log4pai
		receivePower=exp(log(10.0)*(receivePower/10));
		int gridId;
		//Grid grid1;
		//gridId=grid1.findGridId(gridCenterX,gridCenterY);
		 //gridId=3;//��ʱ��ֵ����Ҫ�ĵ�
		//ֻ���ڼ��������ĵ�ͼ��Χ�ڲſ����������д�ȡ����
		//�������Ҫ���ݵ�ͼ�Ĵ�С���ı��
		if(gridCenterX>0&&gridCenterX<55&&gridCenterY>0&&gridCenterY<75)
		{
			Grid grid1;
		//grid1.GetThisGirdRecord(gridCenterX,gridCenterY);
			grid1 = Grid::getMyselfByXY(gridCenterX,gridCenterY);
			gridId=grid1.getGId();
		//cout<<gridId<<endl;
		 

//		gridNumber[gridId].gridFinalPower.push_back(receivePower);//��������غ�������ʷ��뵽�����У��Ա�������
		}
		
	}
	


}
//���ߵ���ʱ����䵽���棬����Ե�������Ĺ���
void gridPower::findGroundGridPowerSecond(float groundCrossPointx,float groundCrossPointy,float shootingStartx,float shootingStarty,float shootingStartz,
	float shootingDirectiona,float shootingDirectionb,float shootingDirectionc,float shootingLength,float antennaGain,float totalRefCoefficient,gridPowerResult gridNumber[])
{
	
	findGrid findgrid1;
	int q1,q2;
	q1=findgrid1.findpointgridx(groundCrossPointx,shootingDirectiona);
	q2=findgrid1.findpointgridy(groundCrossPointy,shootingDirectionb);
	float gridCenterX, gridCenterY;
	rayManage raymanage1;
	gridCenterX=raymanage1.findGridCenterxy(q1);//����������ĵ�ĺ�����
	gridCenterY=raymanage1.findGridCenterxy(q2);//����������ĵ��������
	float receiveBallR;
	receiveBallR=3.14*shootingLength*3/(180*sqrt(3.0));
	float pointDistance;//�㵽ֱ�ߵľ���
	pointDistance=raymanage1.findPointToLineDistance(shootingStartx,shootingStarty,shootingStartz,shootingDirectiona,shootingDirectionb,shootingDirectionc,gridCenterX,gridCenterY,0);
	if(pointDistance<receiveBallR)
	{
		float antennaPower=46;//��վ�������ʼ����Ϊ46dbm�������Ǹ��������ǿɵ���
		float baseStationloss=0;//��վ����ģ������ȿ���Ϊ0
		float receivePower;//���չ���
		receivePower=antennaPower-10.9921-20*log10(shootingLength)+antennaGain+20*log10(totalRefCoefficient);//10.9921����10log4pai
		receivePower=exp(log(10.0)*(receivePower/10));
		int gridId;
		//ֻ���ڼ��������ĵ�ͼ��Χ�ڲſ����������д�ȡ����
		//�������Ҫ���ݵ�ͼ�Ĵ�С���ı��
		if(gridCenterX>0&&gridCenterX<55&&gridCenterY>0&&gridCenterY<75)
		{
		Grid grid1;
		grid1 = Grid::getMyselfByXY(gridCenterX,gridCenterY);
		//grid1.GetThisGirdRecord(gridCenterX,gridCenterY);
		gridId=grid1.getGId();
		//cout<<gridId<<endl;
//		gridNumber[gridId].gridFinalPower.push_back(receivePower);//��������غ�������ʷ��뵽�����У��Ա�������
		}
	}
	 


}

void gridPower::gridAllPowerCalculate(rayPath raypath1,gridPowerResult gridNumber[],float rayInterval,float frequence)//�������߶���������Ĺ���
{
	int lineNumber;//һ�����ߵ��߶���
	lineNumber=raypath1.searchGridNumberTrue.size();
	for(int i=1;i<=lineNumber;i++)
	{
		int lineGridNumber;//һ���߶ΰ�����������
		lineGridNumber=raypath1.searchGridNumberTrue[i-1];
		float lineLengthBefore=0;//�ڼ��������뾶ʱ���ڼ���֮ǰ��·������
		int totalNumber;
		int lineGridNumberBefore=0;//������������ʱ�ܹ���֤���߶α�Ŵ�����
		complex totalCoefficienrt={1,0};//������¼���ķ���ϵ��,��ʼֵ����Ϊ1
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
			int gridX,gridY;//���ڼ�¼������
			gridX=raypath1.searchGridTrueX[lineGridNumberBefore+j-1];
			gridY=raypath1.searchGridTrueY[lineGridNumberBefore+j-1];
			rayManage raymanage3;
			float gridCenterX, gridCenterY;
			gridCenterX=raymanage3.findGridCenterxy(gridX);//����������ĵ�ĺ�����
			gridCenterY=raymanage3.findGridCenterxy(gridY);//����������ĵ��������
			float pointDistance;//�㵽ֱ�ߵľ���
			pointDistance=raymanage3.findPointToLineDistance(raypath1.crossPointx[i-1],raypath1.crossPointy[i-1],raypath1.crossPointz[i-1],
				raypath1.reflecttDirectiona[i-1],raypath1.reflecttDirectionb[i-1],raypath1.reflecttDirectionc[i-1],gridCenterX,gridCenterY,1.5);
			float lineLengthAfter;//��Ա������ߵĳ���
			lineLengthAfter=raymanage3.findShootingLineLength(raypath1.crossPointx[i-1],raypath1.crossPointy[i-1],raypath1.crossPointz[i-1],
				raypath1.reflecttDirectiona[i-1],raypath1.reflecttDirectionb[i-1],raypath1.reflecttDirectionc[i-1],gridCenterX,gridCenterY,1.5);
			float lineLengthFinal;//����·�����ܳ���
			lineLengthFinal=lineLengthAfter+lineLengthBefore;
			float receiveBallR;
			receiveBallR=3.14*lineLengthFinal*rayInterval/(180*sqrt(3.0));
			if(pointDistance<receiveBallR)
			{
				/*
				float antennaPower=46;//��վ�������ʼ����Ϊ46dbm�������Ǹ��������ǿɵ���
				float baseStationloss=0;//��վ����ģ������ȿ���Ϊ0
				float receivePower;//���չ���
				receivePower=antennaPower-10.9921-20*log10( lineLengthFinal)+raypath1.rayGain;//10.9921����10log4pai
				receivePower=exp(log(10.0)*(receivePower/10));				
				*/
				//Grid grid1;
				//gridId=grid1.findGridId(gridCenterX,gridCenterY);
				//gridId=3;//��ʱ��ֵ����Ҫ�ĵ�
				//ֻ���ڼ��������ĵ�ͼ��Χ�ڲſ����������д�ȡ����
				//�������Ҫ���ݵ�ͼ�Ĵ�С���ı��
				//if(gridCenterX>0&&gridCenterX<55&&gridCenterY>0&&gridCenterY<75)
				float waveLength;//���岨��
				waveLength=300/frequence;//Ƶ����MHZΪ��λ
				complex receiveElecFiledStrength;//�õ����յ��ĵ糡ǿ��ֵ�����书����Ȼ��46dbmΪ�ο�������ĵ�λ����w,39.8w
				receiveElecFiledStrength.real=(sqrt(30*39.8))*cos(6.28*lineLengthFinal/waveLength)/lineLengthFinal;
				receiveElecFiledStrength.img=(-1)*(sqrt(30*39.8))*sin(6.28*lineLengthFinal/waveLength)/lineLengthFinal;
				complexCalculate complexcalculate3;
				complexcalculate3.findComplexMulComplex(receiveElecFiledStrength,totalCoefficienrt);//���յ��ĵ糡ǿ�ȳ��Է���ϵ��
				receiveElecFiledStrength=complexcalculate3.consequence;//�õ����յĵ糡ǿ��
				    int gridId;
					Grid grid1;
					grid1 = Grid::getMyselfByXY(gridCenterX,gridCenterY);
					//grid1.GetThisGirdRecord(gridCenterX,gridCenterY);
					gridId=grid1.getGId();
					//cout<<gridId<<endl;
	    		gridNumber[gridId].gridFinalPower.push_back(receiveElecFiledStrength);//��������غ�������ʷ��뵽�����У��Ա�������
				

			}
		}
	}
}
