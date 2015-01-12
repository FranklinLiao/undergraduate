
//lat����֪���γ�ȣ�lon����֪��ľ���
//distance�����Ǹ�X���ﷶΧ,radius�ǵ���뾶��һ��ȡƽ���뾶6371km
#include "stdafx.h"
#include "GetDistanceTool.h"

#define PI 3.14159365
vector<double> GetDistanceTool::boundingCoordinates(double longi,double lati)
{
	double lat = lati * PI /180;
	double lon = longi * PI /180;  //�Ȼ���ɻ���
	double rad_dist = gridDistance / MyEarthRadius;  //����X�����ڵ���Բ���ϵĻ���
	double lat_min = lat - rad_dist;
	double lat_max = lat + rad_dist;   //����γ�ȷ�Χ
	double lon_min, lon_max;
	vector<double>  result;

	double lon_t = asin( sin(rad_dist) / cos(lat) );
	lon_min = lon - lon_t;
	lon_max = lon + lon_t;
	//����û��ɽǶȽ������
	lat_min = lat_min * 180 / PI;
	lat_max = lat_max * 180 / PI;
	lon_min = lon_min * 180 / PI;
	lon_max = lon_max *180 / PI;
	result.push_back(lon_min); 
	result.push_back(lon_max); //�����񻯵Ĺ���   ���ȷ�����
	result.push_back(lat_min); //�����񻯵Ĺ���   ά�ȷ����ϱ�С
	result.push_back(lat_max);
	return result;
	//printf("%d,%d,%d,%d",lat_min,lat_max,lon_min,lon_max);
}
/*
void main() {
	double radius= 6378.137;
	double distance = 0.005;
	double long1=116.366;
	double lat1=39.882864;

	boundingCoordinates(lat1,long1,distance,radius);

}
*/
