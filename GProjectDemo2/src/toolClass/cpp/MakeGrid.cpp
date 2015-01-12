#include "stdafx.h"
#include "MakeGrid.h"
void MakeGrid::makeGrid() {
	double longilength = LONGITUDELENGTH;
	double latilength = LATITUDELENGTH;
	DBHelper::deleteData("Grid");
	_ConnectionPtr sqlSp;
	DBConnect* dbconnection;
	_RecordsetPtr m_pRecordset;
	int GId = 1;
	dbconnection = DBConnPool::Instanse()->GetAConnection();
	sqlSp = dbconnection->_connection_ptr;
	//dbCon.getMyConnection(connection);
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	m_pRecordset->Open("SELECT * FROM  Grid",(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);
	//m_pRecordset->MoveFirst();
	//得到经纬度范围
	vector<double> lonLatBounds=GetLonLatBoundsTool::getLonLatBounds();
	double x11=lonLatBounds.at(1); //最小经度
	double y11=lonLatBounds.at(2);  //最大维度
	//右下角维度最小，经度最大
	double x12=lonLatBounds.at(0); //最大经度
	double y12=lonLatBounds.at(3); //最小维度
	//输入的是最小的经度，最大的经度，最小的维度，最大的维度
	double minLongitude=x11;
	double maxLatitude = y11;
	double maxLongitude=x12;
	double minLatitude=y12;
	double redundency=LONGILATIREDUENCY;
	minLongitude-=redundency;
	minLatitude-=redundency;
	maxLongitude+=redundency;
	maxLatitude+=redundency;
	//将边界点作为网格的左上方的点 
	double latitude=maxLatitude-HALF_LATI;
	double longitude=minLongitude+HALF_LONGI;
	do{
		do{
			try{
				m_pRecordset->AddNew();
				m_pRecordset->PutCollect("GId",_variant_t(GId));
				m_pRecordset->PutCollect("GLongitude",_variant_t(longitude));
				m_pRecordset->PutCollect("GLatitude",_variant_t(latitude));
				m_pRecordset->PutCollect("GColor",_variant_t(255*256*256+255*256+255)); //白色
				m_pRecordset->PutCollect("GRealSNR",_variant_t(double(0)));
				m_pRecordset->Update();
			}catch (_com_error &e){
				cout << e.Description()<<endl;
			}
			GId++;
			latitude=latitude-latilength;
		} while(latitude>(minLatitude+HALF_LATI));  //限制网格不会跑出边界（限制中心点的位置）
		longitude=longitude+longilength;
		latitude=maxLatitude;
	} while(longitude<(maxLongitude-HALF_LONGI));   //限制网格不会跑出边界（限制中心点的位置）
	DBConnPool::Instanse()->CloseRecordSet(m_pRecordset);
	DBConnPool::Instanse()->RestoreAConnection(dbconnection);
}

//
//void MakeGrid::makeGrid() {
//	double longilength = LONGITUDELENGTH;
//	double latilength = LATITUDELENGTH;
//	CMapXLayer lyr = m_ctrlMapX.GetLayers().CreateLayer(_T("GridLayer"),_T("E:\\Franklin\\program\\mapinfo\\mapx\\Maps\\Test_Map\\gridMaker.tab"));
//	m_ctrlMapX.GetLayers().SetAnimationLayer(lyr);
//	CMapXFeatureFactory featureFactory=m_ctrlMapX.GetFeatureFactory();
//	vector<double> lonLatBounds=GetLonLatBoundsTool::getLonLatBounds();
//	double x11=lonLatBounds.at(1); //最小经度
//	double y11=lonLatBounds.at(2);  //最大维度
//	//右下角维度最小，经度最大
//	double x12=lonLatBounds.at(0); //最大经度
//	double y12=lonLatBounds.at(3); //最小维度
//	//输入的是最小的经度，最大的经度，最小的维度，最大的维度
//	double minLongitude=x11;
//	double maxLatitude = y11;
//	double maxLongitude=x12;
//	double minLatitude=y12;
//	double redundency=LONGILATIREDUENCY;
//	minLongitude-=redundency;
//	minLatitude-=redundency;
//	maxLongitude+=redundency;
//	maxLatitude+=redundency;
//	//经度增大，维度减小
//
//	//CGProjectDemo2View cView;
//	CMapXPoints points;
//	for(double lonStart=minLongitude;lonStart<=maxLongitude;lonStart+=longilength) {
//		for(double latStart=maxLatitude;latStart>=minLatitude;latStart-=latilength) {
//			double x1=lonStart;
//			double y1 = latStart;
//			double x2 = lonStart+longilength;
//			double y2 = latStart-latilength;
//			//CMapXFeatureFactory featureFactory = m_ctrlMapX.GetFeatureFactory();
//			CMapXPoints points;
//			points.CreateDispatch(points.GetClsid());
//			CMapXPoint point;
//			point.CreateDispatch(point.GetClsid());
//			point.Set(x1,y1);
//			points.Add(point);
//			point.Set(x2,y1);
//			points.Add(point);
//			point.Set(x2,y2);
//			points.Add(point);
//			point.Set(x1,y2);
//			points.Add(point);
//
//			VARIANT variantPoints;
//			variantPoints.vt=VT_DISPATCH;
//			variantPoints.pdispVal=points.m_lpDispatch;
//			variantPoints.pdispVal->AddRef();
//
//			CMapXStyle sty;
//			sty.CreateDispatch(sty.GetClsid());
//			sty.SetRegionBorderWidth(1);
//			sty.SetRegionBorderColor(miColorBlack);
//			sty.SetRegionPattern(miPatternNoFill);
//			sty.SetRegionTransparent(1);
//			VARIANT variantSty;
//			variantSty.vt=VT_DISPATCH;
//			variantSty.pdispVal=sty.m_lpDispatch;
//			variantSty.pdispVal->AddRef();
//			CMapXFeature featureRegion=featureFactory.CreateRegion(variantPoints,variantSty);
//
//			lyr.AddFeature(featureRegion);
//			lyr.Refresh();
//			long count = lyr.AllFeatures().GetCount();
//		}
//	}
//}