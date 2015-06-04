// SetDb.cpp : 实现文件
//

#include "stdafx.h"
#include "GProjectDemo2.h"
#include "SetDb.h"
#include "afxdialogex.h"


// CSetDb 对话框

IMPLEMENT_DYNAMIC(CSetDb, CDialogEx)

CSetDb::CSetDb(const CString& title,CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetDb::IDD, pParent)
	, m_username(_T(""))
	, m_passwd(_T(""))
	, m_dbname(_T(""))
{
	m_caption = title;
}

CSetDb::~CSetDb()
{
}

void CSetDb::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_username);
	DDX_Text(pDX, IDC_EDIT2, m_passwd);
	DDX_Text(pDX, IDC_EDIT3, m_dbname);
}


BEGIN_MESSAGE_MAP(CSetDb, CDialogEx)
END_MESSAGE_MAP()


// CSetDb 消息处理程序
BOOL CSetDb::OnInitDialog() {
	SetWindowTextA(m_caption);
	return TRUE;
}