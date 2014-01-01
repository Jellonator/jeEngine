#include "jeSpritemap.h"
jeFrame::jeFrame(){
	this->rect = new SDL_Rect();
	this->length = 0;
}
jeFrame::~jeFrame(){
	delete this->rect;
}
jeSpritemap::jeSpritemap() : jeImage()
{
	this->playing = false;
	this->looping = false;
	this->time = 0;
	this->anim = 0;
	this->frame = 0;
	this->speed = 1;
}

jeSpritemap::~jeSpritemap()
{
	for (unsigned int i = 0; i < this->frames.size(); i++){
		delete this->frames[i];
	}
	for (unsigned int i = 0; i < this->anims.size(); i++){
		delete this->anims[i];
	}
}

void jeSpritemap::update(float dt){
	if (this->playing){
		this->time += dt*this->speed*this->anims[this->anim]->speed;
		bool done = false;
		while (done == false){
			//Now that is a long thing to type to get a variable.
			if (this->time >= this->frames[this->anims[this->anim]->frames[this->frame]]->length){
				this->time -= this->frames[this->anims[this->anim]->frames[this->frame]]->length;
				this->frame ++;
				if (this->frame >= (int)this->anims[this->anim]->frames.size()){
					if (looping) this->frame = 0;
					else {this->playing = false; done = true;}
				}
				this->setFrame();
			}else done = true;
		}
	}
}

void jeSpritemap::setFrame(int frame){
	if (frame >= 0) this->frame = frame;
	SDL_Rect* rect = this->frames[this->anims[this->anim]->frames[this->frame]]->rect;
	this->setClip(rect->x, rect->y, rect->w, rect->h);
}

void jeSpritemap::newFrame(float x, float y, float w, float h, float time, int ID){
	if (ID < 0){
		ID = this->frames.size();
	}
	if (ID > int(this->frames.size())-1) this->frames.resize(ID+1, NULL);
	if (this->frames[ID] == NULL) this->frames[ID] = new jeFrame();
	this->frames[ID]->rect->x = x;
	this->frames[ID]->rect->y = y;
	this->frames[ID]->rect->w = w;
	this->frames[ID]->rect->h = h;
	this->frames[ID]->length = time;
}

void jeSpritemap::newAnim(int ID, float speed){
	if (ID < 0){
		ID = this->anims.size();
	}
	if (ID > int(this->anims.size())-1) this->anims.resize(ID+1, NULL);
	if (this->anims[ID] == NULL) this->anims[ID] = new jeAnim();
	else {
		this->anims[ID]->frames.clear();
	}
	this->anims[ID]->speed = speed;
}

void jeSpritemap::play(int anim, bool loop, bool reset, int frame){
	if (anim == this->anim && this->playing){
		if (!reset) return;
	}
	this->anim = anim;
	this->frame = frame;
	this->playing = true;
	this->looping = loop;
	this->setFrame();
}

void jeSpritemap::addFrame(int anim, int frame, int pos){
	if (pos < 0) this->anims[anim]->frames.push_back(frame);
	else{
		if (pos > int(this->anims[anim]->frames.size())-1) this->anims[anim]->frames.resize(pos+1, NULL);
		this->anims[anim]->frames[pos] = frame;
	}
}

void jeSpritemap::pause(){
	this->playing = false;
}

void jeSpritemap::resume(){
	this->playing = true;
}

void jeSpritemap::reset(){
	this->frame = 0;
}

void jeSpritemap::setSpeed(float speed, int anim){
	if (anim < 0) this->speed = speed;
	else this->anims[anim]->speed = speed;
}
