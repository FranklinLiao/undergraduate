#include "StdAfx.h"
#include "PutXY.h"


PutXY::PutXY(void)
{
}


PutXY::~PutXY(void)
{
}


void PutXY::ChangeToXY(void)
{
	bool flag1=true, flag2=true;
	int id=1;
	//double Unitx,Unity;
	int SwitchUnitx,SwitchUnity;
	double longitude1=0.0;
	double longitude2=0.0;
	double longitude=0.0;
	double latitude1=0.0;
	double latitude2=0.0;
	double latitude=0.0;
	_variant_t medm;

	_ConnectionPtr sqlSp;
	DBConnect* dbconnection;
	_RecordsetPtr m_pRecordset;
	_RecordsetPtr m_pRecordset1;
	_RecordsetPtr m_pRecordset2;
	_RecordsetPtr m_pRecordset3;
	dbconnection = DBConnPool::Instanse()->GetAConnection();
	sqlSp = dbconnection->_connection_ptr;
	//dbCon.getMyConnection(connection);
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	m_pRecordset1.CreateInstance(__uuidof(Recordset));
	m_pRecordset2.CreateInstance(__uuidof(Recordset));
	m_pRecordset3.CreateInstance(__uuidof(Recordset));

	try {
			m_pRecordset->Open("SELECT * FROM  BuildingPoint Order By PId",(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);//打开数据库，执行SQL语句
			m_pRecordset1->Open("SELECT * FROM  Grid Order By GId",(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);
			m_pRecordset2->Open("SELECT * FROM  Area Order By AId",(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);
			m_pRecordset3->Open("SELECT * FROM RTData Order By RId",(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic,adCmdText);
	}
	catch (_com_error &e)
		{
			cout << e.Description()<<endl;
		}
	
	medm=m_pRecordset1->GetCollect("GLongitude");
	longitude1=medm;
	medm=m_pRecordset1->GetCollect("GLatitude");
	latitude1=medm;
	//try {
	//m_pRecordset1->MoveFirst();
	//medm=m_pRecordset1->GetCollect("GLongitude");
	//longitude1=medm;
	//medm=m_pRecordset1->GetCollect("GLatitude");
	//latitude1=medm;
	//m_pRecordset1->MoveFirst();
	//while(!m_pRecordset1->EndOfFile)
	//{
	//medm=m_pRecordset1->GetCollect("GLongitude");
	//longitude=medm;
	//medm=medm=m_pRecordset1->GetCollect("GLatitude");
	//latitude=medm;
	//m_pRecordset1->PutCollect("GY",_variant_t(double(int(int(abs(latitude1-latitude)/LATITUDELENGTH+0.5)+1)*5-2.5)));
	//m_pRecordset1->PutCollect("GX",_variant_t(double(int(int(abs(longitude-longitude1)/LONGITUDELENGTH+0.5)+1)*5-2.5)));
	//cout<<id++<<endl;
	//m_pRecordset1->Update();
	//m_pRecordset1->MoveNext();
	//}
	//}
	//catch (_com_error &e)
	//{
	//cout << e.Description()<<endl;
	//}

	//try
	//{
	//m_pRecordset->MoveFirst();
	//while(!m_pRecordset->EndOfFile)
	//{
	//medm=m_pRecordset->GetCollect("PLongitude");
	//longitude=medm;
	//medm=m_pRecordset->GetCollect("PLatitude");
	//latitude=medm;
	//m_pRecordset->PutCollect("PY",_variant_t(double(abs((latitude-latitude1)*5.0/LATITUDELENGTH))+2.5));
	//m_pRecordset->PutCollect("PX",_variant_t(double(abs((longitude1-longitude)*5.0/LONGITUDELENGTH)+2.5)));
	//m_pRecordset->Update();
	//m_pRecordset->MoveNext();
	//}
	//}
	//catch (_com_error &e)
	//{
	//cout << e.Description()<<endl;
	//}
	//
	//	//latitude1 = 39.985128;
	//	//longitude1 = 116.332912;
	//	try
	//	{
	//		m_pRecordset2->MoveFirst();
	//		while(!m_pRecordset2->EndOfFile)
	//		{
	//			medm=m_pRecordset2->GetCollect("ALongitude");
	//			longitude=medm;
	//			medm=m_pRecordset2->GetCollect("ALatitude");
	//			latitude=medm;
	//			m_pRecordset2->PutCollect("AY",_variant_t(double(abs((latitude-latitude1)*5.0/LATITUDELENGTH))+2.5));
	//			m_pRecordset2->PutCollect("AX",_variant_t((absdouble((longitude1-longitude)*5.0/LONGITUDELENGTH)+2.5)));
	//			m_pRecordset2->Update();
	//			m_pRecordset2->MoveNext();
	//		}
	//	}
	//	catch (_com_error &e)
	//	{
	//		cout << e.Description()<<endl;
	//	}

		//RTdata
		/*try
		{
			m_pRecordset3->MoveFirst();
			while(!m_pRecordset3->EndOfFile)
			{
				medm=m_pRecordset3->GetCollect("RLongitude");
				longitude=medm;
				medm=m_pRecordset3->GetCollect("RLatitude");
				latitude=medm;
				m_pRecordset3->PutCollect("RY",_variant_t(double(abs((latitude-latitude1)*5.0/LATITUDELENGTH))+2.5));
				m_pRecordset3->PutCollect("RX",_variant_t(double(abs((longitude1-longitude)*5.0/LONGITUDELENGTH)+2.5)));
				m_pRecordset3->Update();
				m_pRecordset3->MoveNext();
			}
		}
		catch (_com_error &e)
		{
			cout << e.Description()<<endl;
		}*/
		//将RTData的经纬度转换为xy后，再根据XY获得对应的网格
		InsertRTGridIdTool::insertRTGridIdTool();

		/*m_pRecordset2->Close();
		m_pRecordset1->Close();
		m_pRecordset->Close();*/
		DBConnPool::Instanse()->CloseRecordSet(m_pRecordset);
		DBConnPool::Instanse()->CloseRecordSet(m_pRecordset1);
		DBConnPool::Instanse()->CloseRecordSet(m_pRecordset2);
		DBConnPool::Instanse()->CloseRecordSet(m_pRecordset3);
		DBConnPool::Instanse()->RestoreAConnection(dbconnection);
}
