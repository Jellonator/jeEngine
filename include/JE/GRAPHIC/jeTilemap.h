#pragma once
#include "jeCanvas.h"
#include "../jeMain.h"
#include "../jeUtil.h"
#include "../GL/jeModel.h"
#include <memory>
#include <tuple>
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
	SDL_Rect getRectId(int id, int width) const;
	int getWidth() const;
	int getHeight() const;
	int getTileWidth() const;
	int getTileheight() const;
	
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

struct TilemapTile {
	int x;
	int y;
	bool empty;
	TilemapTile(int x, int y, bool empty);
};

class TilemapLayer : public Graphic {
public:
	TilemapLayer(std::shared_ptr<Tileset>& tileset, int width, int height);
	TilemapLayer(std::shared_ptr<Tileset>& tileset, int width, int height, int tile_width, int tile_height);
	virtual ~TilemapLayer();
	
	virtual void update(float dt);
	virtual void drawMatrix(const glm::mat4& camera, float x = 0, float y = 0) const;
	
	bool isInBounds(int x, int y) const;
	bool isTileInBounds(int tile_x, int tile_y) const;
	void setTile(int x, int y, int tile_x, int tile_y);
	void emptyTile(int x, int y);
	
private:
	void updateModel() const;
	
	int tile_width;
	int tile_height;
	int width;
	int height;
	std::shared_ptr<Tileset> tileset;
	std::vector<std::vector<TilemapTile>> tiles;
	mutable JE::GL::Model model;
	mutable bool need_update_model;
};

};};
