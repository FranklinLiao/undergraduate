// MyProcess.cpp : 实现文件
//

#include "stdafx.h"
#include "GProjectDemo2.h"
#include "MyProcess.h"
#include "afxdialogex.h"


// MyProcess 对话框

IMPLEMENT_DYNAMIC(MyProcess, CDialogEx)

MyProcess::MyProcess(CWnd* pParent /*=NULL*/)
	: CDialogEx(MyProcess::IDD, pParent)
	, MyProcessInfo(_T(""))
{

}

MyProcess::~MyProcess()
{
}

void MyProcess::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PROCESS, MyProcessInfo);
}


BEGIN_MESSAGE_MAP(MyProcess, CDialogEx)
END_MESSAGE_MAP()


// MyProcess 消息处理程序


BOOL MyProcess::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	this->SetWindowTextA("提示栏");
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
