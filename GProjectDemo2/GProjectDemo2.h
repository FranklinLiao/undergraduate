
// GProjectDemo2.h : GProjectDemo2 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号
#include "RecordBuildingPointTool.h"
#include "DBConnPool.h"
// CGProjectDemo2App:
// 有关此类的实现，请参阅 GProjectDemo2.cpp
//

class CGProjectDemo2App : public CWinAppEx
{
public:
	CGProjectDemo2App();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	//afx_msg void TestDBConnect();
	//afx_msg void Record_BPoint();
};

extern CGProjectDemo2App theApp;
