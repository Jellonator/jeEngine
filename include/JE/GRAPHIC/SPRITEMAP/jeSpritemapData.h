#pragma once
#include "../../UTIL/jeTime.h"
#include "../jeImage.h"
#include <vector>
namespace JE{namespace GRAPHICS{
class Frame;
class Anim;
class Spritemap;
class SpritemapData{
	public:
	SpritemapData();
	virtual ~SpritemapData();
	Frame& getFrame(unsigned int anim, unsigned int frame);
	Frame& getFrame(unsigned int frame);
	Anim& getAnim(unsigned int anim);
	/** \brief Adds a new frame to the spritemap.
	 * \param x float, the X position.
	 * \param y float, the Y position.
	 * \param w float, the width.
	 * \param h float, the height.
	 * \param time float, the time in seconds of the frame.
	 * \param int ID, the ID to set the frame to.
	 */
	void newFrame(int x, int y, int w, int h, float time, unsigned int ID);
	void newFrame(int x, int y, int w, int h, float time);
	/** \brief Adds a new animation to the spritemap.
	 * \param int ID, the ID to set the anim to.
	 * \param 1 float speed, the speed of the animation.
	 */
	void newAnim(unsigned int ID, float speed);
	void newAnim(float speed = 1);
	/** \brief Adds a frame to an animation.
	 * \param anim int, the animation to add the frame to.
	 * \param frame int, the frame to add.
	 * \param -1 int pos, the position to set the frame to.
	 */
	void addFrameToAnim(unsigned int anim, unsigned int frame, unsigned int ID);
	void addFrameToAnim(unsigned int anim, unsigned int frame);

	unsigned int getFrameCount() const;
	unsigned int getAnimCount() const;
private:
	std::vector<Frame> frames;/**< \brief A list of frames in the image. */
	std::vector<Anim> anims;/**< \brief A list of animations. */
};

};};
