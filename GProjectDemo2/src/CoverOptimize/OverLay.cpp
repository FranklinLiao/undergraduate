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
	string SqlString = "update Grid set GOverLay = 1 where (SELECT AID FROM GridFieldStrenth WHERE GRSRP = (select MAX(GRSRP) from GridFieldStrenth where GId = ";
	SqlString.append(ChangeTypeTool::longToString(gid));
	SqlString.append(" ) AND GID =");
	SqlString.append(ChangeTypeTool::longToString(gid));
	SqlString.append(" )!= (SELECT GAId FROM Grid WHERE GId = ");
	SqlString.append(ChangeTypeTool::longToString(gid));
	SqlString.append(" ) and GId = ");
	SqlString.append(ChangeTypeTool::longToString(gid));
	SqlString.append(" and GColor != 0"); //�����ཻ�����ж�Ϊ������
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

string OverLay::showArea() {
	string column = "AOverLay";
	stringstream info; 
	vector<int> areaIdVector = DBHelper::getLayOptimizeAreaId(column);
	vector<int>::iterator iter = areaIdVector.begin();
	while(iter!=areaIdVector.end()) {
		int areaId = *iter++;
		info<<areaId<<",";
	}
	return info.str().substr(0,info.str().length()-1); //ȥ�����һ��,
}

void OverLay::updateOverCell() {
	string column = "AOverLay";
	stringstream info; 
	vector<int> areaIdVector = DBHelper::getLayOptimizeAreaId(column);
	SetCellDialog setCellDialog;
	setCellDialog.CellDialogcellVector = areaIdVector;
	if(IDOK==setCellDialog.DoModal()) {
		if(setCellDialog.flag) {
			MessageBox(NULL,_T("���ڹ�����С�������޸����!"),_T("֪ͨ"),MB_OK);
		} else {
			MessageBox(NULL,_T("δ�޸�С������!"),_T("֪ͨ"),MB_OK);
		}
	}
}