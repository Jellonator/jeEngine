#include "JE/jeMask.h"
#include "JE/MASK/jeHitbox.h"
#include "JE/MASK/jeMaskList.h"
#include "JE/GRAPHIC/jeGraphic.h"

namespace JE{ namespace MASK{
	
Mask::Mask(int x, int y){
	this->x = x;
	this->y = y;
}

Mask::~Mask(){
	
}

bool Mask::callCollide(Hitbox& box, int move_x, int move_y, int* out_x, int* out_y){
	return box.getCollide(*this, move_x, move_y, out_x, out_y);
}

bool Mask::callCollide(PointMask& point, int move_x, int move_y, int* out_x, int* out_y){
	return point.getCollide(*this, move_x, move_y, out_x, out_y);
}

bool Mask::callCollide(MaskList& mask_list, int move_x, int move_y, int* out_x, int* out_y){
	return mask_list.getCollide(*this, move_x, move_y, out_x, out_y);
}

bool Mask::getCollide(MaskList& mask_list, int move_x, int move_y, int* out_x, int* out_y){
	int output_x = mask_list.getX() + move_x;
	int output_y = mask_list.getY() + move_y;
	int current_x = mask_list.getX();
	int current_y = mask_list.getY();
	bool ret = false;

	MaskListIterator mask_iter = mask_list.getMaskListAll();
	
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

bool Mask::getCollide(PointMask& point, int move_x, int move_y, int* out_x, int* out_y){
	int current_x = point.x;
	int current_y = point.y;
	int new_x = point.x + move_x;
	int new_y = point.y + move_y;
	bool ret = false;
	
	//movement x
	if (       move_x > 0 && current_x < this->x && new_x >= this->x && current_y == this->y){
		current_x = this->x - 1;
		ret = true;
		
	} else if (move_x < 0 && current_x > this->x && new_x <= this->x && current_y == this->y) {
		current_x = this->x + 1;
		ret = true;
		
	} else {
		current_x = new_x;
	}
	
	//movement y
	if (       move_y > 0 && current_y < this->y && new_y >= this->y && current_x == this->x){
		current_y = this->y - 1;
		ret = true;
		
	} else if (move_y < 0 && current_y > this->y && new_y <= this->y && current_x == this->x) {
		current_y = this->y + 1;
		ret = true;
		
	} else {
		current_y = new_y;
	}
	
	if (out_x) *out_x = current_x;
	if (out_y) *out_y = current_y;
	
	return ret;
}

bool Mask::getCollide(Hitbox& box, int move_x, int move_y, int* out_x, int* out_y){
	Hitbox duplicate = box;
	bool ret = false;
	
	if (duplicate.containsPointStretch(this->x, this->y, move_x, 0)){
		ret = true;
		if (move_x > 0){
			duplicate.setX(this->x - duplicate.getX2() - 1);
		} else {
			duplicate.setX(this->x - duplicate.getX1() + 1);
		}
	} else {
		duplicate.moveBy(move_x, 0);
	}
	
	if (duplicate.containsPointStretch(this->x, this->y, 0, move_y)){
		ret = true;
		if (move_y > 0){
			duplicate.setY(this->y - duplicate.getY2() - 1);
		} else {
			duplicate.setY(this->y - duplicate.getY1() + 1);
		}
	} else {
		duplicate.moveBy(0, move_y);
	}
	
	if (out_x) *out_x = duplicate.getX();
	if (out_y) *out_y = duplicate.getY();
	
	return ret;
}

void Mask::moveBy(int x, int y){
	this->x += x;
	this->y += y;
}

void Mask::moveTo(int x, int y){
	this->x = x;
	this->y = y;
}

int Mask::getX() const {
	return this->x;
}

int Mask::getY() const {
	return this->y;
}

int* Mask::ptrX(){
	return &this->x;
}

int* Mask::ptrY(){
	return &this->y;
}

int Mask::getLeft() const {
	return this->x;
}

int Mask::getRight() const {
	return this->x;
}

int Mask::getTop() const {
	return this->y;
}

int Mask::getBottom() const {
	return this->y;
}

void Mask::setX(int value){
	this->x = value;
}

void Mask::setY(int value){
	this->y = value;
}

void Mask::draw(int x, int y){
	JE::GRAPHICS::drawRect(this->getX() + x, this->getY() + y, 1, 1, true);
}

}}