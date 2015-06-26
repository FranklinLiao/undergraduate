#include "stdafx.h"
#include "WriteTxt.h"
//************************************  
// ��������: writeInfo     
// ����˵���� �ļ���ʽΪ��    С��Id:����Id ����Id ����Id     
// ����:Franklin     
// ���ڣ�2015/06/08     
// �� �� ֵ: bool     
// ��    ��: string fileName      
// ��    ��: int cellId      
// ��    ��: T infos      
//************************************
template <typename T> bool WriteTxt::writeInfo(string fileName,int cellId,T infos) {
	ofstream fout(fileName);
	fout<<cellId<<": ";
	T<int>::iterator iter = infos.begin();
	while(iter!=infos.end()) {
		fout<<*iter++<<" ";
	}
	fout<<endl;
	fout.flush();
	fout.close();
	return TRUE;
}