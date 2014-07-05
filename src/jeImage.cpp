#include "jeImage.h"
#include "JE.h"
#include <SDL2/SDL_image.h>
namespace JE{namespace GRAPHICS{
using namespace std;
Texture::Texture(void* owner) : Data(owner){
	this->texture = NULL;
}
Texture::~Texture(){
	if(this->texture != NULL) {SDL_DestroyTexture(this->texture);}
}
Image::Image() : Graphic()
{
	this->texture = new Texture(this);
	this->flip = SDL_FLIP_NONE;
	this->w = -1;
	this->h = -1;
	this->clip = NULL;
}

Image::Image(std::string file) : Graphic()
{
	this->texture = new Texture(this);
	this->flip = SDL_FLIP_NONE;
	this->w = -1;
	this->h = -1;
	this->clip = NULL;
	this->load(file);
}

Image::~Image()
{
	if(this->clip != NULL) delete this->clip;
	if (this->texture != NULL) {if (this->texture->getKill(this)) delete this->texture;}
}

void Image::setColor(int r, int g, int b, int a){
	if (!this->texture) return;
	SDL_SetTextureColorMod(this->texture->texture,r,g,b);
	SDL_SetTextureAlphaMod(this->texture->texture,a);
}

void Image::draw(float x, float y, Camera* camera, Entity* parent){
	//If the texture exists
	if (this->texture->texture != NULL){
		//create two rectangles
		SDL_Rect* srcrect = NULL;
		SDL_Rect* dstrect = new SDL_Rect();
		float dx = 0;
		float dy = 0;
		float dw = 0;
		float dh = 0;

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
			dx -= camera->x;
			dy -= camera->y;
			dx += camera->offX;
			dy += camera->offY;
			dx *= camera->sx * sw;
			dy *= camera->sy * sh;
			dw *= camera->sx * sw;
			dh *= camera->sy * sh;
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

		int windowW;
		int windowH;
		SDL_GetWindowSize(JE::GRAPHICS::window, &windowW, &windowH);
		if (dstrect->x+dstrect->w < 0 || dstrect->y+dstrect->h < 0 || dstrect->x > windowW || dstrect->y > windowH){
			//do nothing. was initially going to use a 'return;' but decided that woudln't work. So instead I'm going to be lazy and keep as is.
		}else{
		SDL_RenderCopy(renderer, this->texture->texture, srcrect, dstrect);
		}
		SDL_RenderSetClipRect(renderer, NULL);
		if (srcrect != NULL) delete srcrect;
		delete dstrect;
	}
}

void Image::drawExt(float x, float y, Camera* camera, Entity* parent, float angle, SDL_Renderer* renderer){
	//If the texture exists
	if (this->texture->texture != NULL){
		//create two rectangles
		SDL_Rect* srcrect = NULL;
		SDL_Rect* dstrect = new SDL_Rect();
		float dx = 0;
		float dy = 0;
		float dw = 0;
		float dh = 0;
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
			dx -= camera->x;
			dy -= camera->y;
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

		SDL_Point* origin = new SDL_Point();
		origin->x = ox;
		origin->y = oy;
		dstrect->x = dx;
		dstrect->y = dy;
		dstrect->w = dw;
		dstrect->h = dh;
		SDL_RenderCopyEx(renderer, this->texture->texture, srcrect, dstrect, this->angle + angle, origin, this->flip);
		SDL_RenderSetClipRect(renderer, NULL);
		delete srcrect;
		delete dstrect;
		delete origin;
	}
}
void Image::load(std::string file, SDL_Renderer* renderer){
	this->texture->load(file, renderer);
}
void Texture::load(std::string file, SDL_Renderer* renderer){
	SDL_Surface* s = IMG_Load(file.c_str());
	if (s == NULL) {
		std::cout << SDL_GetError() << std::endl;
	}else{
		this->texture = SDL_CreateTextureFromSurface(renderer, s);
		if (this->texture == NULL) {std::cout << SDL_GetError() << std::endl;}
		SDL_FreeSurface(s);
	}
}

void Image::setClip(float x, float y, float w, float h){
	if(this->clip == NULL) this->clip = new SDL_Rect();
	this->clip->x = x;
	this->clip->y = y;
	this->clip->w = w;
	this->clip->h = h;
}

void Image::setScale(float x, float y){
	int w, h;
	if (this->clip){
		w = this->clip->w;
		h = this->clip->h;
	}else{
		SDL_QueryTexture(this->texture->texture, NULL, NULL, &w, &h);
	}
	if (y < 0) y = x;
	this->setSize(w*x, h*y);
}

void Image::setSize(float w, float h){
	this->w = w;
	this->h = h;
}

Image* copyImage(Image* image){
	if (image == NULL) return NULL;
	Image* r;
	r = new Image();
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

void Image::useTexture(Texture* texture){
	if (this->texture != NULL) {if (this->texture->getKill(this)) delete this->texture;}
	this->texture = texture;
}

void Image::centerOrigin(){
	int x, y;
	SDL_QueryTexture(this->texture->texture, NULL, NULL, &x, &y);
	this->ox = float(x)/2;
	this->oy = float(y)/2;
}
};};
