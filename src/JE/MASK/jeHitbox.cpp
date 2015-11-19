#include "JE/MASK/jeHitbox.h"
#include "JE/MASK/jeMaskList.h"
#include "JE/GRAPHIC/jeGraphic.h"
#include <algorithm>

namespace JE{ namespace MASK{

Hitbox::Hitbox(int x1, int y1, int x2, int y2) : Mask(0, 0){
	this->x1 = x1;
	this->x2 = x2;
	this->y1 = y1;
	this->y2 = y2;
}

Hitbox::Hitbox(int x, int y, int x1, int y1, int x2, int y2) : Mask(x, y){
	this->x1 = x1;
	this->x2 = x2;
	this->y1 = y1;
	this->y2 = y2;
}

Hitbox::~Hitbox(){
	
}

bool Hitbox::callCollide(Hitbox& box, int move_x, int move_y, int* out_x, int* out_y){
	return box.getCollide(*this, move_x, move_y, out_x, out_y);
}

bool Hitbox::callCollide(PointMask& point, int move_x, int move_y, int* out_x, int* out_y){
	return point.getCollide(*this, move_x, move_y, out_x, out_y);
}

bool Hitbox::callCollide(MaskList& mask_list, int move_x, int move_y, int* out_x, int* out_y){
	return mask_list.getCollide(*this, move_x, move_y, out_x, out_y);
}

/*
 * There is a *slight* difference between this function and the function declared in jeMask.
 * Using '*this' here will allow the object to call a function based on what 'this' is.
 * In this case, 'this' refers to a Hitbox. If this function were to not be declared,
 * then the other object would think this was a Mask.
 */
bool Hitbox::getCollide(MaskList& mask_list, int move_x, int move_y, int* out_x, int* out_y){
	int output_x = mask_list.getX() + move_x;
	int output_y = mask_list.getY() + move_y;
	int current_x = mask_list.getX();
	int current_y = mask_list.getY();
	bool ret = false;

	MaskListIterator mask_iter = mask_list.getMaskListMove(this->getLeft(), this->getTop(), this->getRight(), this->getBottom(), -move_x, -move_y);
	
	int offset_x, offset_y;
	while (Mask* current_mask = mask_iter.get_next(&offset_x, &offset_y)){
		offset_x += current_x;
		offset_y += current_y;
		
		int temp_x;
		
		current_mask->moveBy(offset_x, offset_y);
		bool did_collide = current_mask->callCollide(*this, move_x, 0, &temp_x, nullptr);
		if (did_collide){
			ret = true;
			move_x = temp_x - current_mask->getX();
			output_x = mask_list.getX() + move_x;
		}
		
		current_mask->moveBy(-offset_x, -offset_y);
	}
	current_x = output_x;
	
	mask_iter.reset();
	while (Mask* current_mask = mask_iter.get_next(&offset_x, &offset_y)){
		offset_x += current_x;
		offset_y += current_y;
		
		int temp_y;
		
		current_mask->moveBy(offset_x, offset_y);
		bool did_collide = current_mask->callCollide(*this, 0, move_y, nullptr, &temp_y);
		if (did_collide){
			ret = true;
			move_y = temp_y - current_mask->getY();
			output_y = mask_list.getY() + move_y;
		}
		current_mask->moveBy(-offset_x, -offset_y);
	}
	
	if (out_x) *out_x = output_x;
	if (out_y) *out_y = output_y;
	
	return ret;
}

bool Hitbox::getCollide(PointMask& point, int move_x, int move_y, int* out_x, int* out_y){
	bool ret = false;
	int new_x = point.getX() + move_x;
	int new_y = point.getY();
	
	if (this->containsRect(
		std::min(point.getX(), new_x), 
		std::min(point.getY(), new_y), 
		std::max(point.getX(), new_x), 
		std::max(point.getY(), new_y)
	)){
		ret = true;
		if (move_x > 0){
			new_x = this->getLeft() - 1;
		} else {
			new_x = this->getRight() + 1;
		}
	}
	
	new_y += move_y;
	if (this->containsRect(
		std::min(point.getX(), new_x), 
		std::min(point.getY(), new_y), 
		std::max(point.getX(), new_x), 
		std::max(point.getY(), new_y)
	)){
		ret = true;
		if (move_y > 0){
			new_y = this->getTop() - 1;
		} else {
			new_y = this->getBottom() + 1;
		}
	}
	
	if (out_x) *out_x = new_x;
	if (out_y) *out_y = new_y;
	
	return ret;
}

bool Hitbox::getCollide(Hitbox& box, int move_x, int move_y, int* out_x, int* out_y){
	Hitbox duplicate = box;
	bool ret = false;
	
	if (this->containsRectStretch(duplicate, move_x, 0)){
		ret = true;
		if (move_x > 0){
			duplicate.setX(this->getLeft() - duplicate.getX2() - 1);
		} else {
			duplicate.setX(this->getRight() - duplicate.getX1() + 1);
		}
	} else {
		duplicate.moveBy(move_x, 0);
	}
	
	if (this->containsRectStretch(duplicate, 0, move_y)){
		ret = true;
		if (move_y > 0){
			duplicate.setY(this->getTop() - duplicate.getY2() - 1);
		} else {
			duplicate.setY(this->getBottom() - duplicate.getY1() + 1);
		}
	} else {
		duplicate.moveBy(0, move_y);
	}
	
	if (out_x) *out_x = duplicate.getX();
	if (out_y) *out_y = duplicate.getY();
	
	return ret;
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

bool Hitbox::containsRectStretch(const Hitbox& rect, int move_x, int move_y) const{
	int stretch_x1, stretch_y1, stretch_x2, stretch_y2;
	rect.getStretch(stretch_x1, stretch_y1, stretch_x2, stretch_y2, move_x, move_y);
	
	return this->containsRect(stretch_x1, stretch_y1, stretch_x2, stretch_y2);
}

bool Hitbox::containsRect(int x1, int y1, int x2, int y2) const{
	if (x2 < this->getLeft()
	||  x1 > this->getRight()
	||  y2 < this->getTop()
	||  y1 > this->getBottom()) return false;
	return true;
}

bool Hitbox::containsRect(const Hitbox& rect) const{
	return this->containsRect(rect.getX1(), rect.getY1(), rect.getX2(), rect.getY2());
}

void Hitbox::draw(int x, int y){
	JE::GRAPHICS::drawRect(this->getLeft() + x, this->getTop() + y, this->getWidth(), this->getHeight(), false);
}

}}