#include "stdafx.h"
#include "ShowGridArea.h"
void ShowGridArea::showGridArea(CString title,CString name) {
	// TODO: �ڴ���������������
	CString OpenFilter = title+_T(+"(*.tab)|*.tab;*.TAB|�����ļ�(*.*)|*.*||");
	CFileDialog FileDlgOpen(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, OpenFilter);
	FileDlgOpen.m_ofn.lpstrTitle=name.GetBuffer(0);
	if(IDOK == FileDlgOpen.DoModal())
	{
		CString FileName = FileDlgOpen.GetPathName();
		string fileNameString = FileName.GetBuffer(0);
		fileNameString.append(".mif"); 
		//����ǿֵ����ɫ���ж�Ӧ�ĸı�
		//create process
		openProcess();

		//��������չʾ��ע��������һ��
		SetGridColorTool::SetColor(TRUE,title.GetBuffer());
		//MessageBox(_T("����ɫ��Ϣ�Ѿ�ת���ɹ�!"),_T("֪ͨ"),MB_OK);
		//�����ݿ���ȡ���������ɫ��Ϣ����չʾ
		MakeGridFileTool::makeGridFile(fileNameString);

		//�ں������mif2tab
		Mif2Tab mif2Tab;
		CString path = FileDlgOpen.GetFolderPath();
		mif2Tab.Convert0(path,path);
		//close process
		closeProcess();

		//ɾ��Ŀ¼�е�.mif .mid
		//string cmdLine = "cd " + path;
		//system(cmdLine.c_str());
		//cmdLine = "del *.mif *.mid";
		//system(cmdLine.c_str());
	//	MessageBox(NULL,_T("���Ѿ���ɵ�Ƶ��Ⱦ���ж�!"),_T("֪ͨ"),MB_OK);
	}
}

void ShowGridArea::showAreaMb(string infoHead,string infoBody) {
	CString info = "����";
	ShowInfoMB::showInfo(infoHead,infoBody);
}

void ShowGridArea::openProcess() {
	//create process
	process = new MyProcess();
	process->Create(IDD_PROCESS,NULL);
	process->MyProcessInfo="���Ժ󣬳�������������...";
	process->UpdateData(FALSE);
	process->ShowWindow(SW_SHOW);
	process->RedrawWindow();
}
//�ر�process  �ͷ���Դ
void ShowGridArea::closeProcess() {
	//close process
	process->DestroyWindow();
	delete process;
	process = NULL;
}