#pragma once
#include "../UTIL/jeTime.h"
#include "SPRITEMAP/jeSpritemapAnim.h"
#include "SPRITEMAP/jeSpritemapData.h"
#include "SPRITEMAP/jeSpritemapFrame.h"
#include "jeImage.h"
#include <vector>
namespace JE{namespace GRAPHICS{
class Frame;
class Anim;
class Spritemap;
class SpritemapData;

class Spritemap : public Image
{
public:

	Spritemap();
	Spritemap(std::string file);
	virtual ~Spritemap();
	
	//getter functions
	std::shared_ptr<SpritemapData> getData();
	Frame& getFrame(const std::string& anim, unsigned int frame);
	Frame& getFrame(unsigned int frame);
	Anim& getAnim(const std::string& anim);
	Anim& getCurrentAnim();
	Frame& getCurrentFrame();
	bool doesContainFrame(const Frame& frame, unsigned int* position = nullptr);
	
	//counting functions
	unsigned int getFrameCount() const;
	unsigned int getAnimCount() const;
	
	//data management
	unsigned int newFrame(int x, int y, int w, int h, float time, unsigned int ID);
	unsigned int newFrame(int x, int y, int w, int h, float time = 1.0f);
	Anim& newAnim(const std::string& name, float speed = 1.0f);
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
	void pause();/**< \brief pause the animation. */
	void resume();/**< \brief resume the animation. */
	void reset();/**< \brief reset the animation. */
	void update(float dt = JE::TIME::dt);
	
	//drawing functions
	void drawFrame(const std::string& anim, unsigned int frame, float x = 0, float y = 0, float angle = 0);
	void drawFrameNoAnim(unsigned int frame, float x = 0, float y = 0, float angle = 0);
	void drawWhole(float x = 0, float y = 0, float angle = 0);
	
	//use data functions
	void useData(std::shared_ptr<SpritemapData> data);
	void useData(Spritemap& spritemap);
	
	
private:
	std::shared_ptr<SpritemapData> data;/**<  */
	float time;/**< \brief The time that the frame has been playing. */
	std::string anim;/**< \brief The current animation. */
	unsigned int frame;/**< \brief The current frame of the animation. */
	bool playing;/**< \brief Is the animation playing? */
	bool looping;/**< \brief Is the animation looping? */
	float speed;/**< \brief The speed of the animation. */
};
};};
