#include "jeHitBox.h"
#include "jeGrid.h"
namespace JE{namespace MASK{
GridTile::GridTile(float x1, float y1, float x2, float y2, bool empty, GRID_SIDE side){
	this->empty = empty;
	this->x1 = x1;
	this->x2 = x2;
	this->y1 = y1;
	this->y2 = y2;
	this->side = side;
}

GridData::GridData(Grid*parent) : JE::Data(parent){
	this->types.resize(2,NULL);
	this->types[0] = new GridTile(0,0,parent->tileWidth,parent->tileHeight,true);
	this->types[1] = new GridTile(0,0,parent->tileWidth,parent->tileHeight,false);
}

GridData::~GridData(){
	for (unsigned int i = 0; i < this->types.size(); i ++){
		delete this->types[i];
	}
	this->types.clear();
}

Grid::Grid(int width, int height, int twidth, int theight) : Mask(), tiles(width, std::vector<int>(height, 0))
{
	this->tileWidth = twidth;
	this->tileHeight = theight;
	this->width = width;
	this->height = height;
	this->type = JE_MASK_GRID;
	this->data = new GridData(this);
}
Grid::~Grid()
{
	for (unsigned int i = 0; i < this->tiles.size(); i ++){
		this->tiles[i].clear();
	}
	this->tiles.clear();
	if (this->data != NULL) {this->data->kill(this);}
}
void Grid::setData(GridData* data){
	if (this->data != NULL) {this->data->kill(this);}
	this->data = data;
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
			GridTile* tile = this->data->types[t];
			if (include_empty){
				float rx = (this->x + float(ix)*this->tileWidth + x);
				float ry = (this->y + float(iy)*this->tileHeight + y);
				float rw = (this->tileWidth);
				float rh = (this->tileHeight);
				if (!outline) fillRect(rx,ry,rw,rh,camera);
				else drawRect(rx,ry,rw,rh,camera);
			}
			if(this->data->types[t]->empty == false){
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
		GridTile*t = this->data->types[type];
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
	if (eb->mask == NULL || eg->mask == NULL) return false;
	HitBox* box = static_cast<HitBox*>(eb->mask);
	Grid* grid = static_cast<Grid*>(eg->mask);
	bool c = false;
	//create temporary entity
	JE::Entity* e = new JE::Entity(0,0);
	JE::MASK::HitBox* h = new JE::MASK::HitBox(0,0,1,1);
	e->mask = h;
	float previous_x = box->x;
	float previous_y = box->y;
	float previous_w = box->width;
	float previous_h = box->height;
	if(sweep == true){
		bool cx = false;
		bool cy = false;
		if (x != 0){
			//skew box
			if(x < 0)box->x += x;
			box->width += abs(x);
			//set X to new x
			float X = eb->x + x;
			//iterate over all tiles in range
			for (	 int ix = std::max(double(0),floor((box->x + eb->x - grid->x - eg->x - 1)/grid->tileWidth )); ix < std::min(double(grid->width ),ceil((box->x + box->width + eb->x - grid->x - eg->x + 1)/grid->tileWidth )); ix ++){
				for (int iy = std::max(double(0),floor((box->y + eb->y - grid->y - eg->y - 1)/grid->tileHeight)); iy < std::min(double(grid->height),ceil((box->y + box->height+ eb->y - grid->y - eg->y + 1)/grid->tileHeight)); iy ++){
					//set t to current tile
					int t = grid->tiles[ix][iy];
					//if the current tile is empty
					if(grid->data->types[t]->empty == false) {
						//set the temporary entity and it's mask to fit that of the tile
						e->x = eg->x + grid->x + grid->tileWidth*ix;
						e->y = eg->y + grid->y + grid->tileHeight*iy;
						h->x = grid->data->types[t]->x1;
						h->y = grid->data->types[t]->y1;
						h->width = grid->data->types[t]->x2 - grid->data->types[t]->x1;
						h->height = grid->data->types[t]->y2 - grid->data->types[t]->y1;
						//previous coords
						float px = eb->x;
						float py = eb->y;
					//'unskew' box
					box->x = previous_x;
					box->width = previous_w;
						//grid side exclusion
						if (grid->data->types[t]->side == GRID_SIDE_TOP && eb->y + box->bottom() > e->y + h->top()) {
							if(x < 0)box->x += x;
							box->width += abs(x);
							continue;
						}
						//test collision
						if (JE::MASK::collideBox(eb, e, x, 0, true)) cx = true;
						//reskew box
					if(x < 0)box->x += x;
					box->width += abs(x);
						//set the new X
						if (x > 0) X = std::min(float(X), eb->x);
						if (x < 0) X = std::max(float(X), eb->x);
						//restore coords
						eb->x = px;
						eb->y = py;
					}
				}
			}
			//unskew box
			box->x = previous_x;
			box->width = previous_w;
			//set X
			eb->x = X;
		}
		if (y != 0){
			//Repeat for Y
			if(y < 0)box->y += y;
			box->height += abs(y);
			float Y = eb->y + y;
			for (	 int ix = std::max(double(0),floor((box->x + eb->x - grid->x - eg->x - 1)/grid->tileWidth )); ix < std::min(double(grid->width ),ceil((box->x + box->width + eb->x - grid->x - eg->x + 1)/grid->tileWidth )); ix ++){
				for (int iy = std::max(double(0),floor((box->y + eb->y - grid->y - eg->y - 1)/grid->tileHeight)); iy < std::min(double(grid->height),ceil((box->y + box->height+ eb->y - grid->y - eg->y + 1)/grid->tileHeight)); iy ++){
					int t = grid->tiles[ix][iy];
					if(grid->data->types[t]->empty == false) {
						e->x = eg->x + grid->x + grid->tileWidth*ix;
						e->y = eg->y + grid->y + grid->tileHeight*iy;
						h->x = grid->data->types[t]->x1;
						h->y = grid->data->types[t]->y1;
						h->width = grid->data->types[t]->x2 - grid->data->types[t]->x1;
						h->height = grid->data->types[t]->y2 - grid->data->types[t]->y1;
						float px = eb->x;
						float py = eb->y;
					box->y = previous_y;
					box->height = previous_h;
						//grid side exclusion
						if (grid->data->types[t]->side == GRID_SIDE_TOP && eb->y + box->bottom() > e->y + h->top()) {
							if(y < 0)box->y += y;
							box->height += abs(y);
							continue;
						}
						if (JE::MASK::collideBox(eb, e, 0, y, true)) cx = true;
					if(y < 0)box->y += y;
					box->height += abs(y);
						if (y > 0) Y = std::min(float(Y), eb->y);
						if (y < 0) Y = std::max(float(Y), eb->y);
						eb->x = px;
						eb->y = py;
					}
				}
			}
			box->y = previous_y;
			box->height = previous_h;
			eb->y = Y;
		}
		c = cx || cy;
		//Unstuck player
		/*for (	 int ix = std::max(double(0),floor((box->x + eb->x - grid->x - eg->x - 1)/grid->tileWidth )); ix < std::min(double(grid->width ),ceil((box->x + box->width + eb->x - grid->x - eg->x + 1)/grid->tileWidth )); ix ++){
			for (int iy = std::max(double(0),floor((box->y + eb->y - grid->y - eg->y - 1)/grid->tileHeight)); iy < std::min(double(grid->height),ceil((box->y + box->height+ eb->y - grid->y - eg->y + 1)/grid->tileHeight)); iy ++){
				int t = grid->tiles[ix][iy];
				if(grid->data->types[t]->empty == false) {
					//set the temporary entity and it's mask to fit that of the tile
					e->x = eg->x + grid->x + grid->tileWidth*ix;
					e->y = eg->y + grid->y + grid->tileHeight*iy;
					h->x = grid->data->types[t]->x1;
					h->y = grid->data->types[t]->y1;
					h->width = grid->data->types[t]->x2 - grid->data->types[t]->x1;
					h->height = grid->data->types[t]->y2 - grid->data->types[t]->y1;
					//grid side exclusion
					if (grid->data->types[t]->side == GRID_SIDE_TOP && eb->y + box->bottom() > e->y + h->top()) continue;
					//test collision
					if (JE::MASK::collideBox(eb, e, 0, 0, true)) c = true;
				}
			}
		}*/
	}else{
			if(x < 0)box->x += x;
			box->width += abs(x);
			if(y < 0)box->y += y;
			box->height += abs(y);

			for (	 int ix = std::max(double(0),floor((box->x + eb->x - grid->x - eg->x - 1)/grid->tileWidth )); ix < std::min(double(grid->width ),ceil((box->x + box->width + eb->x - grid->x - eg->x + 1)/grid->tileWidth )); ix ++){
				for (int iy = std::max(double(0),floor((box->y + eb->y - grid->y - eg->y - 1)/grid->tileHeight)); iy < std::min(double(grid->height),ceil((box->y + box->height+ eb->y - grid->y - eg->y + 1)/grid->tileHeight)); iy ++){
					int t = grid->tiles[ix][iy];
					if(grid->data->types[t]->empty == false) {
						//set the temporary entity and it's mask to fit that of the tile
						e->x = eg->x + grid->x + grid->tileWidth*ix;
						e->y = eg->y + grid->y + grid->tileHeight*iy;
						h->x = grid->data->types[t]->x1;
						h->y = grid->data->types[t]->y1;
						h->width = grid->data->types[t]->x2 - grid->data->types[t]->x1;
						h->height = grid->data->types[t]->y2 - grid->data->types[t]->y1;
						//test collision
					box->x = previous_x;
					box->width = previous_w;
					box->y = previous_y;
					box->height = previous_h;
						//grid side exclusion
						if (grid->data->types[t]->side == GRID_SIDE_TOP && eb->y + box->bottom() > e->y + h->top()){
						if(x < 0)box->x += x;
						box->width += abs(x);
						if(y < 0)box->y += y;
						box->height += abs(y);
							continue;
						}
						if (JE::MASK::collideBox(eb, e, x, y)) c = true;
					if(x < 0)box->x += x;
					box->width += abs(x);
					if(y < 0)box->y += y;
					box->height += abs(y);
					}
				}
			}

		box->x = previous_x;
		box->width = previous_w;
		box->y = previous_y;
		box->height = previous_h;
	}
	delete e;
	return c;
}

void Grid::newTile(float x1, float y1, float x2, float y2, bool empty, GRID_SIDE side, int ID){
	this->data->newTile(x1, y1, x2, y2, empty, side, ID);
}
void GridData::newTile(float x1, float y1, float x2, float y2, bool empty, GRID_SIDE side, int ID){
	GridTile* tile;
	tile = new GridTile(x1, y1, x2, y2, empty, side);
	if (ID < 0) {
		this->types.push_back(tile);
	}else{
		if (ID > (int)this->types.size()-1) this->types.resize(ID+1,NULL);
		if (this->types[ID] != NULL) delete this->types[ID];
		this->types[ID] = tile;
	}
}

void Grid::newTileF(float x1, float y1, float x2, float y2, bool empty, GRID_SIDE side, int ID){
	this->newTile(x1*this->tileWidth,y1*this->tileHeight,x2*this->tileWidth,y2*this->tileHeight,empty,side,ID);
}


void Grid::emptyTile(int ID, bool empty){
	this->data->emptyTile(ID, empty);
}
void GridData::emptyTile(int ID, bool empty){
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

		for (unsigned int i = 0; i < this->data->types.size(); i ++){
			if (twidth > 0){this->data->types[i]->x1 *= difx;
							this->data->types[i]->x2 *= difx;}
			if (theight> 0){this->data->types[i]->y1 *= dify;
							this->data->types[i]->y2 *= dify;}
		}
		if (twidth > 0) this->tileWidth = twidth;
		if (theight> 0) this->tileHeight = theight;
	}
}

bool collideBoxGrid(HitBox* box, Grid* grid, float x, float y, bool sweep){return false;}
};};
