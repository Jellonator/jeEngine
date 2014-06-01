#include "jeCanvas.h"
#include "JE.h"
namespace JE{namespace GRAPHICS{
Canvas::Canvas(int width, int height) : Image()
{
	this->texture->texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, width, height);
	this->bind();
	SDL_RenderClear(renderer);//otherwise you get some weird white noise crap
	this->unbind();
	this->setClip(0,0,width,height);
}

Canvas::~Canvas()
{
	//dtor
}

void Canvas::bind(){
	SDL_SetRenderTarget(renderer, this->texture->texture);
}

void Canvas::unbind(){
	SDL_SetRenderTarget(renderer, NULL);
};
};};
