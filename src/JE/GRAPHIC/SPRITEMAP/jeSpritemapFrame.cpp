#include "JE/GRAPHIC/jeSpritemap.h"
#include "JE/GRAPHIC/SPRITEMAP/jeSpritemapAnim.h"
#include "JE/GRAPHIC/SPRITEMAP/jeSpritemapData.h"
#include "JE/GRAPHIC/SPRITEMAP/jeSpritemapFrame.h"
#include <iostream>
#include <algorithm>
namespace JE{namespace GRAPHICS{

Frame::Frame(int x, int y, int w, int h, float length){
	this->setSize(x, y, w, h);
	this->setLength(length);
}

Frame::Frame(){
	this->rect = {0, 0, 1, 1};
	this->length = 1;
}

Frame::~Frame(){

}

void Frame::setSize(int x, int y, int w, int h){
	this->rect.x = x;
	this->rect.y = y;
	this->rect.w = w;
	this->rect.h = h;
}

void Frame::setLength(float length){
	this->length = length;
}

const SDL_Rect& Frame::getRect() const{
	return this->rect;
}

float Frame::getLength() const{
	return this->length;
}

};};
