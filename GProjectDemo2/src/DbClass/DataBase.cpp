#include "stdafx.h"
#include "DataBase.h"

/**
* @brief    插入信息
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
* @brief    更新数据
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

	//查询数据   返回对象    外面的是对象  里面的是对象的属性
	/*
	vector<vector<string>> DataBase::getObjectInfo(string queryString,string tableName,int tableRowCount){
		DBConnect* dbconnection;
		_ConnectionPtr connection;
		_RecordsetPtr recordSet;
		try {
			//返回数据
			//dbCon.getMyConnection(connection);
			dbconnection = DBConnPool::Instanse()->GetAConnection();
			connection = dbconnection->_connection_ptr;
			recordSet.CreateInstance(__uuidof(Recordset));;
			vector<vector<string>> stringObjectSet;
			sqlString = queryString.c_str();
			int rowCount = tableRowCount;
				//获得表的列数
				//int rowCount = getRowCount(T object);
				// 取得表中的记录
			recordSet->Open(sqlString,connection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
			_variant_t vTmp;
	
				//string stringObject[rowCount];
				//int counter= 0;
				while(!recordSet->EndOfFile)
				{
					int i =0;
					//记得更改  此处知道为4
					//int rowCount = 4;
					
					vector<string> stringObject;
					//判断是否非空，非空则清零
					if(!stringObject.empty())
						stringObject.clear();
					
					
					
					for(;i<rowCount;i++) {
						vTmp = recordSet->GetCollect(_variant_t((long)i));//这儿给字段编号和字段名都可以 
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
					recordSet->MoveNext(); ///移到下一条记录
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
* @brief    得到查询的数据，并封装在string的向量中
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
			//判断是否非空，非空则清零
			if(!stringObject.empty())
				stringObject.clear();
			int rowNum = recordSet->Fields->GetCount(); //得到字段数
			for(int i =0;i<rowNum;i++) {
				vTmp = recordSet->GetCollect(_variant_t((long)i));//这儿给字段编号和字段名都可以 
				string tmp;
				if(vTmp.vt==VT_NULL || vTmp.vt==VT_EMPTY) {
					tmp = (_bstr_t)"";
				} else {
					tmp = (_bstr_t)vTmp;
				}
				stringObject.push_back(tmp); 
			}
			stringObjectSet.push_back(stringObject);
			recordSet->MoveNext(); ///移到下一条记录
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
* @brief    得到网格的ID号
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
//	//获得表的列数
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
	//将数据进行组装成对应的对象
	template <typename K>
	K combineObject(vector<string> info,K object) {
		//根据object的类型，将vector的数据提出来（需要考虑到数据表中属性的顺序），进行组装
		 K realObject;
		 //判断object类型   switch case语句
		 //进行组包
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
* @brief    删除表中所有的数据
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

	////得到数据的结果集
	//_RecordsetPtr DataBase::getObjectInfoRecordset(string queryString) {
	//	//GetDBConnTool dbCon;
	//	DBConnect* dbconnection;
	//	_ConnectionPtr connection;  
	//	_RecordsetPtr recordSet;
	//	try {
	//		//返回数据
	//		//dbCon.getMyConnection(connection);
	//		dbconnection = DBConnPool::Instanse()->GetAConnection();
	//		connection = dbconnection->_connection_ptr;
	//		recordSet.CreateInstance(__uuidof(Recordset));;
	//		sqlString = queryString.c_str();
	//		// 取得表中的记录
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
	// 函数名称: getGridLonLatBounds     
	// 函数说明： 得到建筑物的边界的范围     
	// 作者:Franklin     
	// 日期：2015/03/24     
	// 返 回 值: vector<double>     
	//************************************
	vector<double> DataBase::getLonLatBounds() {
		DBConnect* dbconnection;
		_ConnectionPtr conPtr;  
		_RecordsetPtr recordSet;
		vector<double> lonLatBoundsVector;
		try {
			//返回数据
			//dbCon.getMyConnection(connection);
			dbconnection = DBConnPool::Instanse()->GetAConnection();
			conPtr = dbconnection->_connection_ptr;
			recordSet.CreateInstance(__uuidof(Recordset));
			sqlString = CreateSqlTool::getLonLatBoundString.c_str();
			// 取得表中的记录
			recordSet->Open(sqlString,conPtr.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
			_variant_t vTmp;
			vTmp.vt = VT_DECIMAL;
			//while(!recordSet->EndOfFile)
			//{
			int i =0;
			if(!lonLatBoundsVector.empty())
				lonLatBoundsVector.clear();
			//这里取四个数据
			for(;i<4;i++) {
				vTmp = recordSet->GetCollect(_variant_t((long)i));//这儿给字段编号和字段名都可以 
				double tmp;
				if(vTmp.vt==VT_NULL || vTmp.vt==VT_EMPTY) {
					tmp = _variant_t((double)0);
				} else {
					tmp = double(vTmp);//.dblVal;
				}
				lonLatBoundsVector.push_back(tmp); 
				//	}
				//	recordSet->MoveNext(); ///移到下一条记录
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
	// 函数名称: getGridLonLatBounds     
	// 函数说明： 得到网格边界的范围     
	// 作者:Franklin     
	// 日期：2015/03/24     
	// 返 回 值: vector<double>     
	//************************************
	vector<double> DataBase::getGridLonLatBounds() {
		DBConnect* dbconnection;
		_ConnectionPtr conPtr;  
		_RecordsetPtr recordSet;
		vector<double> lonLatBoundsVector;
		try {
			//返回数据
			//dbCon.getMyConnection(connection);
			dbconnection = DBConnPool::Instanse()->GetAConnection();
			conPtr = dbconnection->_connection_ptr;
			recordSet.CreateInstance(__uuidof(Recordset));
			sqlString = CreateSqlTool::getGridLonLatBoundString.c_str();
			// 取得表中的记录
			recordSet->Open(sqlString,conPtr.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
			_variant_t vTmp;
			vTmp.vt = VT_DECIMAL;
			//while(!recordSet->EndOfFile)
			//{
			int i =0;
			if(!lonLatBoundsVector.empty())
				lonLatBoundsVector.clear();
			//这里取四个数据
			for(;i<4;i++) {
				vTmp = recordSet->GetCollect(_variant_t((long)i));//这儿给字段编号和字段名都可以 
				double tmp;
				if(vTmp.vt==VT_NULL || vTmp.vt==VT_EMPTY) {
					tmp = _variant_t((double)0);
				} else {
					tmp = double(vTmp);//.dblVal;
				}
				lonLatBoundsVector.push_back(tmp); 
				//	}
				//	recordSet->MoveNext(); ///移到下一条记录
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
	* @brief    判断最大值和最小值
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
// 函数名称: getUserIdFromDb     
// 函数说明： 在小区areaId中随机生成userCnt个用户     
// 作者:Franklin     
// 日期：2015/04/07     
// 返 回 值: void     
// 参    数: string tableName      
// 参    数: int areaId      
// 参    数: int userCnt      
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
				vTmp = recordSet->GetCollect(_variant_t((long)i));//这儿给字段编号和字段名都可以 
				string tmp;
				if(vTmp.vt==VT_NULL || vTmp.vt==VT_EMPTY) {
					tmp = (_bstr_t) vTmp;
				} else {
					tmp = (_bstr_t)vTmp;//.dblVal;
				}
				userInfo.push_back(tmp); 
			}
			stringObject.push_back(userInfo); 
			recordSet->MoveNext(); ///移到下一条记录
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
 // 函数名称: getAdjAreaId     
 // 函数说明： 得到某小区的邻区Id    
 // 作者:Franklin     
 // 日期：2015/04/08     
 // 返 回 值: vector<int>     
 // 参    数: string tableName      
 // 参    数: int areaId      
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
			 vTmp = recordSet->GetCollect(_variant_t((long)0)); //取出第1个字段（从0开始）
			 int tmp = 0;
			 if(vTmp.vt==VT_NULL || vTmp.vt==VT_EMPTY) {
				 tmp = 0;
			 } else {
				 tmp = int(vTmp);//.dblVal;
			 }
			 intObject.push_back(tmp); 
			 recordSet->MoveNext(); ///移到下一条记录
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
 Sfr优化
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