#pragma once
#include "../../UTIL/jeTime.h"
#include "../jeImage.h"
#include <vector>
namespace JE{namespace GRAPHICS{
class SpritemapFrame;
class SpritemapAnim;
class Spritemap;
class SpritemapData;
class SpritemapFrame{
public:
	SpritemapFrame();
	SpritemapFrame(int x, int y, int w, int h, float length = 1.0);
	virtual ~SpritemapFrame();
	
	//setters
	void setSize(int x, int y, int w, int h);
	void setLength(float length);
	
	//getters
	const SDL_Rect& getRect() const;//scrub
	float getLength() const;
	
private:
	float length;/**< \brief The length of the frame, in seconds. */
	SDL_Rect rect;/**< \brief The clipping rectangle of the frame. */
};
};};
