#include "JE/GRAPHIC/jeSpritemap.h"
#include <iostream>
#include <algorithm>
namespace JE{namespace GRAPHICS{
SpritemapData::SpritemapData(){

}

SpritemapData::~SpritemapData(){

}

void Spritemap::newFrame(int x, int y, int w, int h, float time, int ID){this->data->newFrame(x,y,w,h,time,ID);}
void SpritemapData::newFrame(int x, int y, int w, int h, float time, int ID){
	if (ID < 0){
		ID = this->frames.size();
	}
	this->frames.resize(std::max((int)this->frames.size(),ID+1));
	this->frames[ID].set(x, y, w, h, time);
}

void Spritemap::newAnim(int ID, float speed){this->data->newAnim(ID, speed);}
void SpritemapData::newAnim(int ID, float speed){
	if (ID < 0){
		ID = this->anims.size();
	}
	this->anims.resize(std::max((int)this->anims.size(),ID+1));
	this->anims[ID].frames.clear();
	this->anims[ID].speed = speed;
}

void Spritemap::addFrame(int anim, int frame, int ID){this->data->addFrame(anim, frame, ID);}
void SpritemapData::addFrame(int anim, int frame, int ID){
	if (ID < 0){
		ID = this->anims[anim].frames.size();
	}

	this->anims[anim].frames.resize(std::max((int)this->anims[anim].frames.size(),ID+1));
	this->anims[anim].frames[ID] = frame;
}

Frame* Spritemap::getFrame(int anim, int frame){return this->data->getFrame(anim, frame);}
Frame* SpritemapData::getFrame(int anim, int frame){
	return &this->frames[this->anims[anim].frames[frame]];
}
Frame* Spritemap::getFrame(int frame){return this->data->getFrame(frame);}
Frame* SpritemapData::getFrame(int frame){
	return &this->frames[frame];
}
Anim* Spritemap::getAnim(int anim){return this->data->getAnim(anim);}
Anim* SpritemapData::getAnim(int anim){
	return &this->anims[anim];
}

Frame::Frame(){
	this->rect = {0, 0, 1, 1};
	this->length = 1;
}

Frame::~Frame(){

}

Anim::Anim(){
	this->speed = 1;
}

Anim::~Anim(){

}

void Anim::setSpeed(float speed){
	this->speed = speed;
}

void Frame::set(int x, int y, int w, int h, float length){
	this->rect.x = x;
	this->rect.y = y;
	this->rect.w = w;
	this->rect.h = h;
	this->length = length;
}

Spritemap::Spritemap(std::string file) : Image(){
	this->playing = false;
	this->looping = false;
	this->time = 0;
	this->anim = 0;
	this->frame = 0;
	this->speed = 1;
	this->data = std::shared_ptr<SpritemapData>(new SpritemapData());
	this->load(file);
}

Spritemap::Spritemap() : Image(){
	this->playing = false;
	this->looping = false;
	this->time = 0;
	this->anim = 0;
	this->frame = 0;
	this->speed = 1;
	this->data = std::shared_ptr<SpritemapData>(new SpritemapData());
	//this->data = NULL;
}

Spritemap::~Spritemap(){
	//this->clip = NULL;
	//if (this->data != NULL) {this->data->kill(this);}
}

int Spritemap::getFrameCount(){
	return this->data->frames.size();
}

int Spritemap::getAnimFrameCount(int anim){
	return this->getAnim(anim)->frames.size();
}

int Spritemap::getAnimCount(){
	return this->data->anims.size();
}

float Spritemap::getFrameLength(int frame){
	return this->getFrame(frame)->length;
}

float Spritemap::getAnimFrameLength(int anim, int frame){
	return this->getFrame(anim, frame)->length;
}

SDL_Rect& getFrameRect(int frame){
	
}

SDL_Rect& getAnimFrameRect(int anim, int frame){
	
}

void Spritemap::update(float dt){
	if (this->playing){
		this->time += dt*this->speed*this->getAnim(this->anim)->speed;
		
		while (this->time >= this->getFrame(this->anim, this->frame)->length){
			this->time -= this->getFrame(this->anim, this->frame)->length;
			++this->frame;
			if (this->frame >= (int)this->getAnim(this->anim)->frames.size()){
				if (this->looping) this->frame = 0;
				else {this->playing = false; done = true; this->frame --;}
			}
		}
		this->setFrame();
	}
}

void Spritemap::drawWhole(float x, float y, float angle, const std::shared_ptr<Entity>& parent){
	bool temp = this->use_clip;
	this->use_clip = false;
	this->draw(x,y,angle,parent);
	this->use_clip = temp;
}

void Spritemap::setFrame(int frame){
	if (frame >= 0) this->frame = frame;
	this->clip = this->getFrame(this->anim, this->frame)->rect;
	this->use_clip = true;
}

void Spritemap::setFrameNoAnim(int frame){
	if (frame >= 0) this->frame = frame;
	if (this->frame < 0) this->frame = this->getFrameCount() - 1;
	if (this->frame >= this->getFrameCount()) this->frame = 0;
	this->clip = this->getFrame(this->frame)->rect;
	this->use_clip = true;
}

void Spritemap::play(int anim, bool loop, bool reset, int frame){
	if (anim == this->anim && this->playing){
		if (!reset) return;
	}
	this->anim = anim;
	this->frame = frame;
	this->playing = true;
	this->looping = loop;
	this->setFrame();
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

void Spritemap::setSpeed(float speed, int anim){
	if (anim < 0) this->speed = speed;
	else this->data->anims[anim].speed = speed;
}

void Spritemap::useData(const std::shared_ptr<Spritemap>& spritemap){
	this->useData(spritemap->data);
}

void Spritemap::useData(std::shared_ptr<SpritemapData> data){
	//if (this->data != NULL) {this->data->kill(this);}
	//this->data.reset();
	this->data = data;
}

void Spritemap::drawFrame(int frame, float x, float y, float angle, const std::shared_ptr<Entity>& parent){
	int temp = this->frame;
	this->setFrame(frame);
	this->draw(x, y, angle, parent);
	this->setFrameNoAnim(temp);
}
void Spritemap::drawFrameNoAnim(int frame, float x, float y, float angle, const std::shared_ptr<Entity>& parent){
	int temp = this->frame;
	this->setFrameNoAnim(frame);
	this->draw(x, y, angle, parent);
	this->setFrameNoAnim(temp);
}
};};
