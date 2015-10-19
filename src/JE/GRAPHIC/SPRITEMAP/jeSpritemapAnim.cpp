#include "JE/GRAPHIC/jeSpritemap.h"
#include "JE/GRAPHIC/SPRITEMAP/jeSpritemapAnim.h"
#include "JE/GRAPHIC/SPRITEMAP/jeSpritemapData.h"
#include "JE/GRAPHIC/SPRITEMAP/jeSpritemapFrame.h"
#include <iostream>
#include <algorithm>
namespace JE{namespace GRAPHICS{
Anim::Anim(){
	this->speed = 1;
}

Anim::Anim(float speed){
	this->speed = speed;
}

Anim::~Anim(){

}

//getters
float Anim::getSpeed() const{
	return this->speed;
}

Frame& Anim::getFrameFromData(unsigned int index, SpritemapData& data){
	unsigned int ID = this->getFrameID(index);
	Frame& ret = data.getFrame(ID);
	return ret;
}

unsigned int Anim::getFrameID(unsigned int index) const{
	return this->frames[index];
}

unsigned int Anim::getFrameCount() const{
	return this->frames.size();
}

//setters
void Anim::setSpeed(float speed){
	this->speed = speed;
}

void Anim::addFrame(unsigned int frame, unsigned int ID){
	this->frames.insert(this->frames.begin() + ID, frame);
}

void Anim::addFrame(unsigned int frame){
	this->frames.push_back(frame);
}

void Anim::removeFrame(unsigned int ID){
	this->frames.erase(this->frames.begin() + ID);
}

void Anim::clearFrames(){
	this->frames.clear();
}

};};
