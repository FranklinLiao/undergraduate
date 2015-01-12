#include "stdafx.h"
#include "RecordAreaInfoTool.h"
#define COLCNT 7
#define ROWSTART 4
#define TITLESTART 2
////for  debug memory leak
//#include <crtdbg.h>
//#ifdef _DEBUG
//#define DEBUG_CLIENTBLOCK new(_CLIENT_BLOCK,__FILE__,__LINE__)
//#else
//#define DEBUG_CLIENTBLOCK
//#endif
//#define _CRTDBG_MAP_ALLOC
//#ifdef _DEBUG
//#define new DEBUG_CLIENTBLOCK
//#endif

bool RecordAreaInfoTool::insertAreaInfo(CString FileName) {
	DBHelper::deleteData("Area");
	DBHelper::deleteData("AreaFreq");
	int rowCount=0;
	int columnCount=0;
	bool returnFlag = false;//������ʶ��ȡС����Ϣʱ���Ƿ�������쳣
	bool flag = false;  //��ʶ�Ƿ�ͨ����ͼ��Χ������¼���С��
	//ͨ����ͼ���綨��С���Ƿ��ڵ�ͼ��
	double MaxLongi=180.0,MinLongi=0.0;
	double MaxLati=90.0,MinLati=0.0;
	if(flag) {
		vector<double> lonLatBounds=GetLonLatBoundsTool::getLonLatBounds();
		//���½�ά����С���������
		double x11=lonLatBounds.at(1); //��С����
		double y11=lonLatBounds.at(2); //���ά��
		double x12=lonLatBounds.at(0); //��󾭶�
		double y12=lonLatBounds.at(3); //��Сά��
		//���������С�ľ��ȣ����ľ��ȣ���С��ά�ȣ�����ά��
		double MaxLongi=x12,MinLongi=x11;
		double MaxLati=y11,MinLati=y12;
	}
	/* //������GSMʹ��
	int antannaHeight,antannaAspectAngle;
	int antannaDeclineAngle,refectLength,antannaType,baseStationType,coverType;
	double longitudeValue,latitudeValue,antannaHeightValue,antannaAspectAngleValue;
	double antannaDeclineAngleValue,refectLengthValue;
	int antannaTypeValue,baseStationTypeValue;
	double coverTypeValue;
	long columIndex[COLCNT];
	long freqIndex[24]={0};
	//���ݵ���ȡ
	string antannaHeightValueString;
	vector<int> antannaHeightInt;
	string antannaAspectAngleValueString;
	vector<int> antannaAspectAngleInt;
	string antannaDeclineAngleValueString;
	vector<int> antannaDeclineAngleInt; 
	string refectLengthValueString;
	vector<int> refectLengthInt;
	string baseStationTypeValueString;
	int ABSIC;
	*/
	int height,aspectAngle,declineAngle;
	double longitude,latitude;
	string areaName;
	long columIndex[COLCNT]; //��¼ÿ�����ݵ�������
	//���ݵ���ȡ
	string heightString;
	string aspectAngleString;
	string declineAngleString;
	int aPCI;
	int id = 1;	 //������¼�ж��ٸ�С��
	try {
		const char *p = (LPCSTR)FileName;
		CppCSV cs(p);  
		map<u32, map<u32, string>> stringMap = cs.GetCSVMap();  
		//oef.LoadSheet(1,FALSE);  //δ��֤�Ƿ���Բ��������Ӻ���صķ���
		rowCount = stringMap.size();
		columnCount = stringMap.begin()->second.size();	
		//��ȡ����Ҫ����Ϣ������
		for(long i =1;i<=(long)columnCount;i++) {
				if(strcmp(cs.GetStringValue((long)TITLESTART,i)->c_str(),"����")==0) {
					columIndex[0]=i;
				}else if(strcmp(cs.GetStringValue((long)TITLESTART,i)->c_str(),"γ��")==0) {
					columIndex[1]=i;
				}else if(strcmp(cs.GetStringValue((long)TITLESTART,i)->c_str(),"���߹Ҹ�")==0) {
					columIndex[2]=i;
				}else if(strcmp(cs.GetStringValue((long)TITLESTART,i)->c_str(),"��λ��")==0) {
					columIndex[3]=i;
				}else if(strcmp(cs.GetStringValue((long)TITLESTART,i)->c_str(),"�����")==0) {
					columIndex[4]=i;
				}else if(strcmp(cs.GetStringValue((long)TITLESTART,i)->c_str(),"����С����ʶ")==0) {
					columIndex[5]=i;
				}else if(strcmp(cs.GetStringValue((long)TITLESTART,i)->c_str(),"С������")==0) {
					columIndex[6]=i;
				}
				/*else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"���߳���")==0) {
					columIndex[5]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"�����ͺ�")==0) {
					columIndex[6]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"��վ����")==0) {
					columIndex[7]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"�ǽ���")==0) {
					columIndex[8]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"NCC")==0) {
					columIndex[9]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"BCC")==0) {
					columIndex[10]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"BCCH")==0) {  //��ʼ��ȡƵ��
					freqIndex[0]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"SDCCH")==0) {  //��ʼ��ȡƵ��
					freqIndex[1]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"TRX3")==0) {  //��ʼ��ȡƵ��
					freqIndex[2]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"TRX4")==0) {  //��ʼ��ȡƵ��
					freqIndex[3]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"TRX5")==0) {  //��ʼ��ȡƵ��
					freqIndex[4]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"TRX6")==0) {  //��ʼ��ȡƵ��
					freqIndex[5]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"TRX7")==0) {  //��ʼ��ȡƵ��
					freqIndex[6]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"TRX8")==0) {  //��ʼ��ȡƵ��
					freqIndex[7]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"TRX9")==0) {  //��ʼ��ȡƵ��
					freqIndex[8]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"TRX10")==0) {  //��ʼ��ȡƵ��
					freqIndex[9]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"TRX11")==0) {  //��ʼ��ȡƵ��
					freqIndex[10]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"TRX12")==0) {  //��ʼ��ȡƵ��
					freqIndex[11]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"TRX13")==0) {  //��ʼ��ȡƵ��
					freqIndex[12]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"TRX14")==0) {  //��ʼ��ȡƵ��
					freqIndex[13]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"TRX15")==0) {  //��ʼ��ȡƵ��
					freqIndex[14]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"TRX16")==0) {  //��ʼ��ȡƵ��
					freqIndex[15]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"TRX17")==0) {  //��ʼ��ȡƵ��
					freqIndex[16]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"TRX18")==0) {  //��ʼ��ȡƵ��
					freqIndex[17]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"TRX19")==0) {  //��ʼ��ȡƵ��
					freqIndex[18]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"TRX20")==0) {  //��ʼ��ȡƵ��
					freqIndex[19]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"TRX21")==0) {  //��ʼ��ȡƵ��
					freqIndex[20]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"TRX22")==0) {  //��ʼ��ȡƵ��
					freqIndex[21]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"TRX23")==0) {  //��ʼ��ȡƵ��
					freqIndex[22]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"TRX24")==0) {  //��ʼ��ȡƵ��
					freqIndex[23]=i;
				}*/
		}
		
		//��һ����������,�ڶ����Ƕ�Ӧ��ֵ
		//ȥ�������һ��
		for(long j =ROWSTART;j<((long)rowCount);j++) {
			string valueString[COLCNT];
			//int valueStringLength = COLCNT;
			//ȡ��ÿ������Ҫ�����ݣ����뵽valueString������
			for(int i =0;i<COLCNT;i++) {
					string* temp = cs.GetStringValue(j,columIndex[i]);
					if(temp) {
						valueString[i]=*cs.GetStringValue(j,columIndex[i]);
					} else {
						valueString[i]="0";
					}
					//valueString[i] = *cs.GetStringValue(j,columIndex[i]);
			}
			//��valueString�����ݣ���ȡ�������뵽���ݿ���
			//��γ����Ҫ��ôʹ��
			longitude=ChangeTypeTool::stringToDouble(valueString[0]);
			latitude=ChangeTypeTool::stringToDouble(valueString[1]);
			height = ChangeTypeTool::stringToInt(valueString[2]);
			aspectAngle = ChangeTypeTool::stringToInt(valueString[3]);
			declineAngle = ChangeTypeTool::stringToInt(valueString[4]);
			aPCI = ChangeTypeTool::stringToInt(valueString[5]);
			areaName = valueString[6];
			/*
			baseStationTypeValueString  = valueString[7];
			baseStationTypeValue=FreqTypeDefine::getFreqTypeNum(baseStationTypeValueString);
			coverTypeValue=CoverTypeDefine::getCoverTypeValue(valueString[8]);
			ABSIC = ChangeTypeTool::stringToInt(valueString[9]) * 8 + ChangeTypeTool::stringToInt(valueString[10]);
			antannaHeightValueString=valueString[2];
			antannaHeightInt = ChangeTypeTool::strSplitPlus(antannaHeightValueString);
			antannaAspectAngleValueString = valueString[3];
			antannaAspectAngleInt = ChangeTypeTool::strSplitPlus(antannaAspectAngleValueString);
			antannaDeclineAngleValueString = valueString[4];
			antannaDeclineAngleInt = ChangeTypeTool::strSplitPlus(antannaDeclineAngleValueString);
			refectLengthValueString = valueString[5];
			refectLengthInt = ChangeTypeTool::strSplitPlus(refectLengthValueString);
			*/
			//antannaAspectAngleValue=ChangeTypeTool::stringToInt(valueString[3]);
			//antannaDeclineAngleValue=ChangeTypeTool::stringToInt(valueString[4]);
			//refectLengthValue=ChangeTypeTool::stringToDouble(valueString[5]);
			//antannaTypeValue=AntannaTypeDefine::getAntanaTypeDefineValue(valueString[6]);
			
			/*
			DBHelper::insertBaseStationToDB("Area",id,longitudeValue,latitudeValue,
				antannaHeightValue,antannaAspectAngleValue,antannaDeclineAngleValue,
				refectLengthValue,antannaTypeValue,baseStationTypeValue);
				*/
			
			//�ж������Ƿ���Ч
			/*
			if(!isValid(longitude,latitude,height,aspectAngle,declineAngle,aPCI)) {
				continue;
			}
			*/
			//���õ�ͼ�߽�������С��
			//ֻ�е�flagΪtrue,��������������ʱ���Ų�¼�� "��" �����������Ϊ��ʱ������û����
			if(flag&&(!(longitude > MinLongi) && (longitude < MaxLongi) && (latitude > MinLati) && (latitude < MaxLati))) {
					continue;
			} else {
				//����һ��������ȡ�ͱ����йص�����
				string tableName = "Area";
				string key[] = {"AId","ALongitude","ALatitude","AHeight","AAspectAngle","ADeclineAngle","APCI","AName"};
				string keyValue[] = {ChangeTypeTool::intToString(id),valueString[0],valueString[1],valueString[2],valueString[3],
					valueString[4],valueString[5],"'"+ valueString[6]+"'"};
				DBHelper::insertInfo(tableName,key,keyValue,sizeof(key)/sizeof(key[0]));
				id++;
				if(id==1200) {
					int temp = 1;
					temp+=1;
				}
			}
					/*int kk = antannaAspectAngleInt.size();
					for(int i = 0;i<antannaAspectAngleInt.size();i++) {
						string keyValue[] = {ChangeTypeTool::intToString(id),ChangeTypeTool::doubleToStringPrecise(longitudeValue),
							ChangeTypeTool::doubleToStringPrecise(latitudeValue),ChangeTypeTool::doubleToStringPrecise(antannaHeightInt.at(i),2),
							ChangeTypeTool::intToString(antannaAspectAngleInt.at(i)),ChangeTypeTool::intToString(antannaDeclineAngleInt.at(i)),ChangeTypeTool::intToString(refectLengthInt.at(i)),
							ChangeTypeTool::intToString(baseStationTypeValue),ChangeTypeTool::doubleToString(coverTypeValue),ChangeTypeTool::intToString(ABSIC)};
						DBHelper::insertInfo(tableName,key,keyValue,sizeof(key)/sizeof(key[0]));
				
					*/
					//��ȡƵ�㵽���ݿ���
					//string freqValueString[25]={""};
					/*int freCount=0;
					while(oef.GetCellInt(j,freqIndex[freCount])!=0) {
					int kk = freqIndex[freCount];
					freCount++;
					}*/
					/*
					for(int i =0;(i<sizeof(freqIndex)/sizeof(freqIndex[0]))&&(strcmp(cs.GetStringValue((long)j,freqIndex[i])->c_str(),"")!=0);i++) {
					
							string freqValue=*cs.GetStringValue((long)j,freqIndex[i]);
							//int freqId = j-1;
							string tableName = "AreaFreq";
							string key[] = {"AId","ALongitude","ALatitude","AFreq"};
							string keyValue[] = {ChangeTypeTool::intToString(id),ChangeTypeTool::doubleToStringPrecise(longitudeValue),
								ChangeTypeTool::doubleToStringPrecise(latitudeValue),freqValue};
							DBHelper::insertInfo(tableName,key,keyValue,sizeof(key)/sizeof(key[0]));
					
					}
					*/
		}
		returnFlag = true;
	} catch(COleDispatchException* e) {
		e->ReportError();
		e->Delete();
	} catch(COleException* e) {
		e->ReportError();
		e->Delete();
	}
	return returnFlag;
}


//�ж�¼��������Ƿ���Ч
bool RecordAreaInfoTool::isValid(double longitude,double latitude,int height,int aspectAngle,int declineAngle,int aPCI) {
	if((longitude!=0)&&(latitude!=0)&&(height>0)&&(aspectAngle>0)&&(declineAngle>0)){
		return true;
	}else {
		return false;
	}
}