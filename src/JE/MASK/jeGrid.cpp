#include "JE/MASK/jeGrid.h"
#include "JE/UTIL/jeMath.h"
#include <algorithm>

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

void Grid::limitToBounds(int& left, int& top, int& right, int& bottom) const{
	left = std::max(left, 0);
	top = std::max(top, 0);
	
	right = std::min(right, (int)this->mask_grid_vec.size()-1);
	bottom = std::min(bottom, (int)this->mask_grid_vec.front().size()-1);
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

void Grid::setTile(const std::string& name, int x, int y){
	this->setTile(this->mask_type_map[name], x, y);
}

void Grid::setTile(const std::shared_ptr<Mask>& mask, int x, int y){
	if (this->isInBounds(x, y)) {
		this->mask_grid_vec[x][y] = mask;
	}
}

void Grid::emptyTile(int x, int y){
	if (this->isInBounds(x, y)) {
		this->mask_grid_vec[x][y] = nullptr;
	}
}

void Grid::setRect(const std::string& name, int x1, int y1, int x2, int y2){
	this->setRect(this->mask_type_map[name], x1, y1, x2, y2);
}

void Grid::setRect(const std::shared_ptr<Mask>& mask, int x1, int y1, int x2, int y2){
	this->limitToBounds(x1, y1, x2, y2);
	for (int ix = x1; ix <= x2; ++ix){
		for (int iy = y1; iy <= y2; ++iy){
			this->setTile(mask, ix, iy);
		}
	}
}

void Grid::emptyRect(int x1, int y1, int x2, int y2){
	this->limitToBounds(x1, y1, x2, y2);
	for (int ix = x1; ix <= x2; ++ix){
		for (int iy = y1; iy <= y2; ++iy){
			this->emptyTile(ix, iy);
		}
	}
}

int Grid::getLeft() const{
	return this->getX();
}

int Grid::getRight() const{
	return this->getX() + this->mask_grid_vec.size() * this->tileWidth;
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
	
	left -= this->getX();
	right -= this->getX();
	top -= this->getY();
	bottom -= this->getY();
	
	left   = left   / this->tileWidth  - 1;
	right  = right  / this->tileWidth  + 1;
	top    = top    / this->tileHeight - 1;
	bottom = bottom / this->tileHeight + 1;
	
	this->limitToBounds(left, top, right, bottom);
	
	for (int ix = left; ix <= right; ++ix){
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

void Grid::generateFromPoints(const std::string& name, const std::vector<std::pair<int,int>>& points, int offset_x, int offset_y){
	this->generateFromPoints(this->mask_type_map[name], points, offset_x, offset_y);
}

void Grid::generateFromPoints(const std::shared_ptr<Mask>& mask, const std::vector<std::pair<int,int>>& points, int offset_x, int offset_y){
	if (points.size() == 0) return;
	if (points.size() == 1){
		this->setTile(mask, points.front().first + offset_x, points.front().second + offset_y);
		return;
	}
	
	auto* previous = &points.back();
	int current_x = previous->first;
	int current_y = previous->second;
	
	for (std::vector<std::pair<int,int>>::const_iterator next = points.begin(); next != points.end(); ++next){
		int diff_x = std::abs(previous->first - next->first);
		int diff_y = std::abs(previous->second - next->second);
		int new_x = next->first;
		int new_y = next->second;
		
		while (current_x != new_x || current_y != new_y){
			//Only needs to move on x axis
			if (current_x != new_x && current_y == new_y){
				current_x = JE::MATH::linearTween(current_x, new_x, 1);
				
			//Only needs to move on y axis
			} else if (current_x == new_x && current_y != new_y){
				current_y = JE::MATH::linearTween(current_y, new_y, 1);
				
			//Pick axis to move on based on differences
			} else {
				int diff = std::abs(current_x-new_x)*diff_y - std::abs(current_y-new_y)*diff_x;
				//If X difference is greater than or equal to Y difference
				if (diff >= 0){
					current_x = JE::MATH::linearTween(current_x, new_x, 1);
				}
				//If Y difference is greater than or equal to X difference
				if (diff <= 0) {
					current_y = JE::MATH::linearTween(current_y, new_y, 1);
				} 
			}
			this->setTile(mask, current_x + offset_x, current_y + offset_y);
		}
		
		previous = &*next;
	}
}

}}