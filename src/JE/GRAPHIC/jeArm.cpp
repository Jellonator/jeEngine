#include "JE/UTIL/jeMath.h"
#include "JE/GRAPHIC/jeGraphic.h"
#include "JE/GRAPHIC/jeArm.h"
#include <iostream>

namespace JE{namespace ARM{
//Armature constructor/destructor
Arm::Arm(float x, float y, float length) : JE::Point(x, y){
	this->angle = 0;
	this->length = length;
	this->prev_x = x;
	this->prev_y = y;
	this->prev_angle = 0;
	this->prev_length = length;
	this->relativeAngle = true;
	/*this->animation = std::make_shared<Animation>();
	this->current_animation = "";
	this->animation_position = 0;
	this->animation_loop = true;
	this->keyframe_time = 0;
	this->use_animation = false;
	this->playing = true;*/
}

Arm::Arm(float length) : JE::Point(0, 0){
	this->angle = 0;
	this->length = length;
	this->prev_x = 0;
	this->prev_y = 0;
	this->prev_angle = 0;
	this->prev_length = length;
	this->relativeAngle = true;
	/*this->animation = std::make_shared<Animation>();
	this->current_animation = "";
	this->animation_position = 0;
	this->animation_loop = true;
	this->keyframe_time = 0;
	this->use_animation = false;
	this->playing = true;*/
}

Arm::~Arm(){
}
void Arm::_resetArmPrevious(){
	this->prev_angle = this->angle;
	this->prev_length = this->length;
	this->prev_x = this->x;
	this->prev_y = this->y;
	for (auto arm : this->arm_vec){
		arm->_resetArmPrevious();
	}
}

void Arm::update(float dt){
}

//Armature functions
void Arm::setIsRelative(bool relative){
	this->relativeAngle = relative;
}
void Arm::getOffset(float* x, float* y){
	this->getHinge(x, y);
}
void Arm::getOffset(const std::string& name, float* x, float* y){
	this->getHinge(name, x, y);
}
void Arm::setLength(float length){
	this->length = length;
}
void Arm::setLength(const std::string& name, float length){
	auto arm = this->getArm(name);
	if (arm != nullptr) arm->setLength(length);
}
float Arm::getAngle(){
	if (!this->relativeAngle || this->parent.expired()){
		return this->angle;
	} else {
		auto p = this->parent.lock();
		return p->getAngle() + this->angle;
	}
}
float Arm::getAngle(const std::string& name){
	auto arm = this->getArm(name);
	if (arm != nullptr){
		return arm->getAngle();
	}
	return 0;
}
float Arm::getLength(){
	return this->length;
}
float Arm::getLength(const std::string& name){
	auto arm = this->getArm(name);
	if (arm != nullptr){
		return arm->getLength();
	}
	return 0;
}
void Arm::setOffset(float offset_x, float offset_y){
	this->x = offset_x;
	this->y = offset_y;
}
void Arm::setOffset(const std::string& name, float offset_x, float offset_y){
	auto arm = this->getArm(name);
	if (arm != nullptr) arm->setOffset(offset_x, offset_y);
}
void Arm::getEnd(float* x, float* y){
	float angle = this->getAngle();
	this->getHinge(x, y);
	*x += JE::MATH::Xangle(angle, this->length);
	*y += JE::MATH::Yangle(angle, this->length);
}
void Arm::getHinge(float* x, float* y){
	if (!this->parent.expired()){
		float temp_x, temp_y;
		this->parent.lock()->getEnd(&temp_x, &temp_y);
		if (this->relativeAngle){
			float temp_a = this->parent.lock()->getAngle();
			float dis = JE::MATH::distance(0, 0, this->x, this->y);
			float angle = JE::MATH::getAngle(0, 0, this->x, this->y) + temp_a;
			*x = JE::MATH::Xangle(angle, dis, temp_x);
			*y = JE::MATH::Yangle(angle, dis, temp_y);
		} else {
			*x = this->x + temp_x;
			*y = this->y + temp_y;
		}
	}else{
		*x = this->x;
		*y = this->y;
	}
}
void Arm::getHingeLocal(float* x, float* y){
	*x = this->x;
	*y = this->y;
}
void Arm::getEndLocal(float* x, float* y){
	float angle = this->getAngle();
	*x = JE::MATH::Xangle(angle, this->length, this->x);
	*y = JE::MATH::Yangle(angle, this->length, this->y);
}
void Arm::getEnd(const std::string& name, float* x, float* y){
	auto arm = this->getArm(name);
	if (arm != nullptr) arm->getEnd(x, y);
}
void Arm::getHinge(const std::string& name, float* x, float* y){
	auto arm = this->getArm(name);
	if (arm != nullptr) arm->getHinge(x, y);
}
std::shared_ptr<Arm> Arm::newArm(const std::string& name, float angle, float length, float offset_x, float offset_y){
	size_t seperator = name.find('.');
	if (seperator != name.npos){
		std::string self_name = name.substr(0, seperator);
		std::string pass_name = name.substr(seperator+1, name.npos);
		auto arm = this->getArm(self_name);
		if (arm == nullptr) return nullptr;
		return arm->newArm(pass_name, angle, length, offset_x, offset_y);
	}else{
		auto arm = std::make_shared<Arm>(offset_x, offset_y, length);
		arm->parent = shared_from_this();
		arm->setAngle(angle);
		this->arm_map[name] = arm;
		this->arm_vec.push_back(arm);
		return arm;
	}
	return nullptr;
}
std::shared_ptr<Arm> Arm::getArm(const std::string& name){
	if (name == "") return shared_from_this();
	size_t seperator = name.find('.');
	if (seperator != name.npos){
		std::string self_name = name.substr(0, seperator);
		std::string pass_name = name.substr(seperator+1, name.npos);
		if (this->arm_map.count(self_name) == 0) return nullptr;
		return this->arm_map[self_name]->getArm(pass_name);
	}else{
		if (this->arm_map.count(name) == 0) return nullptr;
		return this->arm_map[name];
	}
}
std::shared_ptr<Arm> Arm::getArm(int ID){
	if (ID >= (int)this->arm_vec.size() || ID < 0) return nullptr;
	return this->arm_vec[ID];
}
std::shared_ptr<Arm> Arm::operator[](const std::string& name){
	return this->getArm(name);
}
std::shared_ptr<Arm> Arm::operator[](int ID){
	return this->getArm(ID);
}
void Arm::draw(float x, float y){
	float end_x, end_y, start_x, start_y;
	this->getHinge(&start_x, &start_y);
	this->getEnd(&end_x, &end_y);
	//JE::GRAPHICS::drawLine(start_x + x, start_y + y, end_x + x, end_y + y);
	//JE::GRAPHICS::drawRect(start_x - 1 + x, start_y - 1 + y, 2, 2, true);
	//JE::GRAPHICS::drawRect(end_x - 1 + x, end_y - 1 + y, 2, 2, true);
	for (auto& arm : this->arm_vec){
		//const std::shared_ptr<Arm>& arm = this->getArm(i);
		arm->draw(x, y);
	}
}
void Arm::rotate(float angle){
	this->angle += angle;
}
void Arm::setAngle(float angle){
	this->angle = angle;
}
void Arm::rotate(const std::string& name, float angle){
	auto arm = this->getArm(name);
	if (arm != nullptr) arm->rotate(angle);
}
void Arm::setAngle(const std::string& name, float angle){
	auto arm = this->getArm(name);
	if (arm != nullptr) arm->setAngle(angle);
}
}}

