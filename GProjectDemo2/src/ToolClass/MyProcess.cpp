// MyProcess.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GProjectDemo2.h"
#include "MyProcess.h"
#include "afxdialogex.h"


// MyProcess �Ի���

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


// MyProcess ��Ϣ�������


BOOL MyProcess::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	this->SetWindowTextA("��ʾ��");
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
