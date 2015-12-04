#include "JE/jeEntity.h"
#include "JE/GRAPHIC/jeCamera.h"
#include "JE/GRAPHIC/jeImage.h"
#include "JE/UTIL/jeMath.h"
#include "JE/GL/jeShader.h"
#include "JE/GL/jeModel.h"
#include "JE/jeUtil.h"
#include <iostream>
#include <cmath>
#include <vector>

#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>

namespace JE{namespace GRAPHICS{

Image::Image() : JE::GRAPHICS::Graphic(){
	this->flip_x = false;
	this->flip_y = false;
	this->scale_x = 1;
	this->scale_y = 1;
	this->origin_x = 0;
	this->origin_y = 0;
	this->angle = 0;
	this->use_clip = false;
	this->clip_rect = {0, 0, 1, 1};
	this->need_update_texcoord_transform = true;
	this->need_update_transform = true;
}

Image::Image(int width, int height) : Image(){
	this->texture = std::make_shared<JE::GL::Texture>(width, height);
}

Image::Image(const std::string& file_name) : Image(){
	this->loadImage(file_name);
	//std::cout << JE::fileOpen(file_name) << std::endl;
}

Image::Image(const Image& image){
	this->texture = image.texture;
	this->flip_x = image.flip_x;
	this->flip_y = image.flip_y;
	this->scale_x = image.scale_x;
	this->scale_y = image.scale_y;
	this->origin_x = image.origin_x;
	this->origin_y = image.origin_y;
	this->angle = image.angle;
	this->use_clip = image.use_clip;
	this->clip_rect = image.clip_rect;
	this->need_update_texcoord_transform = true;
	this->need_update_transform = true;
}

Image::~Image(){
	
}

void Image::setAngle(float value){
	this->angle = value;
	this->need_update_transform = true;
}

void Image::addAngle(float value){
	this->angle = JE::MATH::mod(this->angle + value, JE::MATH::TAU);
	this->need_update_transform = true;
}

void Image::setScale(float x, float y){
	this->scale_x = x;
	this->scale_y = y;
	this->need_update_transform = true;
}

void Image::setScale(float value){
	this->scale_x = value;
	this->scale_y = value;
	this->need_update_transform = true;
}

void Image::setSize(float width, float height){
	this->scale_x = width / this->texture->getWidth();
	this->scale_y = height / this->texture->getHeight();
	this->need_update_transform = true;
}

void Image::setFlip(bool x, bool y){
	this->flip_x = x;
	this->flip_y = y;
	this->need_update_transform = true;
}

void Image::setFlipX(bool value){
	this->flip_x = value;
	this->need_update_transform = true;
}

void Image::setFlipY(bool value){
	this->flip_y = value;
	this->need_update_transform = true;
}

void Image::setOrigin(float x, float y){
	this->origin_x = x;
	this->origin_y = y;
	this->need_update_transform = true;
}

void Image::setClipRect(int x, int y, int width, int height){
	this->clip_rect.x = x;
	this->clip_rect.y = y;
	this->clip_rect.w = width;
	this->clip_rect.h = height;
	this->use_clip = true;
	this->need_update_texcoord_transform = true;
}

void Image::setClipRect(const SDL_Rect& rect){
	this->setClipRect(rect.x, rect.y, rect.w, rect.h);
	this->need_update_texcoord_transform = true;
}

void Image::disableClipRect(){
	this->use_clip = false;
	this->need_update_texcoord_transform = true;
}

const JE::GL::Texture& Image::getTexture() const{
	return *this->texture;
}

bool Image::hasTexture() const{
	return (this->texture != nullptr);
}

void Image::loadImage(const std::string& file_name){
	this->texture = std::make_shared<JE::GL::Texture>(file_name);
	this->need_update_texcoord_transform = true;
}

void Image::setTexture(std::shared_ptr<JE::GL::Texture> tex){
	this->texture = tex;
	this->need_update_texcoord_transform = true;
}

void Image::drawMatrix(const glm::mat4& camera, float x, float y) const{
	if (this->texture == nullptr) {
		std::cout << "No Texture" << std::endl;
		return;
	}
	
	JE::GL::Shader& shader = JE::GL::getDefaultImageShader();
	JE::GL::Model& model = JE::GL::getDefaultImageModel();
	
	// Get drawing transformations
	glm::mat4x4 transform = camera;
	transform = glm::translate(transform, glm::vec3(x, y, 0.0f));
	transform *= this->getTransform();
	
	// Transformation for texture coordinates
	glm::mat4 texcoord_transform = this->getTexcoordTransform();
	
	// Send transformations
	shader.setUniformMat("in_Transform", transform);
	shader.setUniformMat("in_TexcoordTransform", texcoord_transform);
	
	// Actual draw call
	this->texture->use();
	model.draw();
	this->texture->disable();
}

const glm::mat4& Image::getTransform() const{
	if (this->need_update_transform){
		// Transformation for vertex positions
		float scale_width = this->scale_x * (this->flip_x ? -1 : 1);
		float scale_height = this->scale_y * (this->flip_y ? -1 : 1);
		
		// Get drawing transformations
		glm::mat4x4 transform = glm::mat4();//camera;
		transform = glm::translate(transform, glm::vec3(this->x, this->y, 0.0f));
		transform = glm::translate(transform, glm::vec3( this->origin_x,  this->origin_y, 0.0f));
		transform = glm::rotate(transform, this->angle, glm::vec3(0.0f, 0.0f, 1.0f));
		transform = glm::scale(transform, glm::vec3(scale_width, scale_height, 1.0f));
		transform = glm::translate(transform, glm::vec3(-this->origin_x, -this->origin_y, 0.0f));
		if (this->use_clip){
			transform = glm::scale(transform, glm::vec3(this->clip_rect.w, this->clip_rect.h, 1.0f));
		} else {
			transform = glm::scale(transform, glm::vec3(this->texture->getWidth(), this->texture->getHeight(), 1.0f));
		}
		
		this->transform_cache = transform;
		this->need_update_transform = false;
	}
	
	return this->transform_cache;
}

const glm::mat4& Image::getTexcoordTransform() const{
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

glm::mat4 Image::getTransformCustom(int width, int height) const{
	return this->getTransformCustom(width, height, this->use_clip, this->getClipRect());
}

glm::mat4 Image::getTransformCustom(int width, int height, bool custom_use_clip, const SDL_Rect& custom_clip) const{
		// Transformation for vertex positions
		float scale_width = this->scale_x * (this->flip_x ? -1 : 1);
		float scale_height = this->scale_y * (this->flip_y ? -1 : 1);
		
		// Get drawing transformations
		glm::mat4x4 transform = glm::mat4();//camera;
		transform = glm::translate(transform, glm::vec3(this->x, this->y, 0.0f));
		transform = glm::translate(transform, glm::vec3( this->origin_x,  this->origin_y, 0.0f));
		transform = glm::rotate(transform, this->angle, glm::vec3(0.0f, 0.0f, 1.0f));
		transform = glm::scale(transform, glm::vec3(scale_width, scale_height, 1.0f));
		transform = glm::translate(transform, glm::vec3(-this->origin_x, -this->origin_y, 0.0f));
		
		if (custom_use_clip){
			transform = glm::scale(transform, glm::vec3(custom_clip.w, custom_clip.h, 1.0f));
		} else {
			transform = glm::scale(transform, glm::vec3(width, height, 1.0f));
		}
		
		return transform;
}

glm::mat4 Image::getTexcoordTransformCustom(int width, int height) const{
	return this->getTexcoordTransformCustom(width, height, this->use_clip, this->getClipRect());
}

glm::mat4 Image::getTexcoordTransformCustom(int width, int height, bool custom_use_clip, const SDL_Rect& custom_clip) const{
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

bool Image::isClipEnabled() const{
	return this->use_clip;
}

const SDL_Rect& Image::getClipRect() const{
	return this->clip_rect;
}

};};
