#include "Point.h"



Point::Point(int x,int y)
{
	this->x = x;
	this->y = y;
}

int Point::getx()
{
	return x;
}
int Point::gety()
{
	return y;
}

void Point::setx(int pos)
{
	this->x = pos;
}

void Point::sety(int pos)
{
	this->y = pos;
}

Point::~Point()
{
}
