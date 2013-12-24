#include "jeCamera.h"

using namespace std;
jeCamera::jeCamera()
{
	this->x = 0;
	this->clip = NULL;
	this->size = NULL;
	this->reset();
}

jeCamera::~jeCamera()
{
	delete this->clip;
	delete this->size;
}

void jeCamera::reset(){
	this->sx = 1;
	this->sy = 1;
	this->x = 0;
	this->y = 0;
	if(this->clip != NULL) this->disableClip();
	if(this->size != NULL) this->disableSize();
}

void jeCamera::setScale(float x, float y){
	this->sx = x;
	this->sy = y;
}

void jeCamera::setClip(float x, float y, float w, float h){
	if (this->clip == NULL) this->clip = new SDL_Rect();
	this->clip->x = x;
	this->clip->y = y;
	this->clip->w = w;
	this->clip->h = h;
}

void jeCamera::setPosition(float x, float y){
	this->x = x;
	this->y = y;
}

void jeCamera::setSize(float w, float h){
	if (this->size == NULL) this->size = new SDL_Point();
	this->size->x = w;
	this->size->y = h;
}

void jeCamera::disableSize(){
	delete this->size;
	this->size = NULL;
}

void jeCamera::disableClip(){
	delete this->clip;
	this->clip = NULL;
}

void jeCamera::getRatio(float* x, float* y){
	int w;
	int h;
	SDL_GetWindowSize(JE::window, &w, &h);
	if (this->size){
		*x = float(w)/float(this->size->x);
		*y = float(h)/float(this->size->y);
	}else{*x = 1; *y = 1;}
}

void jeCamera::letterbox(float width, float height, float x, float y){
	int iw;
	int ih;
	SDL_GetWindowSize(JE::window, &iw, &ih);
	cout << "Window width: " << iw << "  height: " << ih << endl;
	float w = iw;
	float h = ih;

	float wratio = w/width;
	float hratio = h/height;
	cout << "Ratio width: " << wratio << "  height: " << hratio << endl;

	float ratio = w/h;
	cout << "Window ratio: " << ratio << endl;

	float tratio = width/height;
	cout << "Target ratio: " << tratio << endl;

	float fratio = 1;
	if (ratio < tratio) {
		fratio = wratio;
	}else{
		fratio = hratio;
	}

	cout << "Size width: " << width << "  height: " << height << endl;
	x = (w - width*fratio)*x;
	y = (h - height*fratio)*y;
	cout << "position x: " << x << " y: " << y << endl;
	this->setScale(fratio,fratio);
	//float rx;
	//float ry;
	//this->getRatio(&rx, &ry);
	this->setPosition(x/fratio, y/fratio);
	this->setClip(x, y, width*fratio, height*fratio);
	//cout << "ratio x: " << rx << " y: " << ry << endl;
}
