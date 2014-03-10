#pragma once
#include "JE.h"
class jeLine
{
	public:
		float x1, y1, x2, y2;
		jeLine(float x1, float y1, float x2, float y2);
		virtual ~jeLine();
	protected:
	private:
};

bool jeTestLines(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float* ox, float* oy);
bool jeTestLines(jeLine* a, jeLine* b, float *ox, float *oy);
