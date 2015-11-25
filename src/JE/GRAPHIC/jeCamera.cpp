#include "JE/GRAPHIC/jeCamera.h"
#include "JE/UTIL/jeMath.h"
#include "JE/jeUtil.h"
#include <iostream>
#include <algorithm>
#include <cmath>
namespace JE{namespace GRAPHICS{

Camera::Camera() : JE::Point(0, 0){
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
}

void Camera::setAngle(float value){
	this->angle = value;
}

void Camera::setScale(float x, float y){
	this->scale_x = x;
	this->scale_y = y;
}

void Camera::setScale(float value){
	this->scale_x = value;
	this->scale_y = value;
}

void Camera::pushScale(float x, float y){
	this->scale_x *= x;
	this->scale_y *= y;
}

void Camera::pushScale(float value){
	this->scale_x *= value;
	this->scale_y *= value;
}

glm::mat4 Camera::getTranform() const{
	// Matrices are applied in inverse order, so read bottom to top(it's confusing I know, but it's not my fault!)
	
	// Finally, do whatever it is glm::ortho does.
	glm::mat4 view_matrix = glm::ortho(this->left, this->right, this->bottom, this->top, this->near, this->far);
	
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
	glm::mat4 model_view_matrix = view_matrix * model_matrix * translate_matrix;
	
	return model_view_matrix;
}

};};
