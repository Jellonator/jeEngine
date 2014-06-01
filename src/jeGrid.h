#pragma once
#include "JE.h"
namespace JE{namespace MASK{
class GridTile{
	public:
	GridTile(float x1, float y1, float x2, float y2, bool empty = false);
	bool empty;
	float x1, x2, y1, y2;
};

class Grid : public Mask
{
	public:
		std::vector<std::vector<int> > tiles;/**< \brief a 2D list of tiles in the grid. */
		std::vector<GridTile*> types;/**< \brief a list of tile types in the grid. */
		int width;/**< \brief the width of the grid in tiles. */
		int height;/**< \brief the height of the grid in tiles. */
		float tileWidth;/**< \brief the width of a tile. */
		float tileHeight;/**< \brief the height of a tile. */
		Grid(int width, int height, int twidth, int theight);
		virtual ~Grid();

        /** \brief sets a tile to the value
         * \param x int; the x position of the tile.
         * \param y int; the y position of the tile.
         * \param value int; the ID of the tile type to set it to.
         */
		void setTile(int x, int y, int value);


        /** \brief sets an rectangle of tiles to a value.
         * \param x int; the x position of the rectangle.
         * \param y int; the y position of the rectangle.
         * \param w int; the width of the rectangle.
         * \param h int; the height of the rectangle.
         * \param value int; the ID of the tile type to set them to.
         */
		void setRect(int x, int y, int w, int h, int value);

        /** \brief Creates a new tile type.
         * \param x1 float; the first x position.
         * \param y1 float; the first y position.
         * \param x2 float; the second x position.
         * \param y2 float; the second y position.
         * \param int ID; The ID of the tile type.
         */
		void newTile(float x1, float y1, float x2, float y2, bool empty=false, int ID = -1);

        /** \brief Creates a new tile type, with 0 and 1 being the min/max values.
         * \param x1 float; the first x position.
         * \param y1 float; the first y position.
         * \param x2 float; the second x position.
         * \param y2 float; the second y position.
         * \param int ID; The ID of the tile type.
         */
		void newTileF(float x1, float y1, float x2, float y2, bool empty=false, int ID = -1);

        /** \brief Makes a tile ID empty, or blank.
         * \param ID int; the Tile ID to empty.
         * \param bool empty; whether the tile should be empty or not.
         */
		void emptyTile(int ID, bool empty = true);

        /** \brief Resized the grid.
         * \param width int; the new width in tiles.
         * \param height int; the new height in tiles.
         * \param float twidth; the new tile width.
         * \param float theight; the new tile height.
         */
		void resize(int width, int height, float twidth = -1, float theight = -1);
		void fill(int type, int x, int y);

		void draw(float x = 0, float y = 0, GRAPHICS::Camera* camera = NULL, bool outline = false, bool include_empty = false);/**< \brief draws the grid, for debug purposes. */
		void drawTile(float x, float y, int type, GRAPHICS::Camera* camera = NULL, float width=-1, float height=-1);
	protected:
	private:
};

bool collideBoxGrid(HitBox* box, Grid* grid, float x = 0, float y = 0, bool sweep = false);
bool collideBoxGrid(Entity* eb, Entity* eg, float x = 0, float y = 0, bool sweep = false);
};};
