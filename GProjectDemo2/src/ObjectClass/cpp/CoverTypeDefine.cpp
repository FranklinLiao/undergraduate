#include "stdafx.h"
#include "CoverTypeDefine.h"

double  CoverTypeDefine::getCoverTypeValue(string name) {
	double value=0.0;
	if(name.compare("����")==0) {
		value=15.5;
	} else if(name.compare("����")==0) {
		value=(15.5+17)/2;
	} else if(name.compare("ũ��")==0) {
		value=17.5;
	}
	return value;
}