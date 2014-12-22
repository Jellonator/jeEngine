#include "jeDivider.h"
namespace JE{namespace GUI{
Divider::Divider(int x, int y, int width, int height, bool vertical, bool isStatic) : Frame(x,y,width,height){
	this->style.visible = false;
	this->isStatic = isStatic;
	this->vertical = vertical;
	this->style.border = 2;
	this->style.space = (isStatic)?2:6;
	this->dragging = -1;
	this->mouse_down = false;
}

Divider::~Divider(){
	//dtor
}

void Divider::addFrame(Frame* frame, std::string name, int position){
	this->frames_named[name] = frame;
	if (position < 0 || position >= this->frames.size()) this->frames.push_back(frame);
	else this->frames.insert(frames.begin()+position, frame);
	if (this->frames.size() > 1) this->positions.push_back(0.5f);
	for (int i = 0; i < this->positions.size(); i ++) {this->positions[i] = float(i+1)/float(this->positions.size()+1);}
	this->updateFrames();
}

void Divider::updateFrames(){
	for (int i = 0; i < this->frames.size(); i++){
		Frame* frame = this->frames[i];
		//virtual divider size, including border size
		float divider_x = this->x + this->style.border;
		float divider_y = this->y + this->style.border;
		float divider_width = this->width - this->style.border*2;
		float divider_height = this->height - this->style.border*2;
	//frame size, subtracts spacing from the dimensions to space out the frames
		//upper left corner
		frame->x = divider_x;
		frame->y = divider_y;
		if(this->vertical)frame->y=getPositionStart(i)+this->y; else frame->x=getPositionStart(i)+this->x;
	//lower right corner
		float divider_x2 = divider_x + divider_width;
		float divider_y2 = divider_y + divider_height;
		if(this->vertical)divider_y2=getPositionEnd(i)+this->y; else divider_x2=getPositionEnd(i)+this->x;
	//calculate width and height, use abs just in case
		frame->setSize(divider_x2 - frame->x, divider_y2 - frame->y);
	}
}

float Divider::getPositionLeft(std::string name){
	int position = getID(name);
	return this->getPositionStart(position);
}

float Divider::getPositionRight(std::string name){
	int position = getID(name);
	return this->getPositionEnd(position);
}

float Divider::getPositionLeftF(std::string name){
	int position = getID(name);
	if (position < 0) return 0;
	else if (position >= this->positions.size()) return 1;
	else return this->positions[position];
}

float Divider::getPositionRightF(std::string name){
	int position = getID(name);
	//position --;
	if (position < 0) return 0;
	else if (position >= this->positions.size()) return 1;
	else return this->positions[position];
}

float Divider::getPositionStart(int position){
	position --;
	float s = getLogicalSize();
	if (position < 0) return this->style.border;
	if (position >= this->positions.size()) return s + this->style.border;
	return this->positions[position]*s + this->style.border + this->style.space;
}

float Divider::getPositionEnd(int position){
	//position --;
	float s = getLogicalSize();
	if (position < 0) return this->style.border;
	if (position >= this->positions.size()) return s + this->style.border;
	return this->positions[position]*s + this->style.border - this->style.space;
}

float Divider::getPosition(int position){
	//position --;
	float s = getLogicalSize();
	if (position < 0) return this->style.border;
	if (position >= this->positions.size()) return s + this->style.border;
	return this->positions[position]*s;
}

float Divider::getPositionF(int position){
	if (position < 0) return 0;
	if (position >= this->positions.size()) return 1;
	return this->positions[position];
}

bool Divider::setPositionF(int position, float value){
	if (position < 0 || position >= this->positions.size()) return false;
	value = std::max(getPositionF(position-1)*getLogicalSize() + this->style.space*2 + this->style.minlength, value*getLogicalSize()) / getLogicalSize();
	value = std::min(getPositionF(position+1)*getLogicalSize() - this->style.space*2 - this->style.minlength, value*getLogicalSize()) / getLogicalSize();
	this->positions[position] = value;
	this->updateFrames();
	return true;
}

bool Divider::setPosition(int position, float value){
	this->setPositionF(position, value/getLogicalSize());
}

void Divider::OnDraw(){
	Frame::OnDraw();
	for (int i = 0; i < this->frames.size(); i ++) this->frames[i]->OnDraw();
}
void Divider::OnUpdate(){
	if (!this->isStatic){
		int mx;
		int my;
		bool mouse_new = (SDL_GetMouseState(&mx, &my) & SDL_BUTTON_LEFT);
		if (this->dragging >= 0){
			if (!mouse_new) this->dragging = -1;
			float pos = this->getPosition(this->dragging);
			float to = (this->vertical) ? my - this->y : mx - this->x;
			pos = JE::MATH::smoothTween(pos, to, 100);
			this->setPosition(this->dragging, pos);

		}else{
			if (mouse_new && !this->mouse_down){
				if (mx >= this->x && my >= this->y && mx <= this->x + this->width && my <= this->y + this->height){
					int mpos = (this->vertical)?my:mx;
					for (int i = 0; i < this->positions.size(); i ++){
						int position = this->getPosition(i) + ((this->vertical) ? this->y : this->x);
						if (mpos <= position + this->style.space + this->style.dragspace && mpos >= position - this->style.space - this->style.dragspace){
							this->dragging = i;
						}
					}
				}
			}
		}
		this->mouse_down = mouse_new;
	}
	Frame::OnUpdate();
	for (int i = 0; i < this->frames.size(); i ++) this->frames[i]->OnUpdate();
}
void Divider::update(){};
void Divider::draw(){};
float Divider::getLogicalSize(){
	return ((this->vertical)?this->height:this->width)-this->style.border*2;
}
int Divider::getID(std::string name){
	Frame* frame = this->frames_named[name];
	if (frame == NULL){std::cout << "JE-Error: no such frame named '" << name << "'" << std::endl; return 0;}
	int position = -1;
	for (int i = 0; i < this->frames.size(); i ++) {if (this->frames[i] == frame) position = i;}
	return position;
}
bool Divider::setPositionLeftF(std::string name, float value){
	int i = getID(name);
	i --;
	if (i < 0 || i >= this->positions.size()) return false;
	this->setPositionF(i, value);
	return true;
}

bool Divider::setPositionRightF(std::string name, float value){
	int i = getID(name);
	if (i < 0 || i >= this->positions.size()) return false;
	this->setPositionF(i, value);
	return true;
}

bool Divider::setPositionLeft(std::string name, float value){
	int i = getID(name);
	i --;
	value -= this->style.space;
	if (i < 0 || i >= this->positions.size()) return false;
	this->setPosition(i, value);
	return true;
}

bool Divider::setPositionRight(std::string name, float value){
	int i = getID(name);
	value += this->style.space;
	if (i < 0 || i >= this->positions.size()) return false;
	this->setPosition(i, value);
	return true;
}

void Divider::setSize(int width, int height){
	Frame::setSize(width, height);
	for (int i = 0; i < this->positions.size(); i ++) this->setPositionF(i, this->getPositionF(i));
	updateFrames();
}

void Divider::setVertical(bool vertical){this->vertical = vertical;this->updateFrames();}
void Divider::setStatic(bool isStatic){this->isStatic = isStatic;this->updateFrames();}
}}
