#include "jeTilemap.h"
namespace JE{namespace GRAPHICS{
Tileset::Tileset(std::string file, int twidth, int theight, int offsetX, int offsetY, int spaceX, int spaceY) : JE::Data(){
	this->load(file, twidth, theight, offsetX, offsetY, spaceX, spaceY);
}
Tileset::Tileset(Tilemap* parent, std::string file, int twidth, int theight, int offsetX, int offsetY, int spaceX, int spaceY) : JE::Data(parent){
	this->load(file, twidth, theight, offsetX, offsetY, spaceX, spaceY);
}

void Tileset::load(std::string file, int twidth, int theight, int offsetX, int offsetY, int spaceX, int spaceY){
	this->tileWidth = twidth;
	this->tileHeight = theight;
	this->tileOffsetX = offsetX;
	this->tileOffsetY = offsetY;
	this->tileSpaceX = spaceX;
	this->tileSpaceY = spaceY;
	this->image = new JE::GRAPHICS::Image(file);
}

void Tileset::newTile(int x, int y, int w, int h, int ID){
	this->newFreeformTile(
		x*this->tileWidth + this->tileOffsetX + x*this->tileSpaceX,
		y*this->tileHeight + this->tileOffsetY + y*this->tileSpaceY,
		w*this->tileWidth,
		h*this->tileHeight,
		ID);
}

void Tileset::newFreeformTile(int x, int y, int w, int h, int ID){
	SDL_Rect* rect = new SDL_Rect();
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;
	if (ID < 0) this->tiles.push_back(rect);
	else{
		if ((int)this->tiles.size() < ID + 1) this->tiles.resize(ID+1,NULL);
		this->tiles[ID] = rect;
	}
}

Tileset::~Tileset(){
	delete this->image;
	for (unsigned int j = 0; j < this->tiles.size(); j ++){
		delete this->tiles[j];
	}
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
	for (unsigned int i = 0; i < this->tilesets.size(); i ++){
		this->tilesets[i]->kill(this);
	}
	this->tilesets.clear();
}

void Tilemap::newTileset(std::string file, int tWidth, int tHeight, int offsetX, int offsetY, int spaceX, int spaceY, int ID){
	if (tWidth <= 0) tWidth = this->tileWidth;
	if (tHeight <= 0) tHeight = this->tileHeight;
	if (offsetX <= 0) offsetX = this->tileOffsetX;
	if (offsetY <= 0) offsetY = this->tileOffsetY;
	if (spaceX <= 0) spaceX = this->tileSpaceX;
	if (spaceY <= 0) spaceY = this->tileSpaceY;
	Tileset* tileset = new Tileset(this, file, tWidth, tHeight, offsetX, offsetY, spaceX, spaceY);
	this->addTileset(tileset, ID);
}

void Tilemap::addTileset(Tileset* tileset, int ID){
	if (ID < 0) this->tilesets.push_back(tileset);
	else{
		if ((int)this->tilesets.size() < ID+1) this->tilesets.resize(ID+1,NULL);
		this->tilesets[ID] = tileset;
	}
}

void Tilemap::newFreeformTile(int tileset, int x, int y, int w, int h, int ID){
	this->tilesets[tileset]->newFreeformTile(x, y, w, h, ID);
}

void Tilemap::newTile(int tileset, int x, int y, int w, int h, int ID){
	this->tilesets[tileset]->newTile(x, y, w, h, ID);
}

void Tilemap::drawFreeformTile(int tileset, int tile, float x, float y, float sx, float sy){
	this->bind();
		SDL_Rect* rect = this->tilesets[tileset]->tiles[tile];
		this->tilesets[tileset]->image->clip = rect;
		this->tilesets[tileset]->image->setScale(sx, sy);
		this->tilesets[tileset]->image->draw(x, y);
	this->unbind();
}

void Tilemap::drawTile(int tileset, int tile, int x, int y){
	this->drawFreeformTile(tileset, tile, x*this->tilesets[tileset]->tileWidth, y*this->tilesets[tileset]->tileHeight);
}

void Tilemap::drawTileRect(int tileset, int tile, int x, int y, int w, int h){
	for (int ix = x; ix < x+w; ix++){
	for (int iy = y; iy < y+h; iy++){
		this->drawTile(tileset, tile, ix, iy);
	}
	}
}
void Tilemap::drawTile(int tileset, int tilex, int tiley, int x, int y){
	this->bind();
		SDL_Rect* rect = new SDL_Rect();
		rect->x = tilex*this->tilesets[tileset]->tileWidth + this->tilesets[tileset]->tileOffsetX + tilex*this->tilesets[tileset]->tileSpaceX;
		rect->y = tiley*this->tilesets[tileset]->tileHeight + this->tilesets[tileset]->tileOffsetY + tiley*this->tilesets[tileset]->tileSpaceY;
		rect->w = this->tilesets[tileset]->tileWidth;
		rect->h = this->tilesets[tileset]->tileHeight;
		this->tilesets[tileset]->image->clip = rect;
		this->tilesets[tileset]->image->setScale(1, 1);
		this->tilesets[tileset]->image->draw(x*this->tilesets[tileset]->tileWidth, y*this->tilesets[tileset]->tileHeight);
		this->tilesets[tileset]->image->clip = NULL;
		delete rect;
	this->unbind();
}
void Tilemap::drawTileRect(int tileset, int tilex, int tiley, int x, int y, int w, int h){
	for (int ix = x; ix < x+w; ix++){
	for (int iy = y; iy < y+h; iy++){
		this->drawTile(tileset, tilex, tiley, ix, iy);
	}
	}
}
};};
