#pragma once
#include "../jeMask.h"
#include <vector>

namespace JE{ namespace MASK{

class Maskiterator : public Mask{
public:
	Maskiterator(int x = 0, int y = 0);
	virtual ~Maskiterator();
	
	virtual std::vector<Mask*> getMaskList(int left, int top, int right, int bottom);
	virtual std::vector<Mask*> getMaskListAll();
	std::vector<Mask*> getMaskListMove(int left, int top, int right, int bottom, int move_x, int move_y);
	
	virtual bool getCollide(Hitbox& box, int move_x, int move_y, int* out_x = nullptr, int* out_y = nullptr);
	virtual bool getCollide(PointMask& point, int move_x, int move_y, int* out_x = nullptr, int* out_y = nullptr);
	virtual bool getCollide(Maskiterator& mask_list, int move_x, int move_y, int* out_x = nullptr, int* out_y = nullptr);
	
	virtual bool callCollide(Hitbox& box, int move_x, int move_y, int* out_x = nullptr, int* out_y = nullptr);
	virtual bool callCollide(PointMask& point, int move_x, int move_y, int* out_x = nullptr, int* out_y = nullptr);
	virtual bool callCollide(Maskiterator& mask_list, int move_x, int move_y, int* out_x = nullptr, int* out_y = nullptr);
	
	virtual void draw(int x, int y);
};

}}