#include "stdafx.h"
#include "GetStrongestStrength.h"

void GetStrongestStrength::getStrongestStrength() {
	/*SELECT
top 1 *
from GridFieldStrenthAddBaseNum
where gid = 2
ORDER BY
dbo.GridFieldStrenthAddBaseNum.GId ASC,
dbo.GridFieldStrenthAddBaseNum.GFieldStrength DESC*/
	DataBase db;
	//�˴����ж����������⣬gid�ͱ��е�����������Ӧ��Ӧ����id����������
	//��˸ĳ��˵�grid���У�����grid�ĸ������ж�
	int gRealSnrCount = DBHelper::queryTableInfoNum("Grid");
	for(int id = 1;id <= gRealSnrCount;id++) {
		if(852==id) {
			int kk = 1;
		}
		string sqlString = "SELECT top 1  GId,AId,GFieldStrength from GridFieldStrenthAddBaseNum where gid = ";
		sqlString.append(ChangeTypeTool::intToString(id));
		sqlString.append(" ORDER BY GId ASC, GFieldStrength DESC;");
		vector<vector<string>> vectorString = db.getObjectInfo(sqlString);
		if(vectorString.size()>=1) {
			vector<vector<string>>::iterator iter = vectorString.begin();
			vector<string>::iterator subIter  = (*iter).begin();
			int gid = ChangeTypeTool::stringToInt(*subIter++);
			long aid = ChangeTypeTool::stringToLong(*subIter++);
			double strength = ChangeTypeTool::stringToDouble(*subIter);
			sqlString = "update Grid set GAId = ";
			sqlString.append(ChangeTypeTool::intToString(aid));
			sqlString.append(" ,GRealSNR = ");
			sqlString.append(ChangeTypeTool::doubleToString(strength));
			sqlString.append(" where GId = ");
			sqlString.append(ChangeTypeTool::intToString(gid));
			sqlString.append(";");
			db.updateInfo(sqlString);
		}
	}
}