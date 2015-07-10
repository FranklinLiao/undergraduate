#if _MSC_VER > 1000
#pragma once
#endif

//��дcsv�ļ�
#ifndef __XCFILESTREAM_H__
#define __XCFILESTREAM_H__
/// ���������ļ�
/// Cϵͳ�ļ�
/// C++ϵͳ�ļ�
#include <string>
#include <list>
#include <vector>
using namespace std;
#include <windows.h>
/// ������ͷ�ļ�
/// ����Ŀͷ�ļ�


/// �޴�
#define XC_ERR_NONE 0
/// ��Ч�ļ������ָ���ļ���ʽ
#define XC_ERR_INVALID_FILE_NAME (-1)


/// xun-test�ļ��Ķ���д
class CXCFileStream 
{


public:


	CXCFileStream(void);
	~CXCFileStream(void);


	/*
	* �������ܣ���ȡCSV�ļ����������е����ݣ�Ȼ��洢�������С�
	* ����������
	*     [in] lpszFilename - ����ȡ��CSV�ļ���
	*     [in, out] vlStr - �洢�������CSV����
	* ����ֵ��
	*     �������
	* ע�⣺������Ϊ����Ը�⣨Ŀǰ���������������vector<list<string>>������vector<list<string> >��
	*/
	const int ReadCsvData(LPCTSTR lpszFilename, vector<list<string> > &vlStr);
	/* 
	* �������ܣ��������е����ݾ����Ű桢���֡���ӷָ�����д�뵽CSV�ļ���
	* ����������
	*     [in] lpszFilename - ����ȡ��CSV�ļ���
	*     [in] vlStr - �洢�������CSV����
	* ����ֵ��
	*     �������
	* ע�⣺������Ϊ����Ը�⣨Ŀǰ���������������vector<list<string>>������vector<list<string> >��
	*/
	const int WriteCsvData(LPCTSTR lpszFilename, const vector<list<string> > &vlStr);


private:


	/// �ж��Ƿ���CSV�ļ�
	const bool IsCsvFile(LPCTSTR lpszFilename);


};


#endif