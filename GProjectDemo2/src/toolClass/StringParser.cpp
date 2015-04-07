#include "stdafx.h" 
#include <stdio.h>
#include "StringParser.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool CppCSV::LoadCSV(const char *path)
{
	ifstream  csvFile(path);
	//map<u32, string> stringMap;
	u32 uiIndex = 1;
	//��ÿһ�н��д洢
	while(!csvFile.eof()) {
		string sLine;
		getline(csvFile,sLine);
		//stringMap[uiIndex] = sLine;
		vector<string> stringVec;
		map<u32, string> stringMapTemp;
		//��ÿһ�е��ַ����зָ�
		GetParamFromString(sLine, stringVec);
		vector<string>::size_type idx = 0;
		for (; idx != stringVec.size(); ++idx)
		{
			stringMapTemp[idx + 1] = stringVec[idx];
		}
		m_stringMap[uiIndex] = stringMapTemp;
		uiIndex++;
	}
	csvFile.close();
	m_CSVName = path;
	return true;
}

bool CppCSV::SaveCSV(const char *path /* = NULL */)
{
	if (path != NULL)
	{
		m_CSVName = path;
	}

	FILE *pFile = fopen(m_CSVName.c_str(), "w");
	if (pFile)
	{
		map<u32, map<u32, string>>::iterator iter = m_stringMap.begin();
		for (; iter != m_stringMap.end(); ++iter)
		{
			map<u32, string> &rStringMap = iter->second;
			map<u32, string>::iterator it = rStringMap.begin();
			for (; it != rStringMap.end(); ++it)
			{
				string strTemp = it->second;
				strTemp += ';';
				fwrite(strTemp.c_str(), 1, 1, pFile);
			}

			char delim = '\n';
			fwrite(&delim, 1, 1, pFile);
		}

		fclose(pFile);
		return true;
	} 
	else
	{
		return false;
	}
}

bool CppCSV::GetIntValue(u32 uiRow, u32 uiCol, int &riValue)
{
	string *pStr = GetStringValue(uiRow, uiCol);
	if (pStr)
	{
		riValue = atoi(pStr->c_str());
		return true;
	} 
	else
	{
		return false;
	}
}

bool CppCSV::GetFloatValue(u32 uiRow, u32 uiCol, float &rfValue)
{
	string* pStr = GetStringValue(uiRow, uiCol);
	if (pStr)
	{
		rfValue = atof(pStr->c_str());
		return true;
	} 
	else
	{
		return false;
	}
}

string* CppCSV::GetStringValue(u32 uiRow, u32 uiCol)
{
	map<u32, map<u32, string>>::iterator iter = m_stringMap.find(uiRow);
	if (iter != m_stringMap.end())
	{
		map<u32, string> &rStrMap = iter->second;
		map<u32, string>::iterator it = rStrMap.find(uiCol);
		if (it != rStrMap.end())
		{
			return &(it->second);
		} 
		else
		{
			return NULL;
		}
	} 
	else
	{
		return NULL;
	}
}

//���ڷָ��ַ�������CSV����е�һ�а��չ��������һ���ַ������洢��һ��vector��
//����CSV��������洢�����ݵĲ�ͬ�����ظ�����
int CppCSV::GetParamFromString(string str, vector<string> &stringVec, char delim)
{
	int cutAt;
	while( (cutAt = str.find_first_of(delim)) != str.npos )  
	{  
		if(cutAt > 0)  
		{  
			stringVec.push_back(str.substr(0, cutAt));  
		}else{  
			stringVec.push_back("");  
		}  
		str = str.substr(cutAt + 1);  
	}  
	return stringVec.size();
}
