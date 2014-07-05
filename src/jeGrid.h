#pragma once
#include "JE.h"
namespace JE{namespace MASK{
enum GRID_SIDE{GRID_SIDE_ALL, GRID_SIDE_TOP};
class GridTile{
	public:
		GridTile(float x1, float y1, float x2, float y2, bool empty = false, GRID_SIDE side=GRID_SIDE_ALL);
		bool empty;
		float x1, x2, y1, y2;
		int side;
};
class GridData : public JE::Data
{
	public:
		GridData(Grid* parent = NULL);
		virtual ~GridData();
		std::vector<GridTile*> types;/**< \brief a list of tile types in the grid. */
		void newTile(float x1, float y1, float x2, float y2, bool empty=false, GRID_SIDE side=GRID_SIDE_ALL, int ID = -1);
		//void newTileF(float x1, float y1, float x2, float y2, bool empty=false, GRID_SIDE side=GRID_SIDE_ALL, int ID = -1);
		void emptyTile(int ID, bool empty = true);
};
class Grid : public Mask
{
	public:
		std::vector<std::vector<int> > tiles;/**< \brief a 2D list of tiles in the grid. */
		GridData* data;
		int width;/**< \brief the width of the grid in tiles. */
		int height;/**< \brief the height of the grid in tiles. */
		float tileWidth;/**< \brief the width of a tile. */
		float tileHeight;/**< \brief the height of a tile. */
		void setData(GridData* data);
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
		void newTile(float x1, float y1, float x2, float y2, bool empty=false, GRID_SIDE side=GRID_SIDE_ALL, int ID = -1);

        /** \brief Creates a new tile type, with 0 and 1 being the min/max values.
         * \param x1 float; the first x position.
         * \param y1 float; the first y position.
         * \param x2 float; the second x position.
         * \param y2 float; the second y position.
         * \param int ID; The ID of the tile type.
         */
		void newTileF(float x1, float y1, float x2, float y2, bool empty=false, GRID_SIDE side=GRID_SIDE_ALL, int ID = -1);

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
        /** \brief Fill bucket like function that fills and area with the specified tile.
         * \param type int, the type to fill with.
         * \param x int, the x position to fill.
         * \param y int, the y position to fill.
         */
		void fill(int type, int x, int y);

        /** \brief Draw the grid(debugging)
         * \param x float, the x position to draw to.
         * \param y float, the y position to draw to.
         * \param camera Camera*, the camera for transformations.
         * \param outline bool, whether to draw outlines.
         * \param include_empty bool, whether to draw empty tiles.
         */
		void draw(float x = 0, float y = 0, GRAPHICS::Camera* camera = NULL, bool outline = false, bool include_empty = false);/**< \brief draws the grid, for debug purposes. */
        /** \brief Draw a grid's tile
         * \param x float, the x position to draw to.
         * \param y float, the y position to draw to.
         * \param type int, the type to draw.
         * \param camera Camera*, the camera for transformations.
         * \param width float, the width of the tile.
         * \param height float, the height of the tile.
         */
		void drawTile(float x, float y, int type, GRAPHICS::Camera* camera = NULL, float width=-1, float height=-1);
	protected:
	private:
};

/** \brief Tests whether a hitbox and grid collided.
 * \param box HitBox*, the hitbox to use.
 * \param grid Grid*, the grid to use.
 * \param x float, the x offset of the hitbox.
 * \param y float, the y offset of the hitbox.
 * \param sweep bool, whether the hitbox should move.
 * \return bool, If the masks collided.
 */
bool collideBoxGrid(HitBox* box, Grid* grid, float x = 0, float y = 0, bool sweep = false);

/** \brief Tests whether a hitbox and grid collided(via entities)
 * \param e1 Entity*, the hitbox to use.
 * \param e2 Entity*, the grid to use.
 * \param x float, the x offset of the hitbox.
 * \param y float, the y offset of the hitbox.
 * \param sweep bool, whether the hitbox should move.
 * \return bool, If the masks collided.
 */
bool collideBoxGrid(Entity* eb, Entity* eg, float x = 0, float y = 0, bool sweep = false);
};};
