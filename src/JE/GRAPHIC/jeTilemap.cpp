#include "JE/GRAPHIC/jeTilemap.h"
#include <iostream>

namespace JE{namespace GRAPHICS{
Tileset::Tileset(std::string file, int twidth, int theight, int offsetX, int offsetY, int spaceX, int spaceY) : image(file){
	//this->load(file, twidth, theight, offsetX, offsetY, spaceX, spaceY);
	this->tileWidth = twidth;
	this->tileHeight = theight;
	this->tileOffsetX = offsetX;
	this->tileOffsetY = offsetY;
	this->tileSpaceX = spaceX;
	this->tileSpaceY = spaceY;
}

//void Tileset::load(std::string file, int twidth, int theight, int offsetX, int offsetY, int spaceX, int spaceY){
//	this->image.loadImage(file);
//}

void Tileset::newTile(int x, int y, int ID){
	this->newFreeformTile(
		x*this->tileWidth + this->tileOffsetX + x*this->tileSpaceX,
		y*this->tileHeight + this->tileOffsetY + y*this->tileSpaceY,
		this->tileWidth, this->tileHeight, ID);
}

void Tileset::newFreeformTile(int x, int y, int w, int h, int ID){
	if (ID < 0) ID = this->tiles.size();
	this->tiles.resize(std::max((int)this->tiles.size(),ID+1));
	this->tiles[ID] = {x, y, w, h};
}

void Tileset::drawFreeformTile(const JE::GRAPHICS::Camera& camera, int tile, int x, int y, float sx, float sy){
	this->image.setClipRect(this->tiles[tile]);
	this->image.setScale(sx, sy);
	this->image.draw(camera, x, y);
}

void Tileset::drawTileID(const JE::GRAPHICS::Camera& camera, int tile, int x, int y, int parentTileWidth, int parentTileHeight){
	SDL_Rect& rect = this->tiles[tile];
	this->image.setClipRect(rect);
	int tox, toy;
	if (parentTileWidth > 0 && parentTileHeight > 0){
		this->image.setScale(float(parentTileWidth)/float(rect.w), float(parentTileWidth)/float(rect.h));
		tox = x * parentTileWidth;
		toy = y * parentTileHeight;
	}else{
		this->image.setScale(1);
		tox = x * this->tileWidth;
		toy = y * this->tileHeight;
	}
	this->image.draw(camera, tox, toy);
}

void Tileset::drawTile(const JE::GRAPHICS::Camera& camera, int tilex, int tiley, int x, int y, int parentTileWidth, int parentTileHeight){
	SDL_Rect rect;
	rect.x = tilex*this->tileWidth + this->tileOffsetX + tilex*this->tileSpaceX;
	rect.y = tiley*this->tileHeight + this->tileOffsetY + tiley*this->tileSpaceY;
	rect.w = this->tileWidth;
	rect.h = this->tileHeight;
	this->image.setClipRect(rect);
	int tox, toy;
	if (parentTileWidth > 0 && parentTileHeight > 0){
		this->image.setScale(float(parentTileWidth)/float(rect.w), float(parentTileWidth)/float(rect.h));
		tox = x * parentTileWidth;
		toy = y * parentTileHeight;
	}else{
		this->image.setScale(1);
		tox = x * this->tileWidth;
		toy = y * this->tileHeight;
	}
	this->image.draw(camera, tox, toy);
}

void Tileset::drawTileRectID(const JE::GRAPHICS::Camera& camera, int tile, int x, int y, int w, int h, int parentTileWidth, int parentTileHeight){
	for (int ix = x; ix < x + w; ix ++){
	for (int iy = y; iy < y + h; iy ++){
		this->drawTileID(camera, tile, ix, iy, parentTileWidth, parentTileHeight);
	}
	}
}

void Tileset::drawTileRect(const JE::GRAPHICS::Camera& camera, int tilex, int tiley, int x, int y, int w, int h, int parentTileWidth, int parentTileHeight){
	for (int ix = x; ix < x + w; ix ++){
	for (int iy = y; iy < y + h; iy ++){
		this->drawTile(camera, tilex, tiley, ix, iy, parentTileWidth, parentTileHeight);
	}
	}
}

Tileset::~Tileset(){

}

Tilemap::Tilemap(int width, int height, int twidth, int theight, int offsetX, int offsetY, int spaceX, int spaceY) : Canvas(width*twidth, height*theight){
	this->widthInTiles = width;
	this->heightInTiles = height;
	this->tileWidth = twidth;
	this->tileHeight = theight;
	this->tileOffsetX = offsetX;
	this->tileOffsetY = offsetY;
	this->tileSpaceX = spaceX;
	this->tileSpaceY = spaceY;
}

Tilemap::~Tilemap(){
	//for (unsigned int i = 0; i < this->tilesets.size(); i ++){
	//	this->tilesets[i]->kill(this);
	//}
	//this->tilesets.clear();
}

std::shared_ptr<Tileset> Tilemap::newTileset(const std::string& name, const std::string& file, int tWidth, int tHeight, int offsetX, int offsetY, int spaceX, int spaceY){
	if (tWidth <= 0) tWidth = this->tileWidth;
	if (tHeight <= 0) tHeight = this->tileHeight;
	if (offsetX <= 0) offsetX = this->tileOffsetX;
	if (offsetY <= 0) offsetY = this->tileOffsetY;
	if (spaceX <= 0) spaceX = this->tileSpaceX;
	if (spaceY <= 0) spaceY = this->tileSpaceY;
	//Tileset* tileset = new Tileset(this, file, tWidth, tHeight, offsetX, offsetY, spaceX, spaceY);
	//return this->addTileset(tileset, ID);
	auto tileset = std::make_shared<Tileset>(file, tWidth, tHeight, offsetX, offsetY, spaceX, spaceY);
	return this->addTileset(name, tileset);
}

std::shared_ptr<Tileset> Tilemap::addTileset(const std::string& name, std::shared_ptr<Tileset> tileset){
	this->tilesets[name] = tileset;
	return tileset;
}

void Tilemap::newFreeformTile(const std::string& tileset, int x, int y, int w, int h, int ID){
	this->tilesets[tileset]->newFreeformTile(x, y, w, h, ID);
}

void Tilemap::newTile(const std::string& tileset, int x, int y, int ID){
	this->tilesets[tileset]->newTile(x, y, ID);
}

void Tilemap::drawFreeformTile(const std::string& tileset, int tile, float x, float y, float sx, float sy){
	this->bind();
	this->tilesets[tileset]->drawFreeformTile(this->getCamera(), tile, x, y, sx, sy);
	this->unbind();
}

void Tilemap::drawTile(const std::string& tileset, int tile, int x, int y){
	this->bind();
	this->tilesets[tileset]->drawTileID(this->getCamera(), tile, x, y, this->tileWidth, this->tileHeight);
	this->unbind();
}

void Tilemap::drawTileRect(const std::string& tileset, int tile, int x, int y, int w, int h){
	this->bind();
	this->tilesets[tileset]->drawTileRectID(this->getCamera(), tile, x, y, w, h, this->tileWidth, this->tileHeight);
	this->unbind();
}
void Tilemap::drawTile(const std::string& tileset, int tilex, int tiley, int x, int y){
	this->bind();
	this->tilesets[tileset]->drawTile(this->getCamera(), tilex, tiley, x, y, this->tileWidth, this->tileHeight);
	this->unbind();
}
void Tilemap::drawTileRect(const std::string& tileset, int tilex, int tiley, int x, int y, int w, int h){
	this->bind();
	this->tilesets[tileset]->drawTileRect(this->getCamera(), tilex, tiley, x, y, w, h, this->tileWidth, this->tileHeight);
	this->unbind();
}
};};
