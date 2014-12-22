#include "jeLine.h"
namespace JE{
Line::Line(float x1, float y1, float x2, float y2)
{
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
}

Line::~Line()
{
	//dtor
}

bool testLines(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float* ox, float* oy){
	float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	//Parallel
	if (d == 0) return false;
	// Get the x and y
	float pre = (x1*y2 - y1*x2);
	float post = (x3*y4 - y3*x4);
	float outx = (pre * (x3 - x4) - (x1 - x2) * post) / d;
	float outy = (pre * (y3 - y4) - (y1 - y2) * post) / d;
	//Doesn't collide, but they will intersect eventually
	if (outx < std::min(x1, x2) || outx > std::max(x1, x2) || outx < std::min(x3, x4) || outx > std::max(x3, x4)) return false;
	if (outy < std::min(y1, y2) || outy > std::max(y1, y2) || outy < std::min(y3, y4) || outy > std::max(y3, y4)) return false;
	//Output
	if (ox != NULL) ox = &outx;
	if (oy != NULL) oy = &outy;
	//It does intersect
	return true;
}

bool testLines(Line* a, Line* b, float* ox, float* oy){
	return testLines(a->x1, a->y1, a->x2, a->y2, b->x1, b->y1, b->x2, b->y2, ox, oy);
}

namespace MASK{
bool collideBoxLine(Line* a, JE::MASK::HitBox* box, float* ox, float* oy){
	return collideBoxLine(a->x1, a->y1, a->x2, a->y2, box, ox, oy);
}
bool collideBoxLine(Line* a, Entity* e, float* ox, float* oy){
	return collideBoxLine(a->x1, a->y1, a->x2, a->y2, e, ox, oy);
}
bool collideBoxLine(float x1, float y1, float x2, float y2, JE::MASK::HitBox* box, float* ox, float* oy){
	float outputX;
	float outputY;
	bool c = false;
	if (testLines(x1, y1, x2, y2, box->x, box->y, box->x+box->width, box->y, &outputY, &outputX)){
		ox = &outputX;
		oy = &outputY;
		c = true;
	}
	if (testLines(x1, y1, x2, y2, box->x, box->y, box->x, box->y + box->height, &outputY, &outputX)){
		if (JE::MATH::squareDistance(x1, y1, outputX, outputY) < JE::MATH::squareDistance(x1, y1, *ox, *oy)){
			ox = &outputX;
			oy = &outputY;
		}
		c = true;
	}
	if (testLines(x1, y1, x2, y2, box->x+box->width, box->y, box->x+box->width, box->y + box->height, &outputY, &outputX)){
		if (JE::MATH::squareDistance(x1, y1, outputX, outputY) < JE::MATH::squareDistance(x1, y1, *ox, *oy)){
			ox = &outputX;
			oy = &outputY;
		}
		c = true;
	}
	if (testLines(x1, y1, x2, y2, box->x, box->y+box->height, box->x+box->width, box->y + box->height, &outputY, &outputX)){
		if (JE::MATH::squareDistance(x1, y1, outputX, outputY) < JE::MATH::squareDistance(x1, y1, *ox, *oy)){
			ox = &outputX;
			oy = &outputY;
		}
		c = true;
	}
	return c;
}

bool collideBoxLine(float x1, float y1, float x2, float y2, JE::Entity* e, float* ox, float* oy){
	JE::MASK::HitBox* box = dynamic_cast<JE::MASK::HitBox*>(e->mask);
	if (!box) return false;
	float outputX;
	float outputY;
	bool c = false;
	int x3 = box->x + e->x;//left
	int y3 = box->y + e->y;//top
	int x4 = box->x + e->x + box->width;//right
	int y4 = box->y + e->y + box->height;//bottom
	if (testLines(x1, y1, x2, y2, x3, y3, x4, y3, &outputY, &outputX)){
		if (ox && oy){
			ox = &outputX;
			oy = &outputY;
		}
		c = true;
	}
	if (testLines(x1, y1, x2, y2, x3, y3, x3, y4, &outputY, &outputX)){
		if (ox && oy){
			if (JE::MATH::squareDistance(x1, y1, outputX, outputY) < JE::MATH::squareDistance(x1, y1, *ox, *oy)){
				ox = &outputX;
				oy = &outputY;
			}
		}
		c = true;
	}
	if (testLines(x1, y1, x2, y2, x4, y3, x4, y4, &outputY, &outputX)){
		if (ox && oy){
			if (JE::MATH::squareDistance(x1, y1, outputX, outputY) < JE::MATH::squareDistance(x1, y1, *ox, *oy)){
				ox = &outputX;
				oy = &outputY;
			}
		}
		c = true;
	}
	if (testLines(x1, y1, x2, y2, x3, y4, x4, y4, &outputY, &outputX)){
		if (ox && oy){
			if (JE::MATH::squareDistance(x1, y1, outputX, outputY) < JE::MATH::squareDistance(x1, y1, *ox, *oy)){
				ox = &outputX;
				oy = &outputY;
			}
		}
		c = true;
	}
	return c;
}
};

};
