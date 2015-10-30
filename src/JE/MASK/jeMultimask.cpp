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

bool isPointInsideTriangle (float x, float y, float x1, float y1, float x2, float y2, float x3, float y3){
	float s = y1 * x3 - x1 * y3 + (y3 - y1) * x + (x1 - x3) * y;
	float t = x1 * y2 - y1 * x2 + (y1 - y2) * x + (x2 - x1) * y;

	if ((s < 0) != (t < 0))
		return false;

	float A = -y2 * x3 + y1 * (x3 - x2) + x1 * (y2 - y3) + x2 * y3;
	if (A < 0.0){
		s = -s;
		t = -t;
		A = -A;
	}
	return s > 0 && t > 0 && (s + t) < A;
}

void Multimask::generateFromPoints(int x1, int y1, int x2, int y2, int x3, int y3){
	int x_left  = std::min(std::min(x1, x2), x3);
	int x_right = std::max(std::max(x1, x2), x3);
	int y_top   = std::min(std::min(y1, y2), y3);
	int y_bottom= std::max(std::max(y1, y2), y3);
	
	for (int iter_x = x_left; iter_x <= x_right; ++iter_x){
	for (int iter_y = y_top; iter_y <= y_bottom; ++iter_y){
		if (isPointInsideTriangle(iter_x, iter_y, x1,y1, x2,y2, x3,y3)){
			this->addMask<PointMask>(iter_x, iter_y);
		}
	}
	}
}

}}