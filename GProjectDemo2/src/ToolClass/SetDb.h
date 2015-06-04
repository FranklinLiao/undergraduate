#pragma once


// CSetDb 对话框

class CSetDb : public CDialogEx
{
	DECLARE_DYNAMIC(CSetDb)

public:
	CSetDb(const CString& title,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetDb();

// 对话框数据
	enum { IDD = IDD_SETDB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CString m_username;
	CString m_passwd;
	CString m_dbname;
	CString m_caption;
};
