#pragma once
#include <string>
#include <map>
#include <memory>
#include "../../jePoint.h"
#include "jeArm.h" 
namespace JE{namespace ARM{
	class Arm;
	class Keyframe{public:
		friend Arm;
		Keyframe();
		virtual ~Keyframe();
		std::map<std::string, float> data_angle;
		std::map<std::string, float> data_length;
		std::map<std::string, Point> data_pos;
		
		void setData(const std::string& label, float angle, float length, float x = 0, float y = 0);
		void setAngle(const std::string& label, float angle);
		void setLength(const std::string& label, float length);
		void setOffset(const std::string& label, float x, float y);
		void setTime(float t);
		
		void apply(const std::shared_ptr<Arm>& arm);
		void apply(const std::shared_ptr<Arm>& arm, float value);
		
		void setSpeed(float speed);
		void setAngleSpeed(float speed);
		void setLengthSpeed(float speed);
		void setOffsetSpeed(float speed);
		
		void reset();
		//void addLength(std::string name, float length);
		//void 
	private:
		float speed;
		float speed_angle;
		float speed_length;
		float speed_offset;
		
		//float time;
		
		void _add(const std::shared_ptr<Keyframe>& frame);
	};
}}