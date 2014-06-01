#include "jeHitBox.h"
#include "jeGrid.h"
namespace JE{namespace MASK{
GridTile::GridTile(float x1, float y1, float x2, float y2, bool empty){
	this->empty = empty;
	this->x1 = x1;
	this->x2 = x2;
	this->y1 = y1;
	this->y2 = y2;
}

Grid::Grid(int width, int height, int twidth, int theight) : Mask(), tiles(width, std::vector<int>(height, 0))
{
	this->tileWidth = twidth;
	this->tileHeight = theight;
	this->width = width;
	this->height = height;
	this->type = JE_MASK_GRID;
	this->types.resize(2,NULL);
	this->types[0] = new GridTile(0,0,twidth,theight,true);
	this->types[1] = new GridTile(0,0,twidth,theight,false);
}

Grid::~Grid()
{
	for (unsigned int i = 0; i < this->tiles.size(); i ++){
		this->tiles[i].clear();
	}
	this->tiles.clear();
	for (unsigned int i = 0; i < this->types.size(); i ++){
		delete this->types[i];
	}
	this->types.clear();
}

void Grid::setTile(int x, int y, int value){
	if (x < 0 || y < 0 || x >= this->width || y >= this->height) return;
	this->tiles[x][y] = value;
}

void Grid::setRect(int x, int y, int w, int h, int value){
	for (int ix = std::max(0,x); ix < std::min(this->width, x+w); ix ++){
		for (int iy = std::max(0,y); iy < std::min(this->height, y+h); iy ++){
			this->tiles[ix][iy] = value;
		}
	}
}

void Grid::fill(int type, int x, int y){
	if (x >= 0 && y >= 0 && x < this->width && y < this->height){
		int t = this->tiles[x][y];
		if (t != type){
			this->tiles[x][y] = type;
			if (x-1 >= 0) {if (this->tiles[x-1][y] == t) this->fill(type,x-1,y);}
			if (y-1 >= 0) {if (this->tiles[x][y-1] == t) this->fill(type,x,y-1);}
			if (x+1 < this->width) {if (this->tiles[x+1][y] == t) this->fill(type,x+1,y);}
			if (y+1 < this->height) {if (this->tiles[x][y+1] == t) this->fill(type,x,y+1);}
		}
	}
}

void Grid::draw(float x, float y, GRAPHICS::Camera* camera, bool outline, bool include_empty){
	for (unsigned int ix = 0; ix < this->tiles.size(); ix ++){
		for (unsigned int iy = 0; iy < this->tiles[ix].size(); iy ++){
			int t = this->tiles[ix][iy];
			GridTile* tile = this->types[t];
			if (include_empty){
				float rx = (this->x + float(ix)*this->tileWidth + x);
				float ry = (this->y + float(iy)*this->tileHeight + y);
				float rw = (this->tileWidth);
				float rh = (this->tileHeight);
				if (!outline) fillRect(rx,ry,rw,rh,camera);
				else drawRect(rx,ry,rw,rh,camera);
			}
			if(this->types[t]->empty == false){
				float rx = (this->x + tile->x1+(float(ix))*this->tileWidth + x);
				float ry = (this->y + tile->y1+(float(iy))*this->tileHeight + y);
				float rw = ((tile->x2 - tile->x1));
				float rh = ((tile->y2 - tile->y1));
				if (!outline) fillRect(rx,ry,rw,rh,camera);
				else drawRect(rx,ry,rw,rh,camera);
			}
		}
	}
	SDL_RenderSetClipRect(GRAPHICS::renderer, NULL);
}

void Grid::drawTile(float x, float y, int type, GRAPHICS::Camera* camera, float width, float height){
		//create two rectangles
		SDL_Rect* dstrect = new SDL_Rect();
		GridTile*t = this->types[type];
		float dx = t->x1/this->tileWidth;
		float dy = t->y1/this->tileHeight;
		float dw = std::abs(t->x2-t->x1)/this->tileWidth;
		float dh = std::abs(t->y2-t->y1)/this->tileHeight;

		dx *= (width < 0) ? this->tileWidth : width;
		dy *= (height < 0) ? this->tileHeight : height;
		dw *= (width < 0) ? this->tileWidth : width;
		dh *= (height < 0) ? this->tileHeight : height;

		dx += x;
		dy += y;

		if(camera){
			float sw = 1;
			float sh = 1;
			if (camera->size) camera->getRatio(&sw,&sh);
			dx -= camera->x;
			dy -= camera->y;
			dx *= camera->sx * sw;
			dy *= camera->sy * sh;
			dw *= camera->sx * sw;
			dh *= camera->sy * sh;
			if (camera->clip) {
				if (camera->size){
					SDL_Rect* cliprect = new SDL_Rect();
					cliprect->x = camera->clip->x * sw;
					cliprect->y = camera->clip->y * sh;
					cliprect->w = camera->clip->w * sw;
					cliprect->h = camera->clip->h * sh;
					SDL_RenderSetClipRect(GRAPHICS::renderer, cliprect);
					delete cliprect;
				} else SDL_RenderSetClipRect(GRAPHICS::renderer, camera->clip);
			}
		}
		dstrect->x = dx;
		dstrect->y = dy;
		dstrect->w = dw;
		dstrect->h = dh;
		if (t->empty) SDL_RenderDrawRect(GRAPHICS::renderer, dstrect);
		else SDL_RenderFillRect(GRAPHICS::renderer, dstrect);
		SDL_RenderSetClipRect(GRAPHICS::renderer, NULL);
		delete dstrect;
}

bool collideBoxGrid(Entity* eb, Entity* eg, float x, float y, bool sweep){
	HitBox* box = static_cast<HitBox*>(eb->mask);
	Grid* grid = static_cast<Grid*>(eg->mask);
	bool c = false;
	if(sweep == true){
		bool cx = false;
		bool cy = false;
		if (x != 0){
			if(x < 0)box->x += x;
			box->width += abs(x);
			float X = eb->x + x;
			for (	 int ix = std::max(double(0),floor((box->x + eb->x - grid->x - eg->x)/grid->tileWidth )); ix < std::min(double(grid->width ),ceil((box->x + box->width + eb->x - grid->x - eg->x)/grid->tileWidth )); ix ++){
				for (int iy = std::max(double(0),floor((box->y + eb->y - grid->y - eg->y)/grid->tileHeight)); iy < std::min(double(grid->height),ceil((box->y + box->height+ eb->y - grid->y - eg->y)/grid->tileHeight)); iy ++){
					int t = grid->tiles[ix][iy];
					if(grid->types[t]->empty == false) {
						if(box->left() + eb->x - grid->x - eg->x 		< ix*grid->tileWidth + grid->types[t]->x2
						&& ix*grid->tileWidth + grid->types[t]->x1		< box->right() + eb->x - grid->x - eg->x
						&& box->top() + eb->y - grid->y - eg->y			< iy*grid->tileHeight + grid->types[t]->y2
						&& iy*grid->tileHeight + grid->types[t]->y1		< box->bottom() + eb->y - grid->y - eg->y
						){
							if (x > 0) X = std::min(float(X), ix*grid->tileWidth + grid->types[t]->x1 - box->width + x - grid->x - eg->x);
							if (x < 0) X = std::max(float(X), ix*grid->tileWidth + grid->types[t]->x2 - grid->x - eg->x);
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
			for (	 int ix = std::max(double(0),floor((box->x + eb->x - grid->x - eg->x)/grid->tileWidth )); ix < std::min(double(grid->width ),ceil((box->x + box->width + eb->x - grid->x - eg->x)/grid->tileWidth )); ix ++){
				for (int iy = std::max(double(0),floor((box->y + eb->y - grid->y - eg->y)/grid->tileHeight)); iy < std::min(double(grid->height),ceil((box->y + box->height+ eb->y - grid->y - eg->y)/grid->tileHeight)); iy ++){
					int t = grid->tiles[ix][iy];
					if(grid->types[t]->empty == false) {
						if(box->left() + eb->x - grid->x - eg->x 		< ix*grid->tileWidth + grid->types[t]->x2
						&& ix*grid->tileWidth + grid->types[t]->x1		< box->right() + eb->x - grid->x - eg->x
						&& box->top() + eb->y - grid->y - eg->y			< iy*grid->tileHeight + grid->types[t]->y2
						&& iy*grid->tileHeight + grid->types[t]->y1		< box->bottom() + eb->y - grid->y - eg->y
						){
							if (y > 0) Y = std::min(float(Y), iy*grid->tileHeight + grid->types[t]->y1 - box->height + y - grid->y - eg->y);
							if (y < 0) Y = std::max(float(Y), iy*grid->tileHeight + grid->types[t]->y2 - grid->y - eg->y);
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

			for (	 int ix = std::max(double(0),floor((box->x + eb->x - grid->x - eg->x)/grid->tileWidth )); ix < std::min(double(grid->width ),ceil((box->x + box->width + eb->x - grid->x - eg->x)/grid->tileWidth )); ix ++){
				for (int iy = std::max(double(0),floor((box->y + eb->y - grid->y - eg->y)/grid->tileHeight)); iy < std::min(double(grid->height),ceil((box->y + box->height+ eb->y - grid->y - eg->y)/grid->tileHeight)); iy ++){
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

void Grid::newTile(float x1, float y1, float x2, float y2, bool empty, int ID){
	GridTile* tile;
	tile = new GridTile(x1, y1, x2, y2, empty);
	if (ID < 0) {
		this->types.push_back(tile);
	}else{
		if (ID > (int)this->types.size()-1) this->types.resize(ID+1,NULL);
		if (this->types[ID] != NULL) delete this->types[ID];
		this->types[ID] = tile;
	}
}

void Grid::newTileF(float x1, float y1, float x2, float y2, bool empty, int ID){
	this->newTile(x1*this->tileWidth,y1*this->tileHeight,x2*this->tileWidth,y2*this->tileHeight,empty,ID);
}

void Grid::emptyTile(int ID, bool empty){
	this->types[ID]->empty = empty;
}

void Grid::resize(int width, int height, float twidth, float theight){
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

bool collideBoxGrid(HitBox* box, Grid* grid, float x, float y, bool sweep){return false;}
};};
