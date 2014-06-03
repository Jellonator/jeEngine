#pragma once
#include "JE.h"
namespace JE{
class Line
{
	public:
		float x1, y1, x2, y2;
		Line(float x1, float y1, float x2, float y2);
		virtual ~Line();
	protected:
	private:
};

bool testLines(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float *ox = NULL, float *oy = NULL);
bool testLines(Line* a, Line* b, float *ox = NULL, float *oy = NULL);
};
