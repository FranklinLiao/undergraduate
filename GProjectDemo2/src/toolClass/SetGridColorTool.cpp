#include "StdAfx.h"
#include "SetGridColorTool.h"


SetGridColorTool::SetGridColorTool(void)
{
	
	FilePosition="E:\\eeeexxxxx\\docky\\Grid.MIF";
}


SetGridColorTool::~SetGridColorTool(void)
{
}



//************************************  
// 函数名称: SetColor     
// 函数说明： flag用于标识是否按场强显示 
// true:不按场强，按Grid的状态（弱覆盖、过覆盖、导频污染）  false:按场强    
// 作者:Franklin     
// 日期：2015/06/09     
// 返 回 值: bool     
// 参    数: bool flag      
//************************************
bool SetGridColorTool::SetColor(bool flag,string col)
{
	//将原来的颜色擦除  将颜色不为0的全部变成白色
	DBHelper::resetGridColor();
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
		//不处理那些相交性的网格
		m_pRecordset->Open("SELECT * FROM  Grid where GColor!=0",(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);
	}
	catch (_com_error &e)
	{
		cout << e.Description()<<endl;
	}
	if(flag) {  //falg为真  那么就为覆盖优化
		//bool
		bool status = false;
		m_pRecordset->MoveFirst();
		//开始进行赋值
		while(!m_pRecordset->EndOfFile)
		{
			//if(((m_pRecordset->GetCollect("GRealRSRP")).vt!=VT_NULL)&&((m_pRecordset->GetCollect("GRealRSRP")).vt!=VT_EMPTY)) {
			status=bool(m_pRecordset->GetCollect(col.c_str()));
			if(status) //为1  那么这个网格有问题
			{
				m_pRecordset->PutCollect("GColor",_variant_t(UNNORMALCOLOR));
				m_pRecordset->Update();
			} else {
				m_pRecordset->PutCollect("GColor",_variant_t(NORMALCOLOR));
				m_pRecordset->Update();
			}
			m_pRecordset->MoveNext();
			//}
		}
	} else {
		double GStrength;
		double Min=10000,Max=-10000;
		double range;
		//m_pRecordset->MoveFirst();
		//找出最大最小的场强
		while(!m_pRecordset->EndOfFile)
		{
			//var.vt==VT_NULL || var.vt==VT_EMPTY
			//if(((m_pRecordset->GetCollect("GRealRSRP")).vt!=VT_NULL)&&((m_pRecordset->GetCollect("GRealRSRP")).vt!=VT_EMPTY)) {
			//本来准备没有得到场强数据的网格的GRealRSRP用NULL来替代 后来决定用0来替代
			GStrength=m_pRecordset->GetCollect("GRealRSRP");

				if(GStrength>Max&&GStrength!=0)
					Max=GStrength;
				if(GStrength<Min)
					Min=GStrength;
				m_pRecordset->MoveNext();
			//}
		}
		range=Max-Min;
		m_pRecordset->MoveFirst();
		//开始进行赋值
		while(!m_pRecordset->EndOfFile)
		{
			//if(((m_pRecordset->GetCollect("GRealRSRP")).vt!=VT_NULL)&&((m_pRecordset->GetCollect("GRealRSRP")).vt!=VT_EMPTY)) {
				GStrength=double(m_pRecordset->GetCollect("GRealRSRP"));
				if(GStrength>=0.01||GStrength<=-0.01) //GStrength！=0
				{
					m_pRecordset->PutCollect("GColor",_variant_t(int(255*256*256+int(255-(abs((GStrength-Min))/range*255))*256)));
					m_pRecordset->Update();
				}
				m_pRecordset->MoveNext();
			//}
		}
	}
	DBConnPool::Instanse()->CloseRecordSet(m_pRecordset);
	DBConnPool::Instanse()->RestoreAConnection(dbconnection);
	return true;
}


