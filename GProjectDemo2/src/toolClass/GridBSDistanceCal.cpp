#include "stdafx.h"
#include "GridBSDistanceCal.h"
#define COUNTSIZE 100
void GridBSDistanceCal::updateDistance() {

	//得到grid的个数
	string tableName = "GridFieldStrenth";
	long rowCount = DBHelper::queryTableInfoNum(tableName);
	//rowCount = 1000;
	int time = rowCount / (COUNTSIZE);
	int left = rowCount % (COUNTSIZE);
	int index = 0;
	while(index <time) {
		string sqlString = CreateSqlTool::createUpdateDistance((COUNTSIZE),(index*(COUNTSIZE))+1);
		DataBase db;
		db.updateInfo(sqlString);
		index++;
	}
	//left插入
	if(left!=0) {
		string sqlString = CreateSqlTool::createUpdateDistance(left,(index*(COUNTSIZE))+1);
		DataBase db;
		db.updateInfo(sqlString);
	}
}

void GridBSDistanceCal::updateGridAidRsrp() {
	/*
	string maxGid =  "SELECT MAX(gid) from Grid";
	DataBase Maxgid;
	long maxgid = Maxgid.MaxId(maxGid);
	for(long gid = 1;gid<=maxgid;gid++){
		string SqlString = "update Grid set GAId = (select MIN(AId) from GridFieldStrenth where AId in (select AId from GridFieldStrenth where DAtoG in (select MIN(DAtoG) from GridFieldStrenth where GId =";
		SqlString.append(ChangeTypeTool::longToString(gid));
		SqlString.append(")))where GId = ");
		SqlString.append(ChangeTypeTool::longToString(gid));
		DataBase db;
		db.updateInfo(SqlString);
	}
	*/
	string maxGid =  "SELECT MAX(gid) from Grid";
	DataBase Maxgid;
	long maxgid = Maxgid.MaxId(maxGid);
	for(long gid = 1;gid<=maxgid;gid++){
		string sqlString = "\
			declare @gid int\
			declare @gaid int\
			declare @grealrsrp float\
			set @gaid = 0;\
			set @gid = ";
		sqlString.append(ChangeTypeTool::longToString(gid));
		sqlString.append("\
			set @grealrsrp = 0;\
			select @gaid = MIN(AId) from GridFieldStrenth where AId in (select AId from GridFieldStrenth where DAtoG in (select MIN(DAtoG) from GridFieldStrenth where Gid = @gid))\
			select @grealrsrp = GRSRP from GridFieldStrenth where Aid = @gaid and Gid = @gid;\
			if(@gaid!=0 and @grealrsrp !=0)\
				begin\
				update Grid set GAId = @gaid,GRealRsrp = @grealrsrp where GId =@gid;\
				end");
		//string SqlString = "update Grid set GAId = (select MIN(AId) from GridFieldStrenth where AId in (select AId from GridFieldStrenth where DAtoG in (select MIN(DAtoG) from GridFieldStrenth where GId =";
		//SqlString.append(ChangeTypeTool::longToString(gid));
		//SqlString.append(")))where GId = ");
		//SqlString.append(ChangeTypeTool::longToString(gid));
		DataBase db;
		db.updateInfo(sqlString);
	}
	/*
	string SqlString = "\
		declare @gridCnt int\
		declare @gid int\
		declare @gaid int\
		declare @grealrsrp float\
		SELECT @gridCnt = MAX(gid)  from Grid\
		set @gid = 1\
		while @gid <= @gridCnt\
			begin\
				set @gaid = 0;\
				set @grealrsrp = 0;\
				select @gaid = MIN(AId) from GridFieldStrenth where AId in (select AId from GridFieldStrenth where DAtoG in (select MIN(DAtoG) from GridFieldStrenth where Gid = @gid))\
				select @grealrsrp = GRSRP from GridFieldStrenth where Aid = @gaid and Gid = @gid;\
				if(@gaid!=0 and @grealrsrp !=0)\
					begin\
						update Grid set GAId = @gaid,GRealRsrp = @grealrsrp where GId =@gid;\
					end\
				set @gid = @gid + 1;\
			end";
	DataBase db;
	db.updateInfo(SqlString);
	*/
}