#pragma once
#include "jeCanvas.h"
#include "../jeMain.h"
#include "../jeUtil.h"
#include <memory>
#include <map>
#include <vector>
/*
namespace JE{namespace GRAPHICS{
class Tileset;
class Tilemap;
class Tileset{
	public:
	Tileset(std::string file, int twidth, int theight, int offsetX = 0, int offsetY = 0, int spaceX = 0, int spaceY = 0);
	//Tileset(Tilemap* parent, std::string file, int twidth, int theight, int offsetX = 0, int offsetY = 0, int spaceX = 0, int spaceY = 0);
	void load(std::string file, int twidth, int theight, int offsetX = 0, int offsetY = 0, int spaceX = 0, int spaceY = 0);
	virtual ~Tileset();
	int tileWidth;
	int tileHeight;
	int tileOffsetX;
	int tileOffsetY;
	int tileSpaceX;
	int tileSpaceY;
	void newTile(int x, int y, int ID = -1);
	void newFreeformTile(int x, int y, int w, int h, int ID = -1);

	void drawFreeformTile(int tile, int x, int y, float sx = 1, float sy = 1);

	void drawTileID(int tile, int x, int y, int parentTileWidth = -1, int parentTileHeight = -1);
	void drawTile(int tilex, int tiley, int x, int y, int parentTileWidth = -1, int parentTileHeight = -1);
	void drawTileRect(int tilex, int tiley, int x, int y, int w, int h, int parentTileWidth = -1, int parentTileHeight = -1);
	void drawTileRectID(int tile, int x, int y, int w, int h, int parentTileWidth = -1, int parentTileHeight = -1);
	Image image;
	std::vector<SDL_Rect> tiles;
};

class Tilemap : public Canvas
{
	public:
		std::map<std::string, std::shared_ptr<Tileset>> tilesets;
		int tileWidth;
		int tileHeight;
		int tileOffsetX;
		int tileOffsetY;
		int tileSpaceX;
		int tileSpaceY;
		int widthInTiles;
		int heightInTiles;
		Tilemap(int width, int height, int twidth = 1, int theight = 1, int offsetX = 0, int offsetY = 0,
		int spaceX = 0, int spaceY = 0);
		std::shared_ptr<Tileset> newTileset(const std::string& name, const std::string& file, int tWidth = -1, int tHeight = -1,
		int offsetX = -1, int offsetY = -1, int spaceX = -1, int spaceY = -1);
		std::shared_ptr<Tileset> addTileset(const std::string& name, std::shared_ptr<Tileset> tileset);
		void newTile(const std::string& tileset, int x, int y, int ID = -1);
		void newFreeformTile(const std::string& tileset, int x, int y, int w, int h, int ID = -1);
		void drawTile(const std::string& tileset, int tile, int x, int y);
		void drawTile(const std::string& tileset, int tilex, int tiley, int x, int y);
		void drawTileRect(const std::string& tileset, int tilex, int tiley, int x, int y, int w, int h);
		void drawTileRect(const std::string& tileset, int tile, int x, int y, int w, int h);
		//void drawTile(int tileset, int tx, int ty, float x, float y);
		void drawFreeformTile(const std::string& tileset, int tile, float x, float y, float sx = 1, float sy = 1);
		virtual ~Tilemap();
	protected:
	private:
};
};};
*/