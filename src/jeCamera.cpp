#include "jeCamera.h"
namespace JE{namespace GRAPHICS{
Camera::Camera()
{
	this->x = 0;
	this->y = 0;
	this->clip = NULL;
	this->size = NULL;
	this->reset();
}

Camera::~Camera()
{
	delete this->clip;
	delete this->size;
}

void Camera::reset(){
	this->sx = 1;
	this->sy = 1;
	this->x = 0;
	this->y = 0;
	this->offX = 0;
	this->offY = 0;
	if(this->clip != NULL) this->disableClip();
	if(this->size != NULL) this->disableSize();
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
	if (this->clip == NULL) this->clip = new SDL_Rect();
	this->clip->x = x;
	this->clip->y = y;
	this->clip->w = w;
	this->clip->h = h;
}

void Camera::setPosition(float x, float y){
	this->x = x;
	this->y = y;
}

void Camera::setSize(float w, float h){
	if (this->size == NULL) this->size = new SDL_Point();
	this->size->x = w;
	this->size->y = h;
}

void Camera::disableSize(){
	if(this->size != NULL) delete this->size;
	this->size = NULL;
}

void Camera::disableClip(){
	if (this->clip != NULL) delete this->clip;
	this->clip = NULL;
}

void Camera::getRatio(float* x, float* y){
	int w;
	int h;
	SDL_GetWindowSize(window, &w, &h);
	if (this->size){
		*x = float(w)/float(this->size->x);
		*y = float(h)/float(this->size->y);
	}else{*x = 1; *y = 1;}
}

void Camera::zoom(float width, float height, float x, float y){
	int iw = 1;
	int ih = 1;
	SDL_GetWindowSize(window, &iw, &ih);
	float w = iw;//Window width
	float h = ih;//Window height

	float wratio = w/width;
	float hratio = h/height;

	float ratio = w/h;

	float tratio = width/height;

	float fratio = 1;
	if (ratio > tratio) {
		width = width * wratio;
		height = height * wratio;
		fratio = wratio;
	}else{
		width = width * hratio;
		height = height * hratio;
		fratio = hratio;
	}
	x = (w - width)*x;
	y = (h - height)*y;
	this->setScale(fratio,fratio);
	//this->setPosition(x/fratio, y/fratio);
	//std::cout << x << " " << y << " " << width << " " << height << std::endl;
	this->offX += x / this->sx;
	this->offY += y / this->sy;
	this->setClip(x, y, width, height);
}

void Camera::letterbox(float width, float height, float x, float y){
	int iw = 1;
	int ih = 1;
	SDL_GetWindowSize(window, &iw, &ih);
	float w = iw;//Window width
	float h = ih;//Window height

	float wratio = w/width;
	float hratio = h/height;

	float ratio = w/h;

	float tratio = width/height;

	float fratio = 1;
	if (ratio < tratio) {
		width = width * wratio;
		height = height * wratio;
		fratio = wratio;
	}else{
		width = width * hratio;
		height = height * hratio;
		fratio = hratio;
	}
	x = (w - width)*x;
	y = (h - height)*y;
	this->setScale(fratio,fratio);
	//this->setPosition(x/fratio, y/fratio);
	//std::cout << x << " " << y << " " << width << " " << height << std::endl;
	this->offX += x / this->sx;
	this->offY += y / this->sy;
	this->setClip(x, y, width, height);
}
};};
