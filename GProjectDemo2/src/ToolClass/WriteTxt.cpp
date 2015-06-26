#include "stdafx.h"
#include "WriteTxt.h"
//************************************  
// 函数名称: writeInfo     
// 函数说明： 文件格式为：    小区Id:邻区Id 邻区Id 邻区Id     
// 作者:Franklin     
// 日期：2015/06/08     
// 返 回 值: bool     
// 参    数: string fileName      
// 参    数: int cellId      
// 参    数: T infos      
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