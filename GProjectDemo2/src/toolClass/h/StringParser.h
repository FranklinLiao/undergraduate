#pragma once
//#include "stringparser.h"
#include <assert.h>
#include <map>
#include <vector>
#include <string>
using namespace std;

typedef unsigned long   u32;

class CppCSV
{
private:
	map<u32, map<u32, string>> m_stringMap;
	string m_CSVName;
public:
	CppCSV(){}
	CppCSV(const char *path)
	{
		assert(LoadCSV(path));
	}
	~CppCSV(){}

	bool LoadCSV(const char *path);
	bool SaveCSV(const char *path = NULL);

	bool GetIntValue(u32 uiRow, u32 uiCol, int &riValue);
	bool GetFloatValue(u32 uiRow, u32 uiCol, float &rfValue);
	string* GetStringValue(u32 uiRow, u32 uiCol);
	//ע��˴����ǵ���Ԫ������"��",���Խ�����ΪCSV�ķָ�����Ϊ��";"
	//�޸İ취���������-����-����-�б�ָ����
	//int GetParamFromString(string str, vector<string> &stringVec, char delim  = ',');
	int GetParamFromString(string str, vector<string> &stringVec, char delim  = ';');

	//map<u32, map<u32, string>>& GetCSVMap()
	map<u32, map<u32, string>> GetCSVMap()
	{
		return m_stringMap;
	}

};

