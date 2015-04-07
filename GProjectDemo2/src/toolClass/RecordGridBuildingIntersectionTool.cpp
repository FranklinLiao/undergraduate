#include "stdafx.h"
#include "RecordGridBuildingIntersectionTool.h"
extern CMapX m_ctrlMapX;
//#import "C:\\program files\\common files\\system\\ado\\msado15.dll"  no_namespace rename("EOF", "adoEOF")
void RecordGridBuildingIntersectionTool::recordGridBuildingIntersectionTool() {
	////////////////删除BuilldingGridId表中数据////////////////////////////	
	DBHelper::deleteData("BuildingGridId");

	double GDotX;
	double GDotY;
	double BDotX;
	double BDotY;
	double ResultX;
	double ResultY;
	double Y1,Y2;
	double X1,X2;
	double result;
	int n1,n2,m1,m2;
	int count;
	double med;
	double XM=0,YM=0;
	_variant_t medm;
	bool borderf;
	int border=0;
	int Bid;
	int BidM=1;
	int Repeat;
	int id=1;
	string RBid;
	string Ext;
	stringstream ss;
	vector<vector<double>> BDotsXs,BDotsYs;
	vector<double> BDotsX,BDotsY;
	vector<double> Ymed,Xmed,Ymed1,Xmed1,MED;
	vector<vector<double>> Ymeds,Xmeds,Ymed1s,Xmed1s,MEDs;
	double BVecX,BVecY;
	double GVecX,GVecY;
	double a[5][2]={{-2.5,-2.5},{2.5,-2.5},{2.5,2.5},{-2.5,2.5},{-2.5,-2.5}};

	DBConnect* dbconnection;
	_ConnectionPtr  sqlSp;
	dbconnection = DBConnPool::Instanse()->GetAConnection();
	sqlSp = dbconnection->_connection_ptr;
	_RecordsetPtr m_pRecordset; //记录集对象指针，用来执行SQL语句并记录查询结果
	_RecordsetPtr m_pRecordset1;
	_RecordsetPtr m_pRecordset2;
	/////////////////得到建筑物最大编号////////////////////////////////////
	BidM= DBHelper::queryTableInfoNum("Building");
	///////////////得到网格最大XY值/////////////////////////////
	vector<int> maxXY = DBHelper::queryGridMaxXY();
	XM=maxXY.at(0);
	YM=maxXY.at(1);
	/////////////////////////////////////////////////////////////
	if(FAILED(m_pRecordset.CreateInstance( _uuidof( Recordset ))))
	{
		cout<<"记录集对象指针实例化失败！"<<endl;
		return;
	}
	if(FAILED(m_pRecordset1.CreateInstance( _uuidof( Recordset ))))
	{
		cout<<"记录集对象指针1实例化失败！"<<endl;
		return;
	}
	if(FAILED(m_pRecordset2.CreateInstance( _uuidof( Recordset ))))
	{
		cout<<"记录集对象指针2实例化失败！"<<endl;
		return;
	}
	try {
		m_pRecordset->Open("SELECT * FROM  Grid order by GId",(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);//打开数据库，执行SQL语句
		m_pRecordset1->Open("SELECT * FROM  BuildingPoint order by PId",(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);
		m_pRecordset2->Open("SELECT * FROM  Building  order by BId",(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);
	}
	catch (_com_error &e)
	{
		cout << e.Description()<<endl;
	}
	
	//////////////////用射线法判断是否点在多边形内部////////////////////////////////////
	for(Bid=1;Bid<=BidM;Bid++)
	{
		Ext.append("SELECT * FROM  BuildingPoint WHERE PBuildingId=");
		ss<<Bid;
		Ext.append(ss.str());
		Ext.append(" order by PId");
		m_pRecordset1->Close();
		m_pRecordset1->Open(Ext.c_str(),(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);
		ss.str("");
		ss.clear();
		Ext.clear();
		while((!m_pRecordset1->EndOfFile))
		{
				
			BDotsX.push_back(m_pRecordset1->GetCollect("PX"));
			BDotsY.push_back(m_pRecordset1->GetCollect("PY"));
			m_pRecordset1->MoveNext();
		}
		BDotsXs.push_back(BDotsX);
		BDotsYs.push_back(BDotsY);
		BDotsX.clear();
		BDotsY.clear();
	}
	////////////////////////////////////////////////////////////////////
	for(Bid=1;Bid<=BidM;Bid++)
	{
		for(int j=0;j<BDotsXs[Bid-1].size()-1;j++)
		{
			Y1=BDotsYs[Bid-1][j+1];
			Y2=BDotsYs[Bid-1][j];
			X1=BDotsXs[Bid-1][j+1];
			X2=BDotsXs[Bid-1][j];
			Xmed1.push_back(X1-X2);
			Ymed1.push_back(Y1-Y2);
			Xmed.push_back(1/(X1-X2));
			Ymed.push_back(1/(Y1-Y2));
			MED.push_back((X1*Y2-X2*Y1));
		}
		MEDs.push_back(MED);
		MED.clear();
		Xmed1s.push_back(Xmed1);
		Ymed1s.push_back(Ymed1);
		Xmed1.clear();
		Ymed1.clear();
		Xmeds.push_back(Xmed);
		Ymeds.push_back(Ymed);
		Ymed.clear();
		Xmed.clear();
	}
	int buildingGridId=1;
	for(GDotX=0;GDotX<=XM;GDotX=GDotX+5){
		for(GDotY=0;GDotY<=YM;GDotY=GDotY+5){
			cout<<id++<<"	";
			for(Bid=1;Bid<=BidM;Bid++){
				n1=0;
				n2=0;
				m1=0;
				m2=0;
				count=0;
				for(int j=0;j<BDotsXs[Bid-1].size()-1;j++){
					X1=BDotsXs[Bid-1][j+1];
					X2=BDotsXs[Bid-1][j];
					Y1=BDotsYs[Bid-1][j+1];
					Y2=BDotsYs[Bid-1][j];
					if(Y1!=Y2){
						ResultX=(Xmed1s[Bid-1][j]*GDotY-MEDs[Bid-1][j])*Ymeds[Bid-1][j];
						if(ResultX>0){
							////////X12Y12大小排序///////////
							if(X1<X2){
								med=X1;
								X1=X2;
								X2=med;
							}
							if(Y1<Y2){
								med=Y1;
								Y1=Y2;
								Y2=med;
							}
							/////////////////判断交点在线段上//////////////////////
							if(GDotY>=Y2&&GDotY<Y1&&ResultX>=X2&&ResultX<X1){
								if(ResultX>GDotX){
									n1++;
								}else{
									n2++;
								}
							}
						}
					}
				}
				if(n1%2==1)
					count++;
				if(n2%2==1)
					count++;
				if(count==2){
					for(int i=0;i<4;i++){
						if(GDotX+a[i][0]>0&&GDotY+a[i][1]>0){
							int BBid=Bid;
							Ext.append("SELECT * FROM  Grid WHERE GX=");
							ss<<GDotX+a[i][0];
							Ext.append(ss.str());
							Ext.append(" AND GY=");
							ss.str("");
							ss.clear();
							ss<<GDotY+a[i][1];
							Ext.append(ss.str());
							ss.str("");
							ss.clear();
							m_pRecordset->Close();
							m_pRecordset->Open(Ext.c_str(),(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);
							Ext.clear();
							//1.记录相交性信息
							//2.相交网格颜色变成白色
							int gId = m_pRecordset->GetCollect("GId");
							int bId = BBid;
							string tableBuildingName = "BuildingGridId";
							string key[] = {"Id","BId","BGridId"};
							string keyValue[] = {ChangeTypeTool::intToString(buildingGridId),ChangeTypeTool::intToString(bId),
								ChangeTypeTool::intToString(gId)};
							DBHelper::insertInfo(tableBuildingName,key,keyValue,sizeof(key)/sizeof(key[0]));
							buildingGridId++;

							//m_pRecordset->PutCollect("GBId",_variant_t(RBid.c_str()));
							m_pRecordset->PutCollect("GRealSNR",_variant_t(double(0)));
							m_pRecordset->PutCollect("GColor",_variant_t(int(0)));
							m_pRecordset->Update();
							RBid.clear();
						}
					}
				}
			}
		}
	}
	DBConnPool::Instanse()->CloseRecordSet(m_pRecordset);
	DBConnPool::Instanse()->CloseRecordSet(m_pRecordset1);
	DBConnPool::Instanse()->CloseRecordSet(m_pRecordset2);
	DBConnPool::Instanse()->RestoreAConnection(dbconnection);
}
//void RecordGridBuildingIntersectionTool::recordGridBuildingIntersectionTool() {
//	CMapXFeatureFactory featureFactory = m_ctrlMapX.GetFeatureFactory();
//	int count = m_ctrlMapX.GetLayers().GetCount();
//	CString name = m_ctrlMapX.GetLayers().Item(1).GetName();
//	CString name2 = m_ctrlMapX.GetLayers().Item(2).GetName();
//	CMapXFeatures featureBuildings = m_ctrlMapX.GetLayers().Item(_T("Beihang")).AllFeatures();
//	CMapXFeatures featureGrids = m_ctrlMapX.GetLayers().Item(_T("gridMaker")).AllFeatures();
//	CMapXFeature featureBuilding;
//	featureBuilding.CreateDispatch(featureBuilding.GetClsid());
//	CMapXFeature featureGrid; 
//	featureGrid.CreateDispatch(featureGrid.GetClsid());
//	BOOL flag;
//	int intersectionCount = 0;
//	int id = 1;
//	for(int i = 1;i<=featureGrids.GetCount();i++) {
//		int pointId = 0;
//		for(int j = 1;j<=featureBuildings.GetCount();j++) {
//			featureGrid = featureGrids.Item(i);
//			featureBuilding = featureBuildings.Item(j);
//			CMapXParts  m_Feature =featureBuilding.GetParts();
//			CMapXPoints m_Points = m_Feature.Item(1);
//			int count = m_Points.GetCount();
//			flag = featureFactory.IntersectionTest(featureBuilding.m_lpDispatch,featureGrid.m_lpDispatch);
//			int gId = 0;
//			int bId = 0;
//			//建筑物和网格的相交判断
//			if(flag==TRUE) {
//				gId = i;
//				bId = j;
//				string tableBuildingName = "BuildingGridId";
//				string key[] = {"Id","BId","BGridId"};
//				string keyValue[] = {ChangeTypeTool::intToString(id),ChangeTypeTool::intToString(bId),
//				ChangeTypeTool::intToString(gId)};
//				DBHelper::insertInfo(tableBuildingName,key,keyValue,sizeof(key)/sizeof(key[0]));
//				//TCHAR szBuffer[256]={0};  
//				id++;
//				intersectionCount++;
//				//double a=featureGrid.GetCenterX();  
//				//wsprintf(szBuffer,_T("%.6f"),a);  
//				//MessageBox(szBuffer,_T("计算"),MB_OK);  
//			}
//			//建筑物折点和网格的相交判断
//			string tableBuildPointName = "BuildingPoint";
//			for(int m = 1;m<=m_Points.GetCount();m++) {
//				CMapXPoint point ;
//				point.CreateDispatch(point.GetClsid());
//				point = m_Points.Item(m);
//				if(point.GetX()>=featureGrid.GetBounds().GetXMin()&&point.GetX()<=featureGrid.GetBounds().GetXMax()&&
//					point.GetY()>=featureGrid.GetBounds().GetYMin()&&point.GetY()<=featureGrid.GetBounds().GetYMax()) {
//						flag=TRUE;
//				} else {
//					flag = FALSE;
//				}
//				//flag = featureFactory.IntersectionTest(point.m_lpDispatch,featureGrid.m_lpDispatch);
//				pointId++;
//				if(flag==TRUE) {
//					//pointId+=m;
//					string key[1] = {"PGridId"};
//					string keyValue[1] = {ChangeTypeTool::intToString(gId)};
//					string whereKey[1] = {"PId"};
//					string whereKeyValue[1] = {ChangeTypeTool::intToString(pointId)};
//					DBHelper::updateInfo(tableBuildPointName,key,keyValue,sizeof(key)/sizeof(key[0]),whereKey,
//						whereKeyValue,sizeof(whereKey)/sizeof(whereKey[0]));
//				}
//			}
//			//pointId+=m_Points.GetCount();
//		}
//	}
//	TCHAR szBuffer[256]={0};
//	wsprintf(szBuffer,_T("%d"),intersectionCount);  
//	MessageBox(NULL,szBuffer,_T("计算"),MB_OK);  
//}