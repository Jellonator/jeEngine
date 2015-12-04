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
	Image(int width, int height);
	
	void setAngle(float value);
	void addAngle(float value);
	
	void setScale(float x, float y);
	void setScale(float value);
	void setSize(float width, float height);
	void setFlip(bool x, bool y);
	void setFlipX(bool value);
	void setFlipY(bool value);
	void setOrigin(float x, float y);
	
	void loadImage(const std::string& file_name);
	void setClipRect(int x, int y, int width, int height);
	void setClipRect(const SDL_Rect& rect);
	void disableClipRect();
	
	void setTexture(std::shared_ptr<JE::GL::Texture> tex);
	
	virtual ~Image();
	virtual void drawMatrix(const glm::mat4& camera, float x = 0, float y = 0) const;
	
	const JE::GL::Texture& getTexture() const;
	bool hasTexture() const;
	
	const glm::mat4& getTransform() const;
	const glm::mat4& getTexcoordTransform() const;
	
	glm::mat4 getTransformCustom(int width, int height) const;
	glm::mat4 getTexcoordTransformCustom(int width, int height) const;
	glm::mat4 getTransformCustom(int width, int height, bool custom_use_clip, const SDL_Rect& custom_clip) const;
	glm::mat4 getTexcoordTransformCustom(int width, int height, bool custom_use_clip, const SDL_Rect& custom_clip) const;
	
	bool isClipEnabled() const;
	const SDL_Rect& getClipRect() const;
	
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
	
	mutable bool need_update_transform;
	mutable bool need_update_texcoord_transform;
	mutable glm::mat4 transform_cache;
	mutable glm::mat4 texcoord_transform_cache;
};

};};
