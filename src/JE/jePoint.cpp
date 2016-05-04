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

void Point::moveBy(float x, float y){
	this->x += x;
	this->y += y;
}

void Point::moveTo(float x, float y){
	this->x = x;
	this->y = y;
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

void Point::operator *=(float value){
	this->x *= value;
	this->y *= value;
}

void Point::operator /=(float value){
	this->x /= value;
	this->y /= value;
}

void Point::operator  =(const JE::Point& point){
	this->x = point.getX();
	this->y = point.getY();
}

bool operator ==(const JE::Point& a, const JE::Point& b){
	return (JE::MATH::isClose(a.x, b.x) && JE::MATH::isClose(a.y, b.y));
}

bool operator !=(const JE::Point& a, const JE::Point& b){
	return !(JE::MATH::isClose(a.x, b.x) && JE::MATH::isClose(a.y, b.y));
}

JE::Point operator +(const JE::Point& a, const JE::Point& b){
	return JE::Point(a.x + b.x, a.y + b.y);
}

JE::Point operator -(const JE::Point& a, const JE::Point& b){
	return JE::Point(a.x - b.x, a.y - b.y);
}

JE::Point operator *(const JE::Point& a, const JE::Point& b){
	return JE::Point(a.x * b.x, a.y * b.y);
}

JE::Point operator /(const JE::Point& a, const JE::Point& b){
	return JE::Point(a.x / b.x, a.y / b.y);
}

JE::Point operator !(const JE::Point& a){
	return JE::Point(-a.x, -a.y);
}

JE::Point operator *(const JE::Point& a, float b){
	return JE::Point(a.x * b, a.y * b);
}

JE::Point operator /(const JE::Point& a, float b){
	return JE::Point(a.x / b, a.y / b);
}

JE::Point operator %(const JE::Point& a, float b){
	return JE::Point(std::fmod(a.x, b), std::fmod(a.y, b));
}

JE::Point operator *(float a, const JE::Point& b){
	return JE::Point(b.x * a, b.y * a);
}

JE::Point operator /(float a, const JE::Point& b){
	return JE::Point(b.x / a, b.y / a);
}

JE::Point operator %(float a, const JE::Point& b){
	return JE::Point(std::fmod(b.x, a), std::fmod(b.y, a));
}

void Point::modulate(float value){
	this->x = std::fmod(this->x, value);
	this->y = std::fmod(this->y, value);
}

JE::Point Point::modulous(float value) const{
	return JE::Point(std::fmod(this->x, value), std::fmod(this->y, value));
}

JE::Point Point::clamp(float length) const{
	float dis = this->getDistance();
	if (dis > 1) dis = 1;
	return *this * dis / this->getDistance();
}

JE::Point Point::floor() const{
	return JE::Point(std::floor(this->x), std::floor(this->y));
}

JE::Point Point::ceil() const{
	return JE::Point(std::ceil(this->x), std::ceil(this->y));
}

JE::Point Point::round() const{
	return JE::Point(std::round(this->x), std::round(this->y));
}

float Point::getDistance() const{
	return this->getDistance(0, 0);
}

float Point::getDistance(float x, float y) const{
	return JE::MATH::distance(this->x, this->y, x, y);
}

float Point::getDistance(const JE::Point& p) const{
	return this->getDistance(p.x, p.y);
}

float Point::getAngle() const{
	return this->getAngle(0, 0);
}

float Point::getAngle(float x, float y) const{
	return JE::MATH::getAngle(x, y, this->x, this->y);
}

float Point::getAngle(const JE::Point& p) const{
	return this->getAngle(p.x, p.y);
}

void Point::getAsInt(int* x, int* y) const{
	if (x) *x = int(this->x);
	if (y) *y = int(this->y);
}

};
