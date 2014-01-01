#pragma once
#include "JE.h"

class jeTileset{
	public:
	int tileWidth;/**< \brief Width of each tile. */
	int tileHeight;/**< \brief Height of each tile. */
	int tileOffsetX;/**< \brief X offset of the tileset. */
	int tileOffsetY;/**< \brief Y offset of the tileset. */
	int tileSpaceX;/**< \brief X spacing between tiles. */
	int tileSpaceY;/**< \brief Y spacing between tiles. */
	jeImage* image;/**< \brief The tileset's image. */
	std::vector<SDL_Rect*> tiles;/**< \brief A list of tiles in the tileset. */
};

class jeTilemap : public jeCanvas
{
	public:
		std::vector<jeTileset*> tilesets;/**<  */
		int tileWidth;/**< \brief Width of each tile. */
		int tileHeight;/**< \brief Height of each tile. */
		int tileOffsetX;/**< \brief X offset of the tileset. */
		int tileOffsetY;/**< \brief Y offset of the tileset. */
		int tileSpaceX;/**< \brief X spacing between tiles. */
		int tileSpaceY;/**< \brief Y spacing between tiles. */
		int width;/**< \brief Width of the tileset, in tiles. */
		int height;/**< \brief Height of the tileset, in tiles. */

        /** \brief A class used to represent a map of tiles
         * \param width int, width of the tilemap, in tiles.
         * \param height int, height of the tilemap, in tiles.
         * \param 1 int twidth, default width of each tile.
         * \param 1 int theight, default height of each tile.
         * \param 0 int offsetX, default X offset of tiles in the tileset.
         * \param 0 int offsetY, default Y offset of tiles in the tileset.
         * \param 0 int spaceX, default X spacing between tiles in the tileset.
         * \param 0 int spaceY, default Y spacing between tiles in the tileset.
         */
		jeTilemap(int width, int height, int twidth = 1, int theight = 1, int offsetX = 0, int offsetY = 0, int spaceX = 0, int spaceY = 0);

        /** \brief Creates a new tileset for the tilemap.
         * \param file std::string, the file to load.
         * \param -1 int ID, the ID of the tileset.  Defaults to appending to the back.
         * \param -1 int twidth, width of each tile.
         * \param -1 int theight, height of each tile.
         * \param -1 int offsetX, X offset of tiles in the tileset.
         * \param -1 int offsetY, Y offset of tiles in the tileset.
         * \param -1 int spaceX, X spacing between tiles in the tileset.
         * \param -1 int spaceY, Y spacing between tiles in the tileset.
         */
		void newTileset(std::string file, int ID = -1, int tWidth = -1, int tHeight = -1, int offsetX = -1, int offsetY = -1, int spaceX = -1, int spaceY = -1);

        /** \brief Creates a new tile.
         * \param tileset int, the tileset to use.
         * \param x int, the X position of the tile, in tiles.
         * \param y int, the Y position of the tile, in tiles.
         * \param 1 int w, the width of the tile, in tiles.
         * \param 1 int h, the height of the tile, in tiles.
         * \param -1 int ID, the ID of the tile.  Defaults to appending to the back.
         */
		void newTile(int tileset, int x, int y, int w = 1, int h = 1, int ID = -1);

        /** \brief Creates a new tile, without using a grid.
         * \param tileset int, the tileset to use.
         * \param x int, the X position of the tile.
         * \param y int, the Y posiiton of the tile.
         * \param w int, the width of the tile.
         * \param h int, the height of the tile.
         * \param -1 int ID, the ID of the tile.  Defaults to appending to the back.
         */
		void newFreeformTile(int tileset, int x, int y, int w, int h, int ID = -1);

        /** \brief Draws a tile to the tilemap.
         * \param tileset int, the ID of the tileset to use.
         * \param tile int, the ID of the tile to draw.
         * \param x float, the X position to draw to, in tiles.
         * \param y float, the Y position to draw to, in tiles.
         */
		void drawTile(int tileset, int tile, float x, float y);

        /** \brief Draw a freeform tile to the tilemap.
         * \param tileset int, the ID of the tileset to use.
         * \param tile int, the ID of the tile to draw.
         * \param x float
         * \param y float
         * \param NULL jeCamera* camera, the camera to use.
         * \param NULL jeEntity* parent, the parent entity to use.
         * \param 1 float sx, the X scaling factor.
         * \param 1 float sy, the Y scaling factor.
         */
		void drawFreeformTile(int tileset, int tile, float x, float y, jeCamera* camera = NULL, jeEntity* parent = NULL, float sx = 1, float sy = 1);
		virtual ~jeTilemap();
	protected:
	private:
};

