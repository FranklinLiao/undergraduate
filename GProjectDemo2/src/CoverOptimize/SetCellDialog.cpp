// SetCellDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GProjectDemo2.h"
#include "SetCellDialog.h"
#include "afxdialogex.h"


// SetCellDialog �Ի���

IMPLEMENT_DYNAMIC(SetCellDialog, CDialogEx)

SetCellDialog::SetCellDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(SetCellDialog::IDD, pParent)
	, newDeclineAngel(_T(""))
	, oldDeclineAngel(_T(""))
	, oldAspectAngel(_T(""))
	, newAspectAngel(_T(""))
	, oldSendPower(_T(""))
	, newSendPower(_T(""))
{
	
}

SetCellDialog::~SetCellDialog()
{
}

void SetCellDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, newDeclineAngel);
	DDX_Control(pDX, IDC_COMBO1, CellList);
	DDX_Text(pDX, IDC_EDIT4, oldDeclineAngel);
	DDX_Text(pDX, IDC_EDIT5, oldAspectAngel);
	DDX_Text(pDX, IDC_EDIT2, newAspectAngel);
	DDX_Text(pDX, IDC_EDIT7, oldSendPower);
	DDX_Text(pDX, IDC_EDIT6, newSendPower);
}


BEGIN_MESSAGE_MAP(SetCellDialog, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &SetCellDialog::OnSelchangeCombo1)
	ON_BN_CLICKED(IDOK, &SetCellDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// SetCellDialog ��Ϣ�������


void SetCellDialog::OnSelchangeCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��֪��ѡ���ĸ�С�� Ȼ��ȡ����С���������  �ٸ�ֵ 
	int selId = CellList.GetCurSel();
	if(CellDialogcellVector.size()>0) {
		//���id
		vector<int>::iterator iter = CellDialogcellVector.begin();
		int cnt = 0;
		int cellId = 0;
		while(iter!=CellDialogcellVector.end()) {
			if(cnt==selId) {
				cellId = *iter;
			}
			cnt++;
			iter++;
		}
		currentCellId = cellId;
		//ȡ��cellId��Ӧ�������
		vector<float> cellInfos = DBHelper::getCellInfo(cellId);
		stringstream ss;
		string info;
		ss<<cellInfos.at(0);
		info = ss.str();
		oldDeclineAngel = info.c_str();
		ss.str("");
		ss<<cellInfos.at(1);
		info = ss.str();
		oldAspectAngel = info.c_str();
		ss.str("");
		ss<<cellInfos.at(2);
		info = ss.str();
		ss.str("");
		oldSendPower = info.c_str();
		UpdateData(FALSE); //�ӱ������ؼ�
	}
}


BOOL SetCellDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	currentCellId = 0;
	flag = false;
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	if(CellDialogcellVector.size()>0) {
		vector<int>::iterator  iter = CellDialogcellVector.begin();
		while(iter!=CellDialogcellVector.end()) {
			int cellId = *iter++;
			string infos;
			stringstream info;
			info<<"С��:";
			info<<cellId;
			info>>infos;
			
			CellList.AddString(infos.c_str());
		}
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}




void SetCellDialog::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
	UpdateData(TRUE);
	//update newangle to db
	string tableName = "Area";
	string key[]={"ADeclineAngle","AAspectAngle","ASendPower"};
	
	if(currentCellId==0) { //û��ѡ��cell
		return;
	}
	
	if(newDeclineAngel.GetLength()<1) {
		newDeclineAngel = oldDeclineAngel;
	}
	if(newAspectAngel.GetLength()<1) {
		newAspectAngel = oldAspectAngel;
	}
	if(newSendPower.GetLength()<1) {
		newSendPower = oldSendPower;
	}
	string keyValue[]={newDeclineAngel,newAspectAngel,newSendPower};
	string whereKey[]={"AId"};
	string whereValue[]= {ChangeTypeTool::intToString(currentCellId)};
	DBHelper::updateInfo(tableName,key,keyValue,sizeof(key)/sizeof(key[0]),
		whereKey,whereValue,sizeof(whereKey)/sizeof(whereKey[0]));
	flag = true;
}


