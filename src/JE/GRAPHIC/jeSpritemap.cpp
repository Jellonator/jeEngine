#include "JE/GRAPHIC/jeSpritemap.h"
#include "JE/GRAPHIC/SPRITEMAP/jeSpritemapAnim.h"
#include "JE/GRAPHIC/SPRITEMAP/jeSpritemapData.h"
#include "JE/GRAPHIC/SPRITEMAP/jeSpritemapFrame.h"
#include "JE/UTIL/jeMath.h"
#include <algorithm>

namespace JE{namespace GRAPHICS{

Spritemap::Spritemap(std::string file) : Image(){
	this->playing = false;
	this->looping = false;
	this->time = 0;
	this->anim = "";
	this->frame = 0;
	this->speed = 1;
	this->data = std::shared_ptr<SpritemapData>(new SpritemapData());
	this->load(file);
}

Spritemap::Spritemap() : Image(){
	this->playing = false;
	this->looping = false;
	this->time = 0;
	this->anim = "";
	this->frame = 0;
	this->speed = 1;
	this->data = std::shared_ptr<SpritemapData>(new SpritemapData());
}

Spritemap::~Spritemap(){

}

Anim& Spritemap::getCurrentAnim(){
	return this->getAnim(this->anim);
}

Frame& Spritemap::getCurrentFrame(){
	return this->getFrame(this->anim, this->frame);
}

//new frame
unsigned int Spritemap::newFrame(int x, int y, int w, int h, float time, unsigned int ID){
	return this->data->newFrame(x,y,w,h,time,ID);
}

unsigned int Spritemap::newFrame(int x, int y, int w, int h, float time){
	return this->data->newFrame(x,y,w,h,time);
}

//new anim
Anim& Spritemap::newAnim(const std::string& name, float speed){
	return this->data->newAnim(name, speed);
}

//add frame
void Spritemap::addFrameToAnim(const std::string& anim, unsigned int frame, unsigned int ID){
	this->data->addFrameToAnim(anim, frame, ID);
}

void Spritemap::addFrameToAnim(const std::string& anim, unsigned int frame){
	this->data->addFrameToAnim(anim, frame);
}

//get frame
Frame& Spritemap::getFrame(const std::string& anim, unsigned int frame){
	return this->data->getFrame(anim, frame);
}

Frame& Spritemap::getFrame(unsigned int frame){
	return this->data->getFrame(frame);
}

//get anim
Anim& Spritemap::getAnim(const std::string& anim){
	return this->data->getAnim(anim);
}

//count
unsigned int Spritemap::getFrameCount() const{
	return this->data->getFrameCount();
}

unsigned int Spritemap::getAnimCount() const{
	return this->data->getAnimCount();
}

//update
void Spritemap::update(float dt){
	if (this->playing){
		this->time += dt*this->speed*this->getCurrentAnim().getSpeed();
		
		while (this->time >= this->getCurrentFrame().getLength()){
			this->time -= this->getCurrentFrame().getLength();
			
			if (this->looping) {
				this->frame = (this->frame + 1) % this->getCurrentAnim().getFrameCount();
			} else {
				if (this->frame >= this->getCurrentAnim().last()){
					this->playing = false;
				} else {
					this->frame ++;
				}
			}
			
			this->updateClip();
		}
		
	}
}

void Spritemap::drawWhole(float x, float y, float angle, const std::shared_ptr<Entity>& parent){
	bool temp = this->use_clip;
	this->use_clip = false;
	this->draw(x,y,angle,parent);
	this->use_clip = temp;
}

void Spritemap::updateClip(){
	this->clip = this->getCurrentFrame().getRect();
	this->use_clip = true;
}

void Spritemap::setFrame(const std::string& name, unsigned int frame){
	this->anim = name;
	this->frame = frame;
	this->playing = false;
}

void Spritemap::setFrame(unsigned int frame){
	this->frame = frame;
	this->updateClip();
}

void Spritemap::setFrameNoAnim(unsigned int frame){
	this->use_clip = true;
	this->clip = this->getFrame(frame).getRect();
}

void Spritemap::play(const std::string& anim, bool loop, bool reset, unsigned int frame){
	if (anim == this->anim && this->playing){
		if (!reset) return;
	}
	this->anim = anim;
	this->frame = frame;
	this->playing = true;
	this->looping = loop;
	this->time = 0;
	this->updateClip();
}

void Spritemap::pause(){
	this->playing = false;
}

void Spritemap::resume(){
	this->playing = true;
}

void Spritemap::reset(){
	this->frame = 0;
}

void Spritemap::setSpeed(float speed){
	this->speed = speed;
}

std::shared_ptr<SpritemapData> Spritemap::getData(){
	return this->data;
}

void Spritemap::useData(Spritemap& spritemap){
	this->useData(spritemap.getData());
}

void Spritemap::useData(std::shared_ptr<SpritemapData> data){
	this->data = data;
}

void Spritemap::drawFrame(const std::string& anim, unsigned int frame, float x, float y, float angle, const std::shared_ptr<Entity>& parent){
	int temp = this->frame;
	this->setFrame(frame);
	this->draw(x, y, angle, parent);
	this->setFrameNoAnim(temp);
}
void Spritemap::drawFrameNoAnim(unsigned int frame, float x, float y, float angle, const std::shared_ptr<Entity>& parent){
	int temp = this->frame;
	this->setFrameNoAnim(frame);
	this->draw(x, y, angle, parent);
	this->setFrameNoAnim(temp);
}

bool Spritemap::doesContainFrame(const Frame& frame, unsigned int* position){
	return this->data->doesContainFrame(frame, position);
}

};};
