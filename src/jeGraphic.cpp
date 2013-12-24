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
