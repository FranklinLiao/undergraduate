#include "stdafx.h"
#include "DBHelper.h"

void DBHelper::deleteAllTable() {
	deleteData("ANeighbourCell");
	deleteData("Area");
	deleteData("AreaFreq");
	deleteData("AreaGridId");
	deleteData("AtennaGain");
	deleteData("Building");
	deleteData("BuildingAreaId");
	deleteData("BuildingBuildingPointId");
	deleteData("BuildingGridId");
	deleteData("BuildingMaterial");
	deleteData("BuildingPoint");
	deleteData("BuildingPointParam");
	deleteData("Grid");
	deleteData("GridFieldStrength");
	deleteData("RTData");
	//_CrtDumpMemoryLeaks();
}

void DBHelper::deleteData(string tableName) {
	DataBase db;
	db.deletAllInfo(tableName);
}

//void DBHelper::insertBuildingInfoToDB(string tableName,int bId,double longitude,double latitude) {
//	string sqlString = CreateSqlTool::createInsertSql(tableName,CreateSqlTool::createBuildingSqlInfoPart(bId,longitude,latitude));
//	DataBase db;
//	db.insertInfo(sqlString);
//}

//
//void DBHelper::insertBuildingPointToDB(string tableName,int pId,double longitude,double latitude,int bId) {
//	string sqlString = CreateSqlTool::createInsertSql(tableName,CreateSqlTool::createBuildingPointSqlInfoPart(pId,longitude,latitude,bId));
//	DataBase db;
//	db.insertInfo(sqlString);
//}

//void DBHelper::insertBuildingPointLinkToDB (string tableName,int bId,int pId) {
//	string sqlString = CreateSqlTool::createInsertSql(tableName,CreateSqlTool::createSqlLinkInfoPart(bId,pId));
//	DataBase db;
//	//DBCC CHECKIDENT ('BuildingBuildingPointId), RESEED, 1) 
//	db.insertInfo(sqlString);
//}

//void DBHelper::insertGridToDB(string tableName,int gId,double longitude,double latitude) {
//	string sqlString = CreateSqlTool::createInsertSql(tableName,CreateSqlTool::createGridSqlInfoPart(gId,longitude,latitude));
//	DataBase db;
//	db.insertInfo(sqlString);
//}

//void DBHelper::insertGridBuildingIntersectionToDB(string tableName,int id,int bId,int gId) {
//	string sqlString = CreateSqlTool::createInsertSql(tableName,CreateSqlTool::createGridBuildingSqlInfoPart(id,bId,gId));
//	DataBase db;
//	db.insertInfo(sqlString);
//}

//void DBHelper::updateGridBuildingPointIntersectionToDB(string tableName,int pId,int PGridId) {
//	string sqlString = CreateSqlTool::createUpdateSql(tableName,CreateSqlTool::createGridBuildingPointSqlInfoPart(pId,PGridId));
//	DataBase db;
//	db.updateInfo(sqlString);
//}

/*
void DBHelper::insertBaseStationToDB(string tableName,int AId,double ALongitude,double ALatitude,double AHeight,double AAspectAngle,double ADeclineAngle,double ALength,int AType,int ABaseStationAttr) {
	string sqlString = CreateSqlTool::createInsertSql(tableName,CreateSqlTool::createBaseStationSqlInfoPart(AId,ALongitude,ALatitude,AHeight,AAspectAngle,ADeclineAngle,ALength,AType,ABaseStationAttr));
	DataBase db;
	db.insertInfo(sqlString);
}
*/

//void DBHelper::insertBaseStationToDB(string tableName,int AId,double ALongitude,double ALatitude,double AHeight,int ABaseStationAttr,double coverTypeValue) {
//	string sqlString = CreateSqlTool::createInsertSql(tableName,CreateSqlTool::createBaseStationSqlInfoPart(AId,ALongitude,ALatitude,AHeight,ABaseStationAttr,coverTypeValue));
//	DataBase db;
//	db.insertInfo(sqlString);
//}

//void DBHelper::insertBSGridLinkToDB(string tableName,int Id,int AId,int AGridId) {
//	string sqlString = CreateSqlTool::createInsertSql(tableName,CreateSqlTool::createBSGridSqlInfoPart(Id,AId,AGridId));
//	DataBase db;
//	db.insertInfo(sqlString);
//}


vector<vector<string>>  DBHelper::queryGridInfoFromDB() {
	DataBase db;
	vector<vector<string>> stringVector = db.getObjectInfo(CreateSqlTool::getNotNullSNRGridString);
	//_CrtDumpMemoryLeaks();
	return stringVector;
}

vector<vector<string>> DBHelper::queryAreaInfoFromDB() {
	DataBase db;
	vector<vector<string>> stringVector=db.getObjectInfo(CreateSqlTool::queryAllAreaString);
	//_CrtDumpMemoryLeaks();
	return stringVector;
}

//调整后
void DBHelper::insertInfo(string tableName,string* key,string* keyValue,int count) {
	DataBase db;
	db.insertInfo(CreateSqlTool::createInsertKeyValueSql(tableName,key,keyValue,count));
	//_CrtDumpMemoryLeaks();
}

void DBHelper::updateInfo(string tableName,string* key,string* keyValue,int count,string* whereKey,string* whereValue,int whereCount) {
	DataBase db;
	db.updateInfo(CreateSqlTool::createUpdateKeyValueSql(tableName,key,keyValue,count,whereKey,whereValue,whereCount));
	//_CrtDumpMemoryLeaks();
}

vector<vector<string>> DBHelper::queryInfo(string tableName,string* whereKey,string* whereValue,int whereCount) {
	DataBase db;
	vector<vector<string>> objectInfo = db.getObjectInfo(CreateSqlTool::createQueryWhereKeyValueSql(tableName,whereKey,whereValue,whereCount));
	//_CrtDumpMemoryLeaks();
	return objectInfo;
}

void DBHelper::insertStringInfo(string SqlString) {
	DataBase db;
	db.insertInfo(SqlString);
	//_CrtDumpMemoryLeaks();
}

void DBHelper::updateStringInfo(string SqlString) {
	DataBase db;
	db.updateInfo(SqlString);
	//_CrtDumpMemoryLeaks();
}

vector<vector<string>> DBHelper::queryStringInfo(string SqlString) {
	DataBase db;
	vector<vector<string>> objectInfo = db.getObjectInfo(SqlString);
	//_CrtDumpMemoryLeaks();
	return objectInfo;
}


double DBHelper::getLargestStrength() {
	DataBase db;
	vector<vector<string>> SqlString = db.getObjectInfo("select max(GRealSNR) FROM Grid;");
	vector<vector<string>>::iterator iter = SqlString.begin();
	vector<string>::iterator subIter = (*iter).begin();
	double largestStrength = ChangeTypeTool::stringToDouble(*subIter);
	//_CrtDumpMemoryLeaks();
	return largestStrength;
}

int DBHelper::queryTableInfoNum(string tableName) {
	int num = 0;
	DataBase db;
	string getTableInfoNumStr = CreateSqlTool::getTableInfoNum;
	vector<vector<string>> sqlString = db.getObjectInfo(getTableInfoNumStr.append(tableName).append(";"));
	vector<vector<string>>::iterator iter = sqlString.begin();
	vector<string>::iterator subIter = (*iter).begin();
	num = ChangeTypeTool::stringToInt(*subIter);
	return num;
}

vector<int> DBHelper::queryGridMaxXY() {
	vector<int> maxXY;
	DataBase db;
	vector<vector<string>> sqlString = db.getObjectInfo(CreateSqlTool::getMaxXY);
	vector<vector<string>>::iterator iter = sqlString.begin();
	vector<string>::iterator subIter = (*iter).begin();
	maxXY.push_back(ChangeTypeTool::stringToDouble(*subIter++)); //得到maxX
	maxXY.push_back(ChangeTypeTool::stringToDouble(*subIter));   //得到maxY
	return maxXY;
}

//vector<double> DBHelper::queryGridXY(int id) {
//	vector<double> xy;
//	DataBase db;
//	string getGridXYStr = CreateSqlTool::getGridXY;
//	vector<vector<string>> sqlString = db.getObjectInfo(getGridXYStr.append(ChangeTypeTool::intToString(id).append(";")));
//	vector<vector<string>>::iterator iter = sqlString.begin();
//	vector<string>::iterator subIter = (*iter).begin();
//	xy.push_back(ChangeTypeTool::stringToDouble(*subIter++)); //得到X
//	xy.push_back(ChangeTypeTool::stringToDouble(*subIter));   //得到Y
//	return xy;
//}
vector<double> DBHelper::queryRTDataXY(int id) {
	vector<double> xy;
	DataBase db;
	string getRTDataXYStr = CreateSqlTool::getRTDataXY;
	vector<vector<string>> sqlString = db.getObjectInfo(getRTDataXYStr.append(ChangeTypeTool::intToString(id).append(";")));
	vector<vector<string>>::iterator iter = sqlString.begin();
	vector<string>::iterator subIter = (*iter).begin();
	xy.push_back(ChangeTypeTool::stringToDouble(*subIter++)); //得到X
	xy.push_back(ChangeTypeTool::stringToDouble(*subIter));   //得到Y
	return xy;
}

int DBHelper::getRTDataId(string tableName,double x,double y){
	int id;
	DataBase db;
	vector<vector<string>> sqlString = db.getObjectInfo(CreateSqlTool::creategetRTDataId(tableName,x,y));
	if(sqlString.size()>0) { //如果这个路测点在网格的范围内  就返回对应的网格号
		vector<vector<string>>::iterator iter = sqlString.begin();
		
		vector<string>::iterator subIter = (*iter).begin(); //这里放置的是第一行数据中的各个字段
		string idString = *subIter; //取出第一个字段
		return ChangeTypeTool::stringToInt(idString);
	} else {  //否则返回0
		return 0;
	}
	
}

//干扰优化
vector<User> DBHelper::getUser(int areaId,int userCnt) {
	DataBase db;
	string tableName = "Grid";
	vector<User> users;
	vector<vector<string>> userInfos = db.getUserFromDb(tableName,areaId,userCnt);
	vector<vector<string>>::iterator iterout = userInfos.begin();
	while(iterout!=userInfos.end()) {
		vector<string>::iterator iterin = (*iterout++).begin();
		int gridId = ChangeTypeTool::stringToInt(*iterin++);
		double rsrp = ChangeTypeTool::stringToDouble(*iterin++);
		double x = ChangeTypeTool::stringToDouble(*iterin++);
		double y = ChangeTypeTool::stringToDouble(*iterin++);
		User user = User(gridId,rsrp,x,y);
		users.push_back(user);
	}
	return users;
}

vector<int> DBHelper::getAdjAreaId(int areaId) {
	DataBase db;
	string tableName="ANeighbourCell";
	vector<int> adjAreaId = db.getAdjAreaIdFromDb(tableName,areaId);
	return adjAreaId;
}

double DBHelper::getAdjAreaGridStrength(int aid,int gridId) {
	DataBase db;
	double strength = db.getAdjAreaGridStrength(aid,gridId);
	return strength;
}


double DBHelper::getServerRSRP(int aid,int gid) {
	DataBase db;
	double strength = db.getServerRSRPFromDB(aid,gid);
	return strength;
}

double DBHelper::getGridMaxXY(int flag) {
	DataBase db;
	double xy = db.getMaxGridXY(flag);
	return xy;
}

vector<UserANR> DBHelper::getUserANR(int areaId,int userCnt) {
	DataBase db;
	string tableName = "Grid";
	vector<UserANR> users;
	vector<vector<string>> userInfos = db.getUserANRFromDb(tableName,areaId,userCnt);
	vector<vector<string>>::iterator iterout = userInfos.begin();
	while(iterout!=userInfos.end()) {
		vector<string>::iterator iterin = (*iterout++).begin();
		int gridId = ChangeTypeTool::stringToInt(*iterin++);
		double x = ChangeTypeTool::stringToDouble(*iterin++);
		double y = ChangeTypeTool::stringToDouble(*iterin++);
		UserANR userANR = UserANR(gridId,x,y);
		users.push_back(userANR);
	}
	return users;
}



int DBHelper::getGidFromXY(double x,double y) {
	DataBase db;
	int gid = db.getGidFromXY(x,y);
	return gid;
}
