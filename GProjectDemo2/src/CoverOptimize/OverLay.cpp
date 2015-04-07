/*function: �������ж�
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
// ��������: ojudge     
// ����˵�����ж�ĳ������Ĳ����Ƿ�ﵽ�˹����ǵı�׼     
// ����:Franklin     
// ���ڣ�2015/03/17     
// �� �� ֵ: std::string     
// ��    ��: long gid      
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
// ��������: ajudge     
// ����˵����ͨ���ж�Area�й����ǵ�grid���ı��������ж�Area�Ƿ��ǹ�����С��    
// ����:Franklin     
// ���ڣ�2015/03/17     
// �� �� ֵ: std::string     
// ��    ��: long minaid      
// ��    ��: long maxaid      
// ��    ��: double percent      
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