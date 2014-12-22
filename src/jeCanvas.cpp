#include "jeCanvas.h"
#include "JE.h"
namespace JE{namespace GRAPHICS{
Canvas::Canvas(int width, int height) : Image(){
	this->texture->texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, width, height);
	SDL_SetTextureBlendMode(this->texture->texture, SDL_BLENDMODE_BLEND);
	this->clear();
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
bool Canvas::resize(int width, int height){
	if (this->width == width && this->height == height) return false;
	this->texture->kill(this);
	this->texture = new Texture(this);
	this->texture->texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, width, height);
	SDL_SetTextureBlendMode(this->texture->texture, SDL_BLENDMODE_BLEND);
	this->setClip(0,0,width,height);
	return true;
}
}}
