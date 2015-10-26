#include "JE/jeEntity.h"
#include "JE/GRAPHIC/jeCamera.h"
#include "JE/GRAPHIC/jeImage.h"
#include <iostream>
#include <cmath>
#include <vector>

namespace JE{namespace GRAPHICS{
using namespace std;

Texture::Texture(SDL_Texture* tex){
	this->texture = tex;
}
Texture::Texture(std::string file){
	this->texture = nullptr;
	this->load(file);
	SDL_SetTextureBlendMode(this->get(), SDL_BLENDMODE_BLEND);
}
Texture::~Texture(){
	if (this->texture != nullptr) SDL_DestroyTexture(this->texture);
}
void Texture::set(SDL_Texture* tex){
	if (this->texture != nullptr) SDL_DestroyTexture(this->texture);
	this->texture = tex;
}
SDL_Texture* Texture::get() const{
	return this->texture;
}
void Texture::getSize(int* width, int* height){
	SDL_QueryTexture(this->texture, NULL, NULL, width, height);
}

void Texture::load(std::string file, SDL_Renderer* renderer){
	SDL_Surface* s = IMG_Load(file.c_str());
	if (s == nullptr) {
		std::cout << SDL_GetError() << std::endl;
	}else{
		SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, s);
		if (tex == nullptr)
			std::cout << SDL_GetError() << std::endl;
		else
			this->set(tex);
		SDL_FreeSurface(s);
	}
}

Image::Image() : Graphic(){
	this->texture = std::shared_ptr<Texture>(new Texture(NULL));
	//this->flip = SDL_FLIP_NONE;
	this->width = -1;
	this->height = -1;
	this->use_clip = false;
	this->flip_x = 1;
	this->flip_y = 1;
}

Image::Image(std::string file) : Graphic(){
	this->texture = std::shared_ptr<Texture>(new Texture(NULL));
	//this->flip = SDL_FLIP_NONE;
	this->width = -1;
	this->height = -1;
	this->use_clip = false;
	this->flip_x = 1;
	this->flip_y = 1;
	this->load(file);
}

Image::~Image(){

}

void Image::setColor(int r, int g, int b, int a){
	if (!this->texture) return;
	SDL_SetTextureColorMod(this->texture->get(),r,g,b);
	SDL_SetTextureAlphaMod(this->texture->get(),a);
}
void Image::draw(float x, float y, float angle){
	bool do_rotate = (std::abs(angle + this->angle) > 0.001 || this->flip_x != 1 || this->flip_y != 1);
	float draw_x, draw_y, draw_w, draw_h, texture_x, texture_y, texture_w, texture_h;
	draw_x = x + this->x;
	draw_y = y + this->y;
	texture_x = 0;
	texture_y = 0;
	SDL_GL_BindTexture(this->texture->get(), &texture_w, &texture_h);
	if (this->use_clip){
		texture_x = this->clip.x;
		texture_y = this->clip.y;
		texture_w = this->clip.w;
		texture_h = this->clip.h;
	}
	//std::cout << "texture size: " << this->width << ", " << this->height << std::endl;
	draw_w = (this->width > 0) ? this->width : texture_w;
	draw_h = (this->height> 0) ? this->height: texture_h;
	//if (this->flip_x == -1) draw_x += (draw_w);
	//if (this->flip_y == -1) draw_y += (draw_h);
	//draw_w *= this->flip_x;
	//draw_h *= this->flip_y;
	if (do_rotate){
		float mat[16];
		glGetFloatv(GL_PROJECTION_MATRIX, mat);
		//kinda wish I didn't have to do this, but eh, it's not a big deal.
		float x_move = mat[12] + draw_x + this->ox;
		float y_move = mat[13] + draw_y + this->oy;
		float z_move = mat[14];
		glPushMatrix();
		glTranslatef( x_move, y_move, z_move);
		glRotatef(angle, 0, 0, 1.0);
		glScalef(this->flip_x, this->flip_y, 1.0f);
		glTranslatef(-x_move,-y_move,-z_move);
	}
	glBegin( GL_QUADS );//aww yeah work dem (outdated opengl 1.2) quads!
		glColor4f(forecolor.r, forecolor.g, forecolor.b, forecolor.a);
		glTexCoord2f(texture_x,           texture_y);
		glVertex3f(  draw_x,              draw_y,  0.0f );

		glTexCoord2f(texture_x+texture_w, texture_y);
		glVertex3f(  draw_x   +draw_w,    draw_y,  0.0f );

		glTexCoord2f(texture_x+texture_w, texture_y+texture_h);
		glVertex3f(  draw_x   +draw_w,    draw_y   +draw_h,  0.0f );

		glTexCoord2f(texture_x,           texture_y+texture_h);
		glVertex3f(  draw_x,              draw_y   +draw_h,  0.0f );
	glEnd( );
	SDL_GL_UnbindTexture(this->texture->get());
	if (do_rotate){
		glPopMatrix();
	}
}

void Image::load(std::string file, SDL_Renderer* renderer){
	this->texture->load(file, renderer);
}

void Image::setClip(float x, float y, float w, float h){
	this->clip.x = x;
	this->clip.y = y;
	this->clip.w = w;
	this->clip.h = h;
	this->use_clip = true;
}

void Image::setScale(float x, float y){
	int w, h;
	if (this->use_clip){
		w = this->clip.w;
		h = this->clip.h;
	}else{
		SDL_QueryTexture(this->texture->get(), NULL, NULL, &w, &h);
	}
	if (y < 0) y = x;
	this->setSize(w*x, h*y);
}

void Image::setSize(float w, float h){
	this->width = w;
	this->height = h;
	//std::cout << "setting size to w=" << w << ", h=" << h << std::endl;
}

void Image::disableSize(){
	this->setSize(-1, -1);
}

Image* copyImage(Image* image){
	if (image == NULL) return NULL;
	Image* r;
	r = new Image();
	r->x       = image->x;
	r->y       = image->y;
	r->ox      = image->ox;
	r->oy      = image->oy;
	r->angle   = image->angle;
	//r->flip    = image->flip;
	r->width   = image->width;
	r->height  = image->height;
	r->clip    = image->clip;
	r->use_clip= image->use_clip;
	r->texture = image->texture;
	return r;
}

void Image::useTexture(std::shared_ptr<Texture> texture){
	this->texture = texture;
}

void Image::useTexture(const std::shared_ptr<Image>& img){
	this->useTexture(img->texture);
}

void Image::centerOrigin(){
	int x, y;
	SDL_QueryTexture(this->texture->get(), NULL, NULL, &x, &y);
	this->ox = float(x)/2;
	this->oy = float(y)/2;
}
void Image::getSize(int* width, int* height){
	SDL_QueryTexture(this->texture->get(), NULL, NULL, width, height);
}
void Image::drawSection(float x, float y, int section_x, int section_y, int section_width, int section_height){
	SDL_Rect previous_rect = this->clip;
	bool previous_bool = this->use_clip;
	this->setClip(section_x, section_y, section_width, section_height);
	this->draw(x, y, 0);
	this->clip = previous_rect;
	this->use_clip = previous_bool;
}
void Image::setFlip(bool x, bool y){
	this->flip_x = x ? -1 : 1;
	this->flip_y = y ? -1 : 1;
}
};};
