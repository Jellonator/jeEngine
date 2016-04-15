#include "JE/GRAPHIC/TILEMAP/jeTileset.h"
#include "JE/GL/jeShader.h"
#include <iostream>

namespace JE{namespace GRAPHICS{

//Tileset
Tileset::Tileset(const std::string& file, int tile_width, int tile_height,
	int offset_x, int offset_y, int space_x, int space_y)
	: Tileset(tile_width, tile_height, offset_x, offset_y, space_x, space_y){
	this->texture = std::make_shared<JE::GL::Texture>(file);
}
		
Tileset::Tileset(SDL_Surface* surface, int tile_width, int tile_height,
	int offset_x, int offset_y, int space_x, int space_y)
	: Tileset(tile_width, tile_height, offset_x, offset_y, space_x, space_y){
	this->texture = std::make_shared<JE::GL::Texture>(surface);
}
		
Tileset::Tileset(std::shared_ptr<JE::GL::Texture>& texture, int tile_width, int tile_height,
	int offset_x, int offset_y, int space_x, int space_y)
	: Tileset(tile_width, tile_height, offset_x, offset_y, space_x, space_y){
	this->texture = texture;
}

Tileset::Tileset(int tile_width, int tile_height, int offset_x, int offset_y, int space_x, int space_y) : 
	tile_width(tile_width),
	tile_height(tile_height),
	offset_x(offset_x),
	offset_y(offset_y),
	space_x(space_x),
	space_y(space_y){
}

SDL_Rect Tileset::getRect(int x, int y) const{
	SDL_Rect ret = {
		x * (this->tile_width + this->space_x) + this->offset_x, 
		y * (this->tile_height+ this->space_y) + this->offset_y, 
		this->tile_width, 
		this->tile_height
	};
	
	return ret;
}

SDL_Rect Tileset::getRectId(int id) const{
	int width = this->getWidthInTiles();
	if (width == 0) return SDL_Rect{0,0,0,0};
	
	int ix = id % width;
	int iy = id / width;
	return this->getRect(ix, iy);
}

SDL_Point Tileset::getTileId(int id) const{
	int width = this->getWidthInTiles();
	if (width == 0) return SDL_Point{0,0};
	
	SDL_Point ret = {
		id % width, // x
		id / width  // y
	};
	
	return ret;
}

int Tileset::getWidth() const{
	if (this->texture == nullptr) return 1;
	return this->texture->getWidth();
}

int Tileset::getHeight() const{
	if (this->texture == nullptr) return 1;
	return this->texture->getHeight();
}

int Tileset::getTileWidth() const{
	return this->tile_width;
}

int Tileset::getTileHeight() const{
	return this->tile_height;
}

int Tileset::getWidthInTiles() const {
	return (this->getWidth()-this->offset_x+this->space_x) / (this->tile_width+this->space_x);
}

int Tileset::getHeightInTiles() const{
	return (this->getHeight()-this->offset_y+this->space_y) / (this->tile_height+this->space_y);
}

int Tileset::getNumTiles() const{
	return this->getWidthInTiles() * this->getHeightInTiles();
}

std::shared_ptr<JE::GL::Texture>& Tileset::getTexture(){
	return this->texture;
}
};};
