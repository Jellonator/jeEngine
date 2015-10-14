#include "jeCanvas.h"
namespace JE{namespace GRAPHICS{
Canvas::Canvas(int width, int height) : Image(){
	this->texture->set(SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, width, height));
	SDL_SetTextureBlendMode(this->texture->get(), SDL_BLENDMODE_BLEND);
	this->clear();
	this->setClip(0,0,width,height);
}

Canvas::~Canvas(){
	//dtor
}

void Canvas::bind(){
	this->binded = true;
	SDL_SetRenderTarget(renderer, this->texture->get());
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
	this->texture->set(SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, width, height));
	SDL_SetTextureBlendMode(this->texture->get(), SDL_BLENDMODE_BLEND);
	this->setClip(0,0,width,height);
	return true;
}
void Canvas::setPixel(int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a){
	JE::GRAPHICS::setColor(r, g, b, a);
	this->setPixelp(x, y);
}
void Canvas::setPixelf(int x, int y, float r, float g, float b, float a){
	JE::GRAPHICS::setColorF(r, g, b, a);
	this->setPixelp(x, y);
}
void Canvas::setPixelp(int x, int y){
	this->bind();
	SDL_SetTextureBlendMode(this->texture->get(), SDL_BLENDMODE_NONE);
	SDL_RenderDrawPoint(JE::GRAPHICS::renderer, x, y);
	SDL_SetTextureBlendMode(this->texture->get(), SDL_BLENDMODE_BLEND);
	this->unbind();
}
}}
