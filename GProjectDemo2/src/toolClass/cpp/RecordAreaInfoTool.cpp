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
	bool returnFlag = false;//用来标识读取小区信息时，是否出现了异常
	bool flag = false;  //标识是否通过地图范围来限制录入的小区
	//通过地图来界定该小区是否在地图中
	double MaxLongi=180.0,MinLongi=0.0;
	double MaxLati=90.0,MinLati=0.0;
	if(flag) {
		vector<double> lonLatBounds=GetLonLatBoundsTool::getLonLatBounds();
		//右下角维度最小，经度最大
		double x11=lonLatBounds.at(1); //最小经度
		double y11=lonLatBounds.at(2); //最大维度
		double x12=lonLatBounds.at(0); //最大经度
		double y12=lonLatBounds.at(3); //最小维度
		//输入的是最小的经度，最大的经度，最小的维度，最大的维度
		double MaxLongi=x12,MinLongi=x11;
		double MaxLati=y11,MinLati=y12;
	}
	/* //用来给GSM使用
	int antannaHeight,antannaAspectAngle;
	int antannaDeclineAngle,refectLength,antannaType,baseStationType,coverType;
	double longitudeValue,latitudeValue,antannaHeightValue,antannaAspectAngleValue;
	double antannaDeclineAngleValue,refectLengthValue;
	int antannaTypeValue,baseStationTypeValue;
	double coverTypeValue;
	long columIndex[COLCNT];
	long freqIndex[24]={0};
	//数据的提取
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
	long columIndex[COLCNT]; //记录每个数据的列索引
	//数据的提取
	string heightString;
	string aspectAngleString;
	string declineAngleString;
	int aPCI;
	int id = 1;	 //用来记录有多少个小区
	try {
		const char *p = (LPCSTR)FileName;
		CppCSV cs(p);  
		map<u32, map<u32, string>> stringMap = cs.GetCSVMap();  
		//oef.LoadSheet(1,FALSE);  //未验证是否可以采用这种延后加载的方法
		rowCount = stringMap.size();
		columnCount = stringMap.begin()->second.size();	
		//获取所需要的信息的列数
		for(long i =1;i<=(long)columnCount;i++) {
				if(strcmp(cs.GetStringValue((long)TITLESTART,i)->c_str(),"经度")==0) {
					columIndex[0]=i;
				}else if(strcmp(cs.GetStringValue((long)TITLESTART,i)->c_str(),"纬度")==0) {
					columIndex[1]=i;
				}else if(strcmp(cs.GetStringValue((long)TITLESTART,i)->c_str(),"天线挂高")==0) {
					columIndex[2]=i;
				}else if(strcmp(cs.GetStringValue((long)TITLESTART,i)->c_str(),"方位角")==0) {
					columIndex[3]=i;
				}else if(strcmp(cs.GetStringValue((long)TITLESTART,i)->c_str(),"下倾角")==0) {
					columIndex[4]=i;
				}else if(strcmp(cs.GetStringValue((long)TITLESTART,i)->c_str(),"物理小区标识")==0) {
					columIndex[5]=i;
				}else if(strcmp(cs.GetStringValue((long)TITLESTART,i)->c_str(),"小区名称")==0) {
					columIndex[6]=i;
				}
				/*else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"馈线长度")==0) {
					columIndex[5]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"天线型号")==0) {
					columIndex[6]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"基站属性")==0) {
					columIndex[7]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"城郊区")==0) {
					columIndex[8]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"NCC")==0) {
					columIndex[9]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"BCC")==0) {
					columIndex[10]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"BCCH")==0) {  //开始提取频点
					freqIndex[0]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"SDCCH")==0) {  //开始提取频点
					freqIndex[1]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"TRX3")==0) {  //开始提取频点
					freqIndex[2]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"TRX4")==0) {  //开始提取频点
					freqIndex[3]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"TRX5")==0) {  //开始提取频点
					freqIndex[4]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"TRX6")==0) {  //开始提取频点
					freqIndex[5]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"TRX7")==0) {  //开始提取频点
					freqIndex[6]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"TRX8")==0) {  //开始提取频点
					freqIndex[7]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"TRX9")==0) {  //开始提取频点
					freqIndex[8]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"TRX10")==0) {  //开始提取频点
					freqIndex[9]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"TRX11")==0) {  //开始提取频点
					freqIndex[10]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"TRX12")==0) {  //开始提取频点
					freqIndex[11]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"TRX13")==0) {  //开始提取频点
					freqIndex[12]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"TRX14")==0) {  //开始提取频点
					freqIndex[13]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"TRX15")==0) {  //开始提取频点
					freqIndex[14]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"TRX16")==0) {  //开始提取频点
					freqIndex[15]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"TRX17")==0) {  //开始提取频点
					freqIndex[16]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"TRX18")==0) {  //开始提取频点
					freqIndex[17]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"TRX19")==0) {  //开始提取频点
					freqIndex[18]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"TRX20")==0) {  //开始提取频点
					freqIndex[19]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"TRX21")==0) {  //开始提取频点
					freqIndex[20]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"TRX22")==0) {  //开始提取频点
					freqIndex[21]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"TRX23")==0) {  //开始提取频点
					freqIndex[22]=i;
				}else if(strcmp(cs.GetStringValue((long)1,i)->c_str(),"TRX24")==0) {  //开始提取频点
					freqIndex[23]=i;
				}*/
		}
		
		//第一行是中文名,第二行是对应的值
		//去除掉最后一行
		for(long j =ROWSTART;j<((long)rowCount);j++) {
			string valueString[COLCNT];
			//int valueStringLength = COLCNT;
			//取出每行中需要的数据，放入到valueString数组中
			for(int i =0;i<COLCNT;i++) {
					string* temp = cs.GetStringValue(j,columIndex[i]);
					if(temp) {
						valueString[i]=*cs.GetStringValue(j,columIndex[i]);
					} else {
						valueString[i]="0";
					}
					//valueString[i] = *cs.GetStringValue(j,columIndex[i]);
			}
			//将valueString的数据，提取出来放入到数据库中
			//经纬度需要这么使用
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
			
			//判断数据是否有效
			/*
			if(!isValid(longitude,latitude,height,aspectAngle,declineAngle,aPCI)) {
				continue;
			}
			*/
			//采用地图边界来限制小区
			//只有当flag为true,并且数据有问题时，才不录入 "！" 后的限制条件为真时，数据没问题
			if(flag&&(!(longitude > MinLongi) && (longitude < MaxLongi) && (latitude > MinLati) && (latitude < MaxLati))) {
					continue;
			} else {
				//上面一行用来提取和北航有关的数据
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
					//提取频点到数据库中
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


//判断录入的数据是否有效
bool RecordAreaInfoTool::isValid(double longitude,double latitude,int height,int aspectAngle,int declineAngle,int aPCI) {
	if((longitude!=0)&&(latitude!=0)&&(height>0)&&(aspectAngle>0)&&(declineAngle>0)){
		return true;
	}else {
		return false;
	}
}