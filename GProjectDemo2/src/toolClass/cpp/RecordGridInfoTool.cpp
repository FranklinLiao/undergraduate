#include "stdafx.h"
#include "RecordGridInfoTool.h"

bool RecordGridInfoTool::recordGridInfoToDB() {
	//ɾ������ԭ������  ֮����Բ���ɾ��ȫ���������ݣ�����App�Ĺ��캯����
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
		//���뽨������Ϣ
		string tableName = "Grid";
		string key[] = {"GId","GLongitude","GLatitude"};
		string keyValue[] = {ChangeTypeTool::intToString(gridId),ChangeTypeTool::doubleToStringPrecise(gridLongitude),
			ChangeTypeTool::doubleToStringPrecise(gridLatitude)};
		DBHelper::insertInfo(tableName,key,keyValue,sizeof(key)/sizeof(key[0]));
	}
	flag = true;
	return flag;
}