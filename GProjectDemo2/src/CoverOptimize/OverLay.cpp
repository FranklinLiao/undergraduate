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
	string SqlString = "update Grid set GOverLay = 1 where (SELECT AID FROM GridFieldStrength WHERE GFieldStrength = (select MAX(GFieldStrength) from GridFieldStrength where GId = ";
	SqlString.append(ChangeTypeTool::longToString(gid));
	SqlString.append(" ) AND GID =");
	SqlString.append(ChangeTypeTool::longToString(gid));
	SqlString.append(" )!= (SELECT GAId FROM Grid WHERE GId = ");
	SqlString.append(ChangeTypeTool::longToString(gid));
	SqlString.append(" ) and GId = ");
	SqlString.append(ChangeTypeTool::longToString(gid));
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