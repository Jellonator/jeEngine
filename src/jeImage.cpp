#include "jeImage.h"
#include "jeEntity.h"

jeImage::jeImage() : jeGraphic()
{
	this->flip = SDL_FLIP_NONE;
	this->w = -1;
	this->h = -1;
	this->clip = NULL;
}

jeImage::~jeImage()
{
	//SDL_DestroyTexture(this->texture);
	delete this->clip;
}

void jeImage::draw(float x, float y, jeCamera* camera, jeEntity* parent, SDL_Renderer* renderer){
	//If the texture exists
	if (this->texture != NULL){
		//create two rectangles
		SDL_Rect* srcrect = new SDL_Rect();
		SDL_Rect* dstrect = new SDL_Rect();

		float ox = this->ox;
		float oy = this->oy;

		srcrect->x = this->clip->x;
		srcrect->y = this->clip->y;
		srcrect->w = this->clip->w;
		srcrect->h = this->clip->h;

		float dx = 0, dy = 0, dw = 1, dh = 1;
		dx = this->x + x;
		dy = this->y + y;

		if(this->w > 0) dw = this->w; else
			dw = this->clip->w;
		if(this->h > 0) dh = this->h; else
			dh = this->clip->h;

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
		SDL_RenderCopyEx(renderer, this->texture, srcrect, dstrect, this->angle, origin, this->flip);
		SDL_RenderSetClipRect(renderer, NULL);
		delete srcrect;
		delete dstrect;
		delete origin;
	}
}

void jeImage::load(std::string file, SDL_Renderer* renderer){
    SDL_Surface* img = IMG_Load(file.c_str());
    if (img == NULL) {std::cout << SDL_GetError() << std::endl;}else{
		this->texture = SDL_CreateTextureFromSurface(renderer, img);
		if (this->texture == NULL) {std::cout << SDL_GetError() << std::endl;}
    }
	int w, h;
	SDL_QueryTexture(this->texture, NULL, NULL, &w, &h);
	this->setClip(0,0,w,h);
}

void jeImage::setClip(float x, float y, float w, float h){
	if(this->clip == NULL) this->clip = new SDL_Rect();
	this->clip->x = x;
	this->clip->y = y;
	this->clip->w = w;
	this->clip->h = h;
}

void jeImage::setScale(float x, float y){
	int w;
	int h;
	if (y < 0) y = x;
	SDL_QueryTexture(this->texture, NULL, NULL, &w, &h);
	this->setSize(w*x, h*y);
}

void jeImage::setSize(float w, float h){
	this->w = w;
	this->h = h;
}

