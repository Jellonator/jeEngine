#include "JE/GRAPHIC/ARMATURE/jeAnimation.h"
#include "JE/UTIL/jeMath.h"
#include <iostream>

namespace JE{namespace ARM{
// Animation data
	Animator::Animator(std::shared_ptr<Animation> anim){
		this->animation = anim;
		this->animation_loop = false;
		this->animation_name = "";
		this->animation_position = 0;
		this->animation_time = 0;
		this->animation_playing = false;
		this->temp_frame = std::make_shared<Keyframe>();
		this->frame_update = false;
	}
	Animator::~Animator(){
		
	}
	bool Animator::isPlaying(){
		return this->animation_playing;
	}
	void Animator::apply(const std::shared_ptr<Arm>& arm){
		int count = this->animation->getAnimLength(this->animation_name);
		if (count == 0) return;
		if (count == 1){
			std::shared_ptr<Keyframe> frame = this->animation->getKeyframe(this->animation->getFrameName(this->animation_name, 0));
			if (frame == nullptr) return;
			frame->apply(arm);
		} else {
			if (this->frame_update){
				std::string frame1, frame2;
				frame1 = this->animation->getFrameName(this->animation_name, this->animation_position);
				frame2 = this->animation->getFramePrev(this->animation_name, this->animation_position);
				float max_time = this->animation->getFrameTime(this->animation_name, this->animation_position);
				float a = JE::MATH::clamp(this->animation_time / max_time, 0.0f, 1.0f);
				float b = 1 - a;
				this->animation->mergeKeyframes({{frame1, a}, {frame2, b}}, this->temp_frame);
			}
			this->temp_frame->apply(arm);
		}
	}
	void Animator::update(float dt){
		if (!this->animation_playing) return;
		if (this->animation == nullptr) return;
		if (!this->animation->hasAnimation(this->animation_name)) return;
		if (this->animation_position >= this->animation->getAnimLength(this->animation_name)) return;
		this->animation_time += dt;
		//std::get<0> is frame name, std::get<1> is frame time
		while (this->animation_time >= this->animation->getFrameTime(this->animation_name, this->animation_position) && this->animation_playing){
			this->animation_time -= this->animation->getFrameTime(this->animation_name, this->animation_position);
			++this->animation_position;
			if (this->animation_position >= this->animation->getAnimLength(this->animation_name)){
				if (this->animation_loop){
					//return to 0
					this->animation_position = 0;
				} else {
					//set to back; stop playing
					this->animation_position = this->animation->getAnimLength(this->animation_name) - 1;
					this->animation_playing = false;
					this->animation_time = this->animation->getFrameTime(this->animation_name, this->animation_position);
				}
			}
		}
		this->frame_update = true;
	}
	void Animator::play(const std::string& name, bool loop, int start){
		if (this->animation_name == name) return;
		this->animation_name = name;
		this->animation_loop = loop;
		this->animation_position = start;
		this->animation_time = 0;
		this->animation_playing = true;
	}
//Animation
	Animation::Animation(){
		
	}
	
	Animation::~Animation(){
		
	}
	//Animation/keyframe functions
	bool Animation::hasKeyframe(const std::string& name){
		return (this->keyframe_map.count(name) > 0);
	}
	std::shared_ptr<Keyframe> Animation::getKeyframe(const std::string& name){
		if (!this->hasKeyframe(name)) return nullptr;
		return this->keyframe_map[name];
	}
	std::shared_ptr<Keyframe> Animation::newKeyframe(const std::string& name){
		std::shared_ptr<Keyframe> frame = std::make_shared<Keyframe>();
		this->keyframe_map[name] = frame;
		return frame;
	}
	void Animation::addKeyframe(const std::string& name, std::shared_ptr<Keyframe> frame){
		this->keyframe_map[name] = frame;
	}
	void Animation::apply(const std::shared_ptr<Arm>& arm, const std::string& name){
		std::shared_ptr<Keyframe> frame = this->getKeyframe(name);
		if (frame != nullptr){
			frame->apply(arm);
		}
	}
	void Animation::apply(const std::shared_ptr<Arm>& arm, const std::string& name, float ammount){
		std::shared_ptr<Keyframe> frame = this->getKeyframe(name);
		if (frame != nullptr){
			frame->apply(arm, ammount);
		}
	}
	float Animation::getFrameTime(const std::string& anim, int position){
		return std::get<1>(this->animation_map[anim][position]);
	}
	std::string Animation::getFrameName(const std::string& anim, int position){
		return std::get<0>(this->animation_map[anim][position]);
	}
	std::string Animation::getFramePrev(const std::string& anim, int position){
		--position;
		if (position < 0) position = this->getAnimLength(anim)-1;
		return this->getFrameName(anim, position);
	}
	int Animation::getAnimLength(const std::string& anim){
		return this->animation_map[anim].size();
	}
	void Animation::mergeKeyframes(std::vector<std::pair<std::string, float>> vec_frames, std::shared_ptr<Keyframe> ret_frame){
		ret_frame->reset();
		///Oh my god this function is a MESS
		//Not to mention it's not very lightweight either
		//Angles are dealt with via point notation, they will be converted back to an angle at the end of the function.
		std::map<std::string, float> map_points_angle;
		std::map<std::string, float> map_points_weight;
		std::map<std::string, float> map_length;
		std::map<std::string, JE::Point> map_offset;
		std::map<std::string, float> map_weights_length;
		std::map<std::string, float> map_weights_offset;
		for (auto& pair : vec_frames){
			if (!this->hasKeyframe(std::get<0>(pair))) continue;
			std::shared_ptr<Keyframe> frame = this->getKeyframe(std::get<0>(pair));
			float weight = std::get<1>(pair);
			
			typedef std::map<std::string, float>::iterator it_type;
			for(it_type iterator = frame->data_angle.begin(); iterator != frame->data_angle.end(); iterator++) {
				//JE::Point* p = &map_points_angle[iterator->first];
				//p->x += JE::MATH::Xangle(iterator->second, weight);
				//p->y += JE::MATH::Yangle(iterator->second, weight);
				map_points_weight[iterator->first] += weight;
				if (map_points_weight[iterator->first] == 0) map_points_angle[iterator->first] = iterator->second;
				else{
					map_points_angle[iterator->first] = JE::MATH::angleMix(map_points_angle[iterator->first], iterator->second, weight / map_points_weight[iterator->first]);
				}
			}
			for(it_type iterator = frame->data_length.begin(); iterator != frame->data_length.end(); iterator++) {
				map_length[iterator->first] += iterator->second * weight;
				map_weights_length[iterator->first] += weight; 
			}
			typedef std::map<std::string, JE::Point>::iterator it_type_pos;
			for(it_type_pos iterator = frame->data_pos.begin(); iterator != frame->data_pos.end(); iterator++) {
				JE::Point* p = &map_offset[iterator->first];
				p->x += iterator->second.x * weight;
				p->y += iterator->second.y * weight;
				map_weights_offset[iterator->first] += weight;
			}
		}
		typedef std::map<std::string, JE::Point>::iterator iter_string_point;
		typedef std::map<std::string, float>::iterator iter_string_float;
		for (iter_string_float iterator = map_points_angle.begin(); iterator != map_points_angle.end(); iterator++){
			ret_frame->setAngle(iterator->first, iterator->second);//JE::MATH::getAngle(0, 0, iterator->second.x, iterator->second.y));
		}
		for (iter_string_point iterator = map_offset.begin(); iterator != map_offset.end(); iterator++){
			float weight = map_weights_offset[iterator->first];
			float x = iterator->second.x;
			float y = iterator->second.y;
			if (weight != 0){
				x /= weight;
				y /= weight;
			} else {
				//shouldn't matter, since the numerator is probably 0 anyways
				std::cout << "Warning! Offset weight is 0!" << std::endl;
			}
			ret_frame->setOffset(iterator->first, x, y);
		}
		for (iter_string_float iterator = map_length.begin(); iterator != map_length.end(); iterator++){
			float weight = map_weights_length[iterator->first];
			float length = iterator->second;
			if (weight != 0){
				length /= weight;
			} else {
				//shouldn't matter, since the numerator is probably 0 anyways
				std::cout << "Warning! Length weight is 0!" << std::endl;
			}
			//std::cout << "Length for " << iterator->first << ":" << length << std::endl;
			ret_frame->setLength(iterator->first, length);
		}
	}
	std::shared_ptr<Keyframe> Animation::mergeKeyframes(std::vector<std::pair<std::string, float>> vec_frames){
		///Oh my god this function is a MESS
		//Not to mention it's not very lightweight either
		//Angles are dealt with via point notation, they will be converted back to an angle at the end of the function.
		std::map<std::string, float> map_points_angle;
		std::map<std::string, float> map_points_weight;
		std::map<std::string, float> map_length;
		std::map<std::string, JE::Point> map_offset;
		std::map<std::string, float> map_weights_length;
		std::map<std::string, float> map_weights_offset;
		for (auto& pair : vec_frames){
			if (!this->hasKeyframe(std::get<0>(pair))) continue;
			std::shared_ptr<Keyframe> frame = this->getKeyframe(std::get<0>(pair));
			float weight = std::get<1>(pair);
			
			typedef std::map<std::string, float>::iterator it_type;
			for(it_type iterator = frame->data_angle.begin(); iterator != frame->data_angle.end(); iterator++) {
				//JE::Point* p = &map_points_angle[iterator->first];
				//p->x += JE::MATH::Xangle(iterator->second, weight);
				//p->y += JE::MATH::Yangle(iterator->second, weight);
				map_points_weight[iterator->first] += weight;
				if (map_points_weight[iterator->first] == 0) map_points_angle[iterator->first] = iterator->second;
				else{
					map_points_angle[iterator->first] = JE::MATH::angleMix(map_points_angle[iterator->first], iterator->second, weight / map_points_weight[iterator->first]);
				}
			}
			for(it_type iterator = frame->data_length.begin(); iterator != frame->data_length.end(); iterator++) {
				map_length[iterator->first] += iterator->second * weight;
				map_weights_length[iterator->first] += weight; 
			}
			typedef std::map<std::string, JE::Point>::iterator it_type_pos;
			for(it_type_pos iterator = frame->data_pos.begin(); iterator != frame->data_pos.end(); iterator++) {
				JE::Point* p = &map_offset[iterator->first];
				p->x += iterator->second.x * weight;
				p->y += iterator->second.y * weight;
				map_weights_offset[iterator->first] += weight;
			}
		}
		std::shared_ptr<Keyframe> ret_frame = std::make_shared<Keyframe>();
		typedef std::map<std::string, JE::Point>::iterator iter_string_point;
		typedef std::map<std::string, float>::iterator iter_string_float;
		for (iter_string_float iterator = map_points_angle.begin(); iterator != map_points_angle.end(); iterator++){
			ret_frame->setAngle(iterator->first, iterator->second);//JE::MATH::getAngle(0, 0, iterator->second.x, iterator->second.y));
		}
		for (iter_string_point iterator = map_offset.begin(); iterator != map_offset.end(); iterator++){
			float weight = map_weights_offset[iterator->first];
			float x = iterator->second.x;
			float y = iterator->second.y;
			if (weight != 0){
				x /= weight;
				y /= weight;
			} else {
				//shouldn't matter, since the numerator is probably 0 anyways
				std::cout << "Warning! Offset weight is 0!" << std::endl;
			}
			ret_frame->setOffset(iterator->first, x, y);
		}
		for (iter_string_float iterator = map_length.begin(); iterator != map_length.end(); iterator++){
			float weight = map_weights_length[iterator->first];
			float length = iterator->second;
			if (weight != 0){
				length /= weight;
			} else {
				//shouldn't matter, since the numerator is probably 0 anyways
				std::cout << "Warning! Length weight is 0!" << std::endl;
			}
			//std::cout << "Length for " << iterator->first << ":" << length << std::endl;
			ret_frame->setLength(iterator->first, length);
		}
		
		return ret_frame;
	}
	
	std::shared_ptr<Animator> Animation::createAnimator(){
		return std::make_shared<Animator>(shared_from_this());
	}
	
	void Animation::newAnimation(const std::string& name, std::vector<std::pair<std::string, float>> frames){
		this->animation_map[name] = frames;
	}
	bool Animation::hasAnimation(const std::string& name){
		return (this->animation_map.count(name) > 0);
	}
	void Animation::addAnimFrame(const std::string& name, std::pair<std::string, float> frame){
		this->animation_map[name].push_back(frame);
	}
	void Animation::setAnimFrames(const std::string& name, std::vector<std::pair<std::string, float>> frames){
		this->animation_map[name] = frames;
	}
	void Animation::addAnimFrames(const std::string& name, std::vector<std::pair<std::string, float>> frames){
		for (auto f : frames){
			this->addAnimFrame(name, f);
		}
	}
}}