#include "JE/MASK/jeMultimask.h"

namespace JE{ namespace MASK{

Multimask::Multimask(int x, int y) : JE::MASK::Maskiterator(x, y){
	
}

Multimask::~Multimask(){
	
}

std::vector<Mask*> Multimask::getMaskList(int left, int top, int right, int bottom){
	std::vector<Mask*> vec;
	
	for (auto& m : this->mask_vec){
		m->moveBy(this->getX(), this->getY());
		if (m->getRight() >= left 
		&&  m->getLeft() <= right 
		&&  m->getBottom() >= top
		&&  m->getTop() <= bottom){
			vec.push_back(m.get());
		}
		m->moveBy(-this->getX(), -this->getY());
	}
	
	return vec;
}

std::vector<Mask*> Multimask::getMaskListAll(){
	std::vector<Mask*> vec;
	for (auto& m : this->mask_vec){
		vec.push_back(m.get());
	}
	return vec;
}

int Multimask::getLeft() const{
	if (this->mask_vec.size() == 0) return this->getX();
	
	auto mask_iter = this->mask_vec.begin();
	int value = (*mask_iter)->getLeft();
	++mask_iter;
	
	for (mask_iter; mask_iter != this->mask_vec.end(); ++ mask_iter){
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
	
	for (mask_iter; mask_iter != this->mask_vec.end(); ++ mask_iter){
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
	
	for (mask_iter; mask_iter != this->mask_vec.end(); ++ mask_iter){
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
	
	for (mask_iter; mask_iter != this->mask_vec.end(); ++ mask_iter){
		int new_value = (*mask_iter)->getBottom();
		if (mask_iter == this->mask_vec.begin() || new_value < value) value = new_value;
	}
	
	return value;
}

}}