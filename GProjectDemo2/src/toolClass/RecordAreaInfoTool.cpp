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
	bool returnFlag = false;//������ʶ��ȡС����Ϣʱ���Ƿ�������쳣
	bool flag = true;  //��ʶ�Ƿ�ͨ����ͼ��Χ������¼���С��  
	//�������ط�Ӧ�ò�����   ��Ϊ��ͼ��Ļ�վ��Ӱ���ͼ�ڵ�С��
	//���ǿ��ǵ����ڣ�3.20����û����Ч��rsrp���õ���2G���ڱ���������)��������һ�����̫Զ�Ļ�վҲ������������
	//ͨ����ͼ���綨��С���Ƿ��ڵ�ͼ��
	double MaxLongi=180.0,MinLongi=0.0;
	double MaxLati=90.0,MinLati=0.0;
	if(flag) {
		//������Χ���޶�  ����ý�����  �Ǹ��п����ڽ����ﷶΧ��Ļ�վ  �Խ������ڵ�������Ӱ��  
		//����������ǿ��ǵ���������Ļ�վ��Ӱ�콨����  ͨ����������Ƚ����ﷶΧ��ĳ̶�  ��������������Ļ�վ�Խ����ﷶΧ�ڶ�û��Ӱ��
		vector<double> lonLatBounds=GetLonLatBoundsTool::getGridLonLatBounds();
		//���½�ά����С���������
		double x11=lonLatBounds.at(1); //��С����
		double y11=lonLatBounds.at(2); //���ά��
		double x12=lonLatBounds.at(0); //��󾭶�
		double y12=lonLatBounds.at(3); //��Сά��
		//���������С�ľ��ȣ����ľ��ȣ���С��ά�ȣ�����ά��
		MaxLongi=x12,MinLongi=x11;
		MaxLati=y11,MinLati=y12;
	}

	int height,aspectAngle,declineAngle;
	double longitude,latitude;
	string areaName;
	long columIndex[COLCNT]; //��¼ÿ�����ݵ�������
	//���ݵ���ȡ
	string heightString;
	string aspectAngleString;
	string declineAngleString;
	string cellIdString;
	int cellId = 0;
	int aPCI;
	int id = 1;	 //������¼�ж��ٸ�С��
	try {
		OperateExcelFileTool oef;
		oef.InitExcel();//��ʼ������
		oef.OpenExcelFile(FileName);//���ļ�
		oef.LoadSheet(1,TRUE); //����Ԥ�ȼ��صķ��������ص�һ��excel�ı�
		//oef.LoadSheet(1,FALSE);  //δ��֤�Ƿ���Բ��������Ӻ���صķ���
		int rowCount = oef.GetRowCount();
		int columnCount = oef.GetColumnCount();
		//��ȡ����Ҫ����Ϣ������
		for(long i =1;i<(long)columnCount;i++) {
				string info = oef.GetCellString((long)TITLESTART,i);
				if(strcmp(oef.GetCellString((long)TITLESTART,i),_T("����"))==0) {
					columIndex[0]=i;
				}else if(strcmp(oef.GetCellString((long)TITLESTART,i),_T("γ��"))==0) {
					columIndex[1]=i;
				}else if(strcmp(oef.GetCellString((long)TITLESTART,i),_T("���߹Ҹ�"))==0) {
					columIndex[2]=i;
				}else if(strcmp(oef.GetCellString((long)TITLESTART,i),_T("��λ��"))==0) {
					columIndex[3]=i;
				}else if(strcmp(oef.GetCellString((long)TITLESTART,i),_T("�����"))==0) {
					columIndex[4]=i;
				}else if(strcmp(oef.GetCellString((long)TITLESTART,i),_T("����С����ʶ"))==0) {
					columIndex[5]=i;
				}else if(strcmp(oef.GetCellString((long)TITLESTART,i),_T("С������"))==0) {
					columIndex[6]=i;
				} else if(strcmp(oef.GetCellString((long)TITLESTART,i),_T("������1"))==0) {
					columIndex[7]=i;
				}
		}
		
		//��һ����������,�ڶ����Ƕ�Ӧ��ֵ
		for(long j =ROWSTART;j<=((long)rowCount);j++) {
			string valueString[COLCNT];
			//int valueStringLength = COLCNT;
			//ȡ��ÿ������Ҫ�����ݣ����뵽valueString������
			for(int i =0;i<COLCNT;i++) {
				//if(oef.IsCellString(j,columIndex[i])) {
				if(i==0||i==1) { //���⴦���Ⱥ�γ�ȣ�����6λ�ľ���
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
			//��valueString�����ݣ���ȡ�������뵽���ݿ���
			//��γ����Ҫ��ôʹ��
			longitude=ChangeTypeTool::stringToDouble(valueString[0]);
			latitude=ChangeTypeTool::stringToDouble(valueString[1]);
			height = ChangeTypeTool::stringToInt(valueString[2]);
			aspectAngle = ChangeTypeTool::stringToInt(valueString[3]);
			declineAngle = ChangeTypeTool::stringToInt(valueString[4]);
			aPCI = ChangeTypeTool::stringToInt(valueString[5]);
			areaName = valueString[6];
			cellIdString = valueString[7];
			//ȥ��cellIdString�е�"-"
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
			
			//�ж������Ƿ���Ч
			/*
			if(!isValid(longitude,latitude,height,aspectAngle,declineAngle,aPCI)) {
				continue;
			}
			*/
			//���õ�ͼ�߽�������С��
			//ֻ�е�flagΪtrue,��������������ʱ���Ų�¼�� "��" �����������Ϊ��ʱ������û����
			if(flag&&!((longitude > MinLongi) && (longitude < MaxLongi) && (latitude > MinLati) && (latitude < MaxLati))) {
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


//�ж�¼��������Ƿ���Ч
bool RecordAreaInfoTool::isValid(double longitude,double latitude,int height,int aspectAngle,int declineAngle,int aPCI) {
	if((longitude!=0)&&(latitude!=0)&&(height>0)&&(aspectAngle>0)&&(declineAngle>0)){
		return true;
	}else {
		return false;
	}
}