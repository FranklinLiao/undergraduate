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

//
//bool recordrtdata::recordrtdata(cstring filename) { 
//	dbhelper::deletedata("rtdata");
//	bool flag = false;
//	try {
//		operateexcelfiletool oef;
//		oef.initexcel();//��ʼ������
//		oef.openexcelfile(filename);//���ļ�
//		oef.loadsheet(1,true); //����Ԥ�ȼ��صķ��������ص�һ��excel�ı�
//		int rowcount = oef.getrowcount();
//		int columncount = oef.getcolumncount();
//			
//		crange m_range;
//		int longitudeindex,latitudeindex,strengthindex;
//		long columindex[5];
//		double longitudevalue[2],latitudevalue[2],strengthvalue[2];
//		int rfreqvalue[2],rbsicvalue[2];
//		int count = 0;
//		��ȡ����Ҫ����Ϣ������
//		˵����ʱ�������ݿ�������У����ȣ�ά�ȣ��߶ȣ�Ƶ�ʣ���վ���ԣ�
//		for(long i =1;i<=(long)columncount;i++) {
//			if(oef.iscellstring((long)1,i)) {
//				cstring kk = oef.getcellstring((long)1,i);
//				if(oef.getcellstring((long)1,i)==_t("����")) {
//					longitudeindex=i;
//					columindex[0]=i;
//				}else if(oef.getcellstring((long)1,i)==_t("γ��")) {
//					latitudeindex=i;
//					columindex[1]=i;
//				}else if(oef.getcellstring((long)1,i)==_t("�ź�ǿ��")) {  
//					strengthindex=i;
//					columindex[2]=i;
//				}
//				else if(oef.getcellstring((long)1,i)==_t("Ƶ��")) {  
//					strengthindex=i;
//					columindex[3]=i;
//				}
//				else if(oef.getcellstring((long)1,i)==_t("bsic")) {  
//					strengthindex=i;
//					columindex[4]=i;
//				}
//			}
//		}
//		int id = 1;	
//
//		�жϷ�Χ
//		vector<double> lonlatbounds=getlonlatboundstool::getlonlatbounds();
//		double x11=lonlatbounds.at(1); //��С����
//		double y11=lonlatbounds.at(2);  //���ά��
//		���½�ά����С���������
//		double x12=lonlatbounds.at(0); //��󾭶�
//		double y12=lonlatbounds.at(3); //��Сά��
//		���������С�ľ��ȣ����ľ��ȣ���С��ά�ȣ�����ά��
//		double minlongitude=x11;
//		double maxlatitude = y11;
//		double maxlongitude=x12;
//		double minlatitude=y12;
//		double maxlongi=x12,minlongi=x11;
//		double maxlati=y11,minlati=y12;
//
//		/*double sumstrength=0;
//		int count  = 1;*/
//		
//		��һ����������,�ڶ����Ƕ�Ӧ��ֵ
//		for(long j =2;j<((long)rowcount-1);j+=1) {
//			
//			string valuestring[5];
//			int valuestringlength = sizeof(valuestring)/sizeof(valuestring[0]);
//			for(int i =0;i<valuestringlength;i++) {
//				valuestring[i] = oef.getcellstringprecise(j,columindex[i],6).getbuffer();
//				/*if(oef.iscellstring(j,columindex[i])) {
//					valuestring[i]=oef.getcellstring(j,columindex[i]).getbuffer();
//
//				} else if(oef.iscelldouble(j,columindex[i])) {
//					valuestring[i]=changetypetool::doubletostring(oef.getcelldouble(j,columindex[i]));
//
//				}  else if(oef.iscellint(j,columindex[i])) {
//					valuestring[i]=changetypetool::inttostring(oef.getcellint(j,columindex[i]));
//
//				}*/
//				valuestring[i]=oef.getcellstring(j,columindex[i]).getbuffer();
//			}
//			longitudevalue[0]=changetypetool::stringtodouble(valuestring[0]);
//			latitudevalue[0]=changetypetool::stringtodouble(valuestring[1]);
//			strengthvalue[0]=changetypetool::stringtodouble(valuestring[2]);
//			rfreqvalue[0]=changetypetool::stringtoint(valuestring[3]);
//			rbsicvalue[0]=changetypetool::stringtoint(valuestring[4]);
//			/*string secondvaluestring[3];
//			int secondvaluestringlength = sizeof(secondvaluestring)/sizeof(secondvaluestring[0]);
//			for(int i =0;i<secondvaluestringlength;i++) {
//			if(oef.iscellstring(j+1,columindex[i])) {
//			secondvaluestring[i]=oef.getcellstring(j,columindex[i]).getbuffer();
//			} 
//			}
//			longitudevalue[1]=changetypetool::stringtodouble(secondvaluestring[0]);
//			latitudevalue[1]=changetypetool::stringtodouble(secondvaluestring[1]);
//			strengthvalue[1]=changetypetool::stringtodouble(secondvaluestring[2]);*/
//			sumstrength=;
//			int count  = 1;
//			bool contiflag = false;
//			/*
//			double sumout = 0;
//			int countout = 0;
//			if(sumstrength == 0) {
//				sumstrength = strengthvalue[0];
//			}*/
//			��������ȡ�������뵽���ݿ���
//			if((longitudevalue!=0)&&(latitudevalue!=0)&&
//				(longitudevalue[0] > minlongi) && (longitudevalue[0] < maxlongi) && (latitudevalue[0] > minlati) && (latitudevalue[0] < maxlati) 
//				&& (longitudevalue[1] > minlongi) && (longitudevalue[1] < maxlongi) && (latitudevalue[1] > minlati) && (latitudevalue[1] < maxlati) 
//				����һ��������ȡ�ͱ����йص�����
//				) {
//				//�ж������Ƿ�����ͬһ���ص�
//				if((longitudevalue[0]==longitudevalue[1])&&(latitudevalue[0]==latitudevalue[1])) {
//					//����ͬһ�ص�
//					contiflag=false;
//					count++;
//					sumstrength += strengthvalue[1];
//					sumout = sumstrength;
//					countout = count;
//				} else {
//					//���Բ�ͬ�ص�
//					contiflag=false;
//					sumout = sumstrength;
//					sumstrength = strengthvalue[1];
//					countout = count;
//					count = 1;
//				}
//
//				˵�����ݵص㲻һ�£����Կ�ʼ�洢�����ݿ���
//				if(contiflag==false) {
//					double averstrength = sumout / countout;
//					string tablename = "rtdata";
//					string key[] = {"rid","rlongitude","rlatitude","rvoltage","rfreq","rbsic"};
//					string keyvalue[] = {changetypetool::inttostring(id),changetypetool::doubletostringprecise(longitudevalue[0]),
//						changetypetool::doubletostringprecise(latitudevalue[0]),changetypetool::doubletostringprecise(strengthvalue[0],4),changetypetool::inttostring(rfreqvalue[0]),changetypetool::inttostring(rbsicvalue[0])};
//					dbhelper::insertinfo(tablename,key,keyvalue,sizeof(key)/sizeof(key[0]));
//					id++;
//				}
//			}
//		}
//		�رյ���excel�Ľ���
//		oef.releaseexcel();
//		flag = true;
//	} catch(coledispatchexception* e) {
//		e->reporterror();
//		e->delete();
//	} catch(coleexception* e) {
//		e->reporterror();
//		e->delete();
//	}
//	_crtdumpmemoryleaks();
//	return flag;
//}
//

//************************************  
// ��������: recordRTData     
// ����˵���� ¼�봦����4g��·������   
// ����:Franklin     
// ���ڣ�2015/03/20     
// �� �� ֵ: bool     
// ��    ��: CString FileName      
//************************************
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
		//columIndex�иõ�����С����γ�ȣ����ȣ�PCI,RSRP,CELLid
		int columIndex[6];
		double longitudeValue,latitudeValue;
		int myPciValue,myCellIdValue;
		double myRsrpValue,mySinrValue;
		//�����������Ϣ �����6������
		int cellIdIndex[6];
		int pciIndex[6];
		int rsrpIndex[6];
		int sinrIndex[6];
		int cellIdValue[6];
		int pciValue[6];
		double rsrpValue[6],sinrValue[6];
		int cellIdCnt=0,pciCnt=0,rsrpCnt=0,sinrCnt=0;
		//int count = 0;
		//��ȡ����Ҫ����Ϣ������
		int neighbourCnt = 0;
		for(long i =1;i<=(long)columnCount;i++) {
			//if(oef.IsCellString((long)1,i)) {
				//CString kk = oef.GetCellString((long)1,i);
				string info = oef.GetCellString((long)1,i);
				if(oef.GetCellString((long)1,i)==_T("Longitude")) {
					columIndex[0]=i;
				}else if(oef.GetCellString((long)1,i)==_T("Latitude")) { 
					columIndex[1]=i;
				}else if(oef.GetCellString((long)1,i)==_T("PCI")) {  
					columIndex[2]=i;
				}
				else if(oef.GetCellString((long)1,i)==_T("RSRP")) {  
					columIndex[3]=i;
				}
				else if(oef.GetCellString((long)1,i)==_T("SCell_ID")) {  
					columIndex[4]=i;
				} else if(oef.GetCellString((long)1,i)==_T("SINR")) {  
					columIndex[5]=i;
				} else if(oef.GetCellString((long)1,i)==_T("NCell_ID")) {  //��ʼȥ������������ 
					cellIdIndex[cellIdCnt]=i;
					cellIdCnt++;
				} else if(oef.GetCellString((long)1,i)==_T("NCell_PCI")) {
					pciIndex[pciCnt]= i;
					pciCnt++;
				} else if(oef.GetCellString((long)1,i)==_T("NCell_RSRP")) {
					rsrpIndex[rsrpCnt]= i;
					rsrpCnt++;
				} else if(oef.GetCellString((long)1,i)==_T("NCell_SINR")) {
					sinrIndex[sinrCnt]= i;
					sinrCnt++;
				}
				// neighbourCnt++;
			//}
		}
		int id = 1;	

		//�жϷ�Χ
		vector<double> lonLatBounds=GetLonLatBoundsTool::getGridLonLatBounds();
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
			
			string valueString[6];
			int valueStringLength = sizeof(valueString)/sizeof(valueString[0]);
			for(int i =0;i<valueStringLength;i++) {
				if(i==0||i==1) { //���⴦���Ⱥ�γ�ȣ�����6λ�ľ���
					valueString[i]=oef.GetCellStringPrecise(j,columIndex[i],6).GetBuffer();
				} else {
					valueString[i]=oef.GetCellString(j,columIndex[i]).GetBuffer();
				}
				//valueString[i] = oef.GetCellStringPrecise(j,columIndex[i],6).GetBuffer();
				/*if(oef.IsCellString(j,columIndex[i])) {
					valueString[i]=oef.GetCellString(j,columIndex[i]).GetBuffer();

				} else if(oef.IsCellDouble(j,columIndex[i])) {
					valueString[i]=ChangeTypeTool::doubleToString(oef.GetCellDouble(j,columIndex[i]));

				}  else if(oef.IsCellInt(j,columIndex[i])) {
					valueString[i]=ChangeTypeTool::intToString(oef.GetCellInt(j,columIndex[i]));

				}*/
				//valueString[i]=oef.GetCellString(j,columIndex[i]).GetBuffer();
			}
			//�õ�������С��������
			
			longitudeValue=ChangeTypeTool::stringToDouble(valueString[0]);
			latitudeValue=ChangeTypeTool::stringToDouble(valueString[1]);
			myPciValue=ChangeTypeTool::stringToInt(valueString[2]);
			myRsrpValue=ChangeTypeTool::stringToDouble(valueString[3]);
			myCellIdValue=ChangeTypeTool::stringToInt(valueString[4]);
			mySinrValue = ChangeTypeTool::stringToDouble(valueString[5]);
			//�õ�����������
			//int cellIdIndex[6];
			//int pciIndex[6];
			//int rsrpIndex[6];
			//int sinrIndex[6];
			string neighValueString[6];
			int neighValueStringLength = sizeof(neighValueString)/sizeof(neighValueString[0]);
			//cellid
			for(int i =0;i<neighValueStringLength;i++) {
				neighValueString[i] = oef.GetCellString(j,cellIdIndex[i]).GetBuffer();
				cellIdValue[i] = ChangeTypeTool::stringToInt(neighValueString[i]);
			}
			//pci
			for(int i =0;i<neighValueStringLength;i++) {
				neighValueString[i] = oef.GetCellString(j,pciIndex[i]).GetBuffer();
				pciValue[i] = ChangeTypeTool::stringToInt(neighValueString[i]);
			}
			//rsrp  �˴���Ϊ��������vba���д����ģ����������λ�����ͱ�ֱ��ȡ��
			for(int i =0;i<neighValueStringLength;i++) {
				neighValueString[i] = oef.GetCellStringPrecise(j,rsrpIndex[i],6).GetBuffer();
				rsrpValue[i] = ChangeTypeTool::stringToDouble(neighValueString[i]);
			}
			//sinr
			for(int i =0;i<neighValueStringLength;i++) {
				neighValueString[i] = oef.GetCellStringPrecise(j,sinrIndex[i],6).GetBuffer();
				sinrValue[i] = ChangeTypeTool::stringToDouble(neighValueString[i]);
			}
			/*string secondValueString[3];
			int secondValueStringLength = sizeof(secondValueString)/sizeof(secondValueString[0]);
			for(int i =0;i<second;i++ValueStringLength) {
			if(oef.IsCellString(j+1,columIndex[i])) {
			secondValueString[i]=oef.GetCellString(j,columIndex[i]).GetBuffer();
			} 
			}
			longitudeValue[1]=ChangeTypeTool::stringToDouble(secondValueString[0]);
			latitudeValue[1]=ChangeTypeTool::stringToDouble(secondValueString[1]);
			strengthValue[1]=ChangeTypeTool::stringToDouble(secondValueString[2]);*/
			//sumStrength=;
			//int count  = 1;
			//bool contiFlag = false;
			/*
			double sumOut = 0;
			int countOut = 0;
			if(sumStrength == 0) {
				sumStrength = strengthValue[0];
			}*/
			//��������ȡ�������뵽���ݿ���
			if((longitudeValue!=0)&&(latitudeValue!=0)
				&& (longitudeValue > MinLongi) && (longitudeValue < MaxLongi) && (latitudeValue > MinLati) && (latitudeValue < MaxLati) 
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
				//if(contiFlag==false) {
					//double averStrength = sumOut / countOut;
					for(int i=0;i<sizeof(cellIdValue)/sizeof(cellIdValue[0]);i++) {
						if(cellIdValue[i]!=0) {
							string tableName = "RTData";
							string key[] = {"RId","RLongitude","RLatitude","RAreaId","RPCI","RRSRP","RSNR","RNeighCellId","RNeighPCI","RNeighRSRP","RNeighSINR"};
							string keyValue[] = {ChangeTypeTool::intToString(id),ChangeTypeTool::doubleToStringPrecise(longitudeValue),
								ChangeTypeTool::doubleToStringPrecise(latitudeValue),ChangeTypeTool::intToString(myCellIdValue),ChangeTypeTool::intToString(myPciValue),ChangeTypeTool::doubleToString(myRsrpValue),ChangeTypeTool::doubleToString(mySinrValue),
								ChangeTypeTool::intToString(cellIdValue[i]),ChangeTypeTool::intToString(pciValue[i]),ChangeTypeTool::doubleToString(rsrpValue[i]),ChangeTypeTool::doubleToString(sinrValue[i])};
							DBHelper::insertInfo(tableName,key,keyValue,sizeof(key)/sizeof(key[0]));
							id++;
						}
					}
				//}
			}
		}
		//�رյ���Excel�Ľ���
		oef.CloseExcelFile(false);
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