
// GProjectDemo2.h : GProjectDemo2 Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������
#include "RecordBuildingPointTool.h"
#include "DBConnPool.h"
// CGProjectDemo2App:
// �йش����ʵ�֣������ GProjectDemo2.cpp
//

class CGProjectDemo2App : public CWinAppEx
{
public:
	CGProjectDemo2App();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
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
