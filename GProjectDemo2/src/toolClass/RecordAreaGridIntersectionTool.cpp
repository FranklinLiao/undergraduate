#include "stdafx.h"
#include "RecordAreaGridIntersectionTool.h"
void RecordAreaGridIntersectionTool::recordAreaGridIntersectionTool() {
	try {
		int id = 1;
		string tableName = "Area";
		vector<Area> areaSet = Area::getObjectSet(DBHelper::queryInfo(tableName,NULL,NULL,0));
		//
		vector<Area>::iterator iter = areaSet.begin();
		while(iter!=areaSet.end()) {
			int AId = (*iter).getAId();
			double longitude = (*iter).getALongtitude();
			double latitude = (*iter).getALatitude();
			tableName = "Grid";
			double minLongitude = longitude-HALF_LONGI;
			double maxLongitude = longitude+HALF_LONGI;
			double minLatitude = latitude-HALF_LATI;
			double maxLatitude = latitude+HALF_LATI;
			vector<Grid> gridSet = Grid::getObjectSet(DBHelper::queryStringInfo(CreateSqlTool::createGetSpecialGridId(tableName,minLongitude,maxLongitude,
				minLatitude,maxLatitude)));
			if (gridSet.size()>1)
			{
				return; //只能选出一个网格
			}
			vector<Grid>::iterator iter  = gridSet.begin();
			int gridId = (*iter).getGId();
			if(gridId!=0) {
				tableName = "AreaGridId";
				string key[] = {"Id","AId","AGridId"};
				string keyValue[] = {ChangeTypeTool::intToString(id),ChangeTypeTool::intToString(AId),ChangeTypeTool::intToString(gridId)};
				DBHelper::insertInfo(tableName,key,keyValue,sizeof(key)/sizeof(key[0]));
				id++;
			}
			iter++; 
		};
	} catch(COleDispatchException* e) {
		e->ReportError();
		e->Delete();
	} catch(COleException* e) {
		e->ReportError();
		e->Delete();
	}
}