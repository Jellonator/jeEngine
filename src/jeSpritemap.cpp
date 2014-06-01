#include "jeSpritemap.h"
namespace JE{namespace GRAPHICS{
SpritemapData::SpritemapData(void* owner) : Data(owner){

}

SpritemapData::~SpritemapData(){
	for (unsigned int i = 0; i < this->frames.size(); i++){
		if(this->frames[i] != NULL) delete this->frames[i];
	}
	for (unsigned int i = 0; i < this->anims.size(); i++){
		if(this->anims[i] != NULL) delete this->anims[i];
	}
	this->frames.clear();
	this->anims.clear();
}

void Spritemap::newFrame(float x, float y, float w, float h, float time, int ID){this->data->newFrame(x,y,w,h,time,ID);}
void SpritemapData::newFrame(float x, float y, float w, float h, float time, int ID){
	if (ID < 0){
		ID = this->frames.size();
	}
	if (ID > int(this->frames.size())-1) this->frames.resize(ID+1, NULL);
	if (this->frames[ID] == NULL) this->frames[ID] = new Frame();
	this->frames[ID]->rect->x = x;
	this->frames[ID]->rect->y = y;
	this->frames[ID]->rect->w = w;
	this->frames[ID]->rect->h = h;
	this->frames[ID]->length = time;
}

void Spritemap::newAnim(int ID, float speed){this->data->newAnim(ID, speed);}
void SpritemapData::newAnim(int ID, float speed){
	if (ID < 0){
		ID = this->anims.size();
	}
	if (ID > int(this->anims.size())-1) this->anims.resize(ID+1, NULL);
	if (this->anims[ID] == NULL) this->anims[ID] = new Anim();
	else {
		this->anims[ID]->frames.clear();
	}
	this->anims[ID]->speed = speed;
}

void Spritemap::addFrame(int anim, int frame, int pos){this->data->addFrame(anim, frame, pos);}
void SpritemapData::addFrame(int anim, int frame, int pos){
	if (pos < 0) this->anims[anim]->frames.push_back(frame);
	else{
		if (pos > int(this->anims[anim]->frames.size())-1) this->anims[anim]->frames.resize(pos+1, NULL);
		this->anims[anim]->frames[pos] = frame;
	}
}

Frame::Frame(){
	this->rect = new SDL_Rect();
	this->length = 0;
}

Frame::~Frame(){
	if (this->rect != NULL) delete this->rect;
}

Spritemap::Spritemap() : Image(){
	this->playing = false;
	this->looping = false;
	this->time = 0;
	this->anim = 0;
	this->frame = 0;
	this->speed = 1;
	this->data = new SpritemapData(this);
	//this->data = NULL;
}

Spritemap::~Spritemap(){
	this->clip = NULL;
	if (this->data != NULL) {if (this->data->getKill(this)) delete this->data;}
}

void Spritemap::update(float dt){
	if (this->playing){
		this->time += dt*this->speed*this->data->anims[this->anim]->speed;
		bool done = false;
		while (done == false){
			//Now that is a long thing to type to get a variable.
			if (this->time >= this->data->frames[this->data->anims[this->anim]->frames[this->frame]]->length){
				this->time -= this->data->frames[this->data->anims[this->anim]->frames[this->frame]]->length;
				this->frame ++;
				if (this->frame >= (int)this->data->anims[this->anim]->frames.size()){
					if (looping) this->frame = 0;
					else {this->playing = false; done = true; this->frame --;}
				}
				this->setFrame();
			}else done = true;
		}
	}
}

void Spritemap::drawWhole(float x, float y, Camera* camera, Entity* parent){
	SDL_Rect* temp = this->clip;
	this->clip = NULL;
	this->draw(x,y,camera,parent);
	this->clip = temp;
}

void Spritemap::setFrame(int frame){
	if (frame >= 0 ) this->frame = frame;
	this->clip = this->data->frames[this->data->anims[this->anim]->frames[this->frame]]->rect;
}

void Spritemap::setFrameNoAnim(int frame){
	if (frame >= 0) this->frame = frame;
	if (this->frame < 0) this->frame = this->data->frames.size() - 1;
	if (this->frame >= this->data->frames.size()) this->frame = 0;
	this->clip = this->data->frames[this->frame]->rect;
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
	else this->data->anims[anim]->speed = speed;
}

void Spritemap::useData(SpritemapData* data){
	if (this->data != NULL) {if (this->data->getKill(this)) delete this->data;}
	this->data = data;
}
};};
