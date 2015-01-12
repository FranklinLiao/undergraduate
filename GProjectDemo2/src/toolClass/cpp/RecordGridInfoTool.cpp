#include "stdafx.h"
#include "RecordGridInfoTool.h"

bool RecordGridInfoTool::recordGridInfoToDB() {
	//删除表中原有数据  之后可以采用删除全部表中数据，放在App的构造函数中
	bool flag = false;
	CMapXFeatures featuresGrid = m_ctrlMapX.GetLayers().Item(_T("gridMaker")).AllFeatures();
	int gridCount = featuresGrid.GetCount();
	CMapXFeature featureGrid;
	featureGrid.CreateDispatch(featureGrid.GetClsid());
	double gridLongitude = 0.0;
	double gridLatitude = 0.0;
	for(int gridId = 1;gridId<=gridCount;gridId++) {
		featureGrid=featuresGrid.Item(gridId);
		gridLongitude=featuresGrid.Item(gridId).GetCenterX();
		gridLatitude=featuresGrid.Item(gridId).GetCenterY();
		//插入建筑物信息
		string tableName = "Grid";
		string key[] = {"GId","GLongitude","GLatitude"};
		string keyValue[] = {ChangeTypeTool::intToString(gridId),ChangeTypeTool::doubleToStringPrecise(gridLongitude),
			ChangeTypeTool::doubleToStringPrecise(gridLatitude)};
		DBHelper::insertInfo(tableName,key,keyValue,sizeof(key)/sizeof(key[0]));
	}
	flag = true;
	return flag;
}