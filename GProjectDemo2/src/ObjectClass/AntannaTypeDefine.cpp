#include "stdafx.h"
#include "AntannaTypeDefine.h"

int AntannaTypeDefine::getAntanaTypeDefineValue(CString typeName) {
	if(typeName==_T("��Ƶ������")) {
		return 1;
	} else if(typeName==_T("��Ƶ˫����")) {
		return 2;
	} else if(typeName==_T("˫Ƶ������")) {
		return 3;
	} else if(typeName==_T("˫Ƶ˫����")) {
		return 4;
	} else if(typeName==_T("��������")) {
		return 5;
	} else {
		return 0;
	}
}