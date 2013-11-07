#pragma once
#include "JE.h"
#include "jeHitBox.h"

class jeHitBox : public jeMask
{
	public:
		float width;
		float height;
		jeHitBox(float x, float y, float width, float height);
		jeHitBox(float width = 32, float height = 32);
		float left();
		float right();
		float top();
		float bottom();
		virtual ~jeHitBox();

		static bool collideBox(jeHitBox* b1, jeHitBox* b2, float x = 0, float y = 0, bool sweep = false, float width = 0, float height = 0);
	protected:
	private:
};
