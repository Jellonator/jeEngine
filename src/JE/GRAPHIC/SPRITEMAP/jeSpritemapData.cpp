#include "JE/GRAPHIC/jeSpritemap.h"
#include "JE/GRAPHIC/SPRITEMAP/jeSpritemapAnim.h"
#include "JE/GRAPHIC/SPRITEMAP/jeSpritemapData.h"
#include "JE/GRAPHIC/SPRITEMAP/jeSpritemapFrame.h"
#include <iostream>
#include <algorithm>
namespace JE{namespace GRAPHICS{
SpritemapData::SpritemapData(){

}

SpritemapData::~SpritemapData(){

}

void SpritemapData::newFrame(int x, int y, int w, int h, float time, unsigned int ID){
	this->frames.emplace(this->frames.begin() + ID, x, y, w, h, time);
}

void SpritemapData::newFrame(int x, int y, int w, int h, float time){
	this->frames.emplace_back(x, y, w, h, time);
}

void SpritemapData::newAnim(unsigned int ID, float speed){
	this->anims.emplace(this->anims.begin() + ID, speed);
}

void SpritemapData::newAnim(float speed){
	this->anims.emplace_back(speed);
}

void SpritemapData::addFrameToAnim(unsigned int anim, unsigned int frame, unsigned int ID){
	this->anims[anim].addFrame(frame, ID);
}

void SpritemapData::addFrameToAnim(unsigned int anim, unsigned int frame){
	this->anims[anim].addFrame(frame);
}

Frame& SpritemapData::getFrame(unsigned int anim, unsigned int frame){
	return this->anims[anim].getFrameFromData(frame, *this);
}

Frame& SpritemapData::getFrame(unsigned int frame){
	return this->frames[frame];
}

Anim& SpritemapData::getAnim(unsigned int anim){
	return this->anims[anim];
}

unsigned int SpritemapData::getAnimCount() const {
	return this->anims.size();
}

unsigned int SpritemapData::getFrameCount() const {
	return this->frames.size();
}

};};
