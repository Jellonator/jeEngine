#pragma once
#include "../UTIL/jeTime.h"
#include "SPRITEMAP/jeSpritemapAnim.h"
#include "SPRITEMAP/jeSpritemapData.h"
#include "SPRITEMAP/jeSpritemapFrame.h"
#include "jeImage.h"
#include <vector>


namespace JE{namespace GRAPHICS{
class SpritemapFrame;
class SpritemapAnim;
class Spritemap;
class SpritemapData;

class Spritemap : public JE::GRAPHICS::Image{
public:
	Spritemap();
	Spritemap(std::string file);
	virtual ~Spritemap();
	
	//getter functions
	std::shared_ptr<SpritemapData> getData();
	SpritemapFrame& getFrame(const std::string& anim, unsigned int frame);
	SpritemapFrame& getFrame(unsigned int frame);
	SpritemapAnim& getAnim(const std::string& anim);
	SpritemapAnim& getCurrentAnim();
	SpritemapFrame& getCurrentFrame();
	bool doesContainFrame(const SpritemapFrame& frame, unsigned int* position = nullptr);
	
	//counting functions
	unsigned int getFrameCount() const;
	unsigned int getAnimCount() const;
	
	//data management
	unsigned int newFrame(int x, int y, int w, int h, float time, unsigned int ID);
	unsigned int newFrame(int x, int y, int w, int h, float time = 1.0f);
	SpritemapAnim& newAnim(const std::string& name, float speed = 1.0f);
	void addFrameToAnim(const std::string& anim, unsigned int frame, unsigned int ID);
	void addFrameToAnim(const std::string& anim, unsigned int frame);

	//setter functions
	void setFrame(unsigned int frame);
	void setFrame(const std::string& name, unsigned int frame);
	void setFrameNoAnim(unsigned int frame);
	void setSpeed(float speed);

	//animation functions
	void updateClip();
	void play(const std::string& anim, bool loop = true, bool reset = true, unsigned int frame = 0);
	void pause();
	void resume();
	void reset();
	void update(float dt = JE::TIME::dt);
	
	//drawing functions
	//void drawFrame(const std::string& anim, unsigned int frame, float x = 0, float y = 0, float angle = 0);
	//void drawFrameNoAnim(unsigned int frame, float x = 0, float y = 0, float angle = 0);
	//void drawWhole(float x = 0, float y = 0, float angle = 0);
	
	//use data functions
	void useData(std::shared_ptr<SpritemapData> data);
	void useData(Spritemap& spritemap);
	
	
private:
	std::shared_ptr<SpritemapData> data;
	float time;
	std::string anim;
	unsigned int frame;
	bool playing;
	bool looping;
	float speed;
};
};};

