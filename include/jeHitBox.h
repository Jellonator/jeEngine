#pragma once
#include "JE.h"

class jeHitBox : public jeMask
{
	public:
		float width;/**< \brief float width, the width of the box. */
		float height;/**< \brief the float height, height of the box. */
		jeHitBox(float x, float y, float width, float height);
		jeHitBox(float width = 32, float height = 32);
		float left();/**< \return float, the left side of the box. */
		float right();/**< \return float, the right side of the box. */
		float top();/**< \return float, the top of the box. */
		float bottom();/**< \return float, the bottom of the box. */
		virtual ~jeHitBox();
	protected:
	private:
};

bool jeCollideBox(jeHitBox* m1, jeHitBox* m2, float x = 0, float y = 0, bool sweep = false);
bool jeCollideBox(jeEntity* e1, jeEntity* e2, float x = 0, float y = 0, bool sweep = false);
