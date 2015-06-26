#include "StdAfx.h"
#include "Staining.h"


Staining::Staining(void)
{

}


Staining::~Staining(void)
{
}


void Staining::PutColor(void)
{
	int id=0;
	string medium;
	string med;
	_variant_t medm;


	_ConnectionPtr sqlSp;
	DBConnect* dbconnection;
	_RecordsetPtr m_pRecordset;
	_RecordsetPtr m_pRecordset1;
	dbconnection = DBConnPool::Instanse()->GetAConnection();
	sqlSp = dbconnection->_connection_ptr;
	//dbCon.getMyConnection(connection);
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	m_pRecordset1.CreateInstance(__uuidof(Recordset));

	try {
			m_pRecordset->Open("SELECT * FROM  Grid",(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);//打开数据库，执行SQL语句
			m_pRecordset1->Open("SELECT * FROM  GRID1",(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);
		}
	catch (_com_error &e)
		{
			cout << e.Description()<<endl;
		}
	try {
			m_pRecordset->MoveFirst();
			m_pRecordset1->MoveFirst();
			while(!m_pRecordset->EndOfFile&&!m_pRecordset1->EndOfFile) 
			{
				id++;
				medium="Pen (1, 2, 0) Brush (2, ";
				medm=m_pRecordset->GetCollect("GRSRP");
				med=(_bstr_t)medm;
				medium.append(med);
				medium.append(", 16777215)");
				cout<<"ID:"<<id<<" Strength:"<<medium<<" "<<endl;
				m_pRecordset1->PutCollect("MI_STYLE",_variant_t(medium.c_str()));
				m_pRecordset1->Update();
				m_pRecordset->MoveNext();
				m_pRecordset1->MoveNext();
				medium.clear();
				med.clear();
			}
		}
		catch (_com_error &e)
		{
			cout << e.Description()<<endl;
		}

}
