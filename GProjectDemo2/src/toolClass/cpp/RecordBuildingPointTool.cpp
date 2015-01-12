#include "StdAfx.h"
#include "RecordBuildingPointTool.h"


RecordBuildingPointTool::RecordBuildingPointTool(void)
{
	//实际使用中的文件时通过读取.mif文件对话框来指定的
	FilePosition="D:\\prgram\\my documents\\BProjectDemo1\\resource\\cutty.MIF";

}


RecordBuildingPointTool::~RecordBuildingPointTool(void)
{
}


bool RecordBuildingPointTool::RecordBuildingLayerInfoToDB()
{
	//先清空所有原来数据表中所有的记录
	DBHelper::deleteData("Building");
	DBHelper::deleteData("BuildingPoint");
	DBHelper::deleteData("BuildingBuildingPointId");
	int LayerCount = m_ctrlMapX.GetLayers().GetCount();
	CMapXFeatures featuresBuildings = m_ctrlMapX.GetLayers().Item(1).AllFeatures();
	//m_ctrlMapX.GetLayers().Item(1).SetAutoLabel(TRUE);
	//首先得到label的属性
	CMapXLabelProperties labelProperty =  m_ctrlMapX.GetLayers().Item(1).GetLabelProperties();
	//labelProperty.SetVisible(FALSE);
	//fall对应的数据
	CString layerName = m_ctrlMapX.GetLayers().Item(1).GetName();
	//CString LyaeName = m_ctrlMapX.GetLayers().Item(2).GetName();
	int fieldCount  = m_ctrlMapX.GetLayers().Item(1).GetDatasets().Item(1).GetFields().GetCount();
	CString name = m_ctrlMapX.GetLayers().Item(1).GetDatasets().Item(1).GetFields().Item(2).GetName();
	//int mm = m_ctrlMapX.GetLayers().Item(2).GetDatasets().GetCount();
	 //fieldCount  = m_ctrlMapX.GetLayers().Item(2).GetDatasets().Item(1).GetFields().GetCount();
	// name = m_ctrlMapX.GetLayers().Item(2).GetDatasets().Item(1).GetFields().Item(1).GetName();
	//rowvalues获得值
	int count =  m_ctrlMapX.GetLayers().Item(1).GetDatasets().Item(1).GetRowCount();
	//CString value2 =  m_ctrlMapX.GetLayers().Item(2).GetDatasets().Item(1).GetName();
	//CString name = fields.Item(1).GetName();
	//style.PickText();



	//feautes中计数从1开始
	int iPoint=1;
	for(int iBuilding=1;iBuilding<=featuresBuildings.GetCount();iBuilding++) {
		CMapXFeature featureBuilding = featuresBuildings.Item(iBuilding);
		double buildingHha = featureBuilding.GetArea();
		double buildingLongitude = featureBuilding.GetCenterX();
		double buildingLatitude = featureBuilding.GetCenterY();
		//得到高度数据

		CString buildingHeight =  m_ctrlMapX.GetLayers().Item(1).GetDatasets().Item(1).GetValue(iBuilding,2);
		//featureBuilding.GetStyle().
		//CString paramBuilding = featureBuilding.GetLayer();
		//插入建筑物信息
		//double MaxLongi=116.34746,MinLongi=116.332971;
		//double MaxLati=39.985083,MinLati=39.975356;
		//按照要求提取出北航的建筑物
		//if((buildingLongitude>MinLongi)&&(buildingLongitude<MaxLongi)&&(buildingLatitude>MinLati)&&(buildingLatitude<MaxLati)) {
			string tableName = "Building";
			string key[] = {"BId","BLongitude","BLatitude","BHeight"};
			string keyValue[] = {ChangeTypeTool::intToString(iBuilding),ChangeTypeTool::doubleToStringPrecise(buildingLongitude),
				ChangeTypeTool::doubleToStringPrecise(buildingLatitude),buildingHeight};
			DBHelper::insertInfo(tableName,key,keyValue,sizeof(key)/sizeof(key[0]));

			//DBHelper::insertBuildingInfoToDB("Building",iBuilding,buildingLongitude,buildingLatitude);
			//插入建筑物折点 
			CMapXParts  m_Feature =featureBuilding.GetParts();
			int fcount = m_Feature.GetCount();
			CMapXPoints m_Points = m_Feature.Item(1);
			int count = m_Points.GetCount();
			for(int i=1;i<=m_Points.GetCount();i++) {
				double pointLongitude = m_Points.Item(i).GetX();
				double pointLatitude = m_Points.Item(i).GetY();
				tableName = "BuildingPoint";
				string key2[] = {"PId","PLongitude","PLatitude","PHeight","PBuildingId"};
				string keyValue2[] = {ChangeTypeTool::intToString(iPoint),ChangeTypeTool::doubleToStringPrecise(pointLongitude),ChangeTypeTool::doubleToStringPrecise(pointLatitude),
					buildingHeight,ChangeTypeTool::intToString(iBuilding)};
				DBHelper::insertInfo(tableName,key2,keyValue2,sizeof(key2)/sizeof(key2[0]));
				//DBHelper::insertBuildingPointToDB("BuildingPoint",iPoint,pointLongitude,pointLatitude,iBuilding);
				tableName = "BuildingBuildingPointId";
				string key3[] = {"Id","BId","BPointId"};
				string keyValue3[] = {ChangeTypeTool::intToString(iBuilding),ChangeTypeTool::intToString(iBuilding),ChangeTypeTool::intToString(iPoint)};
				DBHelper::insertInfo(tableName,key3,keyValue3,sizeof(key3)/sizeof(key3[0]));
				iPoint++;
			}
		//}
	}
	
	/*
	//////////////////
	string num;
	int flag=0;
	int i=0;
	int BId=1;
	int id=1;
	double longitude,latitude;
	file.open(FilePosition);
	if(!file)
	{
		::MessageBox(NULL,_T("文件未打开！"),_T("警告"),MB_OK);
		return false;
	}
		while(file>>num)
	{
		if(num.find("Pen")!=string::npos)
		{
			flag=0;
		}
		if(flag!=0)
		{
			if(flag==1)
			{
				stringstream s(num);
				s>>i;
				flag=2;
				continue;
			}
			try {
			recordSet->AddNew();
			stringstream s1(num);
			s1>>longitude;
			Bpoint.append(num);
			Bpoint.append(",");
			file>>num;
			stringstream s2(num);
			s2>>latitude;
			Bpoint.append(num);
			Bpoint.append(";");
			recordSet->PutCollect("PLongitude",_variant_t(double(longitude)));
			recordSet->PutCollect("PLatitude",_variant_t(double(latitude)));
			recordSet->PutCollect("PId",_variant_t(int(id)));
			recordSet->PutCollect("PBuildingId",_variant_t(int(BId)));
			recordSet->Update();
			id++;
			}
			catch (_com_error &e)
		{
			::MessageBox(NULL,e.Description(),_T("警告"),MB_OK);
		}
		}
		if(num=="1")
		{
			flag=1;
		}
		if(num.find("Center")!=string::npos)
		{
			file>>num;
			file>>num;
			try{
			recordSet1->AddNew();
			//recordSet1->PutCollect("BPoint",_variant_t(Bpoint.c_str()));
			recordSet1->PutCollect("BId",_variant_t(int(BId)));
			//recordSet1->PutCollect("BLongitude",_variant_t(double()))
			recordSet1->Update();
			Bpoint.clear();
			BId++;
			}
			catch (_com_error &e)
		{
			::MessageBox(NULL,e.Description(),_T("警告"),MB_OK);
		}
		}
	}
	*/
		return true;
}