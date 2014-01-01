#include "jeTilemap.h"
jeTilemap::jeTilemap(int width, int height, int twidth, int theight, int offsetX, int offsetY, int spaceX, int spaceY) : jeCanvas(width*twidth, height*theight){
	this->width = width;
	this->height = height;
	this->tileWidth = twidth;
	this->tileHeight = theight;
	this->tileOffsetX = offsetX;
	this->tileOffsetY = offsetY;
	this->tileSpaceX = spaceX;
	this->tileSpaceY = spaceY;
}

jeTilemap::~jeTilemap(){
	for (unsigned int i = 0; i < this->tilesets.size(); i ++){
		for (unsigned int j = 0; j < this->tilesets[i]->tiles.size(); j ++){
			delete this->tilesets[i]->tiles[j];
		}
		delete this->tilesets[i]->image;
		delete this->tilesets[i];
	}
	this->tilesets.clear();
}

void jeTilemap::newTileset(std::string file, int ID, int tWidth, int tHeight, int offsetX, int offsetY, int spaceX, int spaceY){
	jeTileset* tileset = new jeTileset();
	tileset->tileWidth = (tWidth > 0) ? tWidth : this->tileWidth;
	tileset->tileHeight = (tHeight > 0) ? tHeight : this->tileHeight;
	tileset->tileOffsetX = (offsetX >= 0) ? offsetX : this->tileOffsetX;
	tileset->tileOffsetY = (offsetY >= 0) ? offsetY : this->tileOffsetY;
	tileset->tileSpaceX = (spaceX >= 0) ? spaceX : this->tileSpaceX;
	tileset->tileSpaceY = (spaceY >= 0) ? spaceY : this->tileSpaceY;
	tileset->image = new jeImage();
	tileset->image->load(file);
	if (ID < 0) this->tilesets.push_back(tileset);
	else{
		if ((int)this->tilesets.size() < ID+1) this->tilesets.resize(ID+1,NULL);
		this->tilesets[ID] = tileset;
	}
}

void jeTilemap::newFreeformTile(int tileset, int x, int y, int w, int h, int ID){

	SDL_Rect* rect = new SDL_Rect();
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;
	if (ID < 0) this->tilesets[tileset]->tiles.push_back(rect);
	else{
		if ((int)this->tilesets[tileset]->tiles.size() < ID + 1) this->tilesets[tileset]->tiles.resize(ID+1,NULL);
		this->tilesets[tileset]->tiles[ID] = rect;
	}
}

void jeTilemap::newTile(int tileset, int x, int y, int w, int h, int ID){
	this->newFreeformTile(tileset,
	x*this->tilesets[tileset]->tileWidth + this->tilesets[tileset]->tileOffsetX + x*this->tilesets[tileset]->tileSpaceX,
	y*this->tilesets[tileset]->tileHeight + this->tilesets[tileset]->tileOffsetY + y*this->tilesets[tileset]->tileSpaceY,
	w*this->tilesets[tileset]->tileWidth,
	h*this->tilesets[tileset]->tileHeight,
	ID);
}

void jeTilemap::drawFreeformTile(int tileset, int tile, float x, float y, jeCamera* camera, jeEntity* parent, float sx, float sy){
	this->bind();
		SDL_Rect* rect = this->tilesets[tileset]->tiles[tile];
		this->tilesets[tileset]->image->setClip(rect->x, rect->y, rect->w, rect->h);
		this->tilesets[tileset]->image->setScale(sx, sy);
		this->tilesets[tileset]->image->draw(x, y);
	this->unbind();
}

void jeTilemap::drawTile(int tileset, int tile, float x, float y){
	this->drawFreeformTile(tileset, tile, x*this->tilesets[tileset]->tileWidth, y*this->tilesets[tileset]->tileHeight);
}
