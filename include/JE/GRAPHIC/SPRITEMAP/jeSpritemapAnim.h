#pragma once
#include "../../UTIL/jeTime.h"
#include "../jeImage.h"
#include <vector>
namespace JE{namespace GRAPHICS{
class Frame;
class Anim;
class Spritemap;
class SpritemapData;

class Anim{
public:
	Anim();
	Anim(float speed);
	virtual ~Anim();
	
	//getters
	float getSpeed() const;
	Frame& getFrameFromData(unsigned int index, SpritemapData& data);
	unsigned int getFrameID(unsigned int index) const;
	unsigned int getFrameCount() const;
	
	//setters
	void setSpeed(float speed);
	void addFrame(unsigned int frame, unsigned int ID);
	void addFrame(unsigned int frame);
	void removeFrame(unsigned int ID);
	void clearFrames();
	
private:
	float speed;/**< \brief The speed of the animation */
	std::vector<unsigned int> frames;/**< \brief A list of frames for the animation. */
};
};};
