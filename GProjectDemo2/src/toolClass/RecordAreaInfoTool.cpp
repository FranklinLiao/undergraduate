#include "stdafx.h"
#include "RecordAreaInfoTool.h"
#define COLCNT 8
#define ROWSTART 4
#define TITLESTART 2

bool RecordAreaInfoTool::insertAreaInfo(CString FileName) {
	DBHelper::deleteData("Area");
	//DBHelper::deleteData("AreaFreq");
	int rowCount=0;
	int columnCount=0;
	bool returnFlag = false;//用来标识读取小区信息时，是否出现了异常
	bool flag = true;  //标识是否通过地图范围来限制录入的小区  
	//最后，这个地方应该不限制   因为地图外的基站会影响地图内的小区
	//但是考虑到现在（3.20），没有有效的rsrp（用的是2G的在北航的数据)，先限制一下免得太远的基站也在网格有数据
	//通过地图来界定该小区是否在地图中
	double MaxLongi=180.0,MinLongi=0.0;
	double MaxLati=90.0,MinLati=0.0;
	if(flag) {
		//用网格范围来限定  如果用建筑物  那个有可能在建筑物范围外的基站  对建筑物内的网格有影响  
		//而用网格就是考虑到建筑物外的基站会影响建筑物  通过限制网格比建筑物范围大的程度  可以限制网格外的基站对建筑物范围内都没有影响
		vector<double> lonLatBounds=GetLonLatBoundsTool::getGridLonLatBounds();
		//右下角维度最小，经度最大
		double x11=lonLatBounds.at(1); //最小经度
		double y11=lonLatBounds.at(2); //最大维度
		double x12=lonLatBounds.at(0); //最大经度
		double y12=lonLatBounds.at(3); //最小维度
		//输入的是最小的经度，最大的经度，最小的维度，最大的维度
		MaxLongi=x12,MinLongi=x11;
		MaxLati=y11,MinLati=y12;
	}

	int height,aspectAngle,declineAngle;
	double longitude,latitude;
	string areaName;
	long columIndex[COLCNT]; //记录每个数据的列索引
	//数据的提取
	string heightString;
	string aspectAngleString;
	string declineAngleString;
	string cellIdString;
	int cellId = 0;
	int aPCI;
	int id = 1;	 //用来记录有多少个小区
	try {
		OperateExcelFileTool oef;
		oef.InitExcel();//初始化环境
		oef.OpenExcelFile(FileName);//打开文件
		oef.LoadSheet(1,TRUE); //采用预先加载的方法，加载第一个excel的表
		//oef.LoadSheet(1,FALSE);  //未验证是否可以采用这种延后加载的方法
		int rowCount = oef.GetRowCount();
		int columnCount = oef.GetColumnCount();
		//获取所需要的信息的列数
		for(long i =1;i<(long)columnCount;i++) {
				string info = oef.GetCellString((long)TITLESTART,i);
				if(strcmp(oef.GetCellString((long)TITLESTART,i),_T("经度"))==0) {
					columIndex[0]=i;
				}else if(strcmp(oef.GetCellString((long)TITLESTART,i),_T("纬度"))==0) {
					columIndex[1]=i;
				}else if(strcmp(oef.GetCellString((long)TITLESTART,i),_T("天线挂高"))==0) {
					columIndex[2]=i;
				}else if(strcmp(oef.GetCellString((long)TITLESTART,i),_T("方位角"))==0) {
					columIndex[3]=i;
				}else if(strcmp(oef.GetCellString((long)TITLESTART,i),_T("下倾角"))==0) {
					columIndex[4]=i;
				}else if(strcmp(oef.GetCellString((long)TITLESTART,i),_T("物理小区标识"))==0) {
					columIndex[5]=i;
				}else if(strcmp(oef.GetCellString((long)TITLESTART,i),_T("小区名称"))==0) {
					columIndex[6]=i;
				} else if(strcmp(oef.GetCellString((long)TITLESTART,i),_T("索引列1"))==0) {
					columIndex[7]=i;
				}
		}
		
		//第一行是中文名,第二行是对应的值
		for(long j =ROWSTART;j<=((long)rowCount);j++) {
			string valueString[COLCNT];
			//int valueStringLength = COLCNT;
			//取出每行中需要的数据，放入到valueString数组中
			for(int i =0;i<COLCNT;i++) {
				//if(oef.IsCellString(j,columIndex[i])) {
				if(i==0||i==1) { //特殊处理经度和纬度，控制6位的精度
					valueString[i]=oef.GetCellStringPrecise(j,columIndex[i],6).GetBuffer();
				} else {
					valueString[i]=oef.GetCellString(j,columIndex[i]).GetBuffer();
				}

				//} else if(oef.IsCellDouble(j,columIndex[i])) {
				//	valueString[i]=ChangeTypeTool::doubleToString(oef.GetCellDouble(j,columIndex[i]));
				//} else if(oef.IsCellInt(j,columIndex[i])){
				//	valueString[i]=ChangeTypeTool::intToString(oef.GetCellInt(j,columIndex[i]));
				//} 
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
			cellIdString = valueString[7];
			//去除cellIdString中的"-"
			int index = cellIdString.find_first_of('-');
			if(index != string::npos) {
				cellIdString = cellIdString.substr(0,index).append(cellIdString.substr(index+1));
				cellId = ChangeTypeTool::stringToInt(cellIdString);
			}
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
			if(flag&&!((longitude > MinLongi) && (longitude < MaxLongi) && (latitude > MinLati) && (latitude < MaxLati))) {
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
		oef.CloseExcelFile(false);
		oef.ReleaseExcel();
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