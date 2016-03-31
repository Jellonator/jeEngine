#include "JE/GRAPHIC/jeTilemap.h"
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

SDL_Rect Tileset::getRectId(int id, int width) const{
	int ix = id % width;
	int iy = id / width;
	return this->getRect(ix, iy);
}

int Tileset::getWidth() const{
	return this->texture->getWidth();
}

int Tileset::getHeight() const{
	return this->texture->getHeight();
}

int Tileset::getTileWidth() const{
	return this->tile_width;
}

int Tileset::getTileheight() const{
	return this->tile_height;
}

std::shared_ptr<JE::GL::Texture>& Tileset::getTexture(){
	return this->texture;
}

//Tilemap tile
TilemapTile::TilemapTile(int width, int height):
	empty(true),
	rect({0,0,width,height}){}

//Tilemap Layer
TilemapLayer::TilemapLayer(std::shared_ptr<Tileset>& tileset, int width, int height) : 
	TilemapLayer(tileset, width, height, tileset->getTileWidth(), tileset->getTileheight()){}

TilemapLayer::TilemapLayer(std::shared_ptr<Tileset>& tileset, int width, int height, int tile_width, int tile_height) : 
	tile_width(tile_width),
	tile_height(tile_height),
	width(width),
	height(height),
	tileset(tileset),
	tiles(width, std::vector<TilemapTile>(height, TilemapTile(tile_width, tile_height))){
	
}

TilemapLayer::~TilemapLayer(){
	
}

void TilemapLayer::update(float dt){
	
}

void TilemapLayer::drawMatrix(const glm::mat4& camera, float x, float y) const{
	
}

};};
