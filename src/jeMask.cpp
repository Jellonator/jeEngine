#include "jeMask.h"
using namespace std;
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

bool jeCollide(jeMask* m1, jeMask* m2, float x, float y, bool sweep){
	//Just a helper function
	if (m1 == NULL || m2 == NULL) return false;
	//Doesn't matter if the next line is commented or not, I prefer it to be though.  I mean, who declares a their mask as an empty mask?  Actually now that I think about it a lot of people do.
	//if (m1->type == JE_MASK_NONE || m2->type == JE_MASK_NONE) return false;
	if (m1->type == JE_MASK_BOX && m2->type == JE_MASK_BOX) return jeCollideBox(static_cast<jeHitBox*>(m1), static_cast<jeHitBox*>(m2), x, y, sweep);
	if (m1->type == JE_MASK_BOX && m2->type == JE_MASK_GRID) return jeCollideBoxGrid(static_cast<jeHitBox*>(m1), static_cast<jeGrid*>(m2), x, y, sweep);
	if (m1->type == JE_MASK_GRID && m2->type == JE_MASK_BOX) return jeCollideBoxGrid(static_cast<jeHitBox*>(m2), static_cast<jeGrid*>(m1), x, y, sweep);///TODO: Make the grid move, not the box.
	if (sweep){
		m1->x += x;
		m1->y += y;
	}
	return false;
}

bool jeCollide(jeEntity* e1, jeEntity* e2, float x, float y, bool sweep){
	if (e1->mask->type == JE_MASK_BOX && e2->mask->type == JE_MASK_BOX) return jeCollideBox(e1,e2,x,y,sweep);
	if (e1->mask->type == JE_MASK_BOX && e2->mask->type == JE_MASK_GRID) return jeCollideBoxGrid(e1,e2,x,y,sweep);
	if (e1->mask->type == JE_MASK_GRID && e2->mask->type == JE_MASK_BOX) return jeCollideBoxGrid(e2,e1,x,y,sweep);///TODO: Make the grid move, not the box.
	if (sweep){
		e1->x += x;
		e1->y += y;
	}
	return false;
}

bool jeCollideGroup(jeEntity* e, jeGroup* group, float x, float y, bool sweep){
	if (sweep){
		float X = e->x;
		float Y = e->y;
		float px = e->x;
		float py = e->y;
		bool c = false;
		//Move X
		for (unsigned int i = 0; i < group->entities.size(); i ++){
			if (jeCollide(e, group->entities[i], x, y, true)) c = true;
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
			if (jeCollide(e, group->entities[i], x, y, false)) return true;
		}
	}
	return false;
}

bool jeCollideGroup(jeEntity* e, int group, float x, float y, bool sweep){
	return jeCollideGroup(e, JE::world->groups[group], x, y, sweep);
}

