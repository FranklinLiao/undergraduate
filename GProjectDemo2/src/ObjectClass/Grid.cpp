
#include "stdafx.h"
#include "Grid.h"

Grid Grid::getObject(vector<string> param) {
	Grid grid = Grid(param);
	return grid;
}


/*
Grid Grid::getPartObject(vector<string> param) {
	Grid grid;
	vector<string>::iterator iter = param.begin();
	while(iter!=param.end()) {
		grid.setGAId(ChangeTypeTool::stringToInt(*iter++));
		grid.setGRealSNR(ChangeTypeTool::stringToDouble(*iter++));
		grid.setGRTSNR(ChangeTypeTool::stringToDouble(*iter++));
	}
	return grid;
}
*/

vector<Grid> Grid::getObjectSet(vector<vector<string>> param) {
	vector<Grid> gridSet;
	vector<vector<string>>::iterator iter = param.begin();
	/*
	if(iter.size()>3) {
		while(iter!=param.end()) {
			Grid grid = Grid::getFullObject(*iter++);
			gridSet.push_back(grid);
		}
	} else if(iter.size()==3) {
		while(iter!=param.end()) {
			Grid grid = Grid::getPartObject(*iter++);
			gridSet.push_back(grid);
		}
	}
	*/
	while(iter!=param.end()) {
		Grid grid = Grid::getObject(*iter++);
		gridSet.push_back(grid);
	}
	return gridSet;
}

/*
void Grid::GetThisGirdRecord(int GId)
{
	_ConnectionPtr sqlSp;
	DBConnect* dbconnection;
	_RecordsetPtr m_pRecordset;
	dbconnection = DBConnGuard::GetAConnect();
	sqlSp = dbconnection->_connection_ptr;
	//dbCon.getMyConnection(connection);
	m_pRecordset.CreateInstance(__uuidof(Recordset));

	string Ext;
	string medm;
	int mBid1,mBid2;
	stringstream ss;
	Ext.append("SELECT * FROM  Grid WHERE GId=");
	ss<<GId;
	Ext.append(ss.str());
	try
	{
		m_pRecordset->Open(Ext.c_str(),(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);
		Ext.clear();
		id=GId;
		longitude=m_pRecordset->GetCollect("GLongitude");
		latitude=m_pRecordset->GetCollect("GLatitude");
		GPX=m_pRecordset->GetCollect("GPX");
		GPY=m_pRecordset->GetCollect("GPY");
		Ext.append(_bstr_t(m_pRecordset->GetCollect("GBId")));
		GBId=ChangeTypeTool::stringToIntVector(Ext.c_str(),";");
		sort( GBId.begin(), GBId.end() );
		GBId.erase( unique( GBId.begin(), GBId.end() ), GBId.end() );
		Ext.clear();
		
	}
	catch (_com_error &e)
	{
		cout << e.Description()<<endl;
	}
	m_pRecordset->Close();
	sqlSp->Close();
}


void Grid::GetThisGirdRecord(double GX, double GY)
{
	_ConnectionPtr sqlSp;
	DBConnect* dbconnection;
	_RecordsetPtr m_pRecordset;
	dbconnection = DBConnGuard::GetAConnect();
	sqlSp = dbconnection->_connection_ptr;
	//dbCon.getMyConnection(connection);
	m_pRecordset.CreateInstance(__uuidof(Recordset));


	string Ext;
	string medm;
	int mBid1,mBid2;
	stringstream ss;
	Ext.append("SELECT * FROM  Grid WHERE GPX=");
	ss<<GX;
	Ext.append(ss.str());
	ss.str("");
	Ext.append(" AND GPY=");
	ss<<GY;
	Ext.append(ss.str());
	ss.str("");
	try
	{
		m_pRecordset->Open(Ext.c_str(),(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);
		Ext.clear();
		id=m_pRecordset->GetCollect("GId");
		longitude=m_pRecordset->GetCollect("GLongitude");
		latitude=m_pRecordset->GetCollect("GLatitude");
		GPX=GX;
		GPY=GY;
		Ext.append(_bstr_t(m_pRecordset->GetCollect("GBId")));
		GBId=ChangeTypeTool::stringToIntVector(Ext.c_str(),";");
		sort( GBId.begin(), GBId.end() );
		GBId.erase( unique( GBId.begin(), GBId.end() ), GBId.end() );
		
	}
	catch (_com_error &e)
	{
		cout << e.Description()<<endl;
	}
	m_pRecordset->Close();
	sqlSp->Close();
}
*/

vector<Building> Grid::getGridBuilding(int bGridId) {
	vector<Building> buildingSet;
	string tableName = "BuildingGridId";
	string key[1] = {"BGridId"};
	string keyValue[1] = {ChangeTypeTool::intToString(bGridId)};
	vector<BuildingGrid> buildingGridSet = BuildingGrid::getObjectSet(DBHelper::queryInfo(tableName,key,keyValue,sizeof(key)/sizeof(key[0])));
	int bId;
	Building building;
	vector<BuildingGrid>::iterator iter = buildingGridSet.begin();
	while(iter!=buildingGridSet.end()) {
		bId = (*iter).getBId();
		building = Building::getMyself(bId);
		buildingSet.push_back(building);
		iter++;
	}
	return buildingSet;
}

Grid Grid::getMyself(int gId) {
	Grid grid;
	string tableName = "Grid";
	string key[1] = {"GId"};
	string keyValue[1] = {ChangeTypeTool::intToString(gId)};
	vector<Grid> gridSet = Grid::getObjectSet(DBHelper::queryInfo(tableName,key,keyValue,sizeof(key)/sizeof(key[0])));
	vector<Grid>::iterator iter =  gridSet.begin();
	grid = *iter;
	return grid;
}

Grid Grid::getMyselfByXY(double gX,double gY) {
	Grid grid;
	string tableName = "Grid";
	string key[2] = {"GX","GY"};
	string keyValue[2] = {ChangeTypeTool::doubleToString(gX),ChangeTypeTool::doubleToString(gY)};
	vector<Grid> gridSet = Grid::getObjectSet(DBHelper::queryInfo(tableName,key,keyValue,sizeof(key)/sizeof(key[0])));
	vector<Grid>::iterator iter =  gridSet.begin();
	grid = *iter;
	return grid;
}

vector<Grid> Grid::getAllGrid() {
	string tableName = "Grid";
	vector<Grid> gridSet = Grid::getObjectSet(DBHelper::queryInfo(tableName,NULL,NULL,0));
	return gridSet;
}