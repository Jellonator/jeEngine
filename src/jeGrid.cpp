#include "jeGrid.h"
using namespace std;

jeGridTile::jeGridTile(float x1, float y1, float x2, float y2, bool empty){
	this->empty = empty;
	this->x1 = x1;
	this->x2 = x2;
	this->y1 = y1;
	this->y2 = y2;
}

jeGrid::jeGrid(int width, int height, int twidth, int theight) : jeMask(), tiles(width, std::vector<int>(height, 0))
{
	this->tileWidth = twidth;
	this->tileHeight = theight;
	this->width = width;
	this->height = height;
	this->type = JE_MASK_GRID;
	this->types.resize(2,NULL);
	this->types[0] = new jeGridTile(0,0,twidth,theight,true);
	this->types[1] = new jeGridTile(0,0,twidth,theight,false);
}

jeGrid::~jeGrid()
{
	for (unsigned int i = 0; i < this->tiles.size(); i ++){
		this->tiles[i].clear();
	}
	this->tiles.clear();
}

void jeGrid::setTile(int x, int y, int value){
	if (x < 0 || y < 0 || x >= this->width || y >= this->height) return;
	this->tiles[x][y] = value;
}

void jeGrid::setRect(int x, int y, int w, int h, int value){
	for (int ix = max(0,x); ix < min(this->width, x+w); ix ++){
		for (int iy = max(0,y); iy < min(this->height, y+h); iy ++){
			this->tiles[ix][iy] = value;
		}
	}
}

void jeGrid::draw(){
	SDL_Rect* rect = new SDL_Rect();
	for (unsigned int ix = 0; ix < this->tiles.size(); ix ++){
		for (unsigned int iy = 0; iy < this->tiles[ix].size(); iy ++){
			int t = this->tiles[ix][iy];
			if(this->types[t]->empty == false){
				rect->x = this->x + ix*this->tileWidth + this->types[t]->x1;
				rect->y = this->y + iy*this->tileHeight + this->types[t]->y1;
				rect->w = this->types[t]->x2 - this->types[t]->x1;
				rect->h = this->types[t]->y2 - this->types[t]->y1;
				SDL_RenderDrawRect(JE::renderer, rect);
			}
		}
	}
	delete rect;
}

bool jeCollideBoxGrid(jeEntity* eb, jeEntity* eg, float x, float y, bool sweep){
	jeHitBox* box = static_cast<jeHitBox*>(eb->mask);
	jeGrid* grid = static_cast<jeGrid*>(eg->mask);
	bool c = false;
	if(sweep == true){
		bool cx = false;
		bool cy = false;
		if (x != 0){
			if(x < 0)box->x += x;
			box->width += abs(x);
			float X = eb->x + x;
			for (	 int ix = max(float(0),floor((box->x + eb->x - grid->x - eg->x)/grid->tileWidth )); ix < min(float(grid->width ),ceil((box->x + box->width + eb->x - grid->x - eg->x)/grid->tileWidth )); ix ++){
				for (int iy = max(float(0),floor((box->y + eb->y - grid->y - eg->y)/grid->tileHeight)); iy < min(float(grid->height),ceil((box->y + box->height+ eb->y - grid->y - eg->y)/grid->tileHeight)); iy ++){
					int t = grid->tiles[ix][iy];
					if(grid->types[t]->empty == false) {
						if(box->left() + eb->x - grid->x - eg->x 		< ix*grid->tileWidth + grid->types[t]->x2
						&& ix*grid->tileWidth + grid->types[t]->x1		< box->right() + eb->x - grid->x - eg->x
						&& box->top() + eb->y - grid->y - eg->y			< iy*grid->tileHeight + grid->types[t]->y2
						&& iy*grid->tileHeight + grid->types[t]->y1		< box->bottom() + eb->y - grid->y - eg->y
						){
							if (x > 0) X = min(float(X), ix*grid->tileWidth + grid->types[t]->x1 - box->width + x - grid->x - eg->x);
							if (x < 0) X = max(float(X), ix*grid->tileWidth + grid->types[t]->x2 - grid->x - eg->x);
							cx = true;
						}
					}
				}
			}

			if(x < 0)box->x -= x;
			box->width -= abs(x);

			eb->x = X;
		}
		if (y != 0){
			//Repeat for Y
			if(y < 0)box->y += y;
			box->height += abs(y);
			float Y = eb->y + y;
			for (	 int ix = max(float(0),floor((box->x + eb->x - grid->x - eg->x)/grid->tileWidth )); ix < min(float(grid->width ),ceil((box->x + box->width + eb->x - grid->x - eg->x)/grid->tileWidth )); ix ++){
				for (int iy = max(float(0),floor((box->y + eb->y - grid->y - eg->y)/grid->tileHeight)); iy < min(float(grid->height),ceil((box->y + box->height+ eb->y - grid->y - eg->y)/grid->tileHeight)); iy ++){
					int t = grid->tiles[ix][iy];
					if(grid->types[t]->empty == false) {
						if(box->left() + eb->x - grid->x - eg->x 		< ix*grid->tileWidth + grid->types[t]->x2
						&& ix*grid->tileWidth + grid->types[t]->x1		< box->right() + eb->x - grid->x - eg->x
						&& box->top() + eb->y - grid->y - eg->y			< iy*grid->tileHeight + grid->types[t]->y2
						&& iy*grid->tileHeight + grid->types[t]->y1		< box->bottom() + eb->y - grid->y - eg->y
						){
							if (y > 0) Y = min(float(Y), iy*grid->tileHeight + grid->types[t]->y1 - box->height + y - grid->y - eg->y);
							if (y < 0) Y = max(float(Y), iy*grid->tileHeight + grid->types[t]->y2 - grid->y - eg->y);
							cy = true;
						}
					}
				}
			}
			if(y < 0)box->y -= y;
			box->height -= abs(y);
			eb->y = Y;
		}
		c = cx || cy;
	}else{
			if(x < 0)box->x += x;
			box->width += abs(x);
			if(y < 0)box->y += y;
			box->height += abs(y);

			for (	 int ix = max(float(0),floor((box->x + eb->x - grid->x - eg->x)/grid->tileWidth )); ix < min(float(grid->width ),ceil((box->x + box->width + eb->x - grid->x - eg->x)/grid->tileWidth )); ix ++){
				for (int iy = max(float(0),floor((box->y + eb->y - grid->y - eg->y)/grid->tileHeight)); iy < min(float(grid->height),ceil((box->y + box->height+ eb->y - grid->y - eg->y)/grid->tileHeight)); iy ++){
					int t = grid->tiles[ix][iy];
					if(grid->types[t]->empty == false) {
						if(box->left() + eb->x - grid->x - eg->x 		< ix*grid->tileWidth + grid->types[t]->x2
						&& ix*grid->tileWidth + grid->types[t]->x1		< box->right() + eb->x - grid->x - eg->x
						&& box->top() + eb->y - grid->y - eg->y			< iy*grid->tileHeight + grid->types[t]->y2
						&& iy*grid->tileHeight + grid->types[t]->y1		< box->bottom() + eb->y - grid->y - eg->y
						)c = true;
					}
				}
			}

			if(x < 0)box->x -= x;
			box->width -= abs(x);
			if(y < 0)box->y -= y;
			box->height -= abs(y);
	}
	return c;
}

void jeGrid::newTile(float x1, float y1, float x2, float y2, int ID){
	jeGridTile* tile;
	tile = new jeGridTile(x1, y1, x2, y2, false);
	if (ID < 0) {
		this->types.push_back(tile);
	}else{
		if (ID > (int)this->types.size()-1) this->types.resize(ID+1,NULL);
		if (this->types[ID] != NULL) delete this->types[ID];
		this->types[ID] = tile;
	}
}

void jeGrid::newTileF(float x1, float y1, float x2, float y2, int ID){
	this->newTile(x1*this->tileWidth,y1*this->tileHeight,x2*this->tileWidth,y2*this->tileHeight,ID);
}

void jeGrid::emptyTile(int ID, bool empty){
	this->types[ID]->empty = empty;
}

void jeGrid::resize(int width, int height, float twidth, float theight){
	if (width != this->width){
		this->tiles.resize(width, std::vector<int>(height));
	}
	if (height != this->height){
		for (unsigned int i = 0; i < this->tiles.size(); i ++){
			this->tiles[i].resize(height, 0);
		}
	}
	if (twidth > 0 || theight > 0){
		float difx = twidth / this->tileWidth;
		float dify = theight / this->tileHeight;

		for (unsigned int i = 0; i < this->types.size(); i ++){
			if (twidth > 0){this->types[i]->x1 *= difx;
							this->types[i]->x2 *= difx;}
			if (theight> 0){this->types[i]->y1 *= dify;
							this->types[i]->y2 *= dify;}
		}
		if (twidth > 0) this->tileWidth = twidth;
		if (theight> 0) this->tileHeight = theight;
	}
}

bool jeCollideBoxGrid(jeHitBox* box, jeGrid* grid, float x, float y, bool sweep){return false;}
