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

//
//bool recordrtdata::recordrtdata(cstring filename) { 
//	dbhelper::deletedata("rtdata");
//	bool flag = false;
//	try {
//		operateexcelfiletool oef;
//		oef.initexcel();//初始化环境
//		oef.openexcelfile(filename);//打开文件
//		oef.loadsheet(1,true); //采用预先加载的方法，加载第一个excel的表
//		int rowcount = oef.getrowcount();
//		int columncount = oef.getcolumncount();
//			
//		crange m_range;
//		int longitudeindex,latitudeindex,strengthindex;
//		long columindex[5];
//		double longitudevalue[2],latitudevalue[2],strengthvalue[2];
//		int rfreqvalue[2],rbsicvalue[2];
//		int count = 0;
//		获取所需要的信息的列数
//		说明暂时存入数据库的数据有：经度，维度，高度，频率（基站属性）
//		for(long i =1;i<=(long)columncount;i++) {
//			if(oef.iscellstring((long)1,i)) {
//				cstring kk = oef.getcellstring((long)1,i);
//				if(oef.getcellstring((long)1,i)==_t("经度")) {
//					longitudeindex=i;
//					columindex[0]=i;
//				}else if(oef.getcellstring((long)1,i)==_t("纬度")) {
//					latitudeindex=i;
//					columindex[1]=i;
//				}else if(oef.getcellstring((long)1,i)==_t("信号强度")) {  
//					strengthindex=i;
//					columindex[2]=i;
//				}
//				else if(oef.getcellstring((long)1,i)==_t("频点")) {  
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
//		判断范围
//		vector<double> lonlatbounds=getlonlatboundstool::getlonlatbounds();
//		double x11=lonlatbounds.at(1); //最小经度
//		double y11=lonlatbounds.at(2);  //最大维度
//		右下角维度最小，经度最大
//		double x12=lonlatbounds.at(0); //最大经度
//		double y12=lonlatbounds.at(3); //最小维度
//		输入的是最小的经度，最大的经度，最小的维度，最大的维度
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
//		第一行是中文名,第二行是对应的值
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
//			将数据提取出来放入到数据库中
//			if((longitudevalue!=0)&&(latitudevalue!=0)&&
//				(longitudevalue[0] > minlongi) && (longitudevalue[0] < maxlongi) && (latitudevalue[0] > minlati) && (latitudevalue[0] < maxlati) 
//				&& (longitudevalue[1] > minlongi) && (longitudevalue[1] < maxlongi) && (latitudevalue[1] > minlati) && (latitudevalue[1] < maxlati) 
//				上面一行用来提取和北航有关的数据
//				) {
//				//判断数据是否来自同一个地点
//				if((longitudevalue[0]==longitudevalue[1])&&(latitudevalue[0]==latitudevalue[1])) {
//					//来自同一地点
//					contiflag=false;
//					count++;
//					sumstrength += strengthvalue[1];
//					sumout = sumstrength;
//					countout = count;
//				} else {
//					//来自不同地点
//					contiflag=false;
//					sumout = sumstrength;
//					sumstrength = strengthvalue[1];
//					countout = count;
//					count = 1;
//				}
//
//				说明数据地点不一致，可以开始存储到数据库中
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
//		关闭掉与excel的交互
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
// 函数名称: recordRTData     
// 函数说明： 录入处理后的4g的路测数据   
// 作者:Franklin     
// 日期：2015/03/20     
// 返 回 值: bool     
// 参    数: CString FileName      
//************************************
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
		//columIndex中该点所属小区的纬度，经度，PCI,RSRP,CELLid
		int columIndex[6];
		double longitudeValue,latitudeValue;
		int myPciValue,myCellIdValue;
		double myRsrpValue,mySinrValue;
		//邻区的相关信息 最多有6个邻区
		int cellIdIndex[6];
		int pciIndex[6];
		int rsrpIndex[6];
		int sinrIndex[6];
		int cellIdValue[6];
		int pciValue[6];
		double rsrpValue[6],sinrValue[6];
		int cellIdCnt=0,pciCnt=0,rsrpCnt=0,sinrCnt=0;
		//int count = 0;
		//获取所需要的信息的列数
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
				} else if(oef.GetCellString((long)1,i)==_T("NCell_ID")) {  //开始去拿邻区的数据 
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

		//判断范围
		vector<double> lonLatBounds=GetLonLatBoundsTool::getGridLonLatBounds();
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
			
			string valueString[6];
			int valueStringLength = sizeof(valueString)/sizeof(valueString[0]);
			for(int i =0;i<valueStringLength;i++) {
				if(i==0||i==1) { //特殊处理经度和纬度，控制6位的精度
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
			//得到了所属小区的数据
			
			longitudeValue=ChangeTypeTool::stringToDouble(valueString[0]);
			latitudeValue=ChangeTypeTool::stringToDouble(valueString[1]);
			myPciValue=ChangeTypeTool::stringToInt(valueString[2]);
			myRsrpValue=ChangeTypeTool::stringToDouble(valueString[3]);
			myCellIdValue=ChangeTypeTool::stringToInt(valueString[4]);
			mySinrValue = ChangeTypeTool::stringToDouble(valueString[5]);
			//得到邻区的数据
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
			//rsrp  此处因为数据是用vba进行处理后的，如果不控制位数，就被直接取整
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
			//将数据提取出来放入到数据库中
			if((longitudeValue!=0)&&(latitudeValue!=0)
				&& (longitudeValue > MinLongi) && (longitudeValue < MaxLongi) && (latitudeValue > MinLati) && (latitudeValue < MaxLati) 
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
		//关闭掉与Excel的交互
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