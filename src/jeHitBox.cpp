#include "jeHitBox.h"
//Constructors, just setting variables.
using namespace std;
jeHitBox::jeHitBox(float width, float height){
	this->x = 0;
	this->y = 0;
	this->width = width;
	this->height = height;
	this->type = JE_MASK_BOX;
}
jeHitBox::jeHitBox(float x, float y, float width, float height){
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->type = JE_MASK_BOX;
}

jeHitBox::~jeHitBox(){
	//dtor
}

bool jeCollideBox(jeEntity* e1, jeEntity* e2, float x, float y, bool sweep){
	bool c = false;
	jeHitBox* m1 = static_cast<jeHitBox*>(e1->mask);
	jeHitBox* m2 = static_cast<jeHitBox*>(e2->mask);
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
				if (x > 0)e1->x = ceil(m2->left() + e2->x - m1->width);
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
				if (y > 0) e1->y = ceil(m2->top() + e2->y - m1->height);
				else e1->y = floor(m2->bottom() + e2->y);
			}else e1->y += y;
		}
	//And set C to CX or CY
		c = cx || cy;
	}else{
		if (m1->left()+e1->x < m2->right()+e2->x && m2->left()+e2->x < m1->right()+e1->x
		&&  m1->top()+e1->y < m2->bottom()+e2->y && m2->top()+e2->y < m1->bottom()+e1->y){c = true;}
	}
	return c;
}

bool jeCollideBox(jeHitBox* m1, jeHitBox* m2, float x, float y, bool sweep){
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
float jeHitBox::left(){return x;}
float jeHitBox::right(){return x + width;}
float jeHitBox::top(){return y;}
float jeHitBox::bottom(){return y + height;}
