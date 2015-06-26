#pragma once
#include "afxwin.h"
#include "GProjectDemo2.h"
// SetCellDialog 对话框

class SetCellDialog : public CDialogEx
{
	DECLARE_DYNAMIC(SetCellDialog)

public:
	SetCellDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~SetCellDialog();

// 对话框数据
	enum { IDD = IDD_SETCELL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString newDeclineAngel;
	CComboBox CellList;
	CString oldDeclineAngel;
	
	afx_msg void OnSelchangeCombo1();
	virtual BOOL OnInitDialog();
public:
	vector<int> CellDialogcellVector;
	int currentCellId;
	afx_msg void OnBnClickedOk();
	CString oldAspectAngel;
	CString newAspectAngel;
	CString oldSendPower;
	CString newSendPower;
	bool flag; //标识是否更改了小区的参数
};

