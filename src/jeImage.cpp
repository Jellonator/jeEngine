#include "jeImage.h"
#include "JE.h"
#include <SDL2/SDL_image.h>
using namespace std;
jeTexture::jeTexture(void* owner) : jeData(owner){
	this->texture = NULL;
}
jeTexture::~jeTexture(){
	if(this->texture != NULL) {SDL_DestroyTexture(this->texture);}
}
jeImage::jeImage() : jeGraphic()
{
	this->texture = new jeTexture(this);
	this->flip = SDL_FLIP_NONE;
	this->w = -1;
	this->h = -1;
	this->clip = NULL;
}

jeImage::~jeImage()
{
	if(this->clip != NULL) delete this->clip;
	if (this->texture != NULL) {if (this->texture->getKill(this)) delete this->texture;}
}

void jeImage::draw(float x, float y, jeCamera* camera, jeEntity* parent, SDL_Renderer* renderer){
	//If the texture exists
	if (this->texture->texture != NULL){
		//create two rectangles
		SDL_Rect* srcrect = NULL;
		SDL_Rect* dstrect = new SDL_Rect();

		float ox = this->ox;
		float oy = this->oy;

		int w, h;

		if (this->clip){
			srcrect = new SDL_Rect();
			srcrect->x = this->clip->x;
			srcrect->y = this->clip->y;
			srcrect->w = this->clip->w;
			srcrect->h = this->clip->h;
			w = this->clip->w;
			h = this->clip->h;
		}else{
			SDL_QueryTexture(this->texture->texture, NULL, NULL, &w, &h);
		}

		float dx = 0, dy = 0, dw = 1, dh = 1;
		dx = this->x + x;
		dy = this->y + y;

		if(this->w > 0) dw = this->w; else
			dw = w;
		if(this->h > 0) dh = this->h; else
			dh = h;

		if(parent){
			dx += parent->x;
			dy += parent->y;
		}

		if(camera){
			float sw = 1;
			float sh = 1;
			if (camera->size) camera->getRatio(&sw,&sh);
			dx += camera->x;
			dy += camera->y;
			dx *= camera->sx * sw;
			dy *= camera->sy * sh;
			dw *= camera->sx * sw;
			dh *= camera->sy * sh;
			ox *= camera->sx * sw;
			oy *= camera->sy * sh;
			if (camera->clip) {
				if (camera->size){
					SDL_Rect* cliprect = new SDL_Rect();
					cliprect->x = camera->clip->x * sw;
					cliprect->y = camera->clip->y * sh;
					cliprect->w = camera->clip->w * sw;
					cliprect->h = camera->clip->h * sh;
					SDL_RenderSetClipRect(renderer, cliprect);
					delete cliprect;
				} else SDL_RenderSetClipRect(renderer, camera->clip);
			}
		}
		dstrect->x = dx;
		dstrect->y = dy;
		dstrect->w = dw;
		dstrect->h = dh;

		SDL_Point* origin = new SDL_Point();
		origin->x = ox;
		origin->y = oy;
		SDL_RenderCopyEx(renderer, this->texture->texture, srcrect, dstrect, this->angle, origin, this->flip);
		SDL_RenderSetClipRect(renderer, NULL);
		delete srcrect;
		delete dstrect;
		delete origin;
	}
}
void jeImage::load(std::string file, SDL_Renderer* renderer){
	this->texture->load(file, renderer);
}
void jeTexture::load(std::string file, SDL_Renderer* renderer){
	SDL_Surface* s = IMG_Load(file.c_str());
	if (s == NULL) {
		std::cout << SDL_GetError() << std::endl;
	}else{
		this->texture = SDL_CreateTextureFromSurface(JE::renderer, s);
		if (this->texture == NULL) {std::cout << SDL_GetError() << std::endl;}
		SDL_FreeSurface(s);
	}
}

void jeImage::setClip(float x, float y, float w, float h){
	if(this->clip == NULL) this->clip = new SDL_Rect();
	this->clip->x = x;
	this->clip->y = y;
	this->clip->w = w;
	this->clip->h = h;
}

void jeImage::setScale(float x, float y){
	int w, h;
	if (this->clip){
		w = this->clip->w;
		h = this->clip->h;
	}
	if (y < 0) y = x;
	this->setSize(w*x, h*y);
}

void jeImage::setSize(float w, float h){
	this->w = w;
	this->h = h;
}

jeImage* jeCopyImage(jeImage* image){
	if (image == NULL) return NULL;
	jeImage* r;
	r = new jeImage();
	r->x		= image->x;
	r->y		= image->y;
	r->ox		= image->ox;
	r->oy		= image->oy;
	r->angle	= image->angle;
	r->flip		= image->flip;
	r->w		= image->w;
	r->h		= image->h;
	r->clip 	= new SDL_Rect();
	r->clip->x 	= image->clip->x;
	r->clip->y 	= image->clip->y;
	r->clip->w 	= image->clip->w;
	r->clip->h 	= image->clip->h;
	r->texture = image->texture;
	return r;
}

void jeImage::useTexture(jeTexture* texture){
	if (this->texture != NULL) {if (this->texture->getKill(this)) delete this->texture;}
	this->texture = texture;
}
