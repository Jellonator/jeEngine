#pragma once
#include "JE.h"
namespace JE{namespace MASK{
class HitBox : public Mask
{
	public:
		float width;/**< \brief float width, the width of the box. */
		float height;/**< \brief the float height, height of the box. */
		HitBox(float x, float y, float width, float height);
		HitBox(float width = 32, float height = 32);
		float left();/**< \return float, the left side of the box. */
		float right();/**< \return float, the right side of the box. */
		float top();/**< \return float, the top of the box. */
		float bottom();/**< \return float, the bottom of the box. */
		virtual ~HitBox();
	protected:
	private:
};

bool collideBox(HitBox* m1, HitBox* m2, float x = 0, float y = 0, bool sweep = false);
bool collideBox(Entity* e1, Entity* e2, float x = 0, float y = 0, bool sweep = false);
};};
