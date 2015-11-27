#pragma once
#include "jeGraphic.h"
#include "../GL/jeTexture.h"
#include <string>
#include <memory>

namespace JE{namespace GRAPHICS{

class Image : public Graphic
{
public:
	
	Image();
	Image(const std::string& file);
	Image(const Image& image);
	
	void loadImage(const std::string& file_name);
	void setClipRect(int x, int y, int width, int height);
	void disableClipRect();
	
	virtual ~Image();
	virtual void draw(const JE::GRAPHICS::Camera& camera, float x = 0, float y = 0) const;
	
private:
	std::shared_ptr<JE::GL::Texture> texture;
	float angle;
	float width;
	float height;
	
	bool use_clip;
	SDL_Rect clip_rect;
};

};};
