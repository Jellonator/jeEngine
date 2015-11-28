#include "JE/jeEntity.h"
#include "JE/GRAPHIC/jeCamera.h"
#include "JE/GRAPHIC/jeImage.h"
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
	//this->width = 1;
	//this->height = 1;
	this->flip_x = false;
	this->flip_y = false;
	this->scale_x = 1;
	this->scale_y = 1;
	this->angle = 0;
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
	this->angle = image.angle;
}

Image::~Image(){
	
}

void Image::setClipRect(int x, int y, int width, int height){
	this->clip_rect.x = x;
	this->clip_rect.y = y;
	this->clip_rect.w = width;
	this->clip_rect.h = height;
	this->use_clip = true;
}

void Image::disableClipRect(){
	this->use_clip = false;
}

void Image::loadImage(const std::string& file_name){
	SDL_Surface* surface = IMG_Load(file_name.c_str());
	
	this->texture = std::make_shared<JE::GL::Texture>(surface);
	
	//this->width = surface->w;
	//this->height = surface->h;
	
	SDL_FreeSurface(surface);
}

void Image::drawMatrix(const glm::mat4& camera, float x, float y) const{
	if (this->texture == nullptr) {
		std::cout << "No Texture" << std::endl;
		return;
	}
	
	JE::GL::Shader& shader = JE::GL::getDefaultImageShader();
	JE::GL::Model& model = JE::GL::getDefaultImageModel();
	
	// Transformation for vertex positions
	float scale_width = this->scale_x * (this->flip_x ? -1 : 1);
	float scale_height = this->scale_y * (this->flip_y ? -1 : 1);
	glm::mat4x4 transform = camera;
	transform = glm::translate(transform, glm::vec3(this->x + x, this->y + y, 0.0f));
	transform = glm::translate(transform, glm::vec3( this->origin_x,  this->origin_y, 0.0f));
	transform = glm::rotate(transform, this->angle, glm::vec3(0.0f, 0.0f, 1.0f));
	transform = glm::scale(transform, glm::vec3(scale_width, scale_height, 1.0f));
	transform = glm::translate(transform, glm::vec3(-this->origin_x, -this->origin_y, 0.0f));
	
	// Transformation for texture coordinates so they don't bleed
	glm::mat4 texcoord_transform = glm::mat4();
	texcoord_transform = glm::translate(texcoord_transform, glm::vec3(
		0.5f/this->texture->getWidth(), 
		0.5f/this->texture->getHeight(), 
		0.0f
	));
	texcoord_transform = glm::scale(texcoord_transform, glm::vec3(
		(this->texture->getWidth() -1)/this->texture->getWidth(),
		(this->texture->getHeight()-1)/this->texture->getHeight(),
		1.0f
	));
	
	if (this->use_clip){
		transform = glm::scale(transform, glm::vec3(this->clip_rect.w, this->clip_rect.h, 1.0f));
		texcoord_transform = glm::translate(texcoord_transform, glm::vec3(
			this->clip_rect.x / this->texture->getWidth(),
			this->clip_rect.y / this->texture->getHeight(),
			0.0f
		));
		texcoord_transform = glm::scale(texcoord_transform, glm::vec3(
			this->clip_rect.w / this->texture->getWidth(),
			this->clip_rect.h / this->texture->getHeight(),
			1.0f
		));
		
	} else {
		transform = glm::scale(transform, glm::vec3(this->texture->getWidth(), this->texture->getHeight(), 1.0f));
	}
	
	shader.setUniformMat("in_Transform", transform);
	shader.setUniformMat("in_TexcoordTransform", texcoord_transform);
	
	this->texture->use();
	
	model.draw();
	
	this->texture->disable();
}

};};
