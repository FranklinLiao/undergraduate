#include "stdafx.h"
#include "Mif2Tab.h"
#include "TAB2MIF.h"
#include <DIRECT.H>

BOOL Mif2Tab::Convert0(CString strFilePath, CString strDstPath)
{
	nFileIndex = 0;
	m_nSingleFile = TRUE;
	CFileStatus fileStatus;
	CFile::GetStatus( strFilePath, fileStatus );
	if ( fileStatus.m_attribute & CFile::directory )
	{
		CString strFilter = strFilePath + "\\*.*";
		CFileFind findFile;
		CString mstr;
		BOOL bFind = findFile.FindFile( strFilter );
		while( bFind)
		{
			bFind = findFile.FindNextFile();
			mstr = findFile.GetFilePath();
			if (findFile.IsDots()&&findFile.IsDirectory())
				continue;

			if ( findFile.IsDirectory() )
			{
				CString strPath = findFile.GetFilePath();
				CString strDstPath1 = m_strDstPath+
					strPath.Right(strPath.GetLength()-m_strSrcPath.GetLength());
				MakeDir( strDstPath1 );
				Convert0(strPath, strDstPath1);
			}
			else
			{
				//	m_nSingleFile = TRUE;  
				if ( !m_nSingleFile ) //false tab->mif
				{
					CString strFile = findFile.GetFilePath();
					mstr = strFile.Right(3);
					if (!mstr.CompareNoCase("TAB")) {
						strFile = strFile.Left(15) + "......" + strFile.Right(25) ;
						//GetDlgItem( IDC_MSG )->SetWindowText(strFile);

						Convert( findFile.GetFilePath(), strDstPath );
						nFileIndex ++;
						if ( nFileIndex > 100 ) nFileIndex = 0;
						//m_ctrlProgress.SetPos(nFileIndex);
					}
				}
				else  //true mif->tab
				{
					CString strFile = findFile.GetFilePath();
					mstr = strFile.Right(3);
					if (!mstr.CompareNoCase("MIF")) {
						strFile = strFile.Left(15) + "......" + strFile.Right(25) ;
						//GetDlgItem( IDC_MSG )->SetWindowText(strFile);

						Convert2( findFile.GetFilePath(), strDstPath );
						nFileIndex ++;
						if ( nFileIndex > 100 ) nFileIndex = 0;
						//m_ctrlProgress.SetPos(nFileIndex);
					}
				}
			}
		}

	}
	else
	{
		Convert( strFilePath, strDstPath );
	}
	return TRUE;
}
//2
//tab->mif
BOOL Mif2Tab::Convert(CString strFilePath, CString strDstPath)
{
	BOOL bReturn = FALSE;
	CString strSrcPathName;
	CString strDstPathName;

	int nIndex = strFilePath.ReverseFind('\\');
	if ( nIndex >= 0 )
	{
		strSrcPathName = strFilePath;
		strDstPathName = strFilePath.Right( strFilePath.GetLength()-nIndex-1);
		strDstPathName = strDstPathName.Left(strDstPathName.GetLength()-3) + "mif";
		strDstPathName = strDstPath + "\\" + strDstPathName;
	}
	else
	{
		strSrcPathName = strFilePath;
		strDstPathName = strFilePath;
		strDstPathName = strDstPathName.Left(strDstPathName.GetLength()-3) + "mif";
		strDstPathName = strDstPath + "\\" + strDstPathName;
	}


	char *pstrSrc = new char[1024];
	char *pstrDst = new char[1024];
	pstrSrc = strSrcPathName.GetBuffer(0);
	pstrDst = strDstPathName.GetBuffer(0);

	//int version = MITAB_VERSION_INT;
	Tab2Tab(pstrSrc,pstrDst,0);

	return bReturn;
}
//mif->tab
BOOL Mif2Tab::Convert2(CString strFilePath, CString strDstPath)
{
	BOOL bReturn = FALSE;
	CString strSrcPathName;
	CString strDstPathName;

	int nIndex = strFilePath.ReverseFind('\\');
	if ( nIndex >= 0 )
	{
		strSrcPathName = strFilePath;
		strDstPathName = strFilePath.Right( strFilePath.GetLength()-nIndex-1);
		strDstPathName = strDstPathName.Left(strDstPathName.GetLength()-3) + "tab";
		strDstPathName = strDstPath + "\\" + strDstPathName;
	}
	else
	{
		strSrcPathName = strFilePath;
		strDstPathName = strFilePath;
		strDstPathName = strDstPathName.Left(strDstPathName.GetLength()-3) + "tab";
		strDstPathName = strDstPath + "\\" + strDstPathName;
	}


	char *pstrSrc = new char[1024];
	char *pstrDst = new char[1024];
	pstrSrc = strSrcPathName.GetBuffer(0);
	pstrDst = strDstPathName.GetBuffer(0);

	//int version = MITAB_VERSION_INT;
	Tab2Tab(pstrSrc,pstrDst,0);

	return bReturn;
}
//4
void Mif2Tab::MakeDir(CString strPath)
{
	int nIndex = strPath.Find(m_strDstPath);
	if ( nIndex >= 0 )
	{
		_chdir(m_strDstPath);
		MakeDir( strPath.Right(strPath.GetLength()-m_strDstPath.GetLength()-1));
	}
	else
	{
		CFileFind findFile;
		nIndex = strPath.Find('\\');
		if ( nIndex >= 0 )
		{
			CString strLeft = strPath.Left(nIndex);
			BOOL bFind = findFile.FindFile( strLeft );
			if ( !bFind)
			{
				mkdir(strLeft);
			}
			else
			{
				_chdir(strLeft);
			}
			MakeDir( strPath.Right(strPath.GetLength()-nIndex-1));
		}
		else
		{
			BOOL bFind = findFile.FindFile( strPath );
			if ( !bFind)
			{
				mkdir(strPath);
			}
			else
			{
				_chdir(strPath);
			}
		}
	}
}
