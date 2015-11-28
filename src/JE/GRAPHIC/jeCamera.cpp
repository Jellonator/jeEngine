#include "JE/GRAPHIC/jeCamera.h"
#include "JE/UTIL/jeMath.h"
#include "JE/jeUtil.h"
#include <iostream>
#include <algorithm>
#include <cmath>
namespace JE{namespace GRAPHICS{

Camera::Camera() : JE::Point(0, 0){
	this->set(0, 0);
	
	this->angle = 0;
	this->scale_x = 1;
	this->scale_y = 1;
	
	this->left   = -1.0;
	this->right  =  1.0;
	this->top    = -1.0;
	this->bottom =  1.0;
	
	this->near = 0.0f;
	this->far = 100.0f;
	
	this->origin_x = 0;
	this->origin_y = 0;
	
	this->do_clip = false;
	this->need_update_transform = true;
}

Camera::Camera(float x, float y) : Camera(){
	this->set(x, y);
}

Camera::Camera(const Camera& camera){
	this->set(camera.x, camera.y);
	
	this->angle = camera.angle;
	this->scale_x = camera.scale_x;
	this->scale_y = camera.scale_y;
	
	this->top = camera.top;
	this->left = camera.left;
	this->right = camera.right;
	this->bottom = camera.bottom;
	
	this->far = camera.far;
	this->near = camera.near;
	
	this->origin_x = camera.origin_x;
	this->origin_y = camera.origin_y;
	this->need_update_transform = true;
	
	this->do_clip = camera.do_clip;
}

// Angle functions
void Camera::setAngle(float value){
	this->angle = value;
	this->need_update_transform = true;
}

void Camera::addAngle(float value){
	this->angle = JE::MATH::mod(this->angle + value, JE::MATH::TAU);
	this->need_update_transform = true;
}

// Scale functions
void Camera::setScale(float x, float y){
	this->scale_x = x;
	this->scale_y = y;
	this->need_update_transform = true;
}

void Camera::setScale(float value){
	this->scale_x = value;
	this->scale_y = value;
	this->need_update_transform = true;
}

void Camera::pushScale(float x, float y){
	this->scale_x *= x;
	this->scale_y *= y;
	this->need_update_transform = true;
}

void Camera::pushScale(float value){
	this->scale_x *= value;
	this->scale_y *= value;
	this->need_update_transform = true;
}

// Specific functions
void Camera::letterBox(float target_width, float target_height, float x_offset, float y_offset, float zoom, bool do_clip){
	// get size of window
	float window_width, window_height;
	{
		int widthi, heighti;
		SDL_GetWindowSize(JE::GRAPHICS::window, &widthi, &heighti);
		window_width  = widthi;
		window_height = heighti;
	}
	
	// get ratios
	float width_ratio = window_width/target_width;
	float height_ratio = window_height/target_height;
	float window_ratio = window_width/window_height;
	float target_ratio = target_width/target_height;
	
	float new_width = target_width;
	float new_height = target_height;
	float scale_to = 1.0f;
	
	// Compare ratios to determine which axis will be used to scale
	if (window_ratio > target_ratio) {
		new_width = zoom*(target_width * width_ratio) + (1-zoom)*(target_width * height_ratio);
		new_height = zoom*(target_height * width_ratio) + (1-zoom)*(target_height * height_ratio);
		scale_to = zoom*(width_ratio) + (1-zoom)*(height_ratio);
	} else {
		new_width = (1-zoom)*(target_width * width_ratio) + zoom*(target_width * height_ratio);
		new_height = (1-zoom)*(target_height * width_ratio) + zoom*(target_height * height_ratio);
		scale_to = (1-zoom)*(width_ratio) + zoom*(height_ratio);
	}
	
	
	if (do_clip){
		// Set clipping rectangle
		this->clip_rect.x = (window_width - new_width)*x_offset;
		this->clip_rect.y = (window_height - new_height)*y_offset;
		this->clip_rect.w = new_width;
		this->clip_rect.h = new_height;
		this->do_clip = true;
		
		// Set orthographic bounds
		this->left = 0;
		this->top = 0;
		this->right = target_width;
		this->bottom = target_height;
		
	} else {
		// Set orthographic bounds
		this->left = -(window_width - new_width)*x_offset/scale_to;
		this->top = -(window_height - new_height)*y_offset/scale_to;
		this->right = target_width + (window_width - new_width)*(1-x_offset)/scale_to;
		this->bottom = target_height + (window_height - new_height)*(1-y_offset)/scale_to;
		
		this->do_clip = false;
	}
	
	this->need_update_transform = true;
}

// Viewport functions
void Camera::useViewport() const{
	if (this->do_clip){
		glEnable(GL_SCISSOR_TEST);
		glViewport(this->clip_rect.x, this->clip_rect.y, this->clip_rect.w, this->clip_rect.h);
		glScissor(this->clip_rect.x, this->clip_rect.y, this->clip_rect.w, this->clip_rect.h);
	}
}

void Camera::disableViewport() const{
	int w, h;
	SDL_GetWindowSize(JE::GRAPHICS::window, &w, &h);
	glViewport(0, 0, w, h);
	glDisable(GL_SCISSOR_TEST);
}

// Transform functions
const glm::mat4& Camera::getTranform() const{
	// Update cache if needed(It's not that expensive of a calculation, but hey,
	// it doesn't hurt to save on a few easy cycles
	if (need_update_transform){
		this->need_update_transform = false;
		
		// Matrices are applied in inverse order, so read bottom to top(it's confusing I know, but it's not my fault!)
		// Finally, do whatever it is glm::ortho does.
		glm::mat4 view_matrix = glm::ortho(this->left, this->right, this->bottom, this->top, this->near, this->far);
		
		// Find origin position
		float origin_move_x = this->right  * (this->origin_x+1)/2 + this->left * (-this->origin_x+1)/2;
		float origin_move_y = this->bottom * (this->origin_y+1)/2 + this->top  * (-this->origin_y+1)/2;
		
		// Then rotate and scale view with screen center being the origin
		glm::mat4 model_matrix = glm::mat4()
		 * glm::translate(glm::mat4(), glm::vec3(origin_move_x, origin_move_y, 0.0f))
		 * glm::rotate(glm::mat4(), this->angle, glm::vec3(0.0f, 0.0f, 1.0f))
		 * glm::scale(glm::mat4(), glm::vec3(this->scale_x, this->scale_y, 0.0f))
		 * glm::translate(glm::mat4(), glm::vec3(-origin_move_x, -origin_move_y, 0.0f));
		
		// Translate first
		glm::mat4 translate_matrix = glm::translate(glm::mat4(), glm::vec3(-this->x, -this->y, 0.0f));
		
		// I feel really silly writing these comments like holy poop matrices are strange.
		this->transform_cache = view_matrix * model_matrix * translate_matrix;
	}
	
	return this->transform_cache;
}

// Get position
void Camera::getPosition(float x, float y, float* ret_x, float* ret_y) const{
	
	// Get origin position
	float origin_move_x = this->right  * (this->origin_x+1)/2 + this->left * (-this->origin_x+1)/2;
	float origin_move_y = this->bottom * (this->origin_y+1)/2 + this->top  * (-this->origin_y+1)/2;
	
	// Get unscaled position
	float pos_x = this->right  * (x+1)/2 + this->left * (-x+1)/2;
	float pos_y = this->bottom * (y+1)/2 + this->top  * (-y+1)/2;
	
	// Scale from origin
	pos_x -= origin_move_x;
	pos_y -= origin_move_y;
		pos_x /= this->scale_x;
		pos_y /= this->scale_y;
	pos_x += origin_move_x;
	pos_y += origin_move_y;
	
	// Translate with camera
	pos_x += this->x;
	pos_y += this->y;
	
	if (ret_x) *ret_x = pos_x;
	if (ret_y) *ret_y = pos_y;
}

float Camera::getLeft() const{
	float ret;
	this->getPosition(-1, 0, &ret, nullptr);
	return ret;
}

float Camera::getRight() const{
	float ret;
	this->getPosition( 1, 0, &ret, nullptr);
	return ret;
}

float Camera::getTop() const{
	float ret;
	this->getPosition( 0,-1, nullptr, &ret);
	return ret;
}

float Camera::getBottom() const{
	float ret;
	this->getPosition( 0, 1, nullptr, &ret);
	return ret;
}

float Camera::getPixelSize() const{
	// get size of theoretical window
	float window_width, window_height;
	if (this->do_clip){
		window_width = this->clip_rect.w;
		window_height = this->clip_rect.h;
		
	} else {
		int widthi, heighti;
		SDL_GetWindowSize(JE::GRAPHICS::window, &widthi, &heighti);
		window_width  = widthi;
		window_height = heighti;
	}
	
	float width = std::abs(this->getRight() - this->getLeft());
	float height = std::abs(this->getBottom() - this->getTop());
	
	float w_ratio = width / window_width;
	float h_ratio = height / window_height;
	
	return std::max(w_ratio, h_ratio);
}

void Camera::setBounds(float left, float top, float right, float bottom){
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
}

};};
