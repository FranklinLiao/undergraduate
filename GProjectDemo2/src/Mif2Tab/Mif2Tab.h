#ifndef __MIF2TAB__H
#define __MIF2TAB__H
#include "stdafx.h"
class Mif2Tab {
public:
	long nFileIndex;
	CString	m_strDstPath;
	CString	m_strSrcPath;
	BOOL	m_nSingleFile;
	void MakeDir(CString strPath);
	BOOL Convert0(CString strFilePath, CString strDstPath);
	BOOL Convert(CString strFilePath, CString strDstPath);
	BOOL Convert2(CString strFilePath, CString strDstPath);
};
#endif