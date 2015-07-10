
// GProjectDemo2View.cpp : CGProjectDemo2View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "GProjectDemo2.h"
#endif

#include "GProjectDemo2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//int* p = new int;

CMapX m_ctrlMapX;


// CGProjectDemo2View

IMPLEMENT_DYNCREATE(CGProjectDemo2View, CView)

BEGIN_MESSAGE_MAP(CGProjectDemo2View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGProjectDemo2View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_FILE_OPEN, &CGProjectDemo2View::OnFileOpen)
	ON_COMMAND(ID_BUTTON32791, &CGProjectDemo2View::OnButton32791)
	ON_COMMAND(ID_BUTTON32792, &CGProjectDemo2View::OnButton32792)
	ON_COMMAND(ID_BUTTON32793, &CGProjectDemo2View::OnButton32793)
	ON_COMMAND(ID_BUTTON32794, &CGProjectDemo2View::OnButton32794)
	ON_COMMAND(ID_BUTTON32795, &CGProjectDemo2View::OnButton32795)
	
	ON_COMMAND(ID_TESTDBCONNECTION, &CGProjectDemo2View::OnTestdbconnection)
	ON_COMMAND(ID_BINDDATA, &CGProjectDemo2View::OnBinddata)
	ON_COMMAND(ID_GRIDMAKER, &CGProjectDemo2View::OnGridmaker)
	ON_COMMAND(ID_INTERSECTION, &CGProjectDemo2View::OnIntersection)
	ON_COMMAND(ID_RECORDBUILDING, &CGProjectDemo2View::OnRecordbuilding)
	//ON_COMMAND(ID_RECORDGRID, &CGProjectDemo2View::OnRecordgrid)
	ON_COMMAND(ID_MODIFY, &CGProjectDemo2View::OnModify)
	ON_COMMAND(ID_PUTXY, &CGProjectDemo2View::OnPutxy)
	ON_COMMAND(ID_RECORDBS, &CGProjectDemo2View::OnOpenbsxls)
	ON_COMMAND(ID_RECORDRTDATA, &CGProjectDemo2View::OnRecordrtdata)
	ON_COMMAND(ID_CALCULATE, &CGProjectDemo2View::OnCalculate)
	ON_COMMAND(ID_GRIDMIF, &CGProjectDemo2View::OnGridmif)
	ON_COMMAND(ID_CHANGE, &CGProjectDemo2View::OnChange)
	ON_COMMAND(ID_OVERLAY, &CGProjectDemo2View::OnOverlay)
	ON_COMMAND(ID_WEAKLAY, &CGProjectDemo2View::OnWeaklay)
	ON_COMMAND(ID_POLLUTION, &CGProjectDemo2View::OnPollution)
	ON_COMMAND(ID_SFR, &CGProjectDemo2View::OnSfr)
	ON_COMMAND(ID_ANR, &CGProjectDemo2View::OnAnr)
	ON_COMMAND(ID_SETDB, &CGProjectDemo2View::OnSetdb)
	ON_COMMAND(ID_WEAKMODIFY, &CGProjectDemo2View::OnWeakmodify)
	ON_COMMAND(ID_OVERMODIFY, &CGProjectDemo2View::OnOvermodify)
	ON_COMMAND(ID_POLLUTIONMODIFY, &CGProjectDemo2View::OnPollutionmodify)
END_MESSAGE_MAP()

// CGProjectDemo2View 构造/析构


//************************************  
// 函数名称: OnDbSet     
// 函数说明： 用于设置Db的连接信息    
// 作者:Franklin     
// 日期：2015/06/01     
// 返 回 值: void     
//************************************
void CGProjectDemo2View::OnSetdb()
{
	// TODO: 在此添加命令处理程序代码
	//手动输入
	CSetDb m_setDb(_T("数据库设置"));
	int ret = m_setDb.DoModal();
	if(IDOK==ret) {
		m_username = m_setDb.m_username.Trim();
		m_password = m_setDb.m_passwd.Trim();
		m_dbname = m_setDb.m_dbname.Trim();
		if(m_username==""||m_password==""||m_dbname=="") {
			MessageBox(_T("数据库配置信息输入不完全，将采用默认配置"),_T("通知"),MB_OK);
		} else {
			DBConnPool::m_username = this->m_username;
			DBConnPool::m_password = this->m_password;
			DBConnPool::m_dbname = this->m_dbname;
			DBConnPool::Instanse()->SetInstanceNull(); // 重新创建DBPOOL
			MessageBox(_T("数据库配置信息输入成功"),_T("通知"),MB_OK);
		}
	} else {
		MessageBox(_T("数据库连接将使用默认配置"),_T("通知"),MB_OK);
	}
	//DBConnPool::Instanse()->SetDBInfo("127.0.0.1",m_username.c_str(),m_password.c_str(),m_dbname.c_str(),30,50);
}

CGProjectDemo2View::CGProjectDemo2View()
{
	//配置数据库，创建连接  放到了DBConnPool中
	//m_username = "sa";
	//m_password = "123456";
	//m_dbname = "LTE_OPT";
	//初始进入设定数据库连接
	//OnSetdb();
	//DBConnPool::Instanse()->SetDBInfo("127.0.0.1",m_username.c_str(),m_password.c_str(),m_dbname.c_str(),30,50);
	//DBConnPool::Instanse()->SetDBInfo("127.0.0.1","sa","123456","LteArea",30,50);
	//清空现有的数据
	//DBHelper::deleteAllTable();
}

CGProjectDemo2View::~CGProjectDemo2View()
{
}


//************************************  
// 函数名称: OnTestdbconnection     
// 函数说明： 测试数据库连接是否正常    
// 作者:Franklin     
// 日期：2015/03/24     
// 返 回 值: void     
//************************************
void CGProjectDemo2View::OnTestdbconnection()
{
	// TODO: 在此添加命令处理程序代码
	//按照传入的配置信息，进行数据库的连接，并返回结果 
	DBConnect* dbconnection;
	try {
		//返回数据
		dbconnection = DBConnPool::Instanse()->GetAConnection();
		if(dbconnection!=NULL) {
			DBConnPool::Instanse()->RestoreAConnection(dbconnection);
			MessageBox(_T("数据库连接成功"),_T("通知"),MB_OK);
		} else {
			DBConnPool::Instanse()->RestoreAConnection(dbconnection);
			MessageBox(_T("数据库连接失败"),_T("通知"),MB_OK);
		}
	} catch(_com_error e) {
		DBConnPool::Instanse()->RestoreAConnection(dbconnection);
		cout<<e.Description()<<endl;
		MessageBox(_T("数据库连接失败"),_T("通知"),MB_OK);
	}
	//此处采用默认连接数据库的配置
	/*
	_ConnectionPtr connection;
	_RecordsetPtr recordSet;
	HRESULT hr = connection.CreateInstance(__uuidof(Connection));
	recordSet.CreateInstance(__uuidof(Recordset));
	string queryString = "select * from CUT;";
	_bstr_t sqlString  = queryString.c_str();
	connection->Open("Driver=SQL Server;Server=127.0.1;DATABASE=MapData","sa","123456",adModeUnknown) ;
	if (FAILED(hr))
		return;
	recordSet->Open(sqlString,connection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);

	MessageBox(_T("数据库连接成功"),_T("数据库连接测试"),MB_OKCANCEL);
	if(recordSet->State) {
		recordSet->Close();
	}
	if(connection->State) {
		connection->Close();
	}
	*/
	//制作主题地图
	/*
	CMapXTheme thm;
	thm=m_ctrlMapX.GetDatasets().Item(1).GetThemes().Add(miThemeRanged,_T("x"),_T("value"));
	*/


	/*
	CMapXFields field;
	field.CreateDispatch(field.GetClsid());
	field.AddNumericField(_T("x"),10,0);
	field.AddNumericField(_T("y"),10,0);
	CString name[2]={_T("x"),_T("y")};
	
	VARIANT vFlds;
	vFlds.vt = VT_DISPATCH;
	vFlds.pdispVal = field.m_lpDispatch;
	*/
	
	//thm=m_ctrlMapX.GetDatasets().Item(1).GetThemes().Add(miThemeRanged,_T("y"),_T("value2"));
	
	/*
	CMapXFeatures features;
	CMapXFeature feature;
	feature.set
	*/
	//尝试实现数据绑定  用途：用来将场强数据绑定到各个网格中
	//现在尝试实现的是  将自己手动生成的数据绑定到建筑物中
	/*
	CMapXDatasets m_Datasets = m_ctrlMapX.GetDatasets();
	CMapXFields m_Fields;
	m_Fields.Add(2,_T("BuildingValue"),miAggregationAuto);
	DataBase database;
	string sqlString = "select * from BuildingBindTest;";
	*/
}

BOOL CGProjectDemo2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	return CView::PreCreateWindow(cs);
}

// CGProjectDemo2View 绘制

void CGProjectDemo2View::OnDraw(CDC* /*pDC*/)
{
	CGProjectDemo2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}



void CGProjectDemo2View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGProjectDemo2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CGProjectDemo2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CGProjectDemo2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CGProjectDemo2View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CGProjectDemo2View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CGProjectDemo2View 诊断

#ifdef _DEBUG
void CGProjectDemo2View::AssertValid() const
{
	CView::AssertValid();
}

void CGProjectDemo2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGProjectDemo2Doc* CGProjectDemo2View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGProjectDemo2Doc)));
	return (CGProjectDemo2Doc*)m_pDocument;
}
#endif //_DEBUG




int CGProjectDemo2View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	CString strLic = "uQnZi2sFw22L0-MRa8pYX-5E6P0001-6N1M5491-2C935277-58254-34356-52488";
	BSTR bstrLic = strLic.AllocSysString();
	BOOL bSucceed = m_ctrlMapX.Create(NULL, WS_VISIBLE, CRect(0,0,100,100),this,IDC_MAP, NULL, FALSE, bstrLic);
	if(!bSucceed) {
		return -1;
	}
	::SysFreeString(bstrLic);
	//if(!m_ctrlMapX.Create(NULL,WS_VISIBLE,CRect(0,0,100,100),this,IDC_MAP))
	//	return -1;
	m_ctrlMapX.GetLayers().RemoveAll();
	m_ctrlMapX.SetTitleText(_T(""));
	m_ctrlMapX.SetMousewheelSupport(miFullMousewheelSupport);
	/*m_ctrlMapX.SetCenterX(116.36652);
	m_ctrlMapX.SetCenterY(39.88292);
	m_ctrlMapX.SetZoom(0.1);*/
	return 0;
}


void CGProjectDemo2View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	if(cx!=0&&cy!=0)
	{
		m_ctrlMapX.MoveWindow(0,0,cx,cy,TRUE);
	}
	// TODO: 在此处添加消息处理程序代码
}

void CGProjectDemo2View::OnFileOpen()
{
	// TODO: 在此添加命令处理程序代码
	
	CString OpenFilter = _T("地图文件(*.tab)|*.tab;*.TAB|所有文件(*.*)|*.*||");
	CFileDialog FileDlgOpen(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, OpenFilter);
	if(IDOK == FileDlgOpen.DoModal())
	{
		try {
			CString FileName = FileDlgOpen.GetPathName();
			CString FilePartName = FileDlgOpen.GetFileTitle();
			m_ctrlMapX.GetLayers().Add(FileName);
			//将layer绑定到dataset中
			VARIANT vtLayer;
			vtLayer.vt=VT_DISPATCH;
			vtLayer.pdispVal=m_ctrlMapX.GetLayers().Item(m_ctrlMapX.GetLayers().GetCount()).m_lpDispatch;
			m_ctrlMapX.GetDatasets().Add(miDataSetLayer,vtLayer,FilePartName);
			double X,Y;
			m_ctrlMapX.SetBounds(m_ctrlMapX.GetLayers().GetBounds());
			/*m_ctrlMapX.SetCenterX(116.36652);
			m_ctrlMapX.SetCenterY(39.88292);
			m_ctrlMapX.SetZoom(0.1);*/

		//尝试是否已经包含了建筑物数据   结论：可以从mapx中直接取出数据！！  不用手动的提取.mif文件
		
			CMapXFeatures m_Features = m_ctrlMapX.GetLayers().Item(m_ctrlMapX.GetLayers().GetCount()).AllFeatures();
			
			for(int m = 1;m<=m_Features.GetCount();m++) {
				CMapXParts  m_Feature = m_Features.Item(m).GetParts();
				CMapXPoints m_Points = m_Feature.Item(1);
				int count = m_Points.GetCount();
				double x1 = m_Points.Item(1).GetX();
				double y1 = m_Points.Item(1).GetY();
				double x2 = m_Points.Item(m_Points.GetCount()).GetX();
				double y2 = m_Points.Item(m_Points.GetCount()).GetY();
				int freaturesCount = m_Features.GetCount();
			}
			
			//X = m_ctrlMapX.GetLayers().Item(1).AllFeatures().Item(1).GetCenterX();
		} catch(COleDispatchException* e) {
			e->ReportError();
			e->Delete();
		} catch(COleException* e) {
			e->ReportError();
			e->Delete();
		}
		
		
		                                                                                                                                  
	}
}


void CGProjectDemo2View::OnButton32791()
{
	// TODO: 在此添加命令处理程序代码
	m_ctrlMapX.SetCurrentTool(miZoomInTool);
}


void CGProjectDemo2View::OnButton32792()
{
	// TODO: 在此添加命令处理程序代码
	m_ctrlMapX.SetCurrentTool(miZoomOutTool);
}


void CGProjectDemo2View::OnButton32793()
{
	// TODO: 在此添加命令处理程序代码
	m_ctrlMapX.SetCurrentTool(miPanTool);
}


void CGProjectDemo2View::OnButton32794()
{
	// TODO: 在此添加命令处理程序代码
	m_ctrlMapX.SetCurrentTool(miArrowTool);
}


void CGProjectDemo2View::OnButton32795()
{
	// TODO: 在此添加命令处理程序代码
	m_ctrlMapX.GetLayers().LayersDlg();
}






//************************************  
// 函数名称: OnBinddata     
// 函数说明： 数据绑定  但是没成功  所以放弃了    
// 作者:Franklin     
// 日期：2015/03/24     
// 返 回 值: void     
//************************************
void CGProjectDemo2View::OnBinddata()
{
	//进行文本绑定~
	// TODO: 在此添加命令处理程序代码
	/*
	HGLOBAL hGlobalData = NULL;
	char* psz = NULL;
	CString OpenFilter = _T("场强文件(*.txt)|*.txt;*.TXT|所有文件(*.*)|*.*||");
	CFileDialog FileDlgOpen(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, OpenFilter);
	if(IDCANCEL == FileDlgOpen.DoModal()) {
		return;
	}
	CFile fileData(FileDlgOpen.GetPathName(),CFile::modeRead);
	CString strBuffer;
	fileData.Read(strBuffer.GetBuffer(fileData.GetLength()+1),fileData.GetLength());
	strBuffer.ReleaseBuffer(fileData.GetLength()+1);
	fileData.Close();
	hGlobalData=GlobalAlloc(GMEM_MOVEABLE,strBuffer.GetLength()+1);
	psz = (char*) GlobalLock(hGlobalData);

	char* pbuf=NULL;
	int iNum=0;
	iNum=strBuffer.GetLength();
	pbuf=new char[iNum+1];
	memset(pbuf,0,iNum+1);
	memcpy(pbuf,strBuffer.GetBuffer(iNum),iNum);
	const char* p=pbuf;
	strcpy(psz,p);
	//strcpy(psz,strBuffer.GetBuffer(sizeof(strBuffer)));
	GlobalUnlock(hGlobalData);

	short type;
	VARIANT sourceData;
	VARIANT name;
	VARIANT secondaryGeoField;
	VARIANT bindLayerName;
	VARIANT fields;
	CString strname("TestData");
	secondaryGeoField.vt=VT_ERROR;
	secondaryGeoField.scode=DISP_E_PARAMNOTFOUND;

	//bindLayerName.vt = VT_BSTR;
	//bindLayerName.bstrVal=_T("cut");
	bindLayerName.vt = VT_ERROR;
	bindLayerName.scode=DISP_E_PARAMNOTFOUND;

	fields.vt=VT_ERROR;
	fields.scode=DISP_E_PARAMNOTFOUND;

	
	CMapXFields flds;
	flds.CreateDispatch(flds.GetClsid());
	flds.Add(_T("x"),_T("x"),5);
	flds.Add(_T("y"),_T("y"),5);
	                
	name.vt=VT_BSTR;
	name.bstrVal=strname.AllocSysString();

	type=miDataSetGlobalHandle;
	sourceData.vt=VT_I4;
	sourceData.iVal=(long) hGlobalData;

	try {
		CMapXDataset ds = m_ctrlMapX.GetDatasets().Add(type,sourceData,name,COleVariant(1L),secondaryGeoField,
			bindLayerName,fields,COptionalVariant());
		int count = ds.GetRowCount();
		//CMapXFields m_Fields = ds.GetFields();
		//double value = m_Fields.Item(1).GetWidth();
	} catch(COleDispatchException* e) {
		e->ReportError();
		e->Delete();
	}
	*/

	//ADO绑定
	/*
	try {
		short type=miDataSetODBC;
		VARIANT sourceData;

		VARIANT name;
		CString strname("BindData");
		name.vt=VT_BSTR;
		name.bstrVal=strname.AllocSysString();

		VARIANT firstGeoField;
		VARIANT secondaryGeoField;
		VARIANT bindLayerName;
		VARIANT fields;

		CMapXDataset ds = m_ctrlMapX.GetDatasets().Add(type,sourceData,name,COleVariant(1L),secondaryGeoField,
			bindLayerName,fields,COptionalVariant());
	} catch(COleDispatchException* e) {
		e->ReportError();
		e->Delete();
	}
	*/
	//数据绑定
	// layer.add 绑定   ODBC
	/*
	VARIANT sourceData,name,geoField,secondGeoField,bindLayerName,fields,dynamicState;
	short type = miDataSetODBC;

	name.vt = VT_BSTR;
	name.bstrVal=_T("BindData");

	CMapXODBCQueryInfo queryInfo; //此处需要对modbcdataset.dll(在mapx的安装目录下）进行注册   regsvr32  modbcdataset.dll(在该dll所在目录下)
	queryInfo.SetConnectString(_T("ODBC;user=sa,pwd=123456;DLG=2"));
	//queryInfo.SetDataSource(_T("SQL SERVER")); //DBMS:Microsoft SQL Server Database:MapData 
	queryInfo.SetSqlQuery(_T("select * from Grid;"));
	sourceData.pdispVal=queryInfo.m_lpDispatch; //

	geoField.vt=VT_BSTR;
	geoField.bstrVal=_T("GLongitude");
	secondGeoField.vt=VT_BSTR;
	secondGeoField.bstrVal=_T("GLatitude");
	
	
	CMapXFields flds;
	flds.CreateDispatch(flds.GetClsid());
	flds.Add(_T("GLongitude"),_T("GLongitude"),miAggregationAuto);
	flds.Add(_T("GLatitude"),_T("GLatitude"),miAggregationAuto);
	flds.Add(_T("GRealSNR"),_T("BindData"),miAggregationAuto);
	fields.pdispVal=flds.m_lpDispatch;
	/*
	/*
	flds.AddIntegerField(_T("GId"),FALSE);
	flds.AddNumericField(_T("GLongitude"),9,6);
	flds.AddNumericField(_T("GLatitude"),9,6);
	flds.AddNumericField(_T("GRealSNR"),6,3); //GRealSNR中存放校正过后的，每个网格中对应的信噪比
	fields.pdispVal=flds.m_lpDispatch;
	*/

	//包含全部的字段 
	//fields.vt = VT_ERROR;
	//fields.scode = DISP_E_PARAMNOTFOUND;

	//此处仍然存在的问题是，如何将对应的数据绑定到对应的图元上？？？？？？

	/*
	bindLayerName.vt=VT_BSTR;
	bindLayerName.bstrVal=_T("gridMaker");

	dynamicState.vt = VT_BOOL;
	dynamicState.boolVal=false;
	//OBJECT.Add( Type, SourceData, [Name], [Geofield], [SecondaryGeofield], [BindLayer], [Fields], [Dynamic] )
	m_ctrlMapX.GetDatasets().Add(type,sourceData,name,geoField,secondGeoField,bindLayerName,fields,dynamicState);
	*/
	/*
	CMapXTheme thm;
	thm=m_ctrlMapX.GetDatasets().Item(_T("gridMaker")).GetThemes().Add(miThemeRanged,_T("x"),_T("value"));
	*/
    
	


	//LayerInfo 
	/*
	CMapXLayerInfo m_mapxLayerInfo;
	if(!m_mapxLayerInfo.CreateDispatch(m_mapxLayerInfo.GetClsid())) {
		TRACE0("Failed To Create LayerInfo");
		return;
	}
	try {
	
		m_mapxLayerInfo.SetType(miLayerInfoTypeServer);	

		VARIANT sVt;
		sVt.vt = VT_BSTR;
		CString strName;
		strName = "LayerName";
		sVt.bstrVal=strName.AllocSysString();
		//添加NAME参数
		m_mapxLayerInfo.AddParameter(_T("Name"),sVt);
		CString strConnect;
		//strConnect = "DRIVER={SQL SERVER};SERVER=LITIANJIE-PC;UID=sa;PWD=123456;Database=MapData";
		strConnect = "DRIVER={SQL SERVER};SERVER=LITIANJIE-PC;UID=sa;PWD=123456;Database=MapData";
		sVt.bstrVal = strConnect.AllocSysString();
		m_mapxLayerInfo.AddParameter(_T("ConnectString"),sVt);
		CString strQuery;
		strQuery = "select * from BuildingBindTest;";
		sVt.bstrVal=strQuery.AllocSysString();
		m_mapxLayerInfo.AddParameter(_T("query"),sVt);
		CString strToolKit;
		strToolKit="ODBC";
		sVt.bstrVal=strToolKit.AllocSysString();
		m_mapxLayerInfo.AddParameter(_T("toolkit"),sVt);
		COleVariant cache(_T("ON")),mbrsearch(_T("ON"));
		//cache="OFF";
		//mbrsearch="ON";
		m_mapxLayerInfo.AddParameter(_T("cache"),cache);
		m_mapxLayerInfo.AddParameter(_T("mbrsearch"),mbrsearch);
		
		int k = 1;
		sVt.vt = VT_I4;
		sVt.iVal = k;
		//m_mapxLayerInfo.AddParameter(_T("AutoCreateDataset"),sVt);
		
		m_ctrlMapX.GetLayers().Add(m_mapxLayerInfo);
		m_ctrlMapX.Refresh();
	} catch(COleException *e) {
		e->ReportError();
		e->Delete();
	} 
	*/
/*
	DataBase db;
	string sqlString = "select * from Grid;";
	
	_RecordsetPtr  rs = db.getObjectInfoRecordset(sqlString);
	//填写绑定的数据来源
	m_ctrlMapX.GetDatasets().Add(miDataSetADO,rs->,_T("BindData"),0);
	*/
	

	//尝试不使用数据绑定，直接往features中添加fields
	//失败，看到的都是采用添加新的layinfo来创建一个新图层；而实际中需要的是在gridmaker图层中
	//给grid添加字段，这样将gridmaker的场强数据取出来后可以直接画专题图！！！！
	
}


//************************************  
// 函数名称: OnGridmaker     
// 函数说明：生成网格 将数据插入到数据库中去     
// 作者:Franklin     
// 日期：2015/03/20     
// 返 回 值: void     
//************************************
void CGProjectDemo2View::OnGridmaker() 
{
	/*
	process = new MyProcess();
	process->Create(IDD_PROCESS,this);
	process->MyProcessInfo="请稍后，程序正在运行中...";
	process->UpdateData(FALSE);
	process->ShowWindow(SW_SHOW);
	process->RedrawWindow();
	*/
	//create process
	openProcess();

	MakeGrid::makeGrid();

	//close process
	closeProcess();
	/*
	process->DestroyWindow();
	delete process;
	process = NULL;
	*/
	MessageBox(_T("地图网格化成功"),_T("通知"),MB_OK);
}

//
//void CGProjectDemo2View::createGridMapPoints(double minLongitude,double maxLongtitude,double minLatitude,double maxLatitude) {
//	CMapXLayer lyr = m_ctrlMapX.GetLayers().CreateLayer(_T("gridMaker"),_T("E:\\Franklin\\program\\mapinfo\\mapx\\Maps\\Test_Map\\gridMaker.tab"));
//	
//	//为了避免有的建筑物不在网格中，将经纬度分别给0.001的余地
//	double redundency=0.001;
//	minLongitude-=redundency;
//	minLatitude-=redundency;
//	maxLongtitude+=redundency;
//	maxLatitude+=redundency;
//	//经度增大，维度减小
//	CGProjectDemo2View cView;
//	CMapXPoints points;
//
//	lyr.AddFeature(cView.createGridPoints(minLongitude,maxLatitude));
//	lyr.Refresh();
//	long count = lyr.AllFeatures().GetCount();
//}
//
//CMapXFeature  CGProjectDemo2View::createGridPoints(double longitude,double latitude) {
//	double x1=longitude;
//	double y1 = latitude;
//	double x2 = longitude+longilength;
//	double y2 = latitude-latilength;
//	CMapXFeatureFactory featureFactory = m_ctrlMapX.GetFeatureFactory();
//	CMapXPoints points;
//	points.CreateDispatch(points.GetClsid());
//	CMapXPoint point;
//	point.CreateDispatch(point.GetClsid());
//	point.Set(x1,y1);
//	points.Add(point);
//	point.Set(x2,y1);
//	points.Add(point);
//	point.Set(x2,y2);
//	points.Add(point);
//	point.Set(x1,y2);
//	points.Add(point);
//	
//	VARIANT variantPoints;
//	variantPoints.vt=VT_DISPATCH;
//	variantPoints.pdispVal=points.m_lpDispatch;
//	variantPoints.pdispVal->AddRef();
//	
//	CMapXStyle sty;
//	sty.CreateDispatch(sty.GetClsid());
//	sty.SetRegionBorderWidth(1);
//	sty.SetRegionBorderColor(miColorBlack);
//	sty.SetRegionPattern(miPatternNoFill);
//	sty.SetRegionTransparent(1);
//	VARIANT variantSty;
//	variantSty.vt=VT_DISPATCH;
//	variantSty.pdispVal=sty.m_lpDispatch;
//	variantSty.pdispVal->AddRef();
//	CMapXFeature featureRegion=featureFactory.CreateRegion(variantPoints,variantSty);
//	return featureRegion;
//}

//************************************  
// 函数名称: OnIntersection     
// 函数说明： 录入建筑物折点和网格的相交性信息    
// 作者:Franklin     
// 日期：2015/03/24     
// 返 回 值: void     
//************************************
void CGProjectDemo2View::OnIntersection()
{
	//create process
	/*
	process = new MyProcess();
	process->Create(IDD_PROCESS,this);
	process->MyProcessInfo="请稍后，程序正在运行中...";
	process->UpdateData(FALSE);
	process->ShowWindow(SW_SHOW);
	process->RedrawWindow();
	*/
	openProcess();
	RecordGridBuildingIntersectionTool::recordGridBuildingIntersectionTool();
	//基站和网格的关系是得按照SNR计算得出
	//RecordAreaGridIntersectionTool::recordAreaGridIntersectionTool();
	//建筑物和Area的关系不需要计算出来使用

	GridBSDistanceCal::updateDistance();
	GridBSDistanceCal::updateGridAidRsrp();

	//close process
	/*
	process->DestroyWindow();
	delete process;
	process = NULL;
	*/
	closeProcess();
	MessageBox(_T("相交信息已经录入成功"),_T("通知"),MB_OK);
}


//************************************  
// 函数名称: OnRecordbuilding     
// 函数说明： 录入建筑物数据     
// 作者:Franklin     
// 日期：2015/03/24     
// 返 回 值: void     
//************************************
void CGProjectDemo2View::OnRecordbuilding()
{
	// TODO: 在此添加命令处理程序代码
	/*
	//暂时先采用读取.mif，后期可以尝试使用mapx读取该图层，取出数据放入到数据库中
	CString pathName;
	CString fileName;

	TCHAR szFilters[]= _T("MIF Files (*.mif)|*.mif|All Files (*.*)|*.*||");

	// Create an Open dialog; the default file name extension is ".my".
	CFileDialog fileDlg(TRUE, _T("mif"), _T("*.mif"),
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);
	if(fileDlg.DoModal() == IDOK)
	{
		pathName = fileDlg.GetPathName();

		// Implement opening and reading file in here.

		//Change the window's title to the opened file's title.
		fileName = fileDlg.GetFileTitle();

		RecordBuildingPointTool RBP;
		RBP.FilePosition=pathName;
		if(RBP.RecordBuildingLayerInfoToDB()==true)
			::MessageBox(NULL,_T("，录入成功！"),_T("成功"),MB_OK);
	}
	*/
	//create process
	/*
	process = new MyProcess();
	process->Create(IDD_PROCESS,this);
	process->MyProcessInfo="请稍后，程序正在运行中...";
	process->UpdateData(FALSE);
	process->ShowWindow(SW_SHOW);
	process->RedrawWindow();
	*/
	openProcess();
	RecordBuildingPointTool RBP;
	RBP.RecordBuildingLayerInfoToDB();

	//close process
	/*
	process->DestroyWindow();
	delete process;
	process = NULL;
	*/
	closeProcess();
	::MessageBox(NULL,_T("建筑物信息录入成功！"),_T("通知"),MB_OK);
}


//************************************  
// 函数名称: OnRecordgrid     
// 函数说明： 这个方法没有使用  因为太慢了  用makegrid替代了    
// 作者:Franklin     
// 日期：2015/03/24     
// 返 回 值: void     
//************************************
void CGProjectDemo2View::OnRecordgrid()
{/*
	if(RecordGridInfoTool::recordGridInfoToDB()==true) {
		::MessageBox(NULL,_T("，网格信息录入成功!"),_T("录入信息提示"),MB_OK);
	}*/
}


//************************************  
// 函数名称: OnOpenbsxls     
// 函数说明： 录入基站数据 （以网格的范围做了限定）    
// 作者:Franklin     
// 日期：2015/03/24     
// 返 回 值: void     
//************************************
void CGProjectDemo2View::OnOpenbsxls()
{
	//int* p = new int;
	// TODO: 在此添加命令处理程序代码
	//"路测文件(*.xls,*.xlsx)|*.xls;*.XLS;*.xlsx;*.XLSX|所有文件(*.*)|*.*||"
	CString OpenFilter = _T("基站文件(*.xls,*.xlsx)|*.xls;*.XLS;*.xlsx;*.XLSX|所有文件(*.*)|*.*||");
	CFileDialog FileDlgOpen(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, OpenFilter);
	if(IDOK == FileDlgOpen.DoModal())
	{
		CString FileName = FileDlgOpen.GetPathName();
		CString FilePartName = FileDlgOpen.GetFileTitle();
		//清除掉原有的数据库信息

		//create process
		/*
		process = new MyProcess();
		process->Create(IDD_PROCESS,this);
		process->MyProcessInfo="请稍后，程序正在运行中...";
		process->UpdateData(FALSE);
		process->ShowWindow(SW_SHOW);
		process->RedrawWindow();
		*/
		openProcess();
		bool flag = RecordAreaInfoTool::insertAreaInfo(FileName);

		//close process
		/*
		process->DestroyWindow();
		delete process;
		process = NULL;
		*/
		closeProcess();
		if(flag) {
			MessageBox(_T("基站数据录入成功!"),_T("通知"),MB_OK);
		} else {
			MessageBox(_T("基站数据录入失败!"),_T("通知"),MB_OK);
		}
	}
}


//************************************  
// 函数名称: OnModify     
// 函数说明：该方法暂时没用  当时是准备校正路测数据的    
// 作者:Franklin     
// 日期：2015/03/24     
// 返 回 值: void     
//************************************
void CGProjectDemo2View::OnModify()
{
	// TODO: 在此添加命令处理程序代码
/*
	double raw[5]={1.2,1.3,1.5,1.4,1.7};
	double rawPart[2]={1.2,1.4};
	double lt[2]={1.3,1.6};
	double final[5];
	vector<double> finalVector=ModifyLTTool::getArrayModifyData(raw,ARRAYSIZE(raw),rawPart,ARRAYSIZE(rawPart),lt,ARRAYSIZE(lt));
	cout<<"haha"<<endl;
	*/
//	ModifyLTTool::modiyData();
	MessageBox(_T("数据校正模块成功!"),_T("通知"),MB_OK);
}


//************************************  
// 函数名称: OnPutxy     
// 函数说明： 放置XY，已经把路测数据所属的网格也添加了     
// 作者:Franklin     
// 日期：2015/03/24     
// 返 回 值: void     
//************************************
void CGProjectDemo2View::OnPutxy()
{
	// TODO: 在此添加命令处理程序代码
	//create process
	/*
	process = new MyProcess();
	process->Create(IDD_PROCESS,this);
	process->MyProcessInfo="请稍后，程序正在运行中...";
	process->UpdateData(FALSE);
	process->ShowWindow(SW_SHOW);
	process->RedrawWindow();
	*/
	openProcess();
	PutXY::ChangeToXY();
	
	//close process
	/*
	process->DestroyWindow();
	delete process;
	process = NULL;
	*/
	closeProcess();
	//把对Grid判定属于哪个Aid的操作放在了设置完X-Y后

	MessageBox(_T("经纬度-XY转换成功!"),_T("通知"),MB_OK);
}




//************************************  
// 函数名称: OnRecordrtdata     
// 函数说明： 用来录入路测数据 （以地图网格范围做了限制）     
// 作者:Franklin     
// 日期：2015/03/24     
// 返 回 值: void     
//************************************
void CGProjectDemo2View::OnRecordrtdata()
{
	/*
	// TODO: 在此添加命令处理程序代码
	CString OpenFilter = _T("路测文件(*.xls,*.xlsx)|*.xls;*.XLS;*.xlsx;*.XLSX|所有文件(*.*)|*.*||");
	CFileDialog FileDlgOpen(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, OpenFilter);
	if(IDOK == FileDlgOpen.DoModal())
	{
		CString FileName = FileDlgOpen.GetPathName();
		CString FilePartName = FileDlgOpen.GetFileTitle();
		//清除掉原有的数据库信息
		bool flag = RecordRTData::recordRTData(FileName);
		if(flag) {
			MessageBox(_T("路测数据录入成功!"),_T("通知"),MB_OK);
		} else {
			MessageBox(_T("路测数据录入失败!"),_T("通知"),MB_OK);
		}
	}
	*/
}


//************************************  
// 函数名称: OnCalculate     
// 函数说明： 用来计算场强的   但是未和张喆确定是否正确！！ 
// 作者:zhangzhe     
// 日期：2015/03/24     
// 返 回 值: void     
//************************************
void CGProjectDemo2View::OnCalculate()
{
	// TODO: 在此添加命令处理程序代码
	//调用张喆的模块，进行场强的计算
	//GetStrongestStrength::getStrongestStrength();
	//MessageBox(_T("，场强计算成功!"),_T("通知"),MB_OK);
}


//************************************  
// 函数名称: OnGridmif     
// 函数说明： 将场强值转化为对应的颜色，并生成对应的场强值mif文件     
// 作者:Franklin     
// 日期：2015/03/24     
// 返 回 值: void     
//************************************
void CGProjectDemo2View::OnGridmif()
{
	/*
	// TODO: 在此添加命令处理程序代码
	CString OpenFilter = _T("网格文件(*.tab)|*.tab;*.TAB|所有文件(*.*)|*.*||");
	CFileDialog FileDlgOpen(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, OpenFilter);
	if(IDOK == FileDlgOpen.DoModal())
	{
		CString FileName = FileDlgOpen.GetPathName();
		string fileNameString = FileName.GetBuffer(0);
		fileNameString.append(".mif"); 
		//将场强值和颜色进行对应的改变

		//中期数据展示，注释了下面一行
		SetGridColorTool::SetColor(FALSE,"");
		MessageBox(_T("颜色信息转换成功!"),_T("通知"),MB_OK);
		//从数据库中取出网格的颜色信息进行展示
		MakeGridFileTool::makeGridFile(fileNameString);

		//在后面加上mif2tab
		Mif2Tab mif2Tab;
		CString path = FileDlgOpen.GetFolderPath();
		mif2Tab.Convert0(path,path);
		//删除目录中的.mif .mid
		//string cmdLine = "cd " + path;
		//system(cmdLine.c_str());
		//cmdLine = "del *.mif *.mid";
		//system(cmdLine.c_str());
		MessageBox(_T("生成网格TAB文件成功!"),_T("通知"),MB_OK);
	}
	*/
}


//************************************  
// 函数名称: OnChange     
// 函数说明： 未找到对应的按钮 应该是用来做测试的 现在没用了    
// 作者:Franklin     
// 日期：2015/03/24     
// 返 回 值: void     
//************************************
void CGProjectDemo2View::OnChange()
{
	// TODO: 在此添加命令处理程序代码
	clock_t startTime = GetTickCount();
	//GridBSDistanceCal::updateDistance();
	clock_t endTime = GetTickCount();
	DWORD lastTime = endTime-startTime;
	cout<<lastTime;
	MessageBox(_T("计算完成"),_T("通知"),MB_OK);

}


//************************************  
// 函数名称: OnOverlay     
// 函数说明：过覆盖优化    
// 作者:     
// 日期：2015/03/17     
// 返 回 值: void     
//************************************
void CGProjectDemo2View::OnOverlay()
{
	// TODO: 在此添加命令处理程序代码

	//create process
	openProcess();

	long Gid;
	long Aid;
	long maxid,maxgid,maxaid,minaid;
	
	//DBHelper::clearOneCol("Grid","GOverLay");
	//DBHelper::clearOneCol("Area","AOverLay");
	
	//获取gid的范围
	string maxGid = WeakLay::Max("Grid","GId");
	DataBase Maxgid;
	maxgid = Maxgid.MaxId(maxGid);

	//获取aid的范围
	string minAid = WeakLay::Min("Area","AId");
	string maxAid = WeakLay::Max("Area","AId");
	DataBase Minaid,Maxaid;
	minaid = Minaid.MinId(minAid);
	maxaid = Maxaid.MaxId(maxAid);
	/*
	//更新goverlay
	for(long gid = 1;gid<=maxgid;gid++){
		//long gid = 35;
		string ojudge = OverLay::ojudge(gid);
		DataBase oj;
		oj.updateInfo(ojudge);
	}
	
	//更新aoverlay
	string ajudge = OverLay::ajudge(minaid,maxaid,0.1);
	DataBase aj;
	aj.updateInfo(ajudge);
	*/
	//close process
	closeProcess();

	MessageBox(_T("过覆盖判断成功!"),_T("通知"),MB_OK);
	ShowGridArea showGridArea;
	showGridArea.showGridArea("GOverLay","选择过覆盖判断结果存储位置");
	string overArea = OverLay::showArea();
	if(overArea.length()<1) {
		showGridArea.showAreaMb("No OverLayCell","");
	} else {
		showGridArea.showAreaMb("OverLayCell:",overArea);
	}
}


//************************************  
// 函数名称: OnWeaklay     
// 函数说明： 弱覆盖     要先执行 ，将一些距离计算出来  再进行过覆盖判断
// 作者:     
// 日期：2015/03/24     
// 返 回 值: void     
//************************************
void CGProjectDemo2View::OnWeaklay()
{
	// TODO: 在此添加命令处理程序代码
	//create process
	openProcess();
	
	DBHelper::clearOneCol("Grid","GWeakLay");
	DBHelper::clearOneCol("Area","AWeakLay");
	
	long Gid;
	long Aid;
	long maxid,maxgid,maxaid,minaid;
	//获取gid的范围
	string maxGid = WeakLay::Max("Grid","GId");
	DataBase Maxgid;
	maxgid = Maxgid.MaxId(maxGid);
	//获取aid的范围
	string minAid = WeakLay::Min("Area","AId");
	string maxAid = WeakLay::Max("Area","AId");
	DataBase Minaid,Maxaid;
	minaid = Minaid.MinId(minAid);
	maxaid = Maxaid.MaxId(maxAid);
	
	//更新GWeakLay  根据给定的阈值，判断在此阈值下，grid是否处于弱覆盖
	for(long gid = 1;gid<=maxgid;gid++){
		//long gid = 35;
		string wjudge = WeakLay::WJudge(gid,-105); //>-105
		DataBase wj;
		wj.updateInfo(wjudge);
	}
	//对于网格中没有计算到场强值的网格，将他们判定为弱覆盖网格
	//修改  2015.7.2  有的网格没有场强值是正常的，因为是相交的网格  所以不计算
	//但是有的网格没有相交，也没有场强值，因此需要判定为弱覆盖
	//目前未使用
	//DBHelper::setWeakLay();  
	
	//更新AWeaklay 通过比例，判断area是否是弱覆盖的区域
	string ajudge = WeakLay::AJudge(minaid,maxaid,0.1); //90%的区域
	DataBase aj;
	aj.updateInfo(ajudge);
	
	//close process
	closeProcess();

	MessageBox(_T("弱覆盖判断成功!"),_T("通知"),MB_OK);

	
	//上面完成了弱覆盖的判断，下面用于显示弱覆盖的区域和弱覆盖的小区
	//生成弱覆盖区域的tab
	ShowGridArea showGridArea;
	showGridArea.showGridArea("GWeakLay","选择弱覆盖判断结果存储位置");
	string weakArea = WeakLay::showArea();
	if(weakArea.length()<1) {
		showGridArea.showAreaMb("No WeayLayCell","");
	} else {
		showGridArea.showAreaMb("WeakLayCell:",weakArea);
	}
	
}

//************************************  
// 函数名称: OnPollution     
// 函数说明： 导频污染    
// 作者:     
// 日期：2015/03/24     
// 返 回 值: void     
//************************************
void CGProjectDemo2View::OnPollution()
{
	//create process
	openProcess();

	long gid;
	long maxgid;
	long minaid;
	long maxaid;

	//DBHelper::clearOneCol("Grid","GPollution");
	//DBHelper::clearOneCol("Area","APollution");
	//获取gid的范围
	string maxGid = WeakLay::Max("Grid","GId");
	DataBase Maxgid;
	maxgid = Maxgid.MaxId(maxGid);

	//获取aid的范围
	string minAid = WeakLay::Min("Area","AId");
	string maxAid = WeakLay::Max("Area","AId");
	DataBase Minaid,Maxaid;
	minaid = Minaid.MinId(minAid);
	maxaid = Maxaid.MaxId(maxAid);
	/*
	for (long gid = 1;gid<=maxgid;gid++){
		if (gid == 175){
			int kk = 1;
		}
		string pj = pollution::PJudge( gid , 2 ,-100 ,6 );  //4  -95  6
		DataBase db;
		db.updateInfo(pj);	
	}

	string ajudge = pollution::APJudge(0.1,minaid,maxaid); //0.1
	DataBase aj;
	aj.updateInfo(ajudge);
	*/
	//close process
	closeProcess();

	MessageBox(_T("导频污染判断成功!"),_T("通知"),MB_OK);
	ShowGridArea showGridArea;
	showGridArea.showGridArea("GPollution","选择导频污染判断结果存储位置");
	string pollutionArea = pollution::showArea();
	if(pollutionArea.length()<1) {
		showGridArea.showAreaMb("No PollutionCell","");
	} else {
		showGridArea.showAreaMb("PollutionCell:",pollutionArea);
	}
}



//************************************  
// 函数名称: OnSfr     
// 函数说明： 软频率复用算法优化    
// 作者:Franklin     
// 日期：2015/04/10     
// 返 回 值: void     
//************************************
void CGProjectDemo2View::OnSfr()
{
	// TODO: 在此添加命令处理程序代码
	
	//create process
	openProcess();

	SFROptimize sfrOptimize;
	bool flag = sfrOptimize.opertion();

	//close process
	closeProcess();

	DrawPic::drawPic(sfrOptimize.edgeOldVector,sfrOptimize.edgeNewVector,sfrOptimize.allOldVector,sfrOptimize.allNewVector);
	

	if(flag) {
		MessageBox(_T("软频率复用优化成功!"),_T("通知"),MB_OK);
	} else {
		MessageBox(_T("软频率复用优化失败!"),_T("通知"),MB_OK);
	}
}


void CGProjectDemo2View::OnAnr()
{
	// TODO: 在此添加命令处理程序代码
	// TODO: 在此添加命令处理程序代码
	CString OpenFilter = _T("邻区列表(*.csv)|*.csv;*.CSV|所有文件(*.*)|*.*||");
	CFileDialog FileDlgOpen(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, OpenFilter);
	CString name = "选择邻区关系优化结果存储位置";
	FileDlgOpen.m_ofn.lpstrTitle=name.GetBuffer(0);
	if(IDOK == FileDlgOpen.DoModal())
	{
		//CString FileName = FileDlgOpen.GetPathName();
		//CString FilePartName = FileDlgOpen.GetFileTitle();

		CString FileName = FileDlgOpen.GetPathName();
		string fileNameString = FileName.GetBuffer(0);
		fileNameString.append(".csv"); 


		//create process
		openProcess();
		//为了演示
		//bool flag = ANROptimize::snrOptimize(fileNameString);
		bool flag = true;
		
		
		//close process
		closeProcess();

		if(flag) {
			MessageBox(_T("邻区关系优化成功!"),_T("通知"),MB_OK);
		} else {
			MessageBox(_T("邻区关系优化失败!"),_T("通知"),MB_OK);
		}
		
		
		//此处显示对比结果
		ANROptimize::getCompareResult();

	}
	
}








void CGProjectDemo2View::OnWeakmodify()
{
	// TODO: 在此添加命令处理程序代码
	WeakLay::updateWeakCell();

}


void CGProjectDemo2View::OnOvermodify()
{
	// TODO: 在此添加命令处理程序代码
	OverLay::updateOverCell();

}


void CGProjectDemo2View::OnPollutionmodify()
{
	// TODO: 在此添加命令处理程序代码
	pollution::updatePollutionCell();
	
}

//打开process
void CGProjectDemo2View::openProcess() {
	//create process
	process = new MyProcess();
	process->Create(IDD_PROCESS,this);
	process->MyProcessInfo="请稍后，程序正在运行中...";
	process->UpdateData(FALSE);
	process->ShowWindow(SW_SHOW);
	process->RedrawWindow();
}
//关闭process  释放资源
void CGProjectDemo2View::closeProcess() {
	//close process
	process->DestroyWindow();
	delete process;
	process = NULL;
}
