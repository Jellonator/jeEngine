#include "JE/MASK/jeMaskList.h"
#include "JE/MASK/jeHitbox.h"
#include "JE/GRAPHIC/jeGraphic.h"
#include <algorithm>

namespace JE{ namespace MASK{

MaskList::MaskList(int x, int y) : JE::MASK::Mask(x, y){
	this->get_bottom = y;
	this->get_top = y;
	this->get_left = x;
	this->get_right = x;
}

MaskList::~MaskList(){
	
}

/*
 * There is a *slight* difference between this function and the function declared in jeMask.
 * Using '*this' here will allow the object to call a function based on what 'this' is.
 * In this case, 'this' refers to a MaskList. If this function were to not be declared,
 * then the other object would think this was a Mask.
 */
bool MaskList::getCollide(MaskList& mask_list, int move_x, int move_y, int* out_x, int* out_y){
	std::vector<Mask*> mask_vec = mask_list.getMaskListAll();
	int output_x = mask_list.getX() + move_x;
	int output_y = mask_list.getY() + move_y;
	int current_x = mask_list.getX();
	int current_y = mask_list.getY();
	bool ret = false;
	
	for (auto mask : mask_vec){
		int temp_x;
		
		mask->moveBy(current_x, current_y);
		bool did_collide = mask->callCollide(*this, move_x, 0, &temp_x, nullptr);
		if (did_collide){
			ret = true;
			move_x = temp_x - mask->getX();
			output_x = mask_list.getX() + move_x;
		}
		mask->moveBy(-current_x, -current_y);
	}
	
	for (auto mask : mask_vec){
		int temp_y;
		
		mask->moveBy(current_x, current_y);
		bool did_collide = mask->callCollide(*this, 0, move_y, nullptr, &temp_y);
		if (did_collide){
			ret = true;
			move_y = temp_y - mask->getY();
			output_y = mask_list.getY() + move_y;
		}
		mask->moveBy(-current_x, -current_y);
	}
	
	if (out_x) *out_x = output_x;
	if (out_y) *out_y = output_y;
	
	return ret;
}

bool MaskList::getCollide(Hitbox& box, int move_x, int move_y, int* out_x, int* out_y){
	bool ret = false;
	
	Hitbox new_box = box;
	int current_x = new_box.getX() + move_x;
	int current_y = new_box.getY() + move_y;
	
	auto mask_vector = this->getMaskListMove(new_box.getLeft(), new_box.getTop(), new_box.getRight(), new_box.getBottom(), move_x, move_y);
	
	for (auto m : mask_vector){
		int temp_x;
		m->moveBy(this->getX(), this->getY());
		if (m->getCollide(new_box, move_x, 0, &temp_x, nullptr)){
			ret = true;
			if (std::abs(temp_x - new_box.getX()) < std::abs(current_x - new_box.getX())){
				current_x = temp_x;
				new_box.setX(temp_x);
			}
		}
		m->moveBy(-this->getX(), -this->getY());
	}
	
	for (auto m : mask_vector){
		int temp_y;
		m->moveBy(this->getX(), this->getY());
		if (m->getCollide(new_box, 0, move_y, nullptr, &temp_y)){
			ret = true;
			if (std::abs(temp_y - new_box.getY()) < std::abs(current_y - new_box.getY())){
				current_y = temp_y;
				new_box.setY(temp_y);
			}
		}
		m->moveBy(-this->getX(), -this->getY());
	}
	
	if (out_x) *out_x = current_x;
	if (out_y) *out_y = current_y;
	
	return ret;
}

bool MaskList::getCollide(PointMask& point, int move_x, int move_y, int* out_x, int* out_y){
	bool ret = false;
	
	PointMask new_point = point;
	int current_x = point.getX() + move_x;
	int current_y = point.getY() + move_y;
	
	for (auto m : this->getMaskListMove(new_point.getLeft(), new_point.getTop(), new_point.getRight(), new_point.getBottom(), move_x, 0)){
		int temp_x;
		m->moveBy(this->getX(), this->getY());
		if (m->getCollide(new_point, move_x, 0, &temp_x, nullptr)){
			ret = true;
			if (std::abs(temp_x - new_point.getX()) < std::abs(current_x - new_point.getX())){
				new_point.setX(temp_x);
				current_x = temp_x;
			}
		}
		m->moveBy(-this->getX(), -this->getY());
	}
	
	for (auto m : this->getMaskListMove(new_point.getLeft(), new_point.getTop(), new_point.getRight(), new_point.getBottom(), 0, move_y)){
		int temp_y;
		m->moveBy(this->getX(), this->getY());
		if (m->getCollide(new_point, 0, move_y, nullptr, &temp_y)){
			ret = true;
			if (std::abs(temp_y - new_point.getY()) < std::abs(current_y - new_point.getY())){
				current_y = temp_y;
				new_point.setY(temp_y);
			}
		}
		m->moveBy(-this->getX(), -this->getY());
	}
	
	if (out_x) *out_x = current_x;
	if (out_y) *out_y = current_y;
	
	return ret;
}

bool MaskList::callCollide(Hitbox& box, int move_x, int move_y, int* out_x, int* out_y){
	return box.getCollide(*this, move_x, move_y, out_x, out_y);
}

bool MaskList::callCollide(PointMask& point, int move_x, int move_y, int* out_x, int* out_y){
	return point.getCollide(*this, move_x, move_y, out_x, out_y);
}

bool MaskList::callCollide(MaskList& mask_list, int move_x, int move_y, int* out_x, int* out_y){
	return mask_list.getCollide(*this, move_x, move_y, out_x, out_y);
}

std::vector<Mask*> MaskList::getMaskList(int left, int top, int right, int bottom){
	std::vector<Mask*> iter;
	
	return iter;
}

std::vector<Mask*> MaskList::getMaskListMove(int left, int top, int right, int bottom, int move_x, int move_y){
	return this->getMaskList(
		left   + std::min(0, move_x), 
		top    + std::min(0, move_y),
		right  + std::max(0, move_x),
		bottom + std::max(0, move_y)
	);
}

std::vector<Mask*> MaskList::getMaskListAll(){
	std::vector<Mask*> iter;
	return iter;
}

void MaskList::draw(int x, int y){
	for (auto child : this->getMaskListAll()){
		child->draw(x + this->getX(), y + this->getY());
	}
}

void MaskList::updateGetters(){
	auto vec_list = this->getMaskListAll();
	bool first = true;
	
	for (auto mask : vec_list){
		if (first){
			first = false;
			this->get_left  = mask->getLeft();
			this->get_right = mask->getRight();
			this->get_top   = mask->getTop();
			this->get_bottom= mask->getBottom();
		} else {
			this->get_left  = std::min(mask->getLeft(),  this->get_left);
			this->get_right = std::max(mask->getRight(), this->get_right);
			this->get_top   = std::min(mask->getTop(),   this->get_top);
			this->get_bottom= std::max(mask->getBottom(),this->get_bottom);
		}
	}
}

int MaskList::getLeft() const{
	return this->getX() + this->get_left;
}

int MaskList::getRight() const{
	return this->getX() + this->get_right;
}

int MaskList::getTop() const{
	return this->getY() + this->get_top;
}

int MaskList::getBottom() const{
	return this->getY() + this->get_bottom;
}

}}