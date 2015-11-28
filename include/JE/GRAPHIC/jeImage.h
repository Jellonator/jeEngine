#pragma once
#include "jeGraphic.h"
#include "../GL/jeTexture.h"
#include <string>
#include <memory>

namespace JE{namespace GRAPHICS{

class Image : public JE::GRAPHICS::Graphic{
public:
	Image();
	Image(const std::string& file);
	Image(const Image& image);
	
	void setAngle(float value);
	void addAngle(float value);
	
	void loadImage(const std::string& file_name);
	void setClipRect(int x, int y, int width, int height);
	void disableClipRect();
	
	virtual ~Image();
	virtual void drawMatrix(const glm::mat4& camera, float x = 0, float y = 0) const;
	
private:
	std::shared_ptr<JE::GL::Texture> texture;
	float angle;
	float scale_x;
	float scale_y;
	float origin_x;
	float origin_y;
	bool flip_x;
	bool flip_y;
	
	bool use_clip;
	SDL_Rect clip_rect;
};

};};
