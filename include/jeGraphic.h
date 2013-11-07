#pragma once
#include "JE.h"

class jeGraphic
{
	public:
		jeGraphic();
		virtual ~jeGraphic();
		jePoint* origin;
		jePoint* scale;
		float rotation;
		virtual void draw(float x, float y);
		virtual void update();
	protected:
	private:
};
