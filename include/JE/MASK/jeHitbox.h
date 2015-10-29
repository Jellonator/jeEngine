#pragma once
#include "../jeMask.h"

namespace JE{ namespace MASK{

class Hitbox : public Mask{
public:
	Hitbox(int x1, int y1, int x2, int y2);
	virtual ~Hitbox();
	
	bool getCollide(PointMask& point, int move_x, int move_y, int* out_x = nullptr, int* out_y = nullptr);
	bool getCollide(Hitbox& box, int move_x, int move_y, int* out_x = nullptr, int* out_y = nullptr);
	
	virtual bool callCollide(Hitbox& box, int move_x, int move_y, int* out_x = nullptr, int* out_y = nullptr);
	virtual bool callCollide(PointMask& point, int move_x, int move_y, int* out_x = nullptr, int* out_y = nullptr);
	virtual bool callCollide(Maskiterator& mask_list, int move_x, int move_y, int* out_x = nullptr, int* out_y = nullptr);
	
	int getWidth() const;
	int getHeight() const;
	
	int getLeft() const;
	int getRight() const;
	int getTop() const;
	int getBottom() const;
	
	int getX1() const;
	int getY1() const;
	int getX2() const;
	int getY2() const;
	
	void getStretch(int& x1, int& y1, int& x2, int& y2, int move_x, int move_y) const;
	bool containsPointStretch(int x, int y, int move_x, int move_y) const;
	bool containsPoint(int x, int y) const;
	
	bool containsRect(int x1, int y1, int x2, int y2) const;
	bool containsRect(const Hitbox& rect) const;
	bool containsRectStretch(const Hitbox& rect, int move_x, int move_y) const;
	
	virtual void draw(int x, int y);
private:
	int x1;
	int y1;
	int x2;
	int y2;
};

}}