#pragma once
#include "jeKeyFrame.h"
#include "jeAnimation.h"
#include "../../UTIL/jeTime.h"
#include "../../jePoint.h"
#include <map>
#include <vector>
#include <memory>
#include <string>

namespace JE{namespace ARM{
	class Keyframe;
	class Animation;
class Arm : public JE::Point, public std::enable_shared_from_this<Arm>
{
public:
	friend Keyframe;
	Arm(float x, float y, float length);
	Arm(float length = 0);
	virtual ~Arm();
	float angle;
	float length;
	bool relativeAngle;
	
	//set variables
	void rotate(float angle);
	void setAngle(float angle);
	void setLength(float length);
	void setOffset(float offset_x, float offset_y);
	void setIsRelative(bool relative);
	
	//fail-safe child setters
	void rotate(const std::string& name, float angle);
	void setAngle(const std::string& name, float angle);
	void setLength(const std::string& name, float length);
	void setOffset(const std::string& name, float offset_x, float offset_y);
	
	//get variables
	float getLength();
	float getAngle();
	void getOffset(float* x, float* y);
	void getEnd(float* x, float* y);
	void getHinge(float* x, float* y);
	//bool isPlaying();
	
	//fail-safe child getters
	float getLength(const std::string& name);
	float getAngle(const std::string& name);
	void getOffset(const std::string& name, float* x, float* y);
	void getEnd(const std::string& name, float* x, float* y);
	void getHinge(const std::string& name, float* x, float* y);
	
	//get arms(operator is kinda useless but whatever)
	std::shared_ptr<Arm> getArm(const std::string& name);
	std::shared_ptr<Arm> getArm(int ID);
	std::shared_ptr<Arm> operator[](const std::string& name);
	std::shared_ptr<Arm> operator[](int ID);
	
	//debug draw for armature system
	void draw(float x = 0, float y = 0);
	
	//create a new arm with the name, can create arms in children. Arm is not created if the parent does not exist
	std::shared_ptr<Arm> newArm(const std::string& name, float angle, float length, float offset_x = 0, float offset_y = 0);
	
	//update
	void update(float dt = JE::TIME::dt);
	
private:
	//previous values
	float prev_x;
	float prev_y;
	float prev_angle;
	float prev_length;
	void _resetArmPrevious();
	
	//storage for child arms
	std::map<std::string, std::shared_ptr<Arm>> arm_map;
	std::vector<std::shared_ptr<Arm>> arm_vec;
	
	//private functions for non-relative positions
	void getHingeLocal(float* x, float* y);
	void getEndLocal(float* x, float* y);
	
	//parent
	std::weak_ptr<Arm> parent;
};
}}

