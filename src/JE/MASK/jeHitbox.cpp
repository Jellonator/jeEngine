#include "JE/MASK/jeHitbox.h"

namespace JE{ namespace MASK{

Hitbox::Hitbox(int x1, int y1, int x2, int y2) : Mask(0, 0){
	this->x1 = x1;
	this->x2 = x2;
	this->y1 = y1;
	this->y2 = y2;
}

Hitbox::~Hitbox(){
	
}

bool Hitbox::getCollide(const PointMask& point, int move_x, int move_y, int* out_x, int* out_y){
	bool ret = false;
	int new_x = point.getX() + move_x;
	int new_y = point.getY();
	if (){
		
	}
	return true;
}

bool Hitbox::getCollide(const Hitbox& point, int move_x, int move_y, int* out_x, int* out_y){
	return true;
}

int Hitbox::getWidth() const{
	return this->x2 - this->x1 + 1;
}

int Hitbox::getHeight() const{
	return this->y2 - this->y1 + 1;
}

int Hitbox::getLeft() const{
	return this->x1 + this->getX();
}

int Hitbox::getRight() const{
	return this->x2 + this->getX();
}

int Hitbox::getTop() const{
	return this->y1 + this->getY();
}

int Hitbox::getBottom() const{
	return this->y2 + this->getY();
}

int Hitbox::getX1() const{
	return this->x1;
}

int Hitbox::getY1() const{
	return this->y1;
}

int Hitbox::getX2() const{
	return this->x2;
}

int Hitbox::getY2() const{
	return this->y2;
}

bool Hitbox::containsPoint(int x, int y) const{
	return (x >= this->getLeft() && x <= this->getRight() && y >= this->getTop() && y <= this->getBottom());
}

bool Hitbox::containsPointStretch(int x, int y, int move_x, int move_y) const{
	int x1, y1, x2, y2;
	this->getStretch(x1, y1, x2, y2, move_x, move_y);
	return (x >= x1 && x <= x2 && y >= y1 && y <= y2);
}

void Hitbox::getStretch(int& x1, int& y1, int& x2, int& y2, int move_x, int move_y) const{
	x1 = this->getLeft();
	x2 = this->getRight();
	y1 = this->getTop();
	y2 = this->getBottom();
	
	if (move_x < 0) x1 += move_x;
	else x2 += move_x;
	
	if (move_y < 0) y1 += move_y;
	else y2 += move_y;
}

bool Hitbox::containsRect(int x1, int y1, int x2, int y2) const{
	if (x2 < this->getX1()
	||  x1 > this->getX2()
	||  y2 < this->getY1()
	||  y1 > this->getY2()) return false;
	return true;
}

bool Hitbox::containsRect(const Hitbox& rect) const{
	return this->containsRect(rect.getX1(), rect.getY1(), rect.getX2(), rect.getY2());
}

}}