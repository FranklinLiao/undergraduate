#pragma once

#include "resource.h"
// MyProcess 对话框

class MyProcess : public CDialogEx
{
	DECLARE_DYNAMIC(MyProcess)

public:
	MyProcess(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MyProcess();

// 对话框数据
	enum { IDD = IDD_PROCESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString MyProcessInfo;
	virtual BOOL OnInitDialog();

	
};
