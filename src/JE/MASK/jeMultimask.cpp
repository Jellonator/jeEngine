#include "JE/MASK/jeMultimask.h"
#include "JE/UTIL/jeMath.h"
#include <cmath>
namespace JE{ namespace MASK{

Multimask::Multimask(int x, int y) : JE::MASK::MaskList(x, y){
	this->stored_left = 0;
	this->stored_right = 0;
	this->stored_top = 0;
	this->stored_bottom = 0;
}

Multimask::~Multimask(){
	
}

MaskListIterator Multimask::getMaskList(int left, int top, int right, int bottom){
	MaskListIterator vec;
	
	for (auto& m : this->mask_vec){
		m->moveBy(this->getX(), this->getY());
		if (m->getRight() >= left 
		&&  m->getLeft() <= right 
		&&  m->getBottom() >= top
		&&  m->getTop() <= bottom){
			vec.addMask(m.get(), 0, 0);
		}
		m->moveBy(-this->getX(), -this->getY());
	}
	
	return vec;
}

MaskListIterator Multimask::getMaskListAll(){
	MaskListIterator vec;
	for (auto& m : this->mask_vec){
		vec.addMask(m.get(), 0, 0);
	}
	return vec;
}

int Multimask::getLeft() const{
	if (this->mask_vec.size() == 0) return this->getX();
	
	auto mask_iter = this->mask_vec.begin();
	int value = (*mask_iter)->getLeft();
	++mask_iter;
	
	for (; mask_iter != this->mask_vec.end(); ++ mask_iter){
		int new_value = (*mask_iter)->getLeft();
		if (mask_iter == this->mask_vec.begin() || new_value < value) value = new_value;
	}
	
	return value;
}

int Multimask::getRight() const{
	if (this->mask_vec.size() == 0) return this->getX();
		
	auto mask_iter = this->mask_vec.begin();
	int value = (*mask_iter)->getRight();
	++mask_iter;
	
	for (; mask_iter != this->mask_vec.end(); ++ mask_iter){
		int new_value = (*mask_iter)->getLeft();
		if (mask_iter == this->mask_vec.begin() || new_value > value) value = new_value;
	}
	
	return value;
}

int Multimask::getTop() const{
	if (this->mask_vec.size() == 0) return this->getY();
		
	auto mask_iter = this->mask_vec.begin();
	int value = (*mask_iter)->getTop();
	++mask_iter;
	
	for (; mask_iter != this->mask_vec.end(); ++ mask_iter){
		int new_value = (*mask_iter)->getTop();
		if (mask_iter == this->mask_vec.begin() || new_value < value) value = new_value;
	}
	
	return value;
}

int Multimask::getBottom() const{
	if (this->mask_vec.size() == 0) return this->getY();
		
	auto mask_iter = this->mask_vec.begin();
	int value = (*mask_iter)->getBottom();
	++mask_iter;
	
	for (; mask_iter != this->mask_vec.end(); ++ mask_iter){
		int new_value = (*mask_iter)->getBottom();
		if (mask_iter == this->mask_vec.begin() || new_value < value) value = new_value;
	}
	
	return value;
}

void Multimask::generateFromPoints(const std::vector<std::pair<int,int>>& points){
	if (points.size() == 0) return;
	if (points.size() == 1){
		this->addMask<PointMask>(points.front().first, points.front().second);
		return;
	}
	
	auto* previous = &points.back();
	int current_x = previous->first;
	int current_y = previous->second;
	
	for (std::vector<std::pair<int,int>>::const_iterator next = points.begin(); next != points.end(); ++next){
		int diff_x = std::abs(previous->first - next->first);
		int diff_y = std::abs(previous->second - next->second);
		int new_x = next->first;
		int new_y = next->second;
		
		while (current_x != new_x || current_y != new_y){
			//Only needs to move on x axis
			if (current_x != new_x && current_y == new_y){
				current_x = JE::MATH::linearTween(current_x, new_x, 1);
				
			//Only needs to move on y axis
			} else if (current_x == new_x && current_y != new_y){
				current_y = JE::MATH::linearTween(current_y, new_y, 1);
				
			//Pick axis to move on based on differences
			} else {
				int diff = std::abs(current_x-new_x)*diff_y - std::abs(current_y-new_y)*diff_x;
				//If X difference is greater than or equal to Y difference
				if (diff >= 0){
					current_x = JE::MATH::linearTween(current_x, new_x, 1);
				}
				//If Y difference is greater than or equal to X difference
				if (diff <= 0) {
					current_y = JE::MATH::linearTween(current_y, new_y, 1);
				} 
			}
			this->addMask<PointMask>(current_x, current_y);
		}
		
		previous = &*next;
	}
}

}}