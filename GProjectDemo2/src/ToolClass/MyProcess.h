#pragma once

#include "resource.h"
// MyProcess �Ի���

class MyProcess : public CDialogEx
{
	DECLARE_DYNAMIC(MyProcess)

public:
	MyProcess(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~MyProcess();

// �Ի�������
	enum { IDD = IDD_PROCESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString MyProcessInfo;
	virtual BOOL OnInitDialog();

	
};
