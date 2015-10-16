#include "JE/GRAPHIC/jeCamera.h"
#include "JE/UTIL/jeMath.h"
#include "JE/jeUtil.h"
#include <iostream>
#include <algorithm>
#include <cmath>
namespace JE{namespace GRAPHICS{
Camera::Camera()
{
	this->x = 0;
	this->y = 0; 
	this->use_clip = false;
	this->use_size = false;
	this->reset();
}

Camera::~Camera()
{

}

void Camera::reset(){
	this->sx = 1;
	this->sy = 1;
	this->x = 0;
	this->y = 0;
	this->offX = 0;
	this->offY = 0;
	this->disableClip();
	this->disableSize();
}
void Camera::centerTo(float x, float y){
	float sw = 1;
	float sh = 1;
	//if (this->use_size) this->getRatio(&sw,&sh);
	float rx = 0;
	float ry = 0;
	rx -= (this->offX);
	ry -= (this->offY);
	rx /= sw;
	ry /= sh;
	if (this->use_clip){
		rx += this->clip.x / this->sx;
		ry += this->clip.y / this->sy;
	}

	this->x = x - this->getWidth() / 2 - rx;
	this->y = y - this->getHeight() / 2 - ry;
}
void Camera::setScaleZoom(float x, float y){
	float p_x = this->offX / this->sx;
	float p_y = this->offY / this->sy;
	y = (y > 0) ? y : x;
	this->setScale(x, y);
	this->offX += (p_x - (this->offX / x));
	this->offY += (p_y - (this->offY / y));
}

void Camera::setScale(float x, float y){
	this->sx = x;
	this->sy = (y < 0) ? x : y;
}

void Camera::pushScale(float x, float y){
	y = (y < 0) ? x : y;
	this->sx *= x;
	this->sy *= y;
}

void Camera::setClip(float x, float y, float w, float h){
	this->clip.x = x;
	this->clip.y = y;
	this->clip.w = w;
	this->clip.h = h;
	this->use_clip = true;
}

void Camera::setPosition(float x, float y){
	this->x = x;
	this->y = y;
}

void Camera::setSize(float w, float h){
	this->size.x = w;
	this->size.y = h;
	this->use_size = true;
}

void Camera::disableSize(){
	this->use_size = false;
}

void Camera::disableClip(){
	this->use_clip = false;
}

void Camera::enableClip(){
	this->use_clip = true;
}

void Camera::getRatio(float* x, float* y, bool ignoreClip){
	int w;
	int h;
	if (this->use_clip && !ignoreClip){
		w = this->clip.w;
		h = this->clip.h;
	} else SDL_GetWindowSize(window, &w, &h);
	if (this->use_size){
		if (x != nullptr) *x = float(w)/float(this->size.x);
		if (y != nullptr) *y = float(h)/float(this->size.y);
	}else{
		if (x != nullptr) *x = 1; 
		if (y != nullptr) *y = 1;
	}
}

void Camera::letterbox(float width, float height, float zoom, float x, float y, bool doCrop){
	float window_width, window_height;
	{
		int widthi, heighti;
		SDL_GetWindowSize(window, &widthi, &heighti);
		window_width  = widthi;
		window_height = heighti;
	}
	float width_ratio = window_width/width;
	float height_ratio = window_height/height;
	float window_ratio = window_width/window_height;
	float ratio = width/height;
	float scale_to = 0;

	if (window_ratio > ratio) {
		width = zoom*(width * width_ratio) + (1-zoom)*(width * height_ratio);
		height = zoom*(height * width_ratio) + (1-zoom)*(height * height_ratio);
		scale_to = zoom*(width_ratio) + (1-zoom)*(height_ratio);
	} else {
		width = (1-zoom)*(width * width_ratio) + zoom*(width * height_ratio);
		height = (1-zoom)*(height * width_ratio) + zoom*(height * height_ratio);
		scale_to = (1-zoom)*(width_ratio) + zoom*(height_ratio);
	}

	x = (window_width - width)*x/scale_to;
	y = (window_height - height)*y/scale_to;
	if (doCrop){
		this->setClip(std::max(0.0f, x*scale_to), std::max(0.0f, y*scale_to),
			std::min(width, window_width), std::min(window_height, height));
	}
	this->offX = x;
	this->offY = y;
	this->setScale(scale_to);
	//this->setSize(width, height);
}
void Camera::getPoint(float* x, float* y){
	float sw = 1;
	float sh = 1;
	if (this->use_size) this->getRatio(&sw,&sh);
	if (x){
		//if (this->use_clip) *x -= this->clip.x;
		*x /= this->sx * sw;
		//a *x -= this->offX;
		*x += this->x;
	}
	if (y){
		//if (this->use_clip) *y -= this->clip.y;
		*y /= this->sy * sh;
		//a *y -= this->offY;
		*y += this->y;
	}
}
float Camera::getPositionX(float pos, float left_bound, float right_bound){
	float left = this->getLeft() + left_bound;
	float right = this->getRight() - right_bound;
	return pos * right + (1-pos) * left;
}
float Camera::getPositionY(float pos, float top_bound, float bottom_bound){
	float top = this->getTop() + top_bound;
	float bottom = this->getBottom() - bottom_bound;
	return pos * bottom + (1-pos) * top;
}

float Camera::getLeft(){
	float sw = 1;
	if (this->use_size) this->getRatio(&sw,nullptr);
	//sw *= this->sx;
	float r = 0;
	r -= (this->offX - this->x);
	r /= sw;
	if (this->use_clip){
		r += this->clip.x / this->sx;
	}
	return r;
}
float Camera::getTop(){
	float sh = 1;
	if (this->use_size) this->getRatio(nullptr,&sh);
	//sh *= this->sy;
	float r = 0;
	r -= (this->offY - this->y);
	r /= sh;
	if (this->use_clip){
		r += this->clip.y / this->sy;
	}
	return r;
}
float Camera::getRight(){
	return this->getLeft() + this->getWidth();
}
float Camera::getBottom(){
	return this->getRight() + this->getHeight();
}
float Camera::getWidth(){
	int width_int;
	if (this->use_size) width_int = this->size.x;
	else SDL_RenderGetLogicalSize(JE::GRAPHICS::renderer, &width_int, NULL);
	float r = width_int;
	if (this->use_clip){
		r = this->clip.w;
	}
	r /= this->sx;
	return r;
}

float Camera::getHeight(){
	int height_int;
	if (this->use_size) height_int = this->size.y;
	else SDL_RenderGetLogicalSize(JE::GRAPHICS::renderer, NULL, &height_int);
	float r = height_int;
	if (this->use_clip){
		r = this->clip.h;
	}
	r /= this->sy;
	return r;
}

void Camera::startClip(){
	if (this->use_clip) {
		/* Enable Scissoring (no not *that* kind of scissoring) */
		glEnable(GL_SCISSOR_TEST);
		if (this->use_size){
			float sw = 1;
			float sh = 1;
			if (this->use_size) this->getRatio(&sw,&sh);
			SDL_Rect cliprect;
			cliprect.x = this->clip.x * sw;
			cliprect.y = this->clip.y * sh;
			cliprect.w = this->clip.w * sw;
			cliprect.h = this->clip.h * sh;
			glScissor(cliprect.x, cliprect.y, cliprect.w, cliprect.h);
		} else glScissor(this->clip.x, this->clip.y, this->clip.w, this->clip.h);
	}

}
void Camera::endClip(){
	glDisable(GL_SCISSOR_TEST);
}
void Camera::getTransforms(float* x, float* y, float* width, float* height, float* originx, float* originy){
	float sw = 1;
	float sh = 1;
	if (this->use_size) this->getRatio(&sw,&sh);
	if (x){
		*x -= this->x;
		*x += this->offX;
		*x *= this->sx * sw;
		if (this->use_clip) *x += this->clip.x;
	}
	if (y){
		*y -= this->y;
		*y += this->offY;
		*y *= this->sy * sh;
		if (this->use_clip) *y += this->clip.y;
	}
	if (width){
		*width *= this->sx * sw;
	}
	if (width){
		*height *= this->sx * sh;
	}
	if (originx){
		*originx *= this->sx * sw;
	}
	if (originy){
		*originy *= this->sx * sh;
	}
}
void Camera::getMousePosition(float* x, float* y){
	int mx_i, my_i;
	SDL_GetMouseState(&mx_i, &my_i);
	float mx = mx_i;
	float my = my_i;
	this->getPoint(&mx, &my);
	mx -= this->offX;
	my -= this->offY;
	*x = mx;
	*y = my;
}
void Camera::push(SDL_Renderer* renderer){
	glPushMatrix();
	this->startClip();
	float sw = 1;
	float sh = 1;
	if (this->use_size) this->getRatio(&sw,&sh);
	sw *= this->sx;
	sh *= this->sy;
	glTranslatef((this->offX - this->x)*sw, (this->offY - this->y)*sh, 0);
	glScalef(sw, sh, 1);
	//if (this->use_clip){
	//	glTranslatef(-this->clip.x, -this->clip.y, 0);
	//}
}
void Camera::pop(SDL_Renderer* renderer){

	this->endClip();
	glPopMatrix();
}

void tempDisableCameras(){

}
void tempEnableCameras(){

}
};};
