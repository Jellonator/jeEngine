#pragma once
#include "JE.h"

class jeGridTile{
	public:
	jeGridTile(float x1, float y1, float x2, float y2, bool empty = false);
	bool empty;
	float x1, x2, y1, y2;
};

class jeGrid : public jeMask
{
	public:
		std::vector<std::vector<int>> tiles;
		std::vector<jeGridTile*> types;
		int width;
		int height;
		int tileWidth;
		int tileHeight;
		jeGrid(int width, int height, int twidth, int theight);
		virtual ~jeGrid();

		void setTile(int x, int y, int value);
		void setRect(int x, int y, int w, int h, int value);
		void newTile(float x1, float y1, float x2, float y2, int ID = -1);
		void emptyTile(int ID);

		void draw();
	protected:
	private:
};

bool jeCollideBoxGrid(jeHitBox* box, jeGrid* grid, float x = 0, float y = 0, bool sweep = false);
bool jeCollideBoxGrid(jeEntity* eb, jeEntity* eg, float x = 0, float y = 0, bool sweep = false);
