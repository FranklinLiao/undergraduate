#include "stdafx.h"
#include "GetLonLatBoundsTool.h"
vector<double> GetLonLatBoundsTool::getLonLatBounds() { //�õ�������ı߽�
	vector<double> lonLatBounds;
	DataBase db;
	lonLatBounds=db.getLonLatBounds();
	return lonLatBounds;
}

vector<double> GetLonLatBoundsTool::getGridLonLatBounds() { //�õ�����ı߽�
	vector<double> lonLatBounds;
	DataBase db;
	lonLatBounds=db.getGridLonLatBounds();
	return lonLatBounds;
}