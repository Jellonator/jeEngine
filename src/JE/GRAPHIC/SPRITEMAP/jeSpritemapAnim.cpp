#include "JE/GRAPHIC/SPRITEMAP/jeSpritemap.h"
#include "JE/GRAPHIC/SPRITEMAP/jeSpritemapAnim.h"
#include "JE/GRAPHIC/SPRITEMAP/jeSpritemapData.h"
#include "JE/GRAPHIC/SPRITEMAP/jeSpritemapFrame.h"
#include <algorithm>

namespace JE{namespace GRAPHICS{
SpritemapAnim::SpritemapAnim(){
	this->speed = 1;
}

SpritemapAnim::SpritemapAnim(float speed){
	this->speed = speed;
}

SpritemapAnim::~SpritemapAnim(){

}

//getters
float SpritemapAnim::getSpeed() const{
	return this->speed;
}

unsigned int SpritemapAnim::getFrameID(unsigned int index) const{
	return this->frames.at(index);
}

SpritemapFrame& SpritemapAnim::getFrameFromData(SpritemapData& data, unsigned int index) {
	return data.getFrame(this->getFrameID(index));
}

unsigned int SpritemapAnim::getFrameCount() const{
	return this->frames.size();
}

unsigned int SpritemapAnim::first() const{
	return 0;
}

unsigned int SpritemapAnim::last() const{
	return this->frames.size()-1;
}

//setters
void SpritemapAnim::setSpeed(float speed){
	this->speed = speed;
}

void SpritemapAnim::addFrame(unsigned int frame, unsigned int ID){
	this->frames.insert(this->frames.begin() + ID, frame);
}

void SpritemapAnim::addFrame(unsigned int frame){
	this->frames.push_back(frame);
}

void SpritemapAnim::removeFrame(unsigned int ID){
	this->frames.erase(this->frames.begin() + ID);
}

void SpritemapAnim::clearFrames(){
	this->frames.clear();
}

};};
