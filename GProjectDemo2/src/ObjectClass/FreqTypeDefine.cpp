#include "stdafx.h"
#include "FreqTypeDefine.h"

int FreqTypeDefine::getFreqTypeNum(string freqType) {
	int num;
	string str2;   
	for(int i=0; i<freqType.size(); i++)
	{
		if ((freqType[i]>='0')&&(freqType[i]<='9'))
			str2 += freqType[i];
	}
	num = ChangeTypeTool::stringToInt(str2);
	return num;
}