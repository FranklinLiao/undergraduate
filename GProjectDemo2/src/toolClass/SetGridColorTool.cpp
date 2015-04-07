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
	_RecordsetPtr m_pRecordset; //��¼������ָ�룬����ִ��SQL��䲢��¼��ѯ���
	if(FAILED(m_pRecordset.CreateInstance( _uuidof( Recordset ))))
	{
		cout<<"��¼������ָ��ʵ����ʧ�ܣ�"<<endl;
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
	//�ҳ������С�ĳ�ǿ
	while(!m_pRecordset->EndOfFile)
	{
		//var.vt==VT_NULL || var.vt==VT_EMPTY
		//if(((m_pRecordset->GetCollect("GRealRSRP")).vt!=VT_NULL)&&((m_pRecordset->GetCollect("GRealRSRP")).vt!=VT_EMPTY)) {
		//����׼��û�еõ���ǿ���ݵ������GRealRSRP��NULL����� ����������0�����
		GStrength=double(m_pRecordset->GetCollect("GRealRSRP"));
			if(GStrength>Max&&GStrength!=0)
				Max=GStrength;
			if(GStrength<Min)
				Min=GStrength;
			m_pRecordset->MoveNext();
		//}
	}
	range=Max-Min;
	m_pRecordset->MoveFirst();
	//��ʼ���и�ֵ
	while(!m_pRecordset->EndOfFile)
	{
		//if(((m_pRecordset->GetCollect("GRealRSRP")).vt!=VT_NULL)&&((m_pRecordset->GetCollect("GRealRSRP")).vt!=VT_EMPTY)) {
			GStrength=double(m_pRecordset->GetCollect("GRealRSRP"));
			if(GStrength!=0)
			{
				m_pRecordset->PutCollect("GColor",_variant_t(int(255*256*256+int(255-(abs((GStrength-Min))/range*255))*256)));
				m_pRecordset->Update();
			}
			m_pRecordset->MoveNext();
		//}
	}
	DBConnPool::Instanse()->CloseRecordSet(m_pRecordset);
	DBConnPool::Instanse()->RestoreAConnection(dbconnection);
	return true;
}


