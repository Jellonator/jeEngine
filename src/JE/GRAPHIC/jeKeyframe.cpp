#include "../UTIL/jeMath.h"
#include "jeKeyframe.h"
#include <iostream>

namespace JE{namespace ARM{
	Keyframe::Keyframe(){
		this->speed = 1;
		this->speed_angle = 1;
		this->speed_length = 1;
		this->speed_offset = 1;
		//this->time = 1;
	}
	Keyframe::~Keyframe(){
		
	}
	
	void Keyframe::reset(){
		this->speed = 1;
		this->speed_angle = 1;
		this->speed_length = 1;
		this->speed_offset = 1;
		this->data_angle.clear();
		this->data_length.clear();
		this->data_pos.clear();
	}
	
	//wow I keep mispelling 'label' as 'lavel' and 'labal'
	void Keyframe::setData(std::string label, float angle, float length, float x, float y){
		this->setAngle(label, angle);
		this->setLength(label, length);
		this->setOffset(label, x, y);
	}
	void Keyframe::setAngle(std::string label, float angle){
		this->data_angle[label] = angle;
	}
	void Keyframe::setLength(std::string label, float length){
		this->data_length[label] = length;
	}
	void Keyframe::setOffset(std::string label, float x, float y){
		this->data_pos[label].x = x;
		this->data_pos[label].y = y;
	}
	
	void Keyframe::setSpeed(float speed){
		this->speed = speed;
	}
	void Keyframe::setAngleSpeed(float speed){
		this->speed_angle = speed;
	}
	void Keyframe::setLengthSpeed(float speed){
		this->speed_length = speed;
	}
	void Keyframe::setOffsetSpeed(float speed){
		this->speed_offset = speed;
	}
	
	void Keyframe::apply(const std::shared_ptr<Arm>& arm){
		typedef std::map<std::string, float>::iterator it_type;
		for(it_type iterator = this->data_angle.begin(); iterator != this->data_angle.end(); iterator++) {
			arm->setAngle(iterator->first, iterator->second);
		}
		for(it_type iterator = this->data_length.begin(); iterator != this->data_length.end(); iterator++) {
			//std::cout << "Length for " << iterator->first << ":" << iterator->second << std::endl;
			arm->setLength(iterator->first, iterator->second);
		}
		typedef std::map<std::string, JE::Point>::iterator it_type_pos;
		for(it_type_pos iterator = this->data_pos.begin(); iterator != this->data_pos.end(); iterator++) {
			arm->setOffset(iterator->first, iterator->second.x, iterator->second.y);
		}
	}
	void Keyframe::apply(const std::shared_ptr<Arm>& arm, float value){
		value *= this->speed;
		typedef std::map<std::string, float>::iterator it_type;
		for(it_type iterator = this->data_angle.begin(); iterator != this->data_angle.end(); iterator++) {
			auto child = arm->getArm(iterator->first);
			float from_angle = child->angle;//arm->getAngle(iterator->first);
			float to_angle = iterator->second;
			float angle = JE::MATH::angleTo(from_angle, to_angle, value * this->speed_angle);
			child->setAngle(angle);
		}
		for(it_type iterator = this->data_length.begin(); iterator != this->data_length.end(); iterator++) {
			auto child = arm->getArm(iterator->first);
			float from_length = child->getLength();
			float to_length = iterator->second;
			child->setLength(JE::MATH::linearTween(from_length, to_length, value * this->speed_length));
		}
		typedef std::map<std::string, JE::Point>::iterator it_type_pos;
		for(it_type_pos iterator = this->data_pos.begin(); iterator != this->data_pos.end(); iterator++) {
			auto child = arm->getArm(iterator->first);
			float to_x = iterator->second.x;
			float to_y = iterator->second.y;
			child->moveToLinear(to_x, to_y, 1, value * this->speed_offset);
			//arm->setOffset(to_x*to + from_x*from, to_y*to + from_y*from);
		}
	}
	void Keyframe::_add(const std::shared_ptr<Keyframe>& frame){
		typedef std::map<std::string, float>::iterator it_type;
		for(it_type iterator = frame->data_angle.begin(); iterator != frame->data_angle.end(); iterator++) {
			this->data_angle[iterator->first] += iterator->second;
		}
		for(it_type iterator = frame->data_length.begin(); iterator != frame->data_length.end(); iterator++) {
			this->data_length[iterator->first] += iterator->second;
		}
		typedef std::map<std::string, JE::Point>::iterator it_type_pos;
		for(it_type_pos iterator = frame->data_pos.begin(); iterator != frame->data_pos.end(); iterator++) {
			this->data_pos[iterator->first].x += iterator->second.x;
			this->data_pos[iterator->first].y += iterator->second.y;
		}
	}
}}