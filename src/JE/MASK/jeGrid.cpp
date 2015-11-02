#include "JE/MASK/jeGrid.h"

namespace JE{ namespace MASK{

Grid::Grid(int width, int height, int tile_width, int tile_height) : MaskList(),
mask_grid_vec(width, std::vector<std::shared_ptr<Mask>>(height, nullptr)) {
	this->tileWidth = tile_width;
	this->tileHeight = tile_height;
}

Grid::Grid(int x, int y, int width, int height, int tile_width, int tile_height) : MaskList(x, y),
mask_grid_vec(width, std::vector<std::shared_ptr<Mask>>(height, nullptr)) {
	this->tileWidth = tile_width;
	this->tileHeight = tile_height;
}

Grid::~Grid(){
	
}

bool Grid::isInBounds(int x, int y) const{
	if (x < 0 || y < 0) return false;
	if (x >= (int)this->mask_grid_vec.size()) return false;
	if (y >= (int)this->mask_grid_vec[x].size()) return false;
	return true;
}

Mask* Grid::getMask(int x, int y){
	if (!this->isInBounds(x, y)) return nullptr;
	return this->mask_grid_vec[x][y].get();
}

void Grid::setTile(int x, int y, const std::string& name){
	if (this->isInBounds(x, y)) {
		this->mask_grid_vec[x][y] = this->mask_type_map[name];
	}
}

void Grid::emptyTile(int x, int y){
	if (this->isInBounds(x, y)) {
		this->mask_grid_vec[x][y] = nullptr;
	}
}

int Grid::getLeft() const{
	return this->getX();
}

int Grid::getRight() const{
	return this->getX() * this->mask_grid_vec.size() * this->tileWidth;
}

int Grid::getTop() const{
	return this->getY();
}

int Grid::getBottom() const{
	if (this->mask_grid_vec.size() == 0) return this->getTop();
	return this->getY() + this->mask_grid_vec.front().size() * this->tileHeight;
}

MaskListIterator Grid::getMaskList(int left, int top, int right, int bottom){
	MaskListIterator iter;
	
	left = std::max(left, 0);
	top = std::max(top, 0);
	
	right = std::min(right, (int)this->mask_grid_vec.size()-1);
	bottom = std::min(bottom, (int)this->mask_grid_vec.front().size()-1);
	
	for (int ix = left; ix <= right; ++ ix){
		auto& sub_vector = this->mask_grid_vec[ix];
		
		for (int iy = top; iy <= bottom; ++iy){
			std::shared_ptr<Mask>& ptr = sub_vector[iy];
			
			if (ptr != nullptr){
				iter.addMask(ptr.get(), ix * this->tileWidth, iy * this->tileHeight);
			}
		}
	}
	
	return iter;
}

MaskListIterator Grid::getMaskListAll(){
	MaskListIterator iter;
	
	typedef std::vector<std::vector<std::shared_ptr<Mask>>>::size_type GridVectorType;
	typedef std::vector<std::shared_ptr<Mask>>::size_type GridSubType;
	
	for (GridVectorType ix = 0; ix < this->mask_grid_vec.size(); ++ ix){
		auto& sub_vector = this->mask_grid_vec[ix];
		
		for (GridSubType iy = 0; iy < sub_vector.size(); ++iy){
			std::shared_ptr<Mask>& ptr = sub_vector[iy];
			
			if (ptr != nullptr){
				iter.addMask(ptr.get(), ix * this->tileWidth, iy * this->tileHeight);
			}
		}
	}
	
	return iter;
}

}}