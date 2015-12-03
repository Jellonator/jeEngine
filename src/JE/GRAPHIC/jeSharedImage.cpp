#include "JE/GRAPHIC/jeSharedImage.h"
#include "JE/GL/jeModel.h"
#include "JE/GL/jeShader.h"

#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>

namespace JE{ namespace GRAPHICS{

SharedImage::SharedImage() : JE::GRAPHICS::Graphic(){
	this->use_clip = false;
	this->clip_rect = {0, 0, 1, 1};
	this->ignore_cliprect = false;
	this->ignore_texture = false;
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
}

void SharedImage::setClipRect(int x, int y, int width, int height){
	this->clip_rect.x = x;
	this->clip_rect.y = y;
	this->clip_rect.w = width;
	this->clip_rect.h = height;
}

void SharedImage::setClipRect(const SDL_Rect& rect){
	this->clip_rect = rect;
	this->use_clip = true;
}

void SharedImage::disableClipRect(){
	this->use_clip = false;
}

void SharedImage::drawMatrix(const glm::mat4& camera, float x, float y) const{
	if (this->ignore_texture && this->texture == nullptr) return;
	
	std::vector<std::weak_ptr<JE::GRAPHICS::Image>>::const_iterator iter;
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
	glm::mat4 texcoord_transform;
	if (this->texture != nullptr) texcoord_transform = this->getTexcoordTransform();
	
	// Use own texture
	if (this->texture != nullptr) this->texture->use();
	
	while (iter != this->image_vec.end()){
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
		
		// Use image's clip rect
		if (!this->ignore_cliprect){
			if (img->isClipEnabled()){
				glm::mat4 local_clip = img->getTexcoordTransform();
				shader.setUniformMat("in_TexcoordTransform", local_clip);
			} else {
				shader.setUniformMat("in_TexcoordTransform", texcoord_transform);
			}
		}
		
		// Get local transformation of image
		glm::mat4 local_transform = transform * img->getTransform();
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

glm::mat4 SharedImage::getTexcoordTransform() const{
	// Source is texture coordinates
	float source_x = 0;
	float source_y = 0;
	float source_width = this->texture->getWidth();
	float source_height = this->texture->getHeight();
	
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
		source_x/this->texture->getWidth(), 
		source_y/this->texture->getHeight(), 
		0.0f
	));
	texcoord_transform = glm::scale(texcoord_transform, glm::vec3(
		source_width/this->texture->getWidth(),
		source_height/this->texture->getHeight(),
		1.0f
	));
	
	return texcoord_transform;
}

}}