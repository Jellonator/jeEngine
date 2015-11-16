#include "JE/jePoint.h"
#include "JE/UTIL/jeMath.h"
#include <cmath>
namespace JE{

Point::Point(const JE::Point& point){
	this->set(point.getX(), point.getY());
}

Point::Point(float x, float y){
	this->x = x;
	this->y = y;
}

Point::~Point(){
	//dtor
}

void Point::setX(float value){
	this->x = value;
}

void Point::setY(float value){
	this->y = value;
}

void Point::set(float x, float y){
	this->x = x;
	this->y = y;
}

float Point::getX()const{
	return this->x;
}
float Point::getY()const{
	return this->y;
}

bool Point::moveToSmooth(float x, float y, float dt, float speed, float snap, float dead){
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

bool Point::moveToLinear(float x, float y, float dt, float speed, float snap, float dead){
	float xd = x-this->x;
	float yd = y-this->y;
	if (std::abs(xd) <= snap && std::abs(yd) <= snap){this->x = x; this->y = y;return true;}
	else {
		float dis = std::sqrt(std::pow(xd,2) + std::pow(yd,2));
		dis -= dead;
		if (dis > 0){
			float angle = std::atan2(y - this->y, x - this->x);
			float s = dt*speed;
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

void Point::operator+=(const JE::Point& point){
	this->x += point.getX();
	this->y += point.getY();
}

void Point::operator -=(const JE::Point& point){
	this->x -= point.getX();
	this->y -= point.getY();
}

void Point::operator *=(const JE::Point& point){
	this->x *= point.getX();
	this->y *= point.getY();
}

void Point::operator /=(const JE::Point& point){
	this->x /= point.getX();
	this->y /= point.getY();
}

void Point::operator  =(const JE::Point& point){
	this->x = point.getX();
	this->y = point.getY();
}

bool Point::operator ==(const JE::Point& point){
	return (JE::MATH::isClose(this->x, point.getX()) && JE::MATH::isClose(this->y, point.getY()));
}

bool Point::operator !=(const JE::Point& point){
	return !(this->operator ==(point));
}

void Point::modulate(float value){
	this->x = std::fmod(this->x, value);
	this->y = std::fmod(this->y, value);
}

void Point::getAsInt(int* x, int* y) const{
	if (x) *x = int(this->x);
	if (y) *y = int(this->y);
}

};
