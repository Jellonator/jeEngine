#include "jeMask.h"

jeMask::jeMask()
{
	x = 0;
	y = 0;
	type = JE_MASK_NONE;
}

jeMask::~jeMask()
{
	//dtor
}

bool jeMask::collide(jeMask* m1, jeMask* m2, float x, float y, bool sweep){
	//Just a helper function
	if (m1 == NULL || m2 == NULL) return false;
	//Doesn't matter if the next line is commented or not, I prefer it to be though.  I mean, who declares a their mask as an empty mask?  Actually now that I think about it a lot of people do.
	//if (m1->type == JE_MASK_NONE || m2->type == JE_MASK_NONE) return false;
	if (m1->type == JE_MASK_BOX && m2->type == JE_MASK_BOX) return jeHitBox::collideBox(static_cast<jeHitBox*>(m1), static_cast<jeHitBox*>(m2));
	return false;
}

bool jeMask::collideEntity(jeMask* mask, jeEntity* entity, float x, float y, bool sweep){
	//Also a helper function
	return jeMask::collide(mask, entity->mask, x, y, sweep);
}

bool jeMask::collideGroup(jeMask* mask, jeGroup* group, float x, float y, bool sweep){
	//Kind of a helper function, but it actually has a use.
	bool r = false;
	for (unsigned int i = 0; i < group->entities.size(); i ++){
		if (group->__EREMOVED__[i] == false) {
			if (jeMask::collide(mask, group->entities[i]->mask)) r = true;
		}
	}
	return r;
}
