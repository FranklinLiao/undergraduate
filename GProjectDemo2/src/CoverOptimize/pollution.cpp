/*function: µº∆µŒ€»æ
  author: YuanMan
  date: 2014/09/28
*/
#include  "stdafx.h"
#include  "pollution.h"
#include "ChangeTypeTool.h"
#include "Windows.h"
#include <iostream>
#include <string>
#include <iterator>
using namespace std;

string pollution::PJudge(long gid,int count, double threshold,double difference ){
	string SqlString ="declare @kk bigint \
                       select GID,GFieldStrength,ROW_NUMBER() over(order by GID,GFieldStrength DESC) as rows into ##temp1 from GridFieldStrength";
	SqlString.append(" if (select COUNT(*) from GridFieldStrength where GId = ");
	SqlString.append(ChangeTypeTool::longToString(gid));
	SqlString.append(" and GFieldStrength> ");
	SqlString.append(ChangeTypeTool::doubleToString(threshold));
	SqlString.append(" )> ");
	SqlString.append(ChangeTypeTool::intToString(count));
	SqlString.append(" begin\
                       set @kk = (select TOP 1 rows from ##temp1 where GId = ");
	SqlString.append(ChangeTypeTool::longToString(gid));
	SqlString.append(" and GFieldStrength =(select MAX(GFieldStrength) FROM GridFieldStrength where GId =");
	SqlString.append(ChangeTypeTool::longToString(gid));
	SqlString.append(" ) ) \
                     update Grid set GPollution = 1 where (abs((select GFieldStrength from ##temp1 where rows = @kk) - (select GFieldStrength from ##temp1 where rows = (@kk+3)))< ");
	SqlString.append(ChangeTypeTool::doubleToString(difference));
	SqlString.append(" ) and GId=");
	SqlString.append(ChangeTypeTool::longToString(gid));
	SqlString.append(" end\
                       drop table ##temp1");
	return SqlString;
}

string pollution::APJudge(double percent,long minaid,long maxaid){
	string SqlString = "declare @aid int\
                        set @aid = ";
	SqlString.append(ChangeTypeTool::longToString(minaid));
	SqlString.append(" declare @ocount decimal(9,3)\
                       declare @acount decimal(9,3)\
                        while @aid<");
	SqlString.append(ChangeTypeTool::longToString(maxaid));
	SqlString.append(" begin\
                       set @acount = (select COUNT (*) from Grid where GAId = @aid)\
                       set @ocount = (select COUNT (*) from Grid where GAId = @aid and GPollution = 1)\
                       update Area set APollution = 1 where AId = @aid and ( @ocount/@acount> ");
	SqlString.append(ChangeTypeTool::doubleToString(percent));
	SqlString.append(" )\
                      set @aid = @aid +1\
                      end");
	return SqlString;
}