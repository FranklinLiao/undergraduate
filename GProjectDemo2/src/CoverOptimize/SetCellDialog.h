#pragma once
#include "afxwin.h"
#include "GProjectDemo2.h"
// SetCellDialog �Ի���

class SetCellDialog : public CDialogEx
{
	DECLARE_DYNAMIC(SetCellDialog)

public:
	SetCellDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~SetCellDialog();

// �Ի�������
	enum { IDD = IDD_SETCELL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
	bool flag; //��ʶ�Ƿ������С���Ĳ���
};

