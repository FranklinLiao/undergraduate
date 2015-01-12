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
//		m_pRecordset->Open("SELECT * FROM  RTData",(IDispatch*)connection,adOpenDynamic,adLockOptimistic, adCmdText);//打开数据库，执行SQL语句
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
		oef.InitExcel();//初始化环境
		oef.OpenExcelFile(FileName);//打开文件
		oef.LoadSheet(1,TRUE); //采用预先加载的方法，加载第一个excel的表
		int rowCount = oef.GetRowCount();
		int columnCount = oef.GetColumnCount();
			
		//CRange m_range;
		int longitudeIndex,latitudeIndex,strengthIndex;
		long columIndex[5];
		double longitudeValue[2],latitudeValue[2],strengthValue[2];
		int RFreqValue[2],RbsicValue[2];
		//int count = 0;
		//获取所需要的信息的列数
		//说明暂时存入数据库的数据有：经度，维度，高度，频率（基站属性）
		for(long i =1;i<=(long)columnCount;i++) {
			if(oef.IsCellString((long)1,i)) {
				CString kk = oef.GetCellString((long)1,i);
				if(oef.GetCellString((long)1,i)==_T("经度")) {
					longitudeIndex=i;
					columIndex[0]=i;
				}else if(oef.GetCellString((long)1,i)==_T("纬度")) {
					latitudeIndex=i;
					columIndex[1]=i;
				}else if(oef.GetCellString((long)1,i)==_T("信号强度")) {  
					strengthIndex=i;
					columIndex[2]=i;
				}
				else if(oef.GetCellString((long)1,i)==_T("频点")) {  
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

		//判断范围
		vector<double> lonLatBounds=GetLonLatBoundsTool::getLonLatBounds();
		double x11=lonLatBounds.at(1); //最小经度
		double y11=lonLatBounds.at(2);  //最大维度
		//右下角维度最小，经度最大
		double x12=lonLatBounds.at(0); //最大经度
		double y12=lonLatBounds.at(3); //最小维度
		//输入的是最小的经度，最大的经度，最小的维度，最大的维度
		double minLongitude=x11;
		double maxLatitude = y11;
		double maxLongitude=x12;
		double minLatitude=y12;
		double MaxLongi=x12,MinLongi=x11;
		double MaxLati=y11,MinLati=y12;

		/*double sumStrength=0;
		int count  = 1;*/
		
		//第一行是中文名,第二行是对应的值
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
			//将数据提取出来放入到数据库中
			if((longitudeValue!=0)&&(latitudeValue!=0)&&
				(longitudeValue[0] > MinLongi) && (longitudeValue[0] < MaxLongi) && (latitudeValue[0] > MinLati) && (latitudeValue[0] < MaxLati) 
				//&& (longitudeValue[1] > MinLongi) && (longitudeValue[1] < MaxLongi) && (latitudeValue[1] > MinLati) && (latitudeValue[1] < MaxLati) 
				//上面一行用来提取和北航有关的数据
				) {
				////判断数据是否来自同一个地点
				//if((longitudeValue[0]==longitudeValue[1])&&(latitudeValue[0]==latitudeValue[1])) {
				//	//来自同一地点
					//contiFlag=false;
				//	count++;
				//	sumStrength += strengthValue[1];
				//	sumOut = sumStrength;
				//	countOut = count;
				//} else {
				//	//来自不同地点
				//	contiFlag=false;
				//	sumOut = sumStrength;
				//	sumStrength = strengthValue[1];
				//	countOut = count;
				//	count = 1;
				//}

				//说明数据地点不一致，可以开始存储到数据库中
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
		//关闭掉与Excel的交互
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