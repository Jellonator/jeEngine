#include "jeMask.h"
#include <cstddef>
#include "jeHitBox.h"
using namespace std;
namespace JE{
Mask::Mask()
{
	x = 0;
	y = 0;
	type = JE_MASK_NONE;
}

Mask::~Mask()
{
	//dtor
}
namespace MASK{
bool collide(Mask* m1, Mask* m2, float x, float y, bool sweep){
	//Just a helper function
	if (m1 == NULL || m2 == NULL) return false;
	//Doesn't matter if the next line is commented or not, I prefer it to be though.  I mean, who declares a their mask as an empty mask?  Actually now that I think about it a lot of people do.
	//if (m1->type == JE_MASK_NONE || m2->type == JE_MASK_NONE) return false;
	if (m1->type == JE_MASK_BOX && m2->type == JE_MASK_BOX) return collideBox(static_cast<HitBox*>(m1), static_cast<HitBox*>(m2), x, y, sweep);
	if (m1->type == JE_MASK_BOX && m2->type == JE_MASK_GRID) return collideBoxGrid(static_cast<HitBox*>(m1), static_cast<Grid*>(m2), x, y, sweep);
	if (m1->type == JE_MASK_GRID && m2->type == JE_MASK_BOX) return collideBoxGrid(static_cast<HitBox*>(m2), static_cast<Grid*>(m1), x, y, sweep);///TODO: Make the grid move, not the box.
	if (sweep){
		m1->x += x;
		m1->y += y;
	}
	return false;
}

bool collide(Entity* e1, Entity* e2, float x, float y, bool sweep){
	if (e1->mask->type == JE_MASK_BOX && e2->mask->type == JE_MASK_BOX) return collideBox(e1,e2,x,y,sweep);
	if (e1->mask->type == JE_MASK_BOX && e2->mask->type == JE_MASK_GRID) return collideBoxGrid(e1,e2,x,y,sweep);
	if (e1->mask->type == JE_MASK_GRID && e2->mask->type == JE_MASK_BOX) return collideBoxGrid(e2,e1,x,y,sweep);///TODO: Make the grid move, not the box.
	if (sweep){
		e1->x += x;
		e1->y += y;
	}
	return false;
}

bool collideGroup(Entity* e, Group* group, float x, float y, bool sweep){
	if (e->mask == NULL) return false;
	if (sweep){
		float X = e->x + x;
		float Y = e->y + y;
		float px = e->x;
		float py = e->y;
		bool c = false;
		//Move X
		for (unsigned int i = 0; i < group->entities.size(); i ++){
			JE::Entity* o = group->entities[i];
			if (o->mask == NULL) continue;
			if (collide(e, o, x, y, true)) c = true;
			if (i == 0) {X = e->x; Y = e->y;}
			else {
				if (x > 0) X = min(X, e->x);
				if (x < 0) X = max(X, e->x);
				if (y > 0) Y = min(Y, e->y);
				if (y < 0) Y = max(Y, e->y);
			}
			e->x = px;
			e->y = py;
		}
		e->x = X;
		e->y = Y;
		return c;
	}else{
		for (unsigned int i = 0; i < group->entities.size(); i ++){
			JE::Entity* o = group->entities[i];
			if (o->mask == NULL) continue;
			if (collide(e, o, x, y, false)) return true;
		}
	}
	return false;
}

bool collideGroup(Entity* e, int group, float x, float y, bool sweep){
	return collideGroup(e, world->groups[group], x, y, sweep);
}
};};
