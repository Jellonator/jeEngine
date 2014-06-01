#include "jePoint.h"
#include "JE.h"
namespace JE{
Point::Point(float x, float y)
{
	this->x = x;
	this->y = y;
	/*speed = 1;
	direction = 1;
	startX = x;
	startY = y;
	endX = x;
	endY = y;
	time = 1;
	startSpeed = 0;*/
}

Point::~Point()
{
	//dtor
}

bool Point::moveTo(float x, float y, float dt, float speed, float snap, float dead){
	float xd = x-this->x;
	float yd = y-this->y;
	if (std::abs(xd) <= snap && std::abs(yd) <= snap){this->x = x; this->y = y;return true;}
	else {
		float dis = std::sqrt(std::pow(xd,2) + std::pow(yd,2));
		dis -= dead;
		if (dis > 0){
			float angle = std::atan2(y - this->y, x - this->x);
			float s = dis*dt*speed;
			float sx = std::cos(angle)*s;
			float sy = std::sin(angle)*s;
			this->x = this->x + sx;
			this->y = this->y + sy;
			if ((sx < 0 && this->x < x) || (sx > 0 && this->x > x)) this->x = x;
			if ((sy < 0 && this->y < y) || (sy > 0 && this->y > y)) this->y = y;
		}else return true;
	}
	return false;
}

/*void Point::moveTo(float x, float y){
	this->x = x;
	this->y = y;
}*/
};
