#include "JE/GRAPHIC/jeSpritemap.h"
#include "JE/GRAPHIC/SPRITEMAP/jeSpritemapAnim.h"
#include "JE/GRAPHIC/SPRITEMAP/jeSpritemapData.h"
#include "JE/GRAPHIC/SPRITEMAP/jeSpritemapFrame.h"
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

unsigned int Anim::getFrameID(unsigned int index) const{
	return this->frames.at(index);
}

Frame& Anim::getFrameFromData(SpritemapData& data, unsigned int index) {
	return data.getFrame(this->getFrameID(index));
}

unsigned int Anim::getFrameCount() const{
	return this->frames.size();
}

unsigned int Anim::first() const{
	return 0;
}

unsigned int Anim::last() const{
	return this->frames.size()-1;
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
