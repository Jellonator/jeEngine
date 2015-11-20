#pragma once
#include <vector>

namespace JE{ namespace MASK{

class Mask;
class Hitbox;
class MaskList;
typedef Mask PointMask;

class Mask{
public:
	Mask(int x = 0, int y = 0);
	virtual ~Mask();
	
	virtual bool getCollide(Hitbox& box, int move_x, int move_y, int* out_x = nullptr, int* out_y = nullptr);
	virtual bool getCollide(PointMask& point, int move_x, int move_y, int* out_x = nullptr, int* out_y = nullptr);
	virtual bool getCollide(MaskList& mask_list, int move_x, int move_y, int* out_x = nullptr, int* out_y = nullptr);
	
	//Call collide is used specifically for 
	virtual bool callCollide(Hitbox& box, int move_x, int move_y, int* out_x = nullptr, int* out_y = nullptr);
	virtual bool callCollide(PointMask& point, int move_x, int move_y, int* out_x = nullptr, int* out_y = nullptr);
	virtual bool callCollide(MaskList& mask_list, int move_x, int move_y, int* out_x = nullptr, int* out_y = nullptr);
	bool callCollideGroup(const std::vector<Mask*>& mask_vec, int move_x, int move_y, int* out_x = nullptr, int* out_y = nullptr);
	
	//virtual bool raytrace(int start_x, int start_y, int dir_x, int dir_y, int* out_x = nullptr, int* out_y = nullptr);
	void moveBy(int x, int y);
	void moveTo(int x, int y);
	void setX(int value);
	void setY(int value);
	int getX() const;
	int getY() const;
	int* ptrX();
	int* ptrY();
	
	virtual int getLeft() const;
	virtual int getRight() const;
	virtual int getTop() const;
	virtual int getBottom() const;
	
	int getWidth() const;
	int getHeight() const;
	
	int getCenterX() const;
	int getCenterY() const;
	
	virtual void draw(int x, int y);
private:
	int x;
	int y;
};

}}