#include "stdafx.h"
#include "RecordRTData.h"

//void RecordRTData::recordRTData() {
//	DBConnect* dbconnection;
//	_ConnectionPtr connection;
//	_RecordsetPtr m_pRecordset;
//	try {
//		DBHelper::deleteData("RTData");
//		dbconnection = DBConnPool::Instanse()->GetAConnection();
//		connection = dbconnection->_connection_ptr;
//		m_pRecordset.CreateInstance(__uuidof(Recordset));
//		m_pRecordset->Open("SELECT * FROM  RTData",(IDispatch*)connection,adOpenDynamic,adLockOptimistic, adCmdText);//�����ݿ⣬ִ��SQL���
//		string reader;
//		string num;
//		int id=0;
//		fstream file;
//		int jump=0;
//		file.open("C:\\Users\\Franklin.LiTianjie-PC\\Documents\\Visual Studio 2010\\Projects\\GProjectDemo2\\RTD.txt");
//		if(!file)
//		{
//			//cout<<"Not Open"<<endl;
//			return;
//		}
//		while(file>>reader)
//		{
//			if(reader.find("_")!=string::npos)
//			{
//				file>>reader;
//				file>>reader;
//				file>>reader;
//				file>>reader;
//				file>>reader;
//				file>>reader;
//				file>>reader;
//				file>>reader;
//				cout<<reader<<endl;
//				id++;
//				m_pRecordset->AddNew();
//				m_pRecordset->PutCollect("RId",_variant_t(id));
//				m_pRecordset->PutCollect("RSNR",_variant_t(reader.c_str()));
//			}
//			if(reader.find(":")!=string::npos)
//			{
//				if(jump==0)
//					jump++;
//				else
//				{
//					num=reader.substr(2,9);
//					m_pRecordset->PutCollect("RLatitude",_variant_t(num.c_str()));
//					//cout<<num<<"	";
//					num=reader.substr(14,10);
//					m_pRecordset->PutCollect("RLongitude",_variant_t(num.c_str()));
//					//cout<<num<<endl;
//					m_pRecordset->Update();
//				}
//			}
//		}
////	DBConnPool::Instanse()->CloseConnection(connection);
//	DBConnPool::Instanse()->RestoreAConnection(dbconnection);
//	} catch(_com_error e) {
//	//	DBConnPool::Instanse()->CloseConnection(connection);
//		DBConnPool::Instanse()->RestoreAConnection(dbconnection);
//		//cout<<e.Description()<<endl;
//		//cout<<"insert info failed";
//	}	
//}

bool RecordRTData::recordRTData(CString FileName) { 
	DBHelper::deleteData("RTData");
	bool flag = false;
	try {
		OperateExcelFileTool oef;
		oef.InitExcel();//��ʼ������
		oef.OpenExcelFile(FileName);//���ļ�
		oef.LoadSheet(1,TRUE); //����Ԥ�ȼ��صķ��������ص�һ��excel�ı�
		int rowCount = oef.GetRowCount();
		int columnCount = oef.GetColumnCount();
			
		//CRange m_range;
		int longitudeIndex,latitudeIndex,strengthIndex;
		long columIndex[5];
		double longitudeValue[2],latitudeValue[2],strengthValue[2];
		int RFreqValue[2],RbsicValue[2];
		//int count = 0;
		//��ȡ����Ҫ����Ϣ������
		//˵����ʱ�������ݿ�������У����ȣ�ά�ȣ��߶ȣ�Ƶ�ʣ���վ���ԣ�
		for(long i =1;i<=(long)columnCount;i++) {
			if(oef.IsCellString((long)1,i)) {
				CString kk = oef.GetCellString((long)1,i);
				if(oef.GetCellString((long)1,i)==_T("����")) {
					longitudeIndex=i;
					columIndex[0]=i;
				}else if(oef.GetCellString((long)1,i)==_T("γ��")) {
					latitudeIndex=i;
					columIndex[1]=i;
				}else if(oef.GetCellString((long)1,i)==_T("�ź�ǿ��")) {  
					strengthIndex=i;
					columIndex[2]=i;
				}
				else if(oef.GetCellString((long)1,i)==_T("Ƶ��")) {  
					strengthIndex=i;
					columIndex[3]=i;
				}
				else if(oef.GetCellString((long)1,i)==_T("BSIC")) {  
					strengthIndex=i;
					columIndex[4]=i;
				}
			}
		}
		int id = 1;	

		//�жϷ�Χ
		vector<double> lonLatBounds=GetLonLatBoundsTool::getLonLatBounds();
		double x11=lonLatBounds.at(1); //��С����
		double y11=lonLatBounds.at(2);  //���ά��
		//���½�ά����С���������
		double x12=lonLatBounds.at(0); //��󾭶�
		double y12=lonLatBounds.at(3); //��Сά��
		//���������С�ľ��ȣ����ľ��ȣ���С��ά�ȣ�����ά��
		double minLongitude=x11;
		double maxLatitude = y11;
		double maxLongitude=x12;
		double minLatitude=y12;
		double MaxLongi=x12,MinLongi=x11;
		double MaxLati=y11,MinLati=y12;

		/*double sumStrength=0;
		int count  = 1;*/
		
		//��һ����������,�ڶ����Ƕ�Ӧ��ֵ
		for(long j =2;j<((long)rowCount-1);j+=1) {
			
			string valueString[5];
			int valueStringLength = sizeof(valueString)/sizeof(valueString[0]);
			for(int i =0;i<valueStringLength;i++) {
				valueString[i] = oef.GetCellStringPrecise(j,columIndex[i],6).GetBuffer();
				/*if(oef.IsCellString(j,columIndex[i])) {
					valueString[i]=oef.GetCellString(j,columIndex[i]).GetBuffer();

				} else if(oef.IsCellDouble(j,columIndex[i])) {
					valueString[i]=ChangeTypeTool::doubleToString(oef.GetCellDouble(j,columIndex[i]));

				}  else if(oef.IsCellInt(j,columIndex[i])) {
					valueString[i]=ChangeTypeTool::intToString(oef.GetCellInt(j,columIndex[i]));

				}*/
				//valueString[i]=oef.GetCellString(j,columIndex[i]).GetBuffer();
			}
			longitudeValue[0]=ChangeTypeTool::stringToDouble(valueString[0]);
			latitudeValue[0]=ChangeTypeTool::stringToDouble(valueString[1]);
			strengthValue[0]=ChangeTypeTool::stringToDouble(valueString[2]);
			RFreqValue[0]=ChangeTypeTool::stringToInt(valueString[3]);
			RbsicValue[0]=ChangeTypeTool::stringToInt(valueString[4]);
			/*string secondValueString[3];
			int secondValueStringLength = sizeof(secondValueString)/sizeof(secondValueString[0]);
			for(int i =0;i<secondValueStringLength;i++) {
			if(oef.IsCellString(j+1,columIndex[i])) {
			secondValueString[i]=oef.GetCellString(j,columIndex[i]).GetBuffer();
			} 
			}
			longitudeValue[1]=ChangeTypeTool::stringToDouble(secondValueString[0]);
			latitudeValue[1]=ChangeTypeTool::stringToDouble(secondValueString[1]);
			strengthValue[1]=ChangeTypeTool::stringToDouble(secondValueString[2]);*/
			//sumStrength=;
			//int count  = 1;
			bool contiFlag = false;
			/*
			double sumOut = 0;
			int countOut = 0;
			if(sumStrength == 0) {
				sumStrength = strengthValue[0];
			}*/
			//��������ȡ�������뵽���ݿ���
			if((longitudeValue!=0)&&(latitudeValue!=0)&&
				(longitudeValue[0] > MinLongi) && (longitudeValue[0] < MaxLongi) && (latitudeValue[0] > MinLati) && (latitudeValue[0] < MaxLati) 
				//&& (longitudeValue[1] > MinLongi) && (longitudeValue[1] < MaxLongi) && (latitudeValue[1] > MinLati) && (latitudeValue[1] < MaxLati) 
				//����һ��������ȡ�ͱ����йص�����
				) {
				////�ж������Ƿ�����ͬһ���ص�
				//if((longitudeValue[0]==longitudeValue[1])&&(latitudeValue[0]==latitudeValue[1])) {
				//	//����ͬһ�ص�
					//contiFlag=false;
				//	count++;
				//	sumStrength += strengthValue[1];
				//	sumOut = sumStrength;
				//	countOut = count;
				//} else {
				//	//���Բ�ͬ�ص�
				//	contiFlag=false;
				//	sumOut = sumStrength;
				//	sumStrength = strengthValue[1];
				//	countOut = count;
				//	count = 1;
				//}

				//˵�����ݵص㲻һ�£����Կ�ʼ�洢�����ݿ���
				if(contiFlag==false) {
					//double averStrength = sumOut / countOut;
					string tableName = "RTData";
					string key[] = {"RId","RLongitude","RLatitude","RVoltage","RFreq","RBSIC"};
					string keyValue[] = {ChangeTypeTool::intToString(id),ChangeTypeTool::doubleToStringPrecise(longitudeValue[0]),
						ChangeTypeTool::doubleToStringPrecise(latitudeValue[0]),ChangeTypeTool::doubleToStringPrecise(strengthValue[0],4),ChangeTypeTool::intToString(RFreqValue[0]),ChangeTypeTool::intToString(RbsicValue[0])};
					DBHelper::insertInfo(tableName,key,keyValue,sizeof(key)/sizeof(key[0]));
					id++;
				}
			}
		}
		//�رյ���Excel�Ľ���
		oef.ReleaseExcel();
		flag = true;
	} catch(COleDispatchException* e) {
		e->ReportError();
		e->Delete();
	} catch(COleException* e) {
		e->ReportError();
		e->Delete();
	}
	//_CrtDumpMemoryLeaks();
	return flag;
}