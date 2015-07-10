/*function: 过覆盖判断
  author: YuanMan
  date: 2014/09/25
*/
#include  "stdafx.h"
#include  "OverLay.h"
#include "ChangeTypeTool.h"
#include "stdarg.h"
#include "Windows.h"
#include <iostream>
#include <string>
#include <iterator>
using namespace std;




//************************************  
// 函数名称: ojudge     
// 函数说明：判断某个网格的参数是否达到了过覆盖的标准     
// 作者:Franklin     
// 日期：2015/03/17     
// 返 回 值: std::string     
// 参    数: long gid      
//************************************
string OverLay::ojudge(long gid){
	string SqlString = "update Grid set GOverLay = 1 where (SELECT AID FROM GridFieldStrenth WHERE GRSRP = (select MAX(GRSRP) from GridFieldStrenth where GId = ";
	SqlString.append(ChangeTypeTool::longToString(gid));
	SqlString.append(" ) AND GID =");
	SqlString.append(ChangeTypeTool::longToString(gid));
	SqlString.append(" )!= (SELECT GAId FROM Grid WHERE GId = ");
	SqlString.append(ChangeTypeTool::longToString(gid));
	SqlString.append(" ) and GId = ");
	SqlString.append(ChangeTypeTool::longToString(gid));
	SqlString.append(" and GColor != 0"); //避免相交网格判断为过覆盖
	return SqlString;
}

//************************************  
// 函数名称: ajudge     
// 函数说明：通过判断Area中过覆盖的grid数的比例，来判定Area是否是过覆盖小区    
// 作者:Franklin     
// 日期：2015/03/17     
// 返 回 值: std::string     
// 参    数: long minaid      
// 参    数: long maxaid      
// 参    数: double percent      
//************************************
string OverLay::ajudge(long minaid,long maxaid,double percent){
	string SqlString = "declare @aid int\
                       set @aid = ";
	SqlString.append(ChangeTypeTool::longToString(minaid));
	SqlString.append("declare @ocount decimal(9,3)\
                      declare @acount decimal(9,3)\
                       while @aid<");
	SqlString.append(ChangeTypeTool::longToString(maxaid+1));
	SqlString.append("begin\
                      set @acount = (select COUNT (*) from Grid where GAId = @aid)\
                      set @ocount = (select COUNT (*) from Grid where GAId = @aid and GOverLay = 1)\
                      update Area set AOverLay = 1 where AId = @aid and ( @ocount/@acount>");
	SqlString.append(ChangeTypeTool::doubleToString(percent));
	SqlString.append(" )\
					 set @aid = @aid +1\
					 end");
	return SqlString;
}

string OverLay::showArea() {
	string column = "AOverLay";
	stringstream info; 
	vector<int> areaIdVector = DBHelper::getLayOptimizeAreaId(column);
	vector<int>::iterator iter = areaIdVector.begin();
	while(iter!=areaIdVector.end()) {
		int areaId = *iter++;
		info<<areaId<<",";
	}
	return info.str().substr(0,info.str().length()-1); //去除最后一个,
}

void OverLay::updateOverCell() {
	string column = "AOverLay";
	stringstream info; 
	vector<int> areaIdVector = DBHelper::getLayOptimizeAreaId(column);
	SetCellDialog setCellDialog;
	setCellDialog.CellDialogcellVector = areaIdVector;
	if(IDOK==setCellDialog.DoModal()) {
		if(setCellDialog.flag) {
			MessageBox(NULL,_T("存在过覆盖小区参数修改完成!"),_T("通知"),MB_OK);
		} else {
			MessageBox(NULL,_T("未修改小区参数!"),_T("通知"),MB_OK);
		}
	}
}