#include "jeMask.h"
#include <cstddef>
#include "jeHitBox.h"
using namespace std;
namespace JE{

bool defaultGetCollidable(Mask* this_mask, Mask* other_mask, Entity* this_entity, Entity* other_entity){
	return true;
}

Mask::Mask()
{
	x = 0;
	y = 0;
	type = JE_MASK_NONE;
	this->getCollidable = defaultGetCollidable;
}

Mask::~Mask()
{
	//dtor
}

void Mask::draw(float x, float y, GRAPHICS::Camera* camera){}
void Mask::setCollisionFunction(function_pointer_mask collisionFunction){
	this->getCollidable = (collisionFunction == NULL) ? defaultGetCollidable : collisionFunction;
}
namespace MASK{
bool collide(Mask* m1, Mask* m2, float x, float y, bool sweep){
	//Just a helper function
	//if (m1 == NULL || m2 == NULL) return false;
	//Doesn't matter if the next line is commented or not, I prefer it to be though.  I mean, who declares a their mask as an empty mask?
	//if (m1->type == JE_MASK_NONE || m2->type == JE_MASK_NONE) return false;
	if (m1 == NULL) return false;
	if (m1 != m2 && m2 != NULL){
		if (m1->type == JE_MASK_BOX && m2->type == JE_MASK_BOX) return collideBox(static_cast<HitBox*>(m1), static_cast<HitBox*>(m2), x, y, sweep);
		if (m1->type == JE_MASK_BOX && m2->type == JE_MASK_GRID) return collideBoxGrid(static_cast<HitBox*>(m1), static_cast<Grid*>(m2), x, y, sweep);
		if (m1->type == JE_MASK_GRID && m2->type == JE_MASK_BOX) return collideBoxGrid(static_cast<HitBox*>(m2), static_cast<Grid*>(m1), x, y, sweep);///TODO: Make the grid move, not the box.
	}
	if (sweep){
		m1->x += x;
		m1->y += y;
	}
	return false;
}

bool collide(Entity* e1, Entity* e2, float x, float y, bool sweep){
	if (e1 == NULL) return false;
	if (e1 != e2 && e2 != NULL){
		if (e1->mask->type == JE_MASK_BOX && e2->mask->type == JE_MASK_BOX) return collideBox(e1,e2,x,y,sweep);
		if (e1->mask->type == JE_MASK_BOX && e2->mask->type == JE_MASK_GRID) return collideBoxGrid(e1,e2,x,y,sweep);
		if (e1->mask->type == JE_MASK_GRID && e2->mask->type == JE_MASK_BOX) return collideBoxGrid(e2,e1,x,y,sweep);///TODO: Make the grid move, not the box.
	}
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

void push(Entity* pusher, Entity* pushed, int direction_x, int direction_y){
	if (JE::MASK::collide(pusher, pushed, 0, 0)){
		float previous_x = pushed->x;
		float previous_y = pushed->y;
		float to_x = pushed->x;
		float to_y = pushed->y;
		float dis = 0;
		float ndis = 0;

		JE::MASK::collide(pushed, pusher, 0, 1, true);
		to_x = pushed->x;
		to_y = pushed->y;
		dis = JE::MATH::distance(to_x, to_y, previous_x, previous_y);
		pushed->x = previous_x;
		pushed->y = previous_y;

		JE::MASK::collide(pushed, pusher, 0,-1, true);
		ndis = JE::MATH::distance(pushed->x, pushed->y, previous_x, previous_y);
		if (ndis < dis){
			dis = ndis;
			to_x = pushed->x;
			to_y = pushed->y;
		}
		pushed->x = previous_x;
		pushed->y = previous_y;

		JE::MASK::collide(pushed, pusher, 1, 0, true);
		ndis = JE::MATH::distance(pushed->x, pushed->y, previous_x, previous_y);
		if (ndis < dis){
			dis = ndis;
			to_x = pushed->x;
			to_y = pushed->y;
		}
		pushed->x = previous_x;
		pushed->y = previous_y;

		JE::MASK::collide(pushed, pusher,-1, 0, true);
		ndis = JE::MATH::distance(pushed->x, pushed->y, previous_x, previous_y);
		if (ndis < dis){
			dis = ndis;
			to_x = pushed->x;
			to_y = pushed->y;
		}
		pushed->x = to_x;
		pushed->y = to_y;
	}
}
void push(int pusher, Entity* pushed, int direction_x, int direction_y){
	push(JE::world->getGroup(pusher), pushed, direction_x, direction_y);
}
void push(Group* pusher, Entity* pushed, int direction_x, int direction_y){
	if (JE::MASK::collideGroup(pushed, pusher, 0, 0)){
		float previous_x = pushed->x;
		float previous_y = pushed->y;
		float to_x = pushed->x;
		float to_y = pushed->y;
		float dis = 0;
		float ndis = 0;

		JE::MASK::collideGroup(pushed, pusher, 0, 1, true);
		to_x = pushed->x;
		to_y = pushed->y;
		dis = JE::MATH::distance(to_x, to_y, previous_x, previous_y);
		pushed->x = previous_x;
		pushed->y = previous_y;

		JE::MASK::collideGroup(pushed, pusher, 0,-1, true);
		ndis = JE::MATH::distance(pushed->x, pushed->y, previous_x, previous_y);
		if (ndis < dis){
			dis = ndis;
			to_x = pushed->x;
			to_y = pushed->y;
		}
		pushed->x = previous_x;
		pushed->y = previous_y;

		JE::MASK::collideGroup(pushed, pusher, 1, 0, true);
		ndis = JE::MATH::distance(pushed->x, pushed->y, previous_x, previous_y);
		if (ndis < dis){
			dis = ndis;
			to_x = pushed->x;
			to_y = pushed->y;
		}
		pushed->x = previous_x;
		pushed->y = previous_y;

		JE::MASK::collideGroup(pushed, pusher,-1, 0, true);
		ndis = JE::MATH::distance(pushed->x, pushed->y, previous_x, previous_y);
		if (ndis < dis){
			dis = ndis;
			to_x = pushed->x;
			to_y = pushed->y;
		}
		pushed->x = to_x;
		pushed->y = to_y;
	}
}
void pushGroup(Entity* pusher, int group, int direction_x, int direction_y){
	pushGroup(pusher, JE::world->getGroup(group), direction_x, direction_y);
}
void pushGroup(Entity* pusher, JE::Group* group, int direction_x, int direction_y){
	for (int i = 0; i < group->entities.size(); i ++){
		push(pusher, group->entities[i], direction_x, direction_y);
	}
}

void pushGroup(JE::Group* pusher, JE::Group* group, int direction_x, int direction_y){
	for (int i = 0; i < group->entities.size(); i ++){
		JE::MASK::push(pusher, group->entities[i], direction_x, direction_y);
	}
}
void pushGroup(int pusher, JE::Group* group, int direction_x, int direction_y){
	for (int i = 0; i < group->entities.size(); i ++){
		JE::MASK::push(JE::world->getGroup(pusher), group->entities[i], direction_x, direction_y);
	}
}
void pushGroup(int pusher, int group, int direction_x, int direction_y){
	pushGroup(JE::world->getGroup(pusher), JE::world->getGroup(group));
}
void pushGroup(JE::Group* pusher, int group, int direction_x, int direction_y){
	pushGroup(pusher, JE::world->getGroup(group));
}
};};
