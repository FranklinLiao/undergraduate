/*function: 弱覆盖判断
  author: YuanMan
  date: 2014/09/25
*/
#include  "stdafx.h"
#include  "WeakLay.h"
#include "ChangeTypeTool.h"
#include "stdarg.h"
#include "Windows.h"
#include <iostream>
#include <string>
#include <iterator>
using namespace std;

//取编号中的最大值和最小值
//tableName = Area columnName = AId
//tableName = Grid columnName = GId
string WeakLay::Max(string tableName,string columnName){
	string MaxString = "SELECT MAX( ";
	MaxString.append(columnName);
	MaxString.append(") FROM ");
	MaxString.append(tableName);
	MaxString.append(" ;");
	return MaxString;
}

string WeakLay::Min(string tableName,string columnName){
	string MinString = "SELECT MIN( ";
	MinString.append(columnName);
	MinString.append(") FROM ");
	MinString.append(tableName);
	MinString.append(" ;");
	return MinString;
}


string WeakLay::GetGAId(long gid){
	string SqlString = "update Grid set GAId = (select MIN(AId) from GridFieldStrength where AId in (select AId from GridFieldStrength where DAtoG in (select MIN(DAtoG) from GridFieldStrength where GId =";
	SqlString.append(ChangeTypeTool::longToString(gid));
	SqlString.append(")))where GId = ");
	SqlString.append(ChangeTypeTool::longToString(gid));
	return SqlString;
}




//string WeakLay::Count(string tableName,string key, string* whereKey, string* whereKeyValue, int whereCount){
//    string sqlString = "select count( ";
//    sqlString.append(key);
//    sqlString.append(") from ");
//    sqlString.append(tableName);
//    sqlString.append(" where ");
//    for(int i = 0; i < whereCount; i++){
//        sqlString.append(whereKey[i]);
//        sqlString.append("=");
//        sqlString.append(whereKeyValue[i]);
//        sqlString.append(" and ");
//     }
//     sqlString = sqlString.substr(0,sqlString.length()-4);
//     sqlString.append(";");
//     return sqlString;
//}


string WeakLay::WJudge(long Gid,double threshold){
       string sqlString = "update Grid set GWeakLay = (select count(*) from GridFieldStrength where GId =  ";
       sqlString.append(ChangeTypeTool::longToString(Gid));
       sqlString.append(" and AId = (select GAId from Grid where GId = ");
       sqlString.append(ChangeTypeTool::longToString(Gid));
       sqlString.append(" ) and GFieldStrength<");
	   sqlString.append(ChangeTypeTool::doubleToString(threshold));
	   sqlString.append(" ) where GId =  ");
	   sqlString.append(ChangeTypeTool::longToString(Gid));
       return sqlString;
}

string WeakLay::AJudge(long minaid,long maxaid,double percent){
	string SqlString = "declare @aid int\
                        set @aid = ";
    SqlString.append(ChangeTypeTool::longToString(minaid));
	SqlString.append(" \
					 declare @wcount decimal(9,3)\
                     declare @acount decimal(9,3)\
					 while @aid<");
	SqlString.append(ChangeTypeTool::longToString((maxaid+1)));
	SqlString.append(" \
					 begin\
                     set @acount = (select COUNT (*) from Grid where GAId = @aid)\
                     set @wcount = (select COUNT (*) from Grid where GAId = @aid and GWeakLay = 1)\
                     update Area set AWeakLay = 1 where AId = @aid and ( @wcount/@acount> ");
    SqlString.append(ChangeTypeTool::doubleToString(percent));
	SqlString.append(" )\
					 set @aid = @aid +1\
					 end");
	return SqlString;
}

