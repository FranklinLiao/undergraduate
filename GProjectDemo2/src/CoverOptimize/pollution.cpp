/*function: 导频污染
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
					  if exists(select * from tempdb..sysobjects where id=object_id('tempdb..##temp1'))\
					  begin\
					  drop table ##temp1\
					  end\
                       select GID,GRSRP,ROW_NUMBER() over(order by GID,GRSRP DESC) as rows into ##temp1 from GridFieldStrenth";
	SqlString.append(" if (select COUNT(*) from GridFieldStrenth where GId = ");
	SqlString.append(ChangeTypeTool::longToString(gid));
	SqlString.append(" and GRSRP> ");
	SqlString.append(ChangeTypeTool::doubleToString(threshold));
	SqlString.append(" )> ");
	SqlString.append(ChangeTypeTool::intToString(count));
	SqlString.append(" begin\
                       set @kk = (select TOP 1 rows from ##temp1 where GId = ");
	SqlString.append(ChangeTypeTool::longToString(gid));
	SqlString.append(" and GRSRP =(select MAX(GRSRP) FROM GridFieldStrenth where GId =");
	SqlString.append(ChangeTypeTool::longToString(gid));
	SqlString.append(" ) ) \
                     update Grid set GPollution = 1 where (abs((select GRSRP from ##temp1 where rows = @kk) - (select GRSRP from ##temp1 where rows = (@kk+");
	SqlString.append(ChangeTypeTool::intToString(count));
	SqlString.append(")))< ");
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

string pollution::showArea() {
	string column = "APollution";
	stringstream info; 
	vector<int> areaIdVector = DBHelper::getLayOptimizeAreaId(column);
	vector<int>::iterator iter = areaIdVector.begin();
	while(iter!=areaIdVector.end()) {
		int areaId = *iter++;
		info<<areaId<<",";
	}
	return info.str().substr(0,info.str().length()-1); //去除最后一个,
}

void pollution::updatePollutionCell() {
	string column = "APollution";
	stringstream info; 
	vector<int> areaIdVector = DBHelper::getLayOptimizeAreaId(column);
	SetCellDialog setCellDialog;
	setCellDialog.CellDialogcellVector = areaIdVector;
	if(IDOK==setCellDialog.DoModal()) {
		if(setCellDialog.flag) {
			MessageBox(NULL,_T("恭喜您，存在导频污染小区参数修改完成!"),_T("通知"),MB_OK);
		} else {
			MessageBox(NULL,_T("未修改小区参数!"),_T("通知"),MB_OK);
		}
	}
}