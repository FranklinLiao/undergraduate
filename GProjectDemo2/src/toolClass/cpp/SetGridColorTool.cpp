#include "StdAfx.h"
#include "SetGridColorTool.h"


SetGridColorTool::SetGridColorTool(void)
{
	
	FilePosition="E:\\eeeexxxxx\\docky\\Grid.MIF";
}


SetGridColorTool::~SetGridColorTool(void)
{
}



bool SetGridColorTool::SetColor(void)
{
	DBConnect* dbconnection;
	_ConnectionPtr  sqlSp;
	dbconnection = DBConnPool::Instanse()->GetAConnection();
	sqlSp = dbconnection->_connection_ptr;
	_RecordsetPtr m_pRecordset; //记录集对象指针，用来执行SQL语句并记录查询结果
	if(FAILED(m_pRecordset.CreateInstance( _uuidof( Recordset ))))
	{
		cout<<"记录集对象指针实例化失败！"<<endl;
		return false;
	}
	try
	{
		m_pRecordset->Open("SELECT * FROM  Grid",(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);
	}
	catch (_com_error &e)
	{
		cout << e.Description()<<endl;
	}
	double GStrength;
	double Min=10000,Max=-10000;
	double range;
	//m_pRecordset->MoveFirst();
	while(!m_pRecordset->EndOfFile)
	{
		GStrength=double(m_pRecordset->GetCollect("GRealSNR"));
		if(GStrength>Max)
			Max=GStrength;
		if(GStrength!=0&&GStrength<Min)
			Min=GStrength;
		m_pRecordset->MoveNext();
	}
	range=Max-Min;
	m_pRecordset->MoveFirst();
	while(!m_pRecordset->EndOfFile)
	{
		GStrength=double(m_pRecordset->GetCollect("GRealSNR"));
		if(GStrength!=0)
		{
			m_pRecordset->PutCollect("GColor",_variant_t(int(255*256*256+int(255-(abs((GStrength-Min))/range*255))*256)));
			m_pRecordset->Update();
		}
		m_pRecordset->MoveNext();
	}
	DBConnPool::Instanse()->CloseRecordSet(m_pRecordset);
	DBConnPool::Instanse()->RestoreAConnection(dbconnection);
	return true;
}


