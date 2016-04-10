#include "JE/GRAPHIC/SPRITEMAP/jeSpritemap.h"
#include "JE/GRAPHIC/SPRITEMAP/jeSpritemapAnim.h"
#include "JE/GRAPHIC/SPRITEMAP/jeSpritemapData.h"
#include "JE/GRAPHIC/SPRITEMAP/jeSpritemapFrame.h"
#include <iostream>
#include <algorithm>
namespace JE{namespace GRAPHICS{

SpritemapFrame::SpritemapFrame(int x, int y, int w, int h, float length){
	this->rect = {0, 0, 1, 1};
	this->length = 1;
	this->setSize(x, y, w, h);
	this->setLength(length);
}

SpritemapFrame::SpritemapFrame(){
	this->rect = {0, 0, 1, 1};
	this->length = 1;
}

SpritemapFrame::~SpritemapFrame(){

}

void SpritemapFrame::setSize(int x, int y, int w, int h){
	this->rect.x = x;
	this->rect.y = y;
	this->rect.w = w;
	this->rect.h = h;
}

void SpritemapFrame::setLength(float length){
	this->length = length;
}

const SDL_Rect& SpritemapFrame::getRect() const{
	return this->rect;
}

float SpritemapFrame::getLength() const{
	return this->length;
}

};};
