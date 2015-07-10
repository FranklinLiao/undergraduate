
// GProjectDemo2View.h : CGProjectDemo2View ��Ľӿ�
//

#pragma once
//#include "stdafx.h"
//���ݿ����ӵ�ͷ�ļ�
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
//�����Ż�
#include "WeakLay.h"
#include "OverLay.h"
#include "pollution.h"
#include "ShowGridArea.h"
//��Ƶ�ʸ����㷨�Ż�
#include "SFROptimize.h"
#include "RecordAdjAreaForSfrTool.h"
#include "DrawPic.h"
//ANR
#include "ANROptimize.h"
class CGProjectDemo2View : public CView
{
protected: // �������л�����
	CGProjectDemo2View();
	DECLARE_DYNCREATE(CGProjectDemo2View)
	
// ����
public:
	CGProjectDemo2Doc* GetDocument() const;
	
// ����
public:
	//virtual CMapXFeature createGridPoints(double longitude,double latitude);
	//virtual void createGridMapPoints(double minLongitude,double maxLongtitude,double minLatitude,double maxLatitude);

//public:
//	double longilength;
//	double latilength;

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CGProjectDemo2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // GProjectDemo2View.cpp �еĵ��԰汾
inline CGProjectDemo2Doc* CGProjectDemo2View::GetDocument() const
   { return reinterpret_cast<CGProjectDemo2Doc*>(m_pDocument); }
#endif

