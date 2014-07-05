#include "jeGraphic.h"
#include "jeCamera.h"
namespace JE{
Graphic::Graphic(float x, float y)
{
	this->x = x;
	this->y = y;
	this->angle = 0;
	this->ox = 0;
	this->oy = 0;
}

Graphic::~Graphic()
{

}

void Graphic::drawExt(float x, float y, GRAPHICS::Camera* camera, Entity* entity, float angle, SDL_Renderer* renderer){}
void Graphic::draw(float x, float y, GRAPHICS::Camera* camera, Entity* entity){}
void Graphic::update(){}

void Graphic::setOrigin(float x, float y){
	this->ox = x;
	this->oy = y;
}
namespace GRAPHICS{
void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a, SDL_Renderer* renderer){
	forecolor->r = r;
	forecolor->g = g;
	forecolor->b = b;
	forecolor->a = a;
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
}
void setColorF(float r, float g, float b, float a, SDL_Renderer* renderer){
	setColor(r*255,g*255,b*255,a*255,renderer);
}
void setBackgroundColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a, SDL_Renderer* renderer){
	backcolor->r = r;
	backcolor->g = g;
	backcolor->b = b;
	backcolor->a = a;
}
void setBackgroundColorF(float r, float g, float b, float a, SDL_Renderer* renderer){
	setBackgroundColor(r*255,g*255,b*255,a*255,renderer);
}
void drawRect(float x, float y, float w, float h, GRAPHICS::Camera* camera){
	SDL_Rect* dstrect = new SDL_Rect();
	float dx = x;
	float dy = y;
	float dw = w;
	float dh = h;

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
	SDL_RenderDrawRect(renderer, dstrect);
	SDL_RenderSetClipRect(renderer, NULL);
	delete dstrect;
}
void fillRect(float x, float y, float w, float h, GRAPHICS::Camera* camera){
	SDL_Rect* dstrect = new SDL_Rect();
	float dx = x;
	float dy = y;
	float dw = w;
	float dh = h;

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
	dstrect->x = std::floor(dx);
	dstrect->y = std::floor(dy);
	dstrect->w = std::ceil(dw);
	dstrect->h = std::ceil(dh);
	SDL_RenderFillRect(renderer, dstrect);
	SDL_RenderSetClipRect(renderer, NULL);
	delete dstrect;
}

void drawImgRectStretch(Image* image, float x, float y, float w, float h, float tileWidth, float tileHeight, GRAPHICS::Camera* camera, Entity* entity){
//store texture width
	int tw, th;
	SDL_QueryTexture(image->texture->texture, NULL, NULL, &tw, &th);
	//make sure image is big enough
	if (tw >= tileWidth*2 && th >= tileHeight*2){
	//store temporary information
		SDL_Rect* temprect = image->clip;
		float tempWidth = image->w;
		float tempHeight = image->h;
		image->clip = new SDL_Rect();
		//Set size to corner
		image->setSize(tileWidth,tileHeight);
	//Drawing operations
		//upper left
		image->setClip(0,0,tileWidth,tileHeight);
		image->draw(x, y, camera, entity);
		//upper right
		image->setClip(tw-tileWidth, 0,tileWidth,tileHeight);
		image->draw(x+w-tileWidth, y, camera, entity);
		//lower left
		image->setClip(0,th-tileHeight, tileWidth,tileHeight);
		image->draw(x, y+h-tileHeight, camera, entity);
		//lower right
		image->setClip(tw-tileWidth, th-tileHeight,tileWidth,tileHeight);
		image->draw(x+w-tileWidth, y+h-tileHeight, camera, entity);
	//Now draw the sides
	//top/bottom size
		if (h > tileHeight*2){
			image->setSize(w-tileWidth*2,tileHeight);
			//top side
			image->setClip(tileWidth,0,tw-tileWidth*2,tileHeight);
			image->draw(x+tileWidth,y,camera,entity);
			//bottom side
			image->setClip(tileWidth,th-tileHeight,tw-tileWidth*2,tileHeight);
			image->draw(x+tileWidth,y+h-tileHeight,camera,entity);
		}
	//left/right sizes
		if (w > tileWidth*2){
			image->setSize(tileWidth, h-tileHeight*2);
			//left side
			image->setClip(0,tileHeight,tileWidth,tw-tileHeight*2);
			image->draw(x,y+tileHeight,camera,entity);
			//right side
			image->setClip(tw-tileWidth,tileHeight,tileWidth,tw-tileHeight*2);
			image->draw(x+w-tileWidth,y+tileHeight,camera,entity);
		}
	//and the center
		if (h > tileHeight*2 && w > tileWidth*2){
			image->setSize(w-tileWidth*2,h-tileHeight*2);
			image->setClip(tileWidth,tileHeight,tw-tileWidth*2,th-tileHeight*2);
			image->draw(x+tileWidth,y+tileHeight,camera,entity);
		}
	//Reset image
		delete image->clip;
		image->clip = temprect;
		image->w = tempWidth;
		image->h = tempHeight;
	}
}
}
}
