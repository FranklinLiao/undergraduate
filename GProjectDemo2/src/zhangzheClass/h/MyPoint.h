#ifndef _MYPOINT_H
#define _MYPOINT_H
#include "stdafx.h"

class MyPoint {
private :
	double lon;
	double lat;
public:
	MyPoint(double lon,double lat) {
		setLon(lon);
		setLat(lat);
	}
	MyPoint(){}

	double getLon() {
		return this->lon;
	}

	double getLat() {
		return this->lat;
	}

	void setLon(double lon) {
		this->lon = lon;
	}

	void setLat(double lat) {
		this->lat = lat;
	}
};

#endif