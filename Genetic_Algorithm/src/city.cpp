/*
	2016-04-19
	auther: Chen Yazheng
*/

#include "../lib/city.h"
#include <cmath>

City::City(float x, float y, int id, char name)
	: m_x(x), m_y(y), m_id(id), m_name(name)
{}
City::~City() {}

float City::distanceTo(const City & city) {
	double x = fabs( getX() - city.getX() );
	double y = fabs( getY() - city.getY() );
	double distance = sqrt( x * x + y * y );
	return distance;
}
