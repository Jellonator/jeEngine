#include "jeHitBox.h"
namespace JE{namespace MASK{
//Constructors, just setting variables
HitBox::HitBox(float width, float height){
	this->x = 0;
	this->y = 0;
	this->width = width;
	this->height = height;
	this->type = JE_MASK_BOX;
}
HitBox::HitBox(float x, float y, float width, float height){
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->type = JE_MASK_BOX;
}

HitBox::~HitBox(){
	//dtor
}

bool collideBox(Entity* e1, Entity* e2, float x, float y, bool sweep){
	if (e1->mask == NULL || e2->mask == NULL) return false;
	bool c = false;
	HitBox* m1 = static_cast<HitBox*>(e1->mask);
	HitBox* m2 = static_cast<HitBox*>(e2->mask);
	if (sweep){
	bool cx = false;
	bool cy = false;
	//X movement
		if (x != 0){
			//Change mask 1's X and Width so that it consumes it's current area and the area where it will be
			if(x < 0)m1->x += x;
			m1->width += abs(x);
			//Test collision
			if (m1->left()+e1->x < m2->right()+e2->x && m2->left()+e2->x < m1->right()+e1->x
			&&  m1->top()+e1->y < m2->bottom()+e2->y && m2->top()+e2->y < m1->bottom()+e1->y){cx = true;}
			//Move it back
			if(x < 0)m1->x -= x;
			m1->width -= abs(x);
			//And move the entity accordingly
			if(cx){
				if (m1->x + e1->x + m1->width/2 < m2->x + e2->x + m2->width / 2) e1->x = ceil(m2->left() + e2->x - m1->width);
				else e1->x = floor(m2->right() + e2->x);
			}else e1->x += x;
		}
		//Now repeat for Y.
	//Y movement
		if (y != 0){
			if(y < 0)m1->y += y;
			m1->height += abs(y);

			if (m1->left()+e1->x < m2->right()+e2->x && m2->left()+e2->x < m1->right()+e1->x
			&&  m1->top()+e1->y < m2->bottom()+e2->y && m2->top()+e2->y < m1->bottom()+e1->y){cy = true;}

			if(y < 0)m1->y -= y;
			m1->height -= abs(y);

			if(cy){
				if (m1->y + e1->y + m1->height/2 < m2->y + e2->y + m2->height / 2) e1->y = ceil(m2->top() + e2->y - m1->height);
				else e1->y = floor(m2->bottom() + e2->y);
			}else e1->y += y;
		}
	//And set C to CX or CY
		c = cx | cy;
		//and unstuck the player
		if (collideBox(e1, e2)){//std::cout << "JE: Stuck in wall. Fixing..." << std::endl;
			float dx = 1;
			float dy = 1;
			if (x > 0){
				if (e1->x + m1->left() < e2->x + m2->right()) dx = -1;else dx = 1;
			}else if (x < 0){
				if (e1->x + m1->right() < e2->x + m2->left()) dx = -1;else dx = 1;
			}else{
				if (e1->x + m1->x + m1->width/2 < e2->x + m2->x + m2->width/2) dx = -1;else dx = 1;
			}

			if (y > 0){
				if (e1->y + m1->top() < e2->y + m2->bottom()) dy = -1;else dy = 1;
			}else if (y < 0){
				if (e1->y + m1->bottom() < e2->y + m2->top()) dy = -1;else dy = 1;
			}else{
				if (e1->y + m1->y + m1->height/2 < e2->y + m2->y + m2->height/2) dy = -1;else dy = 1;
			}
			while(collideBox(e1, e2)){e1->x += dx; e1->y += dy;}
		}
	}else{
		//test collision
		m1->x += x;
		m1->y += y;
		if (m1->left()+e1->x < m2->right()+e2->x && m2->left()+e2->x < m1->right()+e1->x
		&&  m1->top()+e1->y < m2->bottom()+e2->y && m2->top()+e2->y < m1->bottom()+e1->y){c = true;}
		m1->x -= x;
		m1->y -= y;
	}
	return c;
}

bool collideBox(HitBox* m1, HitBox* m2, float x, float y, bool sweep){
	bool c = false;
		if (sweep){
	bool cx = false;
	bool cy = false;
	//X movement
		//Change mask 1's X and Width so that it consumes it's current area and the area where it will be
		if(x < 0)m1->x += x;
		m1->width += abs(x);
		//Test collision
		if (m1->left() < m2->right() && m2->left() < m1->right()
		&&  m1->top() < m2->bottom() && m2->top() < m1->bottom()){cx = true;}
		//Move it back
		if(x < 0)m1->x -= x;
		m1->width -= abs(x);
		//And move the entity accordingly
		if(cx){
			if (x > 0)m1->x = ceil(m2->left() - m1->width);
			else m1->x = floor(m2->right());
		}else m1->x += x;
		//Now repeat for Y.
	//Y movement
		if(y < 0)m1->y += y;
		m1->height += abs(y);

		if (m1->left() < m2->right() && m2->left() < m1->right()
		&&  m1->top() < m2->bottom() && m2->top() < m1->bottom()){cy = true;}

		if(y < 0)m1->y -= y;
		m1->height -= abs(y);

		if(cy){
			if (y > 0) m1->y = ceil(m2->top() - m1->height);
			else m1->y = floor(m2->bottom());
		}else m1->y += y;
	//And set C to CX or CY
		c = cx || cy;
	}else{
		if (m1->left() + x < m2->right() && m2->left() < m1->right() + x
		&&  m1->top()+ y < m2->bottom() && m2->top() < m1->bottom() + y){c = true;}
	}
	return c;

	return c;
}
float HitBox::left(){return x;}
float HitBox::right(){return x + width;}
float HitBox::top(){return y;}
float HitBox::bottom(){return y + height;}
};};
