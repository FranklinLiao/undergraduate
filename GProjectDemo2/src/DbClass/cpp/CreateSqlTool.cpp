#include  "stdafx.h"
#include "CreateSqlTool.h"

string CreateSqlTool::queryAllGridString ="select * from Grid  ORDER BY GId;";
string CreateSqlTool::updateGridSNRString="update Grid set GRealSNR = GRTSNR  where GRTSNR IS NOT NULL;";
string CreateSqlTool::getNotNullSNRGridString = "select * from Grid where GRTSNR IS NOT NULL;";
string CreateSqlTool::getLonLatBoundString = "SELECT MAX(PLongitude),MIN(PLongitude),MAX(PLatitude),MIN(PLatitude) FROM BuildingPoint;";
string CreateSqlTool::queryAllAreaString ="select * from Area Order By AId";
string CreateSqlTool::getTableInfoNum="select count(*) from ";
string CreateSqlTool::getMaxXY="select max(GX),max(GY) from Grid;";
string CreateSqlTool::getRTDataXY = "select RX,RY from RTData where RId = ";
//string CreateSqlTool::createInsertSql(string tableName,string sqlInfo) {
//	string sqlString = "insert into ";
//	sqlString.append(tableName);
//	sqlString.append(" ");
//	sqlString.append(sqlInfo);
//	sqlString.append(";");
//	return sqlString;
//}

//string  CreateSqlTool::createUpdateSql(string tableName,string sqlInfo) {
//	string sqlString = "update ";
//	sqlString.append(tableName);
//	sqlString.append(" set ");
//	sqlString.append(sqlInfo);
//	sqlString.append(";");
//	return sqlString;
//}

//
//string  CreateSqlTool::createAllQuerySql(string tableName,string sqlInfo) {
//	string sqlString = "select * from ";
//	sqlString.append(tableName);
//	sqlString.append(" ");
//	sqlString.append(sqlInfo);
//	sqlString.append(";");
//	return sqlString;
//}
//
//string CreateSqlTool::createPartQuerySql(string tableName,vector<string> param,string sqlInfo) {
//	string sqlString = "select ";
//	vector<string>::iterator iter = param.begin();
//	while(iter!=param.end()) {
//		sqlString.append(*iter++);
//		sqlString.append(",");
//	}
//	//去除最后一个"，"
//	sqlString = sqlString.substr(0,sqlString.length()-1);
//	sqlString.append(" from ");
//	sqlString.append(tableName);
//	sqlString.append(" ");
//	sqlString.append(sqlInfo);
//	sqlString.append(";");
//	return sqlString;
//}

//string CreateSqlTool::getString(int count,...) {
//	string info;
//	va_list pArg;
//	va_start(pArg,count);
//	while(count--) {
//		char* tmp = va_arg(pArg,char *);
//		info.append(tmp);
//	}
//	va_end(pArg);
//	return info;
//}

//string CreateSqlTool::insertBuildingInfo(string tableName,string sqlInfoParts) {
//	string sqlString = "select * from ";
//	sqlString.append(tableName);
//	sqlString.append(" ");
//	sqlString.append(sqlInfoParts);
//	sqlString.append(";");
//	return sqlString;
//}
//string CreateSqlTool::createBuildingSqlInfoPart(int bId,double longitude,double latitude) {
//	//创建建筑物信息部分
//	string sqlInfo=" (BId,BLongitude,BLatitude) values (";
//	sqlInfo.append(ChangeTypeTool::intToString(bId));
//	sqlInfo.append(",");
//	sqlInfo.append(ChangeTypeTool::doubleToStringPrecise(longitude));
//	sqlInfo.append(",");
//	sqlInfo.append(ChangeTypeTool::doubleToStringPrecise(latitude));
//	sqlInfo.append(")");
//	return sqlInfo;
//}
//
//string CreateSqlTool::createBuildingPointSqlInfoPart(int pId,double longitude,double latitude,int bId) {
//	//创建建筑物折点信息部分
//	string sqlInfo=" (PId,PLongitude,PLatitude,PBuildingId) values (";
//	sqlInfo.append(ChangeTypeTool::intToString(pId));
//	sqlInfo.append(",");
//	sqlInfo.append(ChangeTypeTool::doubleToStringPrecise(longitude));
//	sqlInfo.append(",");
//	sqlInfo.append(ChangeTypeTool::doubleToStringPrecise(latitude));
//	sqlInfo.append(",");
//	sqlInfo.append(ChangeTypeTool::intToString(bId));
//	sqlInfo.append(")");
//	return sqlInfo;
//}
//
//string CreateSqlTool::createUpdateGridSNRSqlInfoPart(int gid,double GRealSNR) {
//	string sqlInfo = " GRealSNR = ";
//	sqlInfo.append(ChangeTypeTool::doubleToStringPrecise(GRealSNR));
//	sqlInfo.append(" where GID= ");
//	sqlInfo.append(ChangeTypeTool::intToString(gid));
//	return sqlInfo;
//}

//不用自增，省的调试的时候麻烦
//string CreateSqlTool::createSqlLinkInfoPart(int bId,int pId) {
//	string sqlInfo=" (Id,BId,BPoint) values(";
//	sqlInfo.append(ChangeTypeTool::intToString(bId)); //id数和bpoint的数一样
//	sqlInfo.append(",");
//	sqlInfo.append(ChangeTypeTool::intToString(bId));
//	sqlInfo.append(",");
//	sqlInfo.append(ChangeTypeTool::intToString(pId));
//	sqlInfo.append(")");
//	return sqlInfo;
//}


//string CreateSqlTool::createGridSqlInfoPart(int gId,double longitude,double latitude) {
//	//创建网格建筑物折点信息部分
//	string sqlInfo=" (GId,GLongitude,GLatitude) values (";
//	sqlInfo.append(ChangeTypeTool::intToString(gId));
//	sqlInfo.append(",");
//	sqlInfo.append(ChangeTypeTool::doubleToStringPrecise(longitude));
//	sqlInfo.append(",");
//	sqlInfo.append(ChangeTypeTool::doubleToStringPrecise(latitude));
//	sqlInfo.append(")");
//	return sqlInfo;
//}

//string CreateSqlTool::createGridBuildingSqlInfoPart(int id,int bId,int gId) {
//	string sqlInfo = " (Id,BId,BGridId) values( ";
//	sqlInfo.append(ChangeTypeTool::intToString(id));
//	sqlInfo.append(",");
//	sqlInfo.append(ChangeTypeTool::intToString(bId));
//	sqlInfo.append(",");
//	sqlInfo.append(ChangeTypeTool::intToString(gId));
//	sqlInfo.append(")");
//	return sqlInfo;
//}

//string CreateSqlTool::createGridBuildingPointSqlInfoPart(int pId,int PGridId) {
//	string sqlInfo = " PGridId = ";
//	sqlInfo.append(ChangeTypeTool::intToString(PGridId));
//	sqlInfo.append(" where PId= ");
//	sqlInfo.append(ChangeTypeTool::intToString(pId));
//	return sqlInfo;
//}

/*
string CreateSqlTool::createBaseStationSqlInfoPart(int AId,double ALongitude,double ALatitude,double AHeight,double AAspectAngle,double ADeclineAngle,double ALength,int AType,int ABaseStationAttr) {
	string sqlInfo = " (AId,ALongitude,ALatitude,AHeight,AAspectAngle,ADeclineAngle,ALength,AType,ABaseStationAttr) values(";
	sqlInfo.append(ChangeTypeTool::intToString(AId));
	sqlInfo.append(",");
	sqlInfo.append(ChangeTypeTool::doubleToString(ALongitude));
	sqlInfo.append(",");
	sqlInfo.append(ChangeTypeTool::doubleToString(ALatitude));
	sqlInfo.append(",");
	sqlInfo.append(ChangeTypeTool::doubleToString(AHeight));
	sqlInfo.append(",");
	sqlInfo.append(ChangeTypeTool::doubleToString(AAspectAngle));
	sqlInfo.append(",");
	sqlInfo.append(ChangeTypeTool::doubleToString(ADeclineAngle));
	sqlInfo.append(",");
	sqlInfo.append(ChangeTypeTool::doubleToString(ALength));
	sqlInfo.append(",");
	sqlInfo.append(ChangeTypeTool::intToString(AType));
	sqlInfo.append(",");
	sqlInfo.append(ChangeTypeTool::intToString(ABaseStationAttr));
	sqlInfo.append(")");
	return sqlInfo;
}
*/

//string CreateSqlTool::createBaseStationSqlInfoPart(int AId,double ALongitude,double ALatitude,double AHeight,int ABaseStationAttr,double coverTypeValue) {
//	string sqlInfo = " (AId,ALongitude,ALatitude,AHeight,AFreq,APower) values(";
//	sqlInfo.append(ChangeTypeTool::intToString(AId));
//	sqlInfo.append(",");
//	sqlInfo.append(ChangeTypeTool::doubleToStringPrecise(ALongitude));
//	sqlInfo.append(",");
//	sqlInfo.append(ChangeTypeTool::doubleToStringPrecise(ALatitude));
//	sqlInfo.append(",");
//	sqlInfo.append(ChangeTypeTool::doubleToStringPrecise(AHeight));
//	sqlInfo.append(",");
//	sqlInfo.append(ChangeTypeTool::intToString(ABaseStationAttr));
//	sqlInfo.append(",");
//	sqlInfo.append(ChangeTypeTool::doubleToString(coverTypeValue));
//	sqlInfo.append(")");
//	return sqlInfo;
//}

//string CreateSqlTool::createBSGridSqlInfoPart(int Id,int AId,int AGridId) {
//	string sqlInfo = " (Id,AId,AGridId) values(";
//	sqlInfo.append(ChangeTypeTool::intToString(Id));
//	sqlInfo.append(",");
//	sqlInfo.append(ChangeTypeTool::intToString(AId));
//	sqlInfo.append(",");
//	sqlInfo.append(ChangeTypeTool::intToString(AGridId));
//	sqlInfo.append(")");
//	return sqlInfo;
//}

//string CreateSqlTool::createQueryGridInfo() {
//	string sqlInfo = "select * from Grid where GRTSNR IS NOT NULL;";
//	return sqlInfo;
//}


string CreateSqlTool::createInsertKeyValueSql(string tableName,string* key,string* keyValue,int count) {
	string sqlString = "insert into ";
	sqlString.append(tableName);
	sqlString.append(" (");
	for(int i=0;i<count;i++) {
		sqlString.append(key[i]);
		sqlString.append(",");
	}
	sqlString = sqlString.substr(0,sqlString.length()-1); //去除最后一个,
	sqlString.append(") values(");
	for(int i=0;i<count;i++) {
		sqlString.append(keyValue[i]);
		sqlString.append(",");
	}
	sqlString = sqlString.substr(0,sqlString.length()-1); //去除最后一个,
	sqlString.append(");");
	return sqlString;
}

string CreateSqlTool::createUpdateKeyValueSql(string tableName,string* key,string* keyValue,int count,string* whereKey,string* whereValue,int whereCount) {
	string sqlString = "update  ";
	sqlString.append(tableName);
	sqlString.append(" set ");
	for(int i=0;i<count;i++) {
		sqlString.append(key[i]);
		sqlString.append("=");
		sqlString.append(keyValue[i]);
		sqlString.append(",");
	}
	sqlString =sqlString.substr(0,sqlString.length()-1); //去除最后一个,
	sqlString.append(" where ");
	for(int i=0;i<whereCount;i++) {
		sqlString.append(whereKey[i]);
		sqlString.append("=");
		sqlString.append(whereValue[i]);
		sqlString.append(" and ");
	}
	sqlString = sqlString.substr(0,sqlString.length()- 4); //去除最后一个 "and " 
	sqlString.append(";");
	return sqlString;
}

string CreateSqlTool::createQueryWhereKeyValueSql(string tableName,string* whereKey,string* whereValue,int whereCount) {
	string sqlString = "select * from ";
	sqlString.append(tableName);
	if(whereCount>0) {
		sqlString.append(" where ");
		for(int i=0;i<whereCount;i++) {
			sqlString.append(whereKey[i]);
			sqlString.append("=");
			sqlString.append(whereValue[i]);
			sqlString.append(" and ");
		}
		sqlString = sqlString.substr(0,sqlString.length()- 4); //去除最后一个 "and "
	} 
	sqlString.append(";");
	return sqlString;
}
//查询RTData中xy对应Grid中ID编号
string CreateSqlTool::creategetRTDataId(string tablename,double x,double y){
	string sqlString = "select * from ";
	sqlString.append(tablename);
	sqlString.append(" where GX - ");
	sqlString.append(ChangeTypeTool::doubleToString(x));
	sqlString.append(" < 2.5 and ");
	sqlString.append(ChangeTypeTool::doubleToString(x));
	sqlString.append(" - GX < 2.5 ");
	sqlString.append(" and GY - ");
	sqlString.append(ChangeTypeTool::doubleToString(y));
	sqlString.append(" < 2.5 and ");
	sqlString.append(ChangeTypeTool::doubleToString(y));
	sqlString.append(" - GY  ");
	sqlString.append(" < 2.5;");
	return sqlString;
}


string CreateSqlTool::createGetSpecialGridId(string tableName,double minLongitude,double maxLongitude,double minLatitude,double maxLatitude) {
	string queryString = "select * from ";
	queryString.append(tableName);
	queryString.append(" where (GLongitude Between ");
	queryString.append(ChangeTypeTool::doubleToStringPrecise(minLongitude));
	queryString.append(" and ");
	queryString.append(ChangeTypeTool::doubleToStringPrecise(maxLongitude));
	queryString.append(") and (GLatitude Between ");
	queryString.append(ChangeTypeTool::doubleToStringPrecise(minLatitude));
	queryString.append(" and ");
	queryString.append(ChangeTypeTool::doubleToStringPrecise(maxLatitude));
	queryString.append(");");
	return queryString;
}

string CreateSqlTool::createUpdateDistance(int size,int start) {
	stringstream stream;
	stringstream startStream;
	string startString;
	string sizeString;
	string updateString = "declare @id bigint \
						  declare myCursor CURSOR FOR select top ";
	stream << size;        
	stream >> sizeString;   
	updateString.append(sizeString);
	updateString.append(" gid from Grid where gid >= ");
	startStream << start;        //long型数据输入
	startStream >> startString;   //转换 string
	updateString.append(startString);
	updateString.append(" order by gid \
						open myCursor \
						fetch next from myCursor into @id \
						while @@FETCH_STATUS=0 \
						begin \
						update Grid set GHeight = GLongitude + GLatitude where GId = @id \
						fetch next from myCursor into @id \
						end \
						close myCursor \
						deallocate myCursor");
	return updateString;
}