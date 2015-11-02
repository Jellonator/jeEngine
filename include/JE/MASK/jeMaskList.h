#pragma once
#include "../jeMask.h"
#include <vector>
#include <tuple>

namespace JE{ namespace MASK{
	
class MaskListIterator : public Mask{
	Mask* get_next(int* get_x, int* get_y);
	void addMask(Mask*, int x, int y);
private:
	std::vector<std::pair<int, int>> position_vec;
	std::vector<Mask*> mask_vect;
}

class MaskList : public Mask{
public:
	MaskList(int x = 0, int y = 0);
	virtual ~MaskList();
	
	virtual std::vector<Mask*> getMaskList(int left, int top, int right, int bottom);
	virtual std::vector<Mask*> getMaskListAll();
	std::vector<Mask*> getMaskListMove(int left, int top, int right, int bottom, int move_x, int move_y);
	
	virtual bool getCollide(Hitbox& box, int move_x, int move_y, int* out_x = nullptr, int* out_y = nullptr);
	virtual bool getCollide(PointMask& point, int move_x, int move_y, int* out_x = nullptr, int* out_y = nullptr);
	virtual bool getCollide(MaskList& mask_list, int move_x, int move_y, int* out_x = nullptr, int* out_y = nullptr);
	
	virtual bool callCollide(Hitbox& box, int move_x, int move_y, int* out_x = nullptr, int* out_y = nullptr);
	virtual bool callCollide(PointMask& point, int move_x, int move_y, int* out_x = nullptr, int* out_y = nullptr);
	virtual bool callCollide(MaskList& mask_list, int move_x, int move_y, int* out_x = nullptr, int* out_y = nullptr);
	
	virtual int getLeft() const;
	virtual int getRight() const;
	virtual int getTop() const;
	virtual int getBottom() const;
	
	void updateGetters();
	virtual void draw(int x, int y);
	
private:
	int get_left;
	int get_right;
	int get_top;
	int get_bottom;
};

}}