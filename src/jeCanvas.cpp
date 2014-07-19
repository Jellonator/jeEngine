#include "jeCanvas.h"
#include "JE.h"
namespace JE{namespace GRAPHICS{
Canvas::Canvas(int width, int height) : Image(){
	this->texture->texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, width, height);
	SDL_SetTextureBlendMode(this->texture->texture, SDL_BLENDMODE_BLEND);
	this->bind();
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);//otherwise you get some weird white noise crap
	this->unbind();
	this->setClip(0,0,width,height);
}

Canvas::~Canvas(){
	//dtor
}

void Canvas::bind(){
	this->binded = true;
	SDL_SetRenderTarget(renderer, this->texture->texture);
}

void Canvas::unbind(){
	SDL_SetRenderTarget(renderer, NULL);
	this->binded = false;
}
void Canvas::clear(){
	bool b = this->binded;
	this->bind();
	SDL_SetRenderDrawColor(JE::GRAPHICS::renderer, 0, 0, 0, 0);
	SDL_RenderClear(JE::GRAPHICS::renderer);
	if (!b) this->unbind();
}
};};
