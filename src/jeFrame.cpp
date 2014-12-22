#include "jeFrame.h"
namespace JE{namespace GUI{
Style::Style(Uint8 r, Uint8 g, Uint8 b, Uint8 a){
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
	this->visible = true;
	this->smooth = true;
	this->space = 1;
	this->border = 0;
	this->minlength = 16;
	this->dragspace = 2;
}
void Style::drawRect(float x, float y, float w, float h, GRAPHICS::Camera* camera){
	if (!this->visible) return;
	if (!this->smooth) {
		JE::GRAPHICS::setColor(this->r, this->g, this->b, this->a);
		JE::GRAPHICS::fillRect(x, y, w, h, camera);
	}
	else{
		//camera stuff
		float sx = 1;
		float sy = 1;
		if (camera) {sx /= camera->sx; sy /= camera->sy;}
		//smooth border
		JE::GRAPHICS::setColor(this->r, this->g, this->b, this->a*0.8);
		JE::GRAPHICS::drawRect(x, y, w, h, camera);
		JE::GRAPHICS::setColor(this->r, this->g, this->b, this->a*0.9);
		JE::GRAPHICS::drawRect(x, y+sy, w, h-2*sy, camera);
		JE::GRAPHICS::drawRect(x+sx, y, w-2*sx, h, camera);
		//main block
		JE::GRAPHICS::setColor(this->r, this->g, this->b, this->a);
		JE::GRAPHICS::fillRect(x+sx, y+sy, w-2*sx, h-2*sy, camera);
	}
}
Frame::Frame(int x, int y, int width, int height) : JE::Entity(x, y) , style(255,255,255)
{
	this->canvas = new JE::GRAPHICS::Canvas(width, height);
	this->width = width;
	this->height = height;
	this->needs_redraw = true;
}

Frame::~Frame()
{
	delete this->canvas;
}

void Frame::OnDraw(){
	if (this->needs_redraw){
		this->canvas->clear();
		this->canvas->bind();
		this->style.drawRect(0,0,this->width, this->height);
		Entity::OnDraw();
		this->draw();
		this->canvas->unbind();
		this->needs_redraw = false;
	}
	this->canvas->draw(0,0,NULL,this);
}
void Frame::OnUpdate(){Entity::OnUpdate();this->update();}
void Frame::update(){};
void Frame::draw(){};
void Frame::setSize(int width, int height){
	this->width = width;
	this->height = height;
	this->canvas->resize(width, height);
	this->redraw();
}
void Frame::redraw(){this->needs_redraw = true;}
}}
