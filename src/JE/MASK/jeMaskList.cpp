#include "JE/MASK/jeMaskList.h"
#include "JE/MASK/jeHitbox.h"
#include "JE/GRAPHIC/jeGraphic.h"
#include <algorithm>

namespace JE{ namespace MASK{

MaskListIterator::MaskListIterator(){
	this->reset();
}

void MaskListIterator::reset(){
	this->mask_position = 0;
}

void MaskListIterator::addMask(Mask* mask, int x, int y){
	this->mask_vec.push_back(std::make_tuple(mask, x, y));
}

Mask* MaskListIterator::get_next(int* get_x, int* get_y){
	if (this->mask_position >= this->mask_vec.size()){
		return nullptr;
	}
	
	Mask* ret = std::get<0>(this->mask_vec[this->mask_position]);
	if (get_x) *get_x = std::get<1>(this->mask_vec[this->mask_position]);
	if (get_y) *get_y = std::get<2>(this->mask_vec[this->mask_position]);
	
	++ this->mask_position;
	
	return ret;
}

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

bool MaskList::getCollide(Hitbox& box, int move_x, int move_y, int* out_x, int* out_y){
	bool ret = false;
	
	Hitbox new_box = box;
	int current_x = box.getX() + move_x;
	int current_y = box.getY() + move_y;
	
	MaskListIterator mask_iter = this->getMaskListMove(new_box.getLeft(), new_box.getTop(), new_box.getRight(), new_box.getBottom(), move_x, move_y);
	
	int offset_x, offset_y;
	while (Mask* this_mask = mask_iter.get_next(&offset_x, &offset_y)){
		offset_x += this->getX();
		offset_y += this->getY();
		
		int temp_x;
		
		this_mask->moveBy(offset_x, offset_y);
		if (this_mask->getCollide(new_box, move_x, 0, &temp_x, nullptr)){
			ret = true;
			if (std::abs(temp_x - new_box.getX()) < std::abs(current_x - new_box.getX())){
				current_x = temp_x;
			}
		}
		this_mask->moveBy(-offset_x, -offset_y);
	}
	new_box.setX(current_x);
	
	mask_iter.reset();
	while (Mask* this_mask = mask_iter.get_next(&offset_x, &offset_y)){
		offset_x += this->getX();
		offset_y += this->getY();
		
		int temp_y;
		
		this_mask->moveBy(offset_x, offset_y);
		if (this_mask->getCollide(new_box, 0, move_y, nullptr, &temp_y)){
			ret = true;
			if (std::abs(temp_y - new_box.getY()) < std::abs(current_y - new_box.getY())){
				current_y = temp_y;
			}
		}
		this_mask->moveBy(-offset_x, -offset_y);
	}
	new_box.setY(current_y);
	
	if (out_x) *out_x = current_x;
	if (out_y) *out_y = current_y;
	
	return ret;
}

bool MaskList::getCollide(PointMask& point, int move_x, int move_y, int* out_x, int* out_y){
	bool ret = false;
	
	PointMask new_point = point;
	int current_x = point.getX() + move_x;
	int current_y = point.getY() + move_y;
	
	MaskListIterator mask_iter = this->getMaskListMove(new_point.getLeft(), new_point.getTop(), new_point.getRight(), new_point.getBottom(), move_x, move_y);
	
	int offset_x, offset_y;
	while (Mask* this_mask = mask_iter.get_next(&offset_x, &offset_y)){
		offset_x += this->getX();
		offset_y += this->getY();
		
		int temp_x;
		
		this_mask->moveBy(offset_x, offset_y);
		if (this_mask->getCollide(new_point, move_x, 0, &temp_x, nullptr)){
			ret = true;
			if (std::abs(temp_x - new_point.getX()) < std::abs(current_x - new_point.getX())){
				current_x = temp_x;
			}
		}
		this_mask->moveBy(-offset_x, -offset_y);
	}
	new_point.setX(current_x);
	
	mask_iter.reset();
	while (Mask* this_mask = mask_iter.get_next(&offset_x, &offset_y)){
		offset_x += this->getX();
		offset_y += this->getY();
		
		int temp_y;
		
		this_mask->moveBy(offset_x, offset_y);
		if (this_mask->getCollide(new_point, 0, move_y, nullptr, &temp_y)){
			ret = true;
			if (std::abs(temp_y - new_point.getY()) < std::abs(current_y - new_point.getY())){
				current_y = temp_y;
			}
		}
		this_mask->moveBy(-offset_x, -offset_y);
	}
	new_point.setY(current_y);
	
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

MaskListIterator MaskList::getMaskList(int left, int top, int right, int bottom){
	MaskListIterator iter;
	
	return iter;
}

MaskListIterator MaskList::getMaskListMove(int left, int top, int right, int bottom, int move_x, int move_y){
	return this->getMaskList(
		left   + std::min(0, move_x),
		top    + std::min(0, move_y),
		right  + std::max(0, move_x),
		bottom + std::max(0, move_y)
	);
}

MaskListIterator MaskList::getMaskListAll(){
	MaskListIterator iter;
	
	return iter;
}

void MaskList::draw(const JE::GRAPHICS::Camera& camera, int x, int y){
	MaskListIterator iter = this->getMaskListAll();
	int offset_x, offset_y;
	while (Mask* child = iter.get_next(&offset_x, &offset_y)){
		child->draw(camera, x + this->getX() + offset_x, y + this->getY() + offset_y);
	}
}

void MaskList::updateGetters(){
	MaskListIterator vec_list = this->getMaskListAll();
	bool first = true;
	
	int offset_x, offset_y;
	while (Mask* current_mask = vec_list.get_next(&offset_x, &offset_y)){
		current_mask->moveBy(offset_x, offset_y);
		if (first){
			first = false;
			this->get_left  = current_mask->getLeft();
			this->get_right = current_mask->getRight();
			this->get_top   = current_mask->getTop();
			this->get_bottom= current_mask->getBottom();
		} else {
			this->get_left  = std::min(current_mask->getLeft(),  this->get_left);
			this->get_right = std::max(current_mask->getRight(), this->get_right);
			this->get_top   = std::min(current_mask->getTop(),   this->get_top);
			this->get_bottom= std::max(current_mask->getBottom(),this->get_bottom);
		}
		current_mask->moveBy(-offset_x, -offset_y);
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