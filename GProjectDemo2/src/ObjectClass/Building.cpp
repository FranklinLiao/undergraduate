#include "stdafx.h"
#include "Building.h"

Building Building::getObject(vector<string> param) {
	Building building = Building(param);
	return building;
}

vector<Building> Building::getObjectSet(vector<vector<string>> param) {
	vector<Building> buildingSet;
	vector<vector<string>>::iterator iter = param.begin();
	while(iter!=param.end()) {
		Building building = Building::getObject(*iter++);
		buildingSet.push_back(building);
	}
	return buildingSet;
}

/*
void Building::GetThisBuildingRecord(int BId)
{
	id=BId;
	
	_ConnectionPtr sqlSp;
	DBConnect* dbconnection;
	_RecordsetPtr m_pRecordset;
	dbconnection = DBConnGuard::GetAConnect();
	sqlSp = dbconnection->_connection_ptr;
	//dbCon.getMyConnection(connection);
	m_pRecordset.CreateInstance(__uuidof(Recordset));

	string Ext;
	BuildingPoint BP;
	stringstream ss;
	Ext.append("SELECT * FROM  BuildingPoint WHERE PBuildingId=");
	ss<<BId;
	Ext.append(ss.str());
	try
	{
		m_pRecordset->Open(Ext.c_str(),(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);
		m_pRecordset->MoveFirst();
		while(!m_pRecordset->EndOfFile)
		{
			
			BP.longitude=double(m_pRecordset->GetCollect("PLongitude"));
			BP.latitude=double(m_pRecordset->GetCollect("PLatitude"));
			BP.id=int(m_pRecordset->GetCollect("PId"));
			BP.px=double(m_pRecordset->GetCollect("PX"));
			BP.py=double(m_pRecordset->GetCollect("PY"));
			BP.buildingId=int(m_pRecordset->GetCollect("PBuildingId"));
			BPoint.push_back(BP);
			m_pRecordset->MoveNext();
			
		}
		Ext.clear();

	}
	catch (_com_error &e)
	{
		cout << e.Description()<<endl;
	}

	m_pRecordset->Close();
	sqlSp->Close();
}
*/

Building Building::getMyself(int bId) {
	Building building;
	string tableName = "Building";
	string key[1] = {"BId"};
	string keyValue[1] = {ChangeTypeTool::intToString(bId)};
	vector<Building> buildingSet = Building::getObjectSet(DBHelper::queryInfo(tableName,key,keyValue,sizeof(key)/sizeof(key[0])));
	vector<Building>::iterator iter =  buildingSet.begin();
	building = *iter;
	return building;
}

vector<BuildingPoint> Building::getBuildingBuildingPoint(int bId) {
		vector<BuildingPoint> buildingPointSet;
		string tableName = "BuildingBuildingPointId";
		string key[1] = {"BId"};
		string keyValue[1] = {ChangeTypeTool::intToString(bId)};
		vector<BuildingBuildingPoint> buildingBuildingPointSet = BuildingBuildingPoint::getBuildingBuildingPointSet(DBHelper::queryInfo(tableName,key,keyValue,sizeof(key)/sizeof(key[0])));
		int bPointId;
		BuildingPoint buildingPoint;
		vector<BuildingBuildingPoint>::iterator iter = buildingBuildingPointSet.begin();
		while(iter!=buildingBuildingPointSet.end()) {
			bPointId = (*iter).getBId();
			buildingPoint = BuildingPoint::getMyself(bId);
			buildingPointSet.push_back(buildingPoint);
			iter++;
		}
		return buildingPointSet;
	
}