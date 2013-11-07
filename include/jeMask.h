#pragma once
#include "JE.h"

class jeMask
{
	public:
		float x;
		float y;
		int type;
		jeMask();
		virtual ~jeMask();

		bool collide(jeMask* m1, jeMask* m2, float x = 0, float y = 0, bool sweep = false);
		bool collideGroup(jeMask* mask, jeGroup* group, float x = 0, float y = 0, bool sweep = false);
		bool collideEntity(jeMask* mask, jeEntity* entity, float x = 0, float y = 0, bool sweep = false);
	protected:
	private:
};



#include "jeHitBox.h"
