#pragma once
#include "jeMaskList.h"
#include <vector>
#include <memory>
#include <map>
#include <string>

namespace JE{ namespace MASK{

class Grid : public MaskList {
public:
	Grid(int width, int height, int tile_width, int tile_height);
	Grid(int x, int y, int width, int height, int tile_width, int tile_height);
	virtual ~Grid();
	
	// Getters
	bool isInBounds(int x, int y) const;
	virtual int getLeft() const;
	virtual int getRight() const;
	virtual int getTop() const;
	virtual int getBottom() const;
	void limitToBounds(int& left, int& top, int& right, int& bottom) const;
	
	virtual MaskListIterator getMaskList(int left, int top, int right, int bottom);
	virtual MaskListIterator getMaskListAll();
	Mask* getMask(int x, int y);
	
	// Setters
	void setTile(const std::string& name, int x, int y);
	void setTile(const std::shared_ptr<Mask>& mask, int x, int y);
	void setRect(const std::string& name, int x1, int y1, int x2, int y2);
	void setRect(const std::shared_ptr<Mask>& mask, int x1, int y1, int x2, int y2);
	void emptyTile(int x, int y);
	void emptyRect(int x1, int y1, int x2, int y2);
	
	template <class TName, class... TArgs>
	TName& addNewType(const std::string& name, TArgs... arguments) {
		std::shared_ptr<TName> ptr = std::make_shared<TName>(arguments...);
		this->mask_type_map[name] = ptr;
		return *ptr;
	}
	
	void generateFromPoints(const std::string& name, const std::vector<std::pair<int,int>>& points, int offset_x = 0, int offset_y = 0);
	void generateFromPoints(const std::shared_ptr<Mask>& mask, const std::vector<std::pair<int,int>>& points, int offset_x = 0, int offset_y = 0);
	
	virtual void draw(const JE::GRAPHICS::Camera& camera, int x, int y);
	
private:
	std::map<std::string, std::shared_ptr<Mask>> mask_type_map;
	std::vector<std::vector<std::shared_ptr<Mask>>> mask_grid_vec;
	int tileWidth;
	int tileHeight;
};

}}