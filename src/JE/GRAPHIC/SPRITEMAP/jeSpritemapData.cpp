#include "JE/GRAPHIC/jeSpritemap.h"
#include "JE/GRAPHIC/SPRITEMAP/jeSpritemapAnim.h"
#include "JE/GRAPHIC/SPRITEMAP/jeSpritemapData.h"
#include "JE/GRAPHIC/SPRITEMAP/jeSpritemapFrame.h"
#include <algorithm>

namespace JE{namespace GRAPHICS{
SpritemapData::SpritemapData(){

}

SpritemapData::~SpritemapData(){

}

unsigned int SpritemapData::newFrame(int x, int y, int w, int h, float time, unsigned int ID){
	this->frames.resize(std::max((int)this->frames.size(), (int)ID+1));
	this->frames.at(ID).setLength(time);
	this->frames.at(ID).setSize(x, y, w, h);
	return ID;
}

unsigned int SpritemapData::newFrame(int x, int y, int w, int h, float time){
	this->frames.emplace_back(x, y, w, h, time);
	return this->frames.size()-1;
}

SpritemapAnim& SpritemapData::newAnim(const std::string& name, float speed){
	this->anims.emplace(name, speed);
	return this->anims.at(name);
}

void SpritemapData::addFrameToAnim(const std::string& anim, unsigned int frame, unsigned int ID){
	this->getAnim(anim).addFrame(frame, ID);
}

void SpritemapData::addFrameToAnim(const std::string& anim, unsigned int frame){
	this->getAnim(anim).addFrame(frame);
}

SpritemapFrame& SpritemapData::getFrame(const std::string& anim, unsigned int frame){
	return this->getAnim(anim).getFrameFromData(*this, frame);
}

SpritemapFrame& SpritemapData::getFrame(unsigned int frame){
	return this->frames.at(frame);
}

SpritemapAnim& SpritemapData::getAnim(const std::string& anim){
	return this->anims.at(anim);
}

unsigned int SpritemapData::getAnimCount() const {
	return this->anims.size();
}

unsigned int SpritemapData::getFrameCount() const {
	return this->frames.size();
}

bool SpritemapData::doesContainFrame(const SpritemapFrame& frame, unsigned int* position){
	for (std::vector<SpritemapFrame>::size_type i = 0; i != this->frames.size(); ++i){
		SpritemapFrame& other_frame = this->frames[i];
		if (&other_frame == &frame){
			if (position != nullptr){
				*position = i;
			}
			return true;
		}
	}
	return false;
}

};};
