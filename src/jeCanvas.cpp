#include "jeCanvas.h"
#include "JE.h"
//The smallest 'useful' class in the engine.  Let's face it, jePoint is useless.
jeCanvas::jeCanvas(int width, int height) : jeImage()
{
	this->texture->texture = SDL_CreateTexture(JE::renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, width, height);
	this->bind();
	SDL_RenderClear(JE::renderer);//otherwise you get some weird white noise crap
	this->unbind();
	this->setClip(0,0,width,height);
}

jeCanvas::~jeCanvas()
{
	//dtor
}

void jeCanvas::bind(){
	SDL_SetRenderTarget(JE::renderer, this->texture->texture);
}

void jeCanvas::unbind(){
	SDL_SetRenderTarget(JE::renderer, NULL);
}
