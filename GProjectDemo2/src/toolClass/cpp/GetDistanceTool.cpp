
//lat是已知点的纬度，lon是已知点的经度
//distance就是那个X公里范围,radius是地球半径，一般取平均半径6371km
#include "stdafx.h"
#include "GetDistanceTool.h"

#define PI 3.14159365
vector<double> GetDistanceTool::boundingCoordinates(double longi,double lati)
{
	double lat = lati * PI /180;
	double lon = longi * PI /180;  //先换算成弧度
	double rad_dist = gridDistance / MyEarthRadius;  //计算X公里在地球圆周上的弧度
	double lat_min = lat - rad_dist;
	double lat_max = lat + rad_dist;   //计算纬度范围
	double lon_min, lon_max;
	vector<double>  result;

	double lon_t = asin( sin(rad_dist) / cos(lat) );
	lon_min = lon - lon_t;
	lon_max = lon + lon_t;
	//最后置换成角度进行输出
	lat_min = lat_min * 180 / PI;
	lat_max = lat_max * 180 / PI;
	lon_min = lon_min * 180 / PI;
	lon_max = lon_max *180 / PI;
	result.push_back(lon_min); 
	result.push_back(lon_max); //按网格化的规律   经度方向上
	result.push_back(lat_min); //按网格化的规律   维度方向上变小
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
