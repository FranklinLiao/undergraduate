#pragma once


// CSetDb �Ի���

class CSetDb : public CDialogEx
{
	DECLARE_DYNAMIC(CSetDb)

public:
	CSetDb(const CString& title,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetDb();

// �Ի�������
	enum { IDD = IDD_SETDB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CString m_username;
	CString m_passwd;
	CString m_dbname;
	CString m_caption;
};
