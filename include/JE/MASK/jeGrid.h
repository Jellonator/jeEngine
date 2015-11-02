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
	
	virtual MaskListIterator getMaskList(int left, int top, int right, int bottom);
	virtual MaskListIterator getMaskListAll();
	Mask* getMask(int x, int y);
	
	// Setters
	void setTile(int x, int y, const std::string& name);
	void emptyTile(int x, int y);
	
	template <class TName, class... TArgs>
	TName& addNewType(const std::string& name, TArgs... arguments) {
		std::shared_ptr<TName> ptr = std::make_shared<TName>(arguments...);
		this->mask_type_map[name] = ptr;
		return *ptr;
	}
private:
	std::map<std::string, std::shared_ptr<Mask>> mask_type_map;
	std::vector<std::vector<std::shared_ptr<Mask>>> mask_grid_vec;
	int tileWidth;
	int tileHeight;
};

}}