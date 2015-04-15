#include "stdafx.h"
#include "DataBase.h"

/**
* @brief    ������Ϣ
* @fullName	DataBase::insertInfo
* @param	insertString
* @return	void
* @author	Franklin
* @date		2014/05/22
* @warning	
*/
void DataBase::insertInfo(string insertString) {
	//GetDBConnTool dbCon;
	_ConnectionPtr connection;
	DBConnect* dbconnection;
	try {
		//connection=GetDBConnTool::getMyConnection();
		//GetDBConnTool dbCon;
		//dbCon.getMyConnection(connection);
		//connection.CreateInstance(__uuidof(Connection));
		dbconnection = DBConnPool::Instanse()->GetAConnection();
		connection = dbconnection->_connection_ptr;
		sqlString = insertString.c_str();
		connection->Execute(sqlString,0,0); 
		//dbCon.closeConnection(connection);
//		DBConnPool::Instanse()->CloseConnection(connection);
		DBConnPool::Instanse()->RestoreAConnection(dbconnection);
		//_CrtDumpMemoryLeaks();
	}catch(_com_error e) {
//		DBConnPool::Instanse()->CloseConnection(connection);
		//_CrtDumpMemoryLeaks();
		DBConnPool::Instanse()->RestoreAConnection(dbconnection);
		cout<<e.Description()<<endl;
		cout<<"insert info failed";
	}
			
}


/**
* @brief    ��������
* @fullName	DataBase::updateInfo
* @param	updateString
* @return	void
* @author	Franklin
* @date		2014/05/22
* @warning	
*/
void DataBase::updateInfo(string updateString) {
	//GetDBConnTool dbCon;
	_ConnectionPtr connection;
	DBConnect* dbconnection;
	try {
		//dbCon.getMyConnection(connection);
		dbconnection = DBConnPool::Instanse()->GetAConnection();
		connection = dbconnection->_connection_ptr;
		sqlString=updateString.c_str();
		connection->Execute(sqlString,0,0);
		//dbCon.closeConnection(connection);
//		DBConnPool::Instanse()->CloseConnection(connection);
		//_CrtDumpMemoryLeaks();
		DBConnPool::Instanse()->RestoreAConnection(dbconnection);
	}catch(_com_error e) {
		//dbCon.closeConnection(connection
//		DBConnPool::Instanse()->CloseConnection(connection);
		//_CrtDumpMemoryLeaks();
		cout<<e.Description();
		DBConnPool::Instanse()->RestoreAConnection(dbconnection);
		cout<<"update info failed";
	}
}

	//��ѯ����   ���ض���    ������Ƕ���  ������Ƕ��������
	/*
	vector<vector<string>> DataBase::getObjectInfo(string queryString,string tableName,int tableRowCount){
		DBConnect* dbconnection;
		_ConnectionPtr connection;
		_RecordsetPtr recordSet;
		try {
			//��������
			//dbCon.getMyConnection(connection);
			dbconnection = DBConnPool::Instanse()->GetAConnection();
			connection = dbconnection->_connection_ptr;
			recordSet.CreateInstance(__uuidof(Recordset));;
			vector<vector<string>> stringObjectSet;
			sqlString = queryString.c_str();
			int rowCount = tableRowCount;
				//��ñ������
				//int rowCount = getRowCount(T object);
				// ȡ�ñ��еļ�¼
			recordSet->Open(sqlString,connection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
			_variant_t vTmp;
	
				//string stringObject[rowCount];
				//int counter= 0;
				while(!recordSet->EndOfFile)
				{
					int i =0;
					//�ǵø���  �˴�֪��Ϊ4
					//int rowCount = 4;
					
					vector<string> stringObject;
					//�ж��Ƿ�ǿգ��ǿ�������
					if(!stringObject.empty())
						stringObject.clear();
					
					
					
					for(;i<rowCount;i++) {
						vTmp = recordSet->GetCollect(_variant_t((long)i));//������ֶα�ź��ֶ��������� 
						string tmp;
						if(vTmp.vt==VT_NULL || vTmp.vt==VT_EMPTY) {
							tmp = (_bstr_t)"";
						} else {
							tmp = (_bstr_t)vTmp;
						}
						stringObject.push_back(tmp); 
					}
					//
					stringObjectSet.push_back(stringObject);
					recordSet->MoveNext(); ///�Ƶ���һ����¼
				}
		//	}
			
			//dbCon.closeRecordSet(recordSet);
			//dbCon.closeConnection(connection);
			DBConnPool::Instanse()->CloseRecordSet(recordSet);
			DBConnPool::Instanse()->RestoreAConnection(dbconnection);
			return stringObjectSet;
		} catch(_com_error e) {
			//dbCon.closeRecordSet(recordSet);
			DBConnPool::Instanse()->CloseRecordSet(recordSet);
			DBConnPool::Instanse()->RestoreAConnection(dbconnection);
			//dbCon.closeConnection(connection);
			cout<<"get objectinfo   failed "<<endl;
			cout<<e.Description()<<endl;
			//return NULL;
		}
	}	
	*/
/**
* @brief    �õ���ѯ�����ݣ�����װ��string��������
* @fullName	DataBase::getObjectInfo
* @param	queryString
* @return	vector<vector<string>>
* @author	Franklin
* @date		2014/06/04
* @warning	
*/
vector<vector<string>> DataBase::getObjectInfo(string queryString){
	DBConnect* dbconnection;
	_ConnectionPtr connection;
	_RecordsetPtr recordSet;
	try {
		dbconnection = DBConnPool::Instanse()->GetAConnection();
		connection = dbconnection->_connection_ptr;
		recordSet.CreateInstance(__uuidof(Recordset));;
		vector<vector<string>> stringObjectSet;
		sqlString = queryString.c_str();
		recordSet->Open(sqlString,connection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
		_variant_t vTmp;
		while(!recordSet->EndOfFile)
		{
			vector<string> stringObject;
			//�ж��Ƿ�ǿգ��ǿ�������
			if(!stringObject.empty())
				stringObject.clear();
			int rowNum = recordSet->Fields->GetCount(); //�õ��ֶ���
			for(int i =0;i<rowNum;i++) {
				vTmp = recordSet->GetCollect(_variant_t((long)i));//������ֶα�ź��ֶ��������� 
				string tmp;
				if(vTmp.vt==VT_NULL || vTmp.vt==VT_EMPTY) {
					tmp = (_bstr_t)"";
				} else {
					tmp = (_bstr_t)vTmp;
				}
				stringObject.push_back(tmp); 
			}
			stringObjectSet.push_back(stringObject);
			recordSet->MoveNext(); ///�Ƶ���һ����¼
		}
		DBConnPool::Instanse()->CloseRecordSet(recordSet);
//		DBConnPool::Instanse()->CloseConnection(connection);
		DBConnPool::Instanse()->RestoreAConnection(dbconnection);
		//_CrtDumpMemoryLeaks();
		return stringObjectSet;
	} catch(_com_error e) {
		//dbCon.closeRecordSet(recordSet);
		DBConnPool::Instanse()->CloseRecordSet(recordSet);
//		DBConnPool::Instanse()->CloseConnection(connection);
		DBConnPool::Instanse()->RestoreAConnection(dbconnection);
		//_CrtDumpMemoryLeaks();
		cout<<"get objectinfo   failed "<<endl;
		cout<<e.Description()<<endl;
	}
}	

/**
* @brief    �õ������ID��
* @fullName	DataBase::getGridId
* @param	queryString
* @return	int
* @author	Franklin
* @date		2014/06/04
* @warning	
//*/
//int DataBase::getGridId(string queryString) {
//	DBConnect* dbconnection;
//	_ConnectionPtr connection;
//	_RecordsetPtr recordSet;
//	int gridId=0;
//	try {
//		dbconnection = DBConnPool::Instanse()->GetAConnection();
//		connection = dbconnection->_connection_ptr;
//		recordSet.CreateInstance(__uuidof(Recordset));
//		recordSet->Open(queryString.c_str(),connection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
//		_variant_t vTmp;
//		while(!recordSet->EndOfFile) {
//			vTmp = recordSet->GetCollect(_variant_t((long)0));
//			gridId=(int)vTmp;
//			recordSet->MoveNext();
//		}
//	} catch(_com_error e) {
//		DBConnPool::Instanse()->CloseRecordSet(recordSet);
//		DBConnPool::Instanse()->RestoreAConnection(dbconnection);
//		cout<<"getGridId  failed "<<endl;
//		cout<<e.Description()<<endl;
//	}
//	return gridId;
//}
//
//	//��ñ������
//	
//	int DataBase::getRowCount(string tableName) {
//		DBConnect* dbconnection;
//		_ConnectionPtr connection;
//		_RecordsetPtr recordSet;
//		try {
//			dbconnection = DBConnPool::Instanse()->GetAConnection();
//			connection = dbconnection->_connection_ptr;
//			//dbCon.getMyConnection(connection);
//			recordSet.CreateInstance(__uuidof(Recordset));
//			int rowCount = 0;
//			string sqlString="select count(a.name) as counta from syscolumns a where a.id =object_id('";
//			sqlString.append(tableName);
//			sqlString.append("');");
//			//cout<<"sql string is "<<sqlString<<endl;
//			
//			recordSet->Open(sqlString.c_str(),connection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
//			_variant_t vTmp;
//			vTmp = recordSet->GetCollect(_variant_t((long)0));
//			rowCount=(int)vTmp;
//			//cout<<"row count: "<<rowCount<<endl;
//			//dbCon.closeRecordSet(recordSet);
//			DBConnPool::Instanse()->CloseRecordSet(recordSet);
//			DBConnPool::Instanse()->RestoreAConnection(dbconnection);
//			//dbCon.closeConnection(connection);
//			return rowCount;
//		} catch(_com_error e) {
//			//dbCon.closeRecordSet(recordSet);
//			DBConnPool::Instanse()->CloseRecordSet(recordSet);
//			DBConnPool::Instanse()->RestoreAConnection(dbconnection);
//			//dbCon.closeConnection(connection);
//			cout<<"getrowcount  failed "<<endl;
//			cout<<e.Description()<<endl;
//			return NULL;
//		}
//	}
	
	/*
	//�����ݽ�����װ�ɶ�Ӧ�Ķ���
	template <typename K>
	K combineObject(vector<string> info,K object) {
		//����object�����ͣ���vector���������������Ҫ���ǵ����ݱ������Ե�˳�򣩣�������װ
		 K realObject;
		 //�ж�object����   switch case���
		 //�������
		 return realObject;
	}
	*/

	/*
	string DataBase::createQuerySql(string tableName) {
		string info = "select * from ";
		info.append(tableName);
		info.append(";");
		return info;
	}
	*/
	/*
	void main() {
		DBConnGuard::InitDBIterface("127.0.0.1","sa","Linux2539311","MapData",10,20);
		DataBase database;
		database.insertInfo("insert into basestation (BLongtitude) values(1.00);");
		int max = 1;
		printf("haha");
	}
	*/




/**
* @brief    ɾ���������е�����
* @fullName	DataBase::deletAllInfo
* @param	TableName
* @return	void
* @author	Franklin
* @date		2014/05/23
* @warning	
*/
void DataBase::deletAllInfo(string TableName)
{
	//GetDBConnTool dbCon;
	_ConnectionPtr connection;
	DBConnect* dbconnection;
	_RecordsetPtr recordSet;
	string sqlString="DELETE FROM  ";
	sqlString.append(TableName);
	sqlString.append(";");
	dbconnection = DBConnPool::Instanse()->GetAConnection();
	connection = dbconnection->_connection_ptr;
	recordSet.CreateInstance(__uuidof(Recordset));
	try{	
		recordSet->Open(sqlString.c_str(),(IDispatch*)connection,adOpenDynamic,adLockOptimistic, adCmdText);
		DBConnPool::Instanse()->CloseRecordSet(recordSet);
//		DBConnPool::Instanse()->CloseConnection(connection);
		DBConnPool::Instanse()->RestoreAConnection(dbconnection);
		//_CrtDumpMemoryLeaks();
		recordSet->Close();
	}
	catch (_com_error &e)
	{
		DBConnPool::Instanse()->CloseRecordSet(recordSet);
//		DBConnPool::Instanse()->CloseConnection(connection);
		DBConnPool::Instanse()->RestoreAConnection(dbconnection);
		//_CrtDumpMemoryLeaks();
		cout << e.Description()<<endl;
	}
}

	////�õ����ݵĽ����
	//_RecordsetPtr DataBase::getObjectInfoRecordset(string queryString) {
	//	//GetDBConnTool dbCon;
	//	DBConnect* dbconnection;
	//	_ConnectionPtr connection;  
	//	_RecordsetPtr recordSet;
	//	try {
	//		//��������
	//		//dbCon.getMyConnection(connection);
	//		dbconnection = DBConnPool::Instanse()->GetAConnection();
	//		connection = dbconnection->_connection_ptr;
	//		recordSet.CreateInstance(__uuidof(Recordset));;
	//		sqlString = queryString.c_str();
	//		// ȡ�ñ��еļ�¼
	//		recordSet->Open(sqlString,connection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	//		DBConnPool::Instanse()->CloseRecordSet(recordSet);
	//		DBConnPool::Instanse()->RestoreAConnection(dbconnection);
	//		return  recordSet;
	//	} catch(_com_error e) {
	//		//dbCon.closeRecordSet(recordSet);
	//		DBConnPool::Instanse()->CloseRecordSet(recordSet);
	//		DBConnPool::Instanse()->RestoreAConnection(dbconnection);
	//		cout<<"get objectinfo   failed "<<endl;
	//		cout<<e.Description()<<endl;
	//	}
	//}

	//************************************  
	// ��������: getGridLonLatBounds     
	// ����˵���� �õ�������ı߽�ķ�Χ     
	// ����:Franklin     
	// ���ڣ�2015/03/24     
	// �� �� ֵ: vector<double>     
	//************************************
	vector<double> DataBase::getLonLatBounds() {
		DBConnect* dbconnection;
		_ConnectionPtr conPtr;  
		_RecordsetPtr recordSet;
		vector<double> lonLatBoundsVector;
		try {
			//��������
			//dbCon.getMyConnection(connection);
			dbconnection = DBConnPool::Instanse()->GetAConnection();
			conPtr = dbconnection->_connection_ptr;
			recordSet.CreateInstance(__uuidof(Recordset));
			sqlString = CreateSqlTool::getLonLatBoundString.c_str();
			// ȡ�ñ��еļ�¼
			recordSet->Open(sqlString,conPtr.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
			_variant_t vTmp;
			vTmp.vt = VT_DECIMAL;
			//while(!recordSet->EndOfFile)
			//{
			int i =0;
			if(!lonLatBoundsVector.empty())
				lonLatBoundsVector.clear();
			//����ȡ�ĸ�����
			for(;i<4;i++) {
				vTmp = recordSet->GetCollect(_variant_t((long)i));//������ֶα�ź��ֶ��������� 
				double tmp;
				if(vTmp.vt==VT_NULL || vTmp.vt==VT_EMPTY) {
					tmp = _variant_t((double)0);
				} else {
					tmp = double(vTmp);//.dblVal;
				}
				lonLatBoundsVector.push_back(tmp); 
				//	}
				//	recordSet->MoveNext(); ///�Ƶ���һ����¼
			}

			DBConnPool::Instanse()->CloseRecordSet(recordSet);
			//			DBConnPool::Instanse()->CloseConnection(conPtr);
			DBConnPool::Instanse()->RestoreAConnection(dbconnection);
			//_CrtDumpMemoryLeaks();
			return lonLatBoundsVector;
		} catch(_com_error e) {
			//dbCon.closeRecordSet(recordSet);
			DBConnPool::Instanse()->CloseRecordSet(recordSet);
			//		DBConnPool::Instanse()->CloseConnection(conPtr);
			DBConnPool::Instanse()->RestoreAConnection(dbconnection);
			//_CrtDumpMemoryLeaks();
			cout<<"get lonLatBoundsVector  failed "<<endl;
			cout<<e.Description()<<endl;
		}
	}
	

	//************************************  
	// ��������: getGridLonLatBounds     
	// ����˵���� �õ�����߽�ķ�Χ     
	// ����:Franklin     
	// ���ڣ�2015/03/24     
	// �� �� ֵ: vector<double>     
	//************************************
	vector<double> DataBase::getGridLonLatBounds() {
		DBConnect* dbconnection;
		_ConnectionPtr conPtr;  
		_RecordsetPtr recordSet;
		vector<double> lonLatBoundsVector;
		try {
			//��������
			//dbCon.getMyConnection(connection);
			dbconnection = DBConnPool::Instanse()->GetAConnection();
			conPtr = dbconnection->_connection_ptr;
			recordSet.CreateInstance(__uuidof(Recordset));
			sqlString = CreateSqlTool::getGridLonLatBoundString.c_str();
			// ȡ�ñ��еļ�¼
			recordSet->Open(sqlString,conPtr.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
			_variant_t vTmp;
			vTmp.vt = VT_DECIMAL;
			//while(!recordSet->EndOfFile)
			//{
			int i =0;
			if(!lonLatBoundsVector.empty())
				lonLatBoundsVector.clear();
			//����ȡ�ĸ�����
			for(;i<4;i++) {
				vTmp = recordSet->GetCollect(_variant_t((long)i));//������ֶα�ź��ֶ��������� 
				double tmp;
				if(vTmp.vt==VT_NULL || vTmp.vt==VT_EMPTY) {
					tmp = _variant_t((double)0);
				} else {
					tmp = double(vTmp);//.dblVal;
				}
				lonLatBoundsVector.push_back(tmp); 
				//	}
				//	recordSet->MoveNext(); ///�Ƶ���һ����¼
			}

			DBConnPool::Instanse()->CloseRecordSet(recordSet);
			//			DBConnPool::Instanse()->CloseConnection(conPtr);
			DBConnPool::Instanse()->RestoreAConnection(dbconnection);
			//_CrtDumpMemoryLeaks();
			return lonLatBoundsVector;
		} catch(_com_error e) {
			//dbCon.closeRecordSet(recordSet);
			DBConnPool::Instanse()->CloseRecordSet(recordSet);
			//		DBConnPool::Instanse()->CloseConnection(conPtr);
			DBConnPool::Instanse()->RestoreAConnection(dbconnection);
			//_CrtDumpMemoryLeaks();
			cout<<"get lonLatBoundsVector  failed "<<endl;
			cout<<e.Description()<<endl;
		}
	}
	/*
	* @brief    �ж����ֵ����Сֵ
	* @fullName
	* @param	TableName ColumnName
	* @return	max / min
	* @author	YuanMan
	* @date		2014/09/15
	* @warning	
	*/
	long DataBase::MaxId(string maxidString){
		_ConnectionPtr connection;
		DBConnect* dbconnection;
		_RecordsetPtr recordSet;
		try {
			dbconnection = DBConnPool::Instanse()->GetAConnection();
			connection = dbconnection->_connection_ptr;
			recordSet.CreateInstance(__uuidof(Recordset));
			sqlString=maxidString.c_str();
			recordSet->Open(sqlString,connection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
			_variant_t vTmp;
			vTmp.vt = VT_I4;		
			vTmp = recordSet->GetCollect(_variant_t((long)0));
			long tmp;
			tmp = long(vTmp);//.dblVal;
			DBConnPool::Instanse()->CloseRecordSet(recordSet);
			DBConnPool::Instanse()->RestoreAConnection(dbconnection);
			return tmp;

			//DBConnPool::Instanse()->RestoreAConnection(dbconnection);
		}catch(_com_error e) {
			//dbCon.closeConnection(connection
			//		DBConnPool::Instanse()->CloseConnection(connection);
			//_CrtDumpMemoryLeaks();
			DBConnPool::Instanse()->CloseRecordSet(recordSet);
			DBConnPool::Instanse()->RestoreAConnection(dbconnection);
			cout<<"failed";
		}
	}

	long DataBase::MinId(string minidString){
		_ConnectionPtr connection;
		DBConnect* dbconnection;
		_RecordsetPtr recordSet;
		try {
			dbconnection = DBConnPool::Instanse()->GetAConnection();
			connection = dbconnection->_connection_ptr;
			recordSet.CreateInstance(__uuidof(Recordset));
			sqlString=minidString.c_str();
			recordSet->Open(sqlString,connection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
			_variant_t vTmp;
			vTmp.vt = VT_I4;		
			vTmp = recordSet->GetCollect(_variant_t((long)0));
			long tmp;
			tmp = long(vTmp);//.dblVal;
			DBConnPool::Instanse()->CloseRecordSet(recordSet);
			DBConnPool::Instanse()->RestoreAConnection(dbconnection);
			return tmp;

			//DBConnPool::Instanse()->RestoreAConnection(dbconnection);
		}catch(_com_error e) {
			//dbCon.closeConnection(connection
			//		DBConnPool::Instanse()->CloseConnection(connection);
			//_CrtDumpMemoryLeaks();
			DBConnPool::Instanse()->CloseRecordSet(recordSet);
			DBConnPool::Instanse()->RestoreAConnection(dbconnection);
			cout<<"failed";
		}
	}



//************************************  
// ��������: getUserIdFromDb     
// ����˵���� ��С��areaId���������userCnt���û�     
// ����:Franklin     
// ���ڣ�2015/04/07     
// �� �� ֵ: void     
// ��    ��: string tableName      
// ��    ��: int areaId      
// ��    ��: int userCnt      
//************************************
	
 vector<vector<string>> DataBase::getUserFromDb(string tableName,int areaId,int userCnt) {
	//GetDBConnTool dbCon;
	_ConnectionPtr connection;
	DBConnect* dbconnection;
	_RecordsetPtr recordSet;
	try {
		dbconnection = DBConnPool::Instanse()->GetAConnection();
		connection = dbconnection->_connection_ptr;
		sqlString = CreateSqlTool::getRandonUser(tableName,areaId,userCnt).c_str();
		recordSet.CreateInstance(__uuidof(Recordset));
		recordSet->Open(sqlString,connection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
		_variant_t vTmp;
		vector<vector<string>> stringObject;
		while(!recordSet->EndOfFile)
		{
			vector<string> userInfo;
			int i=0;
			for(;i<3;i++) {
				vTmp = recordSet->GetCollect(_variant_t((long)i));//������ֶα�ź��ֶ��������� 
				string tmp;
				if(vTmp.vt==VT_NULL || vTmp.vt==VT_EMPTY) {
					tmp = (_bstr_t) vTmp;
				} else {
					tmp = (_bstr_t)vTmp;//.dblVal;
				}
				userInfo.push_back(tmp); 
			}
			stringObject.push_back(userInfo); 
			recordSet->MoveNext(); ///�Ƶ���һ����¼
		}
		return stringObject;
		DBConnPool::Instanse()->CloseRecordSet(recordSet);
		DBConnPool::Instanse()->RestoreAConnection(dbconnection);
	}catch(_com_error e) {
		DBConnPool::Instanse()->CloseRecordSet(recordSet);
		DBConnPool::Instanse()->RestoreAConnection(dbconnection);
		cout<<e.Description()<<endl;
		cout<<"getRandomUser failed";
	}
}


 //************************************  
 // ��������: getAdjAreaId     
 // ����˵���� �õ�ĳС��������Id    
 // ����:Franklin     
 // ���ڣ�2015/04/08     
 // �� �� ֵ: vector<int>     
 // ��    ��: string tableName      
 // ��    ��: int areaId      
 //************************************
 vector<int> DataBase::getAdjAreaIdFromDb(string tableName,int areaId) {
	 _ConnectionPtr connection;
	 DBConnect* dbconnection;
	 _RecordsetPtr recordSet;
	 try {
		 dbconnection = DBConnPool::Instanse()->GetAConnection();
		 connection = dbconnection->_connection_ptr;
		 sqlString = CreateSqlTool::getAdjAreaId(tableName,areaId).c_str();
		 recordSet.CreateInstance(__uuidof(Recordset));
		 recordSet->Open(sqlString,connection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
		 _variant_t vTmp;
		 vector<int> intObject;
		 while(!recordSet->EndOfFile)
		 {
			 vTmp = recordSet->GetCollect(_variant_t((long)0)); //ȡ����1���ֶΣ���0��ʼ��
			 int tmp = 0;
			 if(vTmp.vt==VT_NULL || vTmp.vt==VT_EMPTY) {
				 tmp = 0;
			 } else {
				 tmp = int(vTmp);//.dblVal;
			 }
			 intObject.push_back(tmp); 
			 recordSet->MoveNext(); ///�Ƶ���һ����¼
		 }
		 return intObject;
		 DBConnPool::Instanse()->CloseRecordSet(recordSet);
		 DBConnPool::Instanse()->RestoreAConnection(dbconnection);
	 }catch(_com_error e) {
		 DBConnPool::Instanse()->CloseRecordSet(recordSet);
		 DBConnPool::Instanse()->RestoreAConnection(dbconnection);
		 cout<<e.Description()<<endl;
		 cout<<"getRandomUser failed";
	 }
 }

 /****************************************
 Sfr�Ż�
 *********************************************/
double DataBase::getAdjAreaGridStrength(int aid,int gridId) {
	double strength = 0;
	string info = CreateSqlTool::getAdjAreaGridStrength(aid,gridId);
	_ConnectionPtr connection;
	DBConnect* dbconnection;
	_RecordsetPtr recordSet;
	try {
		dbconnection = DBConnPool::Instanse()->GetAConnection();
		connection = dbconnection->_connection_ptr;
		recordSet.CreateInstance(__uuidof(Recordset));
		sqlString=info.c_str();
		recordSet->Open(sqlString,connection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
		_variant_t vTmp;
		vTmp = recordSet->GetCollect(_variant_t((long)0));
		if(vTmp.vt==VT_NULL || vTmp.vt==VT_EMPTY) {
			strength = 0;
		} else {
			strength = double(vTmp);//.dblVal;
		}		
		DBConnPool::Instanse()->CloseRecordSet(recordSet);
		DBConnPool::Instanse()->RestoreAConnection(dbconnection);
		return strength;

		//DBConnPool::Instanse()->RestoreAConnection(dbconnection);
	}catch(_com_error e) {
		//dbCon.closeConnection(connection
		//		DBConnPool::Instanse()->CloseConnection(connection);
		//_CrtDumpMemoryLeaks();
		DBConnPool::Instanse()->CloseRecordSet(recordSet);
		DBConnPool::Instanse()->RestoreAConnection(dbconnection);
		cout<<"failed";
	}
	return strength;
}