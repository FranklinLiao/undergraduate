#include "StdAfx.h"
#include "MakeGridFileTool.h"


//bool MakeGridFileTool::makeGridFile(string fileNameString)
//{
//	ofstream file2(fileNameString,ios::out);
//	file2<<"Version   300"<<endl;
//	file2<<"Charset \"WindowsSimpChinese\""<<endl;
//	file2<<"Delimiter \",\""<<endl;
//	file2<<"CoordSys Earth Projection 1, 104"<<endl;
//	file2<<"Columns 5"<<endl;
//	file2<<"  TYPE Integer"<<endl;
//	file2<<"  SUBTYPE Integer"<<endl;
//	file2<<"  NAME Char(60)"<<endl;
//	file2<<"  x Decimal(20, 8)"<<endl;
//	file2<<"  y Decimal(20, 8)"<<endl;
//	file2<<"Data"<<endl;
//	file2<<endl;
//	
//	//��ȡ������ĸ�������������ĵ����� ׼��д�ļ�������
//	CMapXFeatures featuresGrids = m_ctrlMapX.GetLayers().Item(1).AllFeatures();
//	int gridCount = featuresGrids.GetCount();
//	CMapXFeature featureGrid;
//	double gridLongitude,gridLatitude;
//	CMapXParts  m_Feature;
//	CMapXPoints m_Points;
//	int fcount,count;
//	double pointsLongitude[5];
//	double pointsLatitude[5];
//	for(int iGrid=1;iGrid<gridCount;iGrid++)
//	{	
//		file2<<"Region  1"<<endl;
//		file2<<"  5"<<endl;
//		try 
//		{
//			//�õ����񶥵�ľ�γ��
//			featureGrid = featuresGrids.Item(iGrid);
//			gridLongitude = featureGrid.GetCenterX();
//			gridLatitude = featureGrid.GetCenterY();
//			//���뽨�����۵� 
//			m_Feature =featureGrid.GetParts();
//			fcount = m_Feature.GetCount();
//			m_Points = m_Feature.Item(1);
//			count = m_Points.GetCount();
//			for(int i=1;i<=m_Points.GetCount();i++) {
//				pointsLongitude[i-1] = m_Points.Item(i).GetX();
//				pointsLatitude[i-1] = m_Points.Item(i).GetY();
//			}
//			//��֤�պϣ�pointsLatitude�д�������еĽڵ�����
//			pointsLatitude[4] = m_Points.Item(1).GetX();
//			pointsLatitude[4] = m_Points.Item(1).GetY();
//			for(int pointId = 0;pointId<(sizeof(pointsLongitude)/sizeof(pointsLongitude[0]));pointId++) {
//				file2<<fixed<<setprecision(6)<<pointsLongitude[pointId]<<" "<<pointsLatitude[pointId]<<endl;
//			}
//			file2<<"    Pen (1,2,0) "<<endl;
//			file2<<"    Brush (2,"<<Grid::getMyself(iGrid).getGColor()<<",16777215)"<<endl;
//			file2<<"    Center ";
//			file2<<fixed<<setprecision(6)<<gridLongitude<<" "<<gridLatitude<<endl;
//		} catch (_com_error &e){
//			::MessageBox(NULL,e.Description(),_T("����"),MB_OK);
//		}
//	}
//	return true;
//}
bool MakeGridFileTool::makeGridFile(string fileNameString) {
	_ConnectionPtr sqlSp;
	DBConnect* dbconnection;
	_RecordsetPtr m_pRecordset;
	dbconnection = DBConnPool::Instanse()->GetAConnection();
	sqlSp = dbconnection->_connection_ptr;	
	if(FAILED(m_pRecordset.CreateInstance( _uuidof(Recordset)))){
		cout<<"��¼������ָ��ʵ����ʧ�ܣ�"<<endl;
		return false;
	}
	try{
		m_pRecordset->Open("SELECT * FROM  Grid",(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);
	}
	catch (_com_error &e){
		cout << e.Description()<<endl;
	}
	int Gnum=0;
	int count=0;
	//m_pRecordset->MoveFirst();
	while(!m_pRecordset->EndOfFile)
	{
		Gnum++;
		m_pRecordset->MoveNext();
	}
	m_pRecordset->Close();

	string ext;
	stringstream ss;
	double longitude;
	double latitude;
	ofstream file2(fileNameString,ios::out);
	file2<<"Version   300"<<endl;
	file2<<"Charset \"WindowsSimpChinese\""<<endl;
	file2<<"Delimiter \",\""<<endl;
	file2<<"CoordSys Earth Projection 1, 104"<<endl;
	file2<<"Columns 5"<<endl;
	file2<<"  TYPE Integer"<<endl;
	file2<<"  SUBTYPE Integer"<<endl;
	file2<<"  NAME Char(60)"<<endl;
	file2<<"  x Decimal(20, 8)"<<endl;
	file2<<"  y Decimal(20, 8)"<<endl;
	file2<<"Data"<<endl;
	file2<<endl;
	
	for(int i=0;i<Gnum;i++)
	{	
		file2<<"Region  1"<<endl;
		file2<<"  5"<<endl;
		ext.append("SELECT * FROM  Grid WHERE GId=");
		ss<<i+1;
		cout<<i+1<<endl;
		ext.append(ss.str());
		try 
		{
			m_pRecordset->Open(ext.c_str(),(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);//�����ݿ⣬ִ��SQL���
			longitude=m_pRecordset->GetCollect("GLongitude");
			latitude=m_pRecordset->GetCollect("GLatitude");
			//Ϊ�˽�������ֳ�����ͨ�����ĵ�õ�������ĸ���
			file2<<fixed<<setprecision(6)<<longitude-HALF_LONGI<<" "<<latitude+HALF_LATI<<endl;
			file2<<fixed<<setprecision(6)<<longitude-HALF_LONGI<<" "<<latitude-HALF_LATI<<endl;
			file2<<fixed<<setprecision(6)<<longitude+HALF_LONGI<<" "<<latitude-HALF_LATI<<endl;
			file2<<fixed<<setprecision(6)<<longitude+HALF_LONGI<<" "<<latitude+HALF_LATI<<endl;
			file2<<fixed<<setprecision(6)<<longitude-HALF_LONGI<<" "<<latitude+HALF_LATI<<endl;
		}
		catch (_com_error &e)
		{
			cout << e.Description()<<endl;
		}
		file2<<"    Pen (1,2,0) "<<endl;
		file2<<"    Brush (2,"<<int(m_pRecordset->GetCollect("GColor"))<<",16777215)"<<endl;
		file2<<"    Center ";
		file2<<fixed<<setprecision(6)<<longitude<<" "<<latitude<<endl;
		ss.str("");
		ss.clear();
		ext.clear();
		DBConnPool::Instanse()->CloseRecordSet(m_pRecordset);
		DBConnPool::Instanse()->RestoreAConnection(dbconnection);
	}
	return true;
}
