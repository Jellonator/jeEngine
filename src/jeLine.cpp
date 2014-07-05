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
};
