#include "stdafx.h"
#include "ShowGridArea.h"
void ShowGridArea::showGridArea(CString title) {
	// TODO: �ڴ���������������
	CString OpenFilter = title+_T(+"(*.tab)|*.tab;*.TAB|�����ļ�(*.*)|*.*||");
	CFileDialog FileDlgOpen(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, OpenFilter);
	if(IDOK == FileDlgOpen.DoModal())
	{
		CString FileName = FileDlgOpen.GetPathName();
		string fileNameString = FileName.GetBuffer(0);
		fileNameString.append(".mif"); 
		//����ǿֵ����ɫ���ж�Ӧ�ĸı�

		//��������չʾ��ע��������һ��
		SetGridColorTool::SetColor(TRUE,title.GetBuffer());
		//MessageBox(_T("��ϲ������ɫ��Ϣ�Ѿ�ת���ɹ�!"),_T("֪ͨ"),MB_OK);
		//�����ݿ���ȡ���������ɫ��Ϣ����չʾ
		MakeGridFileTool::makeGridFile(fileNameString);

		//�ں������mif2tab
		Mif2Tab mif2Tab;
		CString path = FileDlgOpen.GetFolderPath();
		mif2Tab.Convert0(path,path);
		//ɾ��Ŀ¼�е�.mif .mid
		//string cmdLine = "cd " + path;
		//system(cmdLine.c_str());
		//cmdLine = "del *.mif *.mid";
		//system(cmdLine.c_str());
	//	MessageBox(NULL,_T("��ϲ�����Ѿ���ɵ�Ƶ��Ⱦ���ж�!"),_T("֪ͨ"),MB_OK);
	}
}

void ShowGridArea::showAreaMb(string infoHead,string infoBody) {
	ShowInfoMB::showInfo(infoHead,infoBody);
}