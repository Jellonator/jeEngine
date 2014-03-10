#include "jePoint.h"
//Not commenting this file, should be easy enough to understand
jePoint::jePoint()
{
	x = 0;
	y = 0;
	speed = 1;
	direction = 1;
	startX = x;
	startY = y;
	endX = x;
	endY = y;
	time = 1;
	startSpeed = 0;
}

jePoint::~jePoint()
{
	//dtor
}
