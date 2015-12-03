#pragma once
#include "jeImage.h"
#include "jeGraphic.h"
#include <memory>
#include <vector>

namespace JE{namespace GRAPHICS{

class SharedImage : public JE::GRAPHICS::Graphic{
public:
	SharedImage();
	SharedImage(const std::string& file_name);
	SharedImage(int width, int height);
	virtual ~SharedImage();
	
	std::shared_ptr<JE::GRAPHICS::Image> grabImage();
	void addImage(std::shared_ptr<JE::GRAPHICS::Image> image);
	
	void loadImage(const std::string& file_name);
	void setClipRect(int x, int y, int width, int height);
	void setClipRect(const SDL_Rect& rect);
	void disableClipRect();
	
	const glm::mat4& getTexcoordTransform() const;
	bool doesIgnoreClip() const;
	bool doesIgnoreTexture() const;
	
	void setIgnoreClip(bool value);
	void setIgnoreTexture(bool value);
	
	virtual void drawMatrix(const glm::mat4& camera, float x = 0, float y = 0) const;
		
private:
	mutable std::vector<std::weak_ptr<JE::GRAPHICS::Image>> image_vec;
	bool ignore_texture;
	bool ignore_cliprect;
	
	// The only properties SharedImage actually needs from Image
	std::shared_ptr<JE::GL::Texture> texture;
	bool use_clip;
	SDL_Rect clip_rect;
	
	mutable bool need_update_texcoord_transform;
	mutable glm::mat4 texcoord_transform_cache;
};

}}