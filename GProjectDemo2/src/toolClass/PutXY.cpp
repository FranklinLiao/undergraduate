#include "StdAfx.h"
#include "PutXY.h"


PutXY::PutXY(void)
{
}


PutXY::~PutXY(void)
{
}


//************************************  
// ��������: ChangeToXY     
// ����˵������Grid��Area��BuildingPoint��RT���ݵľ�γ����Ϣת��ΪXY     
// ����:Franklin     
// ���ڣ�2015/03/17     
// �� �� ֵ: void     
// ��    ��: void      
//************************************
void PutXY::ChangeToXY(void)
{
	bool flag1=true, flag2=true;
	int id=1;
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
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	m_pRecordset1.CreateInstance(__uuidof(Recordset));
	m_pRecordset2.CreateInstance(__uuidof(Recordset));
	m_pRecordset3.CreateInstance(__uuidof(Recordset));

	try {
			m_pRecordset->Open("SELECT * FROM  BuildingPoint Order By PId",(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);//�����ݿ⣬ִ��SQL���
			m_pRecordset1->Open("SELECT * FROM  Grid Order By GId",(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);
			m_pRecordset2->Open("SELECT * FROM  Area Order By AId",(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);
			m_pRecordset3->Open("SELECT * FROM RTData Order By RId",(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic,adCmdText);
	}
	catch (_com_error &e)
		{
			cout << e.Description()<<endl;
		}
	

	
	//��grid�еľ�γ��ת��Ϊ��Ӧ��XY
	try {
	m_pRecordset1->MoveFirst();
	medm=m_pRecordset1->GetCollect("GLongitude");
	longitude1=medm;
	medm=m_pRecordset1->GetCollect("GLatitude");
	latitude1=medm;
	m_pRecordset1->MoveFirst();
	while(!m_pRecordset1->EndOfFile)
	{
	medm=m_pRecordset1->GetCollect("GLongitude");
	longitude=medm;
	medm=medm=m_pRecordset1->GetCollect("GLatitude");
	latitude=medm;
	m_pRecordset1->PutCollect("GY",_variant_t(double(int(int(abs(latitude1-latitude)/LATITUDELENGTH+0.5)+1)*5-2.5)));
	m_pRecordset1->PutCollect("GX",_variant_t(double(int(int(abs(longitude-longitude1)/LONGITUDELENGTH+0.5)+1)*5-2.5)));
	cout<<id++<<endl;
	m_pRecordset1->Update();
	m_pRecordset1->MoveNext();
	}
	}
	catch (_com_error &e)
	{
	cout << e.Description()<<endl;
	}
	
	//���������۵�ľ�γ��װ��ΪXY
	try
	{
	m_pRecordset->MoveFirst();
	while(!m_pRecordset->EndOfFile)
	{
	medm=m_pRecordset->GetCollect("PLongitude");
	longitude=medm;
	medm=m_pRecordset->GetCollect("PLatitude");
	latitude=medm;
	m_pRecordset->PutCollect("PY",_variant_t(double(abs((latitude-latitude1)*5.0/LATITUDELENGTH))+2.5));
	m_pRecordset->PutCollect("PX",_variant_t(double(abs((longitude1-longitude)*5.0/LONGITUDELENGTH)+2.5)));
	m_pRecordset->Update();
	m_pRecordset->MoveNext();
	}
	}
	catch (_com_error &e)
	{
	cout << e.Description()<<endl;
	}

	//����վ�ľ�γ��ת��ΪXY
		try
		{
			m_pRecordset2->MoveFirst();
			while(!m_pRecordset2->EndOfFile)
			{
				medm=m_pRecordset2->GetCollect("ALongitude");
				longitude=medm;
				medm=m_pRecordset2->GetCollect("ALatitude");
				latitude=medm;
				m_pRecordset2->PutCollect("AY",_variant_t(double(abs((latitude-latitude1)*5.0/LATITUDELENGTH))+2.5));
				m_pRecordset2->PutCollect("AX",_variant_t(double(abs((longitude1-longitude)*5.0/LONGITUDELENGTH)+2.5)));
				m_pRecordset2->Update();
				m_pRecordset2->MoveNext();
			}
		}
		catch (_com_error &e)
		{
			cout << e.Description()<<endl;
		}
		
		//��·�����ݵľ�γ��ת��ΪXY
		try
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
		}
		
		//��RTData�ľ�γ��ת��Ϊxy���ٸ���XY��ö�Ӧ������
		InsertRTGridIdTool::insertRTGridIdTool();

		DBConnPool::Instanse()->CloseRecordSet(m_pRecordset);
		DBConnPool::Instanse()->CloseRecordSet(m_pRecordset1);
		DBConnPool::Instanse()->CloseRecordSet(m_pRecordset2);
		DBConnPool::Instanse()->CloseRecordSet(m_pRecordset3);
		DBConnPool::Instanse()->RestoreAConnection(dbconnection);
}
