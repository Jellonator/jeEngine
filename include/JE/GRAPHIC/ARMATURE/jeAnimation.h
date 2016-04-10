#pragma once
#include "../../UTIL/jeTime.h"
#include "../../jePoint.h"
#include "jeArm.h"
#include "jeKeyFrame.h"
#include <map>
#include <vector>
#include <memory>
#include <string>
#include <tuple>

namespace JE{namespace ARM{
	class Arm;
	class Keyframe;
	class Animation;
class Animator{public:
	friend Animation;
	Animator(std::shared_ptr<Animation> anim);
	virtual ~Animator();
	void update(float dt = JE::TIME::dt);
	void apply(const std::shared_ptr<Arm>& arm);
	void play(const std::string& name, bool loop = true, int start = 0);
	bool isPlaying();
	void stop();
private:
	float animation_time;
	int animation_position;
	bool animation_loop;
	std::string animation_name;
	std::shared_ptr<Animation> animation;
	bool animation_playing;
	
	std::shared_ptr<Keyframe> temp_frame;
	bool frame_update;
};
class Animation : public std::enable_shared_from_this<Animation> {
public:
	Animation();
	virtual ~Animation();
	friend Arm;
	friend Keyframe;
	friend Animator;
	//keyframe functions
	std::shared_ptr<Keyframe> newKeyframe(const std::string& name);
	std::shared_ptr<Keyframe> getKeyframe(const std::string& name);
	void addKeyframe(const std::string& name, std::shared_ptr<Keyframe> frame);
	bool hasKeyframe(const std::string& name);
	void apply(const std::shared_ptr<Arm>& arm, const std::string& name);
	void apply(const std::shared_ptr<Arm>& arm, const std::string& name, float ammount);
	
	//merge keyframes
	std::shared_ptr<Keyframe> mergeKeyframes(std::vector<std::pair<std::string, float>> vec_frames);
	void mergeKeyframes(std::vector<std::pair<std::string, float>> vec_frames, std::shared_ptr<Keyframe> ret_frame);
	
	//animator create
	std::shared_ptr<Animator> createAnimator();
	
	//animation functions
	bool hasAnimation(const std::string& name);
	void newAnimation(const std::string& name, std::vector<std::pair<std::string, float>> frames);
	float getFrameTime(const std::string& anim, int position);
	std::string getFrameName(const std::string& anim, int position);
	std::string getFramePrev(const std::string& anim, int position);
	int getAnimLength(const std::string& anim);
	
	void setAnimFrames(const std::string&, std::vector<std::pair<std::string, float>> frames);
	void addAnimFrame(const std::string&, std::pair<std::string, float> frame);
	void addAnimFrames(const std::string&, std::vector<std::pair<std::string, float>> frames);
private:
	//storage for keyframes
	std::map<std::string, std::shared_ptr<Keyframe>> keyframe_map;
	//animation stuff
	std::map<std::string, std::vector<std::pair<std::string, float>>> animation_map;
};
}}
