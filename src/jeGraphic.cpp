#include "jeGraphic.h"
//Not commenting this file, should be easy enough to understand
jeGraphic::jeGraphic()
{
	this->x = 0;
	this->y = 0;
	this->angle = 0;
	this->ox = 0;
	this->oy = 0;
}

jeGraphic::~jeGraphic()
{

}

void jeGraphic::draw(float x, float y, jeCamera* camera, jeEntity* entity){}
void jeGraphic::update(){}

void jeGraphic::setOrigin(float x, float y){
	this->ox = x;
	this->oy = y;
}

void jeSetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a, SDL_Renderer* renderer){
	JE::forecolor->r = r;
	JE::forecolor->g = g;
	JE::forecolor->b = b;
	JE::forecolor->a = a;
	SDL_SetRenderDrawColor(JE::renderer, r, g, b, a);
}
void jeSetColorF(float r, float g, float b, float a, SDL_Renderer* renderer){
	jeSetColor(r*255,g*255,b*255,a*255,renderer);
}
void jeSetBackgroundColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a, SDL_Renderer* renderer){
	JE::backcolor->r = r;
	JE::backcolor->g = g;
	JE::backcolor->b = b;
	JE::backcolor->a = a;
}
void jeSetBackgroundColorF(float r, float g, float b, float a, SDL_Renderer* renderer){
	jeSetBackgroundColor(r*255,g*255,b*255,a*255,renderer);
}
