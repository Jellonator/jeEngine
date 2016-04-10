#pragma once
#include "../jeCanvas.h"
#include "../../jeMain.h"
#include "../../jeUtil.h"
#include "../../GL/jeModel.h"
#include <memory>
#include <map>
#include <vector>

namespace JE{namespace GRAPHICS{

class Tileset{
public:
	Tileset(const std::string& file,
		int tile_width, int tile_height,
		int offset_x = 0, int offset_y = 0,
		int space_x = 0, int space_y = 0);
		
	Tileset(SDL_Surface* surface,
		int tile_width, int tile_height,
		int offset_x = 0, int offset_y = 0,
		int space_x = 0, int space_y = 0);
		
	Tileset(std::shared_ptr<JE::GL::Texture>& texture,
		int tile_width, int tile_height,
		int offset_x = 0, int offset_y = 0,
		int space_x = 0, int space_y = 0);
	
	SDL_Rect getRect(int x, int y) const;
	SDL_Rect getRectId(int id) const;
	SDL_Point getTileId(int id) const;
	
	int getWidth() const;
	int getHeight() const;
	int getTileWidth() const;
	int getTileHeight() const;
	int getWidthInTiles() const;
	int getHeightInTiles() const;
	int getNumTiles() const;
	
	std::shared_ptr<JE::GL::Texture>& getTexture();
	
private:
	int tile_width;
	int tile_height;
	int offset_x;
	int offset_y;
	int space_x;
	int space_y;
	std::shared_ptr<JE::GL::Texture> texture;
	
	//private constructor
	Tileset(int tile_width, int tile_height,
		int offset_x = 0, int offset_y = 0,
		int space_x = 0, int space_y = 0);
};

};};
