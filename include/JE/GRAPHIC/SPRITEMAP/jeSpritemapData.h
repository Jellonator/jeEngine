#pragma once
#include "../../UTIL/jeTime.h"
#include "../jeImage.h"
#include <vector>
#include <map>

namespace JE{namespace GRAPHICS{
class SpritemapFrame;
class SpritemapAnim;
class Spritemap;
class SpritemapData{
public:
	SpritemapData();
	virtual ~SpritemapData();
	
	SpritemapFrame& getFrame(const std::string& anim, unsigned int frame);
	SpritemapFrame& getFrame(unsigned int frame);
	SpritemapAnim& getAnim(const std::string& name);
	
	bool doesContainFrame(const SpritemapFrame& frame, unsigned int* position = nullptr);
	/** \brief Adds a new frame to the spritemap.
	 * \param x float, the X position.
	 * \param y float, the Y position.
	 * \param w float, the width.
	 * \param h float, the height.
	 * \param time float, the time in seconds of the frame.
	 * \param int ID, the ID to set the frame to.
	 */
	unsigned int newFrame(int x, int y, int w, int h, float time, unsigned int ID);
	unsigned int newFrame(int x, int y, int w, int h, float time = 1.0f);
	/** \brief Adds a new animation to the spritemap.
	 * \param int ID, the ID to set the anim to.
	 * \param 1 float speed, the speed of the animation.
	 */
	SpritemapAnim& newAnim(const std::string& name, float speed = 1.0f);
	/** \brief Adds a frame to an animation.
	 * \param anim int, the animation to add the frame to.
	 * \param frame int, the frame to add.
	 * \param -1 int pos, the position to set the frame to.
	 */
	void addFrameToAnim(const std::string& anim, unsigned int frame, unsigned int ID);
	void addFrameToAnim(const std::string& anim, unsigned int frame);

	unsigned int getFrameCount() const;
	unsigned int getAnimCount() const;
	
private:
	std::vector<SpritemapFrame> frames;/**< \brief A list of frames in the image. */
	std::map<std::string, SpritemapAnim> anims;/**< \brief A list of animations. */
};

};};
