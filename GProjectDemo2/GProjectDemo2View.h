
// GProjectDemo2View.h : CGProjectDemo2View 类的接口
//

#pragma once
//#include "stdafx.h"
//数据库连接的头文件
#include "SetDb.h"
#include "DBConnPool.h"
#include "DataBase.h"
#include "string.h"
#include "GetDistanceTool.h"
#include "GProjectDemo2Doc.h"
#include "MakeGrid.h"
#include "MakeGridFileTool.h"
#include "RecordRTData.h"
#include "RecordBuildingPointTool.h"
#include "RecordGridInfoTool.h"
#include "RecordGridBuildingIntersectionTool.h"
#include "RecordAreaGridIntersectionTool.h"
#include "GetStrongestStrength.h"
#include "PutXY.h"
#include "GetLonLatBoundsTool.h"
#include "RecordAreaInfoTool.h"
#include "SetGridColorTool.h"
#include "GridBSDistanceCal.h"
#include "SetCellDialog.h"
//process
#include "MyProcess.h"
//mif2tab
#include "Mif2Tab.h"
//覆盖优化
#include "WeakLay.h"
#include "OverLay.h"
#include "pollution.h"
#include "ShowGridArea.h"
//软频率复用算法优化
#include "SFROptimize.h"
#include "RecordAdjAreaForSfrTool.h"
#include "DrawPic.h"
//ANR
#include "ANROptimize.h"
class CGProjectDemo2View : public CView
{
protected: // 仅从序列化创建
	CGProjectDemo2View();
	DECLARE_DYNCREATE(CGProjectDemo2View)
	
// 特性
public:
	CGProjectDemo2Doc* GetDocument() const;
	
// 操作
public:
	//virtual CMapXFeature createGridPoints(double longitude,double latitude);
	//virtual void createGridMapPoints(double minLongitude,double maxLongtitude,double minLatitude,double maxLatitude);

//public:
//	double longilength;
//	double latilength;

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CGProjectDemo2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnFileOpen();
	afx_msg void OnButton32791();
	afx_msg void OnButton32792();
	afx_msg void OnButton32793();
	afx_msg void OnButton32794();
	afx_msg void OnButton32795();
	afx_msg void InitDataBase();
	afx_msg void OnTestdbconnection();
	afx_msg void OnBinddata();
	afx_msg void OnGridmaker();
	afx_msg void OnIntersection();
	afx_msg void OnRecordbuilding();
	afx_msg void OnRecordgrid();
	afx_msg void OnOpenbsxls();
	afx_msg void OnModify();
	afx_msg void OnPutxy();
	afx_msg void OnRecordbs();
	afx_msg void OnRecordrtdata();
	afx_msg void OnCalculate();
	afx_msg void OnGridmif();
	afx_msg void OnChange();
	afx_msg void OnOverlay();
	afx_msg void OnWeaklay();
	afx_msg void OnPollution();

private:
	HANDLE THandle;
	DWORD TId;
public:
	afx_msg void OnSfr();
	afx_msg void OnAnr();
	afx_msg void OnDbSet();

private:
	string m_username;
	string m_password;
	string m_dbname;
public:
	afx_msg void OnSetdb();
	afx_msg void OnWeakmodify();
	afx_msg void OnOvermodify();
	afx_msg void OnPollutionmodify();
public:
	MyProcess* process;

	void openProcess();
	void closeProcess();
};

#ifndef _DEBUG  // GProjectDemo2View.cpp 中的调试版本
inline CGProjectDemo2Doc* CGProjectDemo2View::GetDocument() const
   { return reinterpret_cast<CGProjectDemo2Doc*>(m_pDocument); }
#endif

