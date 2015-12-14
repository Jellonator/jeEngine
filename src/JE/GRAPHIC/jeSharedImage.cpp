#include "JE/GRAPHIC/jeSharedImage.h"
#include "JE/GL/jeModel.h"
#include "JE/GL/jeShader.h"

#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>

namespace JE{ namespace GRAPHICS{

SharedImage::SharedImage() : JE::GRAPHICS::Graphic(){
	this->use_clip = false;
	this->clip_rect = {0, 0, 1, 1};
	this->ignore_cliprect = true;
	this->ignore_texture = true;
	this->need_update_texcoord_transform = true;
}

SharedImage::SharedImage(const std::string& file_name) : SharedImage(){
	this->loadImage(file_name);
}

SharedImage::SharedImage(int width, int height) : SharedImage(){
	this->texture = std::make_shared<JE::GL::Texture>(width, height);
}

SharedImage::~SharedImage(){
	
}

std::shared_ptr<JE::GRAPHICS::Image> SharedImage::grabImage(){
	std::shared_ptr<JE::GRAPHICS::Image> img = std::make_shared<JE::GRAPHICS::Image>();
	img->setTexture(this->texture);
	img->setClipRect(this->clip_rect);
	if (!this->use_clip) img->disableClipRect();
	this->addImage(img);
	return img;
}

void SharedImage::addImage(std::shared_ptr<JE::GRAPHICS::Image> image){
	this->image_vec.push_back(image);
}

void SharedImage::loadImage(const std::string& file_name){
	this->texture = std::make_shared<JE::GL::Texture>(file_name);
	this->need_update_texcoord_transform = true;
}

void SharedImage::setClipRect(int x, int y, int width, int height){
	this->clip_rect.x = x;
	this->clip_rect.y = y;
	this->clip_rect.w = width;
	this->clip_rect.h = height;
	this->use_clip = true;
	this->need_update_texcoord_transform = true;
}

void SharedImage::setClipRect(const SDL_Rect& rect){
	this->clip_rect = rect;
	this->use_clip = true;
	this->need_update_texcoord_transform = true;
}

void SharedImage::disableClipRect(){
	this->use_clip = false;
	this->need_update_texcoord_transform = true;
}

void SharedImage::drawMatrix(const glm::mat4& camera, float x, float y) const{
	if (this->ignore_texture && this->texture == nullptr) return;
	x += this->x;
	y += this->y;
	
	std::vector<std::weak_ptr<JE::GRAPHICS::Image>>::iterator iter;
	iter = this->image_vec.begin();
	
	// Get model and shader
	JE::GL::Model& model = JE::GL::getDefaultImageModel();
	JE::GL::Shader& shader = JE::GL::getDefaultImageShader();
	
	// Use model and shader
	model.bind();
	shader.use();
	
	// Get drawing transformations
	glm::mat4x4 transform = camera;
	transform = glm::translate(transform, glm::vec3(x, y, 0.0f));
	
	// Transformation for texture coordinates
	if (this->ignore_cliprect && this->ignore_texture){
		shader.setUniformMat("in_TexcoordTransform", this->getTexcoordTransform());
	}
	
	// Use own texture
	if (this->ignore_texture) this->texture->use();
	
	while (iter != this->image_vec.end()){
		// Remove non-existant images
		if (iter->expired()){
			iter = this->image_vec.erase(iter);
			continue;
		}
		
		// Actual draw code
		std::shared_ptr<JE::GRAPHICS::Image> img = iter->lock();
		++iter;

		// Use image's texture
		if (!this->ignore_texture){
			if (img->hasTexture()){
				img->getTexture().use();
			} else {
				continue;
			}
		}
		
		// Special cases for clip rectangles
		if (!this->ignore_cliprect){
			if (this->ignore_texture){
				// Custom clip with own texture
				glm::mat4 local_clip = img->getTexcoordTransformCustom(
					this->texture->getWidth(), this->texture->getHeight()
				);
				shader.setUniformMat("in_TexcoordTransform", local_clip);
				
				// Custom clip with custom texture
			} else {
				glm::mat4 local_clip = img->getTexcoordTransform();
				shader.setUniformMat("in_TexcoordTransform", local_clip);
			}
			
			// Custom texture with own clip
		} else if (!this->ignore_texture){
			glm::mat4 local_clip = this->getTexcoordTransformCustom(
				img->getTexture().getWidth(), img->getTexture().getHeight()
			);
			shader.setUniformMat("in_TexcoordTransform", local_clip);
		}
		
		// Get local transformation of image
		glm::mat4 local_transform = transform;
		if (this->ignore_cliprect){
			if (this->ignore_texture){
				local_transform *= img->getTransformCustom(
					this->texture->getWidth(), this->texture->getHeight(),
					this->use_clip, this->clip_rect
				);
			}  else {
				local_transform *= img->getTransformCustom(
					img->getTexture().getWidth(), img->getTexture().getHeight(),
					this->use_clip, this->clip_rect
				);
			}
		} else {
			if (this->ignore_texture){
				local_transform *= img->getTransformCustom(
					this->texture->getWidth(), this->texture->getHeight()
				);
			} else {
				local_transform *= img->getTransform();
			}
		}
		shader.setUniformMat("in_Transform", local_transform);
		
		// Actual draw call
		glDrawElements(
			model.getDrawMode(),
			model.getNumElements(),
			GL_UNSIGNED_INT,
			0
		);
	}
}

const glm::mat4& SharedImage::getTexcoordTransform() const{
	if (this->need_update_texcoord_transform){
		float tex_w = 1;
		float tex_h = 1;
		if (this->texture){
			tex_w = this->texture->getWidth();
			tex_h = this->texture->getHeight();
		}
		// Source is texture coordinates
		float source_x = 0;
		float source_y = 0;
		float source_width = tex_w;
		float source_height = tex_h;
		
		if (this->use_clip){
			source_x = this->clip_rect.x;
			source_y = this->clip_rect.y;
			source_width = this->clip_rect.w;
			source_height = this->clip_rect.h;
		}
		
		// Pad source
		source_x += 0.5f;
		source_y += 0.5f;
		source_width -= 1.0f;
		source_height -= 1.0f;
		
		glm::mat4 texcoord_transform = glm::mat4();
		texcoord_transform = glm::translate(texcoord_transform, glm::vec3(
			source_x/tex_w, 
			source_y/tex_h, 
			0.0f
		));
		texcoord_transform = glm::scale(texcoord_transform, glm::vec3(
			source_width/tex_w,
			source_height/tex_h,
			1.0f
		));
		this->texcoord_transform_cache = texcoord_transform;
		this->need_update_texcoord_transform = false;
	}
	
	return this->texcoord_transform_cache;
}

glm::mat4 SharedImage::getTexcoordTransformCustom(int width, int height) const{
	return this->getTexcoordTransformCustom(width, height, this->use_clip, this->clip_rect);
}

glm::mat4 SharedImage::getTexcoordTransformCustom(int width, int height, bool custom_use_clip, const SDL_Rect& custom_clip) const{
	// Source is texture coordinates
	float source_x = 0;
	float source_y = 0;
	float source_width = width;
	float source_height = height;
	
	if (custom_use_clip){
		source_x = custom_clip.x;
		source_y = custom_clip.y;
		source_width = custom_clip.w;
		source_height = custom_clip.h;
	}
	
	// Pad source
	source_x += 0.5f;
	source_y += 0.5f;
	source_width -= 1.0f;
	source_height -= 1.0f;
	
	glm::mat4 texcoord_transform = glm::mat4();
	texcoord_transform = glm::translate(texcoord_transform, glm::vec3(
		source_x/width, 
		source_y/height, 
		0.0f
	));
	texcoord_transform = glm::scale(texcoord_transform, glm::vec3(
		source_width/width,
		source_height/height,
		1.0f
	));
	
	return texcoord_transform;
}

bool SharedImage::doesIgnoreClip() const{
	return this->ignore_cliprect;
}

bool SharedImage::doesIgnoreTexture() const{
	return this->ignore_texture;
}

void SharedImage::setIgnoreClip(bool value){
	this->ignore_cliprect = value;
}

void SharedImage::setIgnoreTexture(bool value){
	this->ignore_texture = value;
}

}}