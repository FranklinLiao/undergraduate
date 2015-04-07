#include "stdafx.h"
#include "AntannaTypeDefine.h"

int AntannaTypeDefine::getAntanaTypeDefineValue(CString typeName) {
	if(typeName==_T("单频单极化")) {
		return 1;
	} else if(typeName==_T("单频双极化")) {
		return 2;
	} else if(typeName==_T("双频单极化")) {
		return 3;
	} else if(typeName==_T("双频双极化")) {
		return 4;
	} else if(typeName==_T("美化天线")) {
		return 5;
	} else {
		return 0;
	}
}