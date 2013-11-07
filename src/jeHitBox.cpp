#include "jeHitBox.h"
//Constructors, just setting variables.
jeHitBox::jeHitBox(float width, float height){
	this->x = 0;
	this->y = 0;
	this->width = width;
	this->height = height;
}
jeHitBox::jeHitBox(float x, float y, float width, float height){
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

jeHitBox::~jeHitBox(){
	//dtor
}

bool jeHitBox::collideBox(jeHitBox* m1, jeHitBox* m2, float x, float y, bool sweep, float width, float height){
	//Set our box's width and x according to
	m1->width += std::abs(width);
	if (width < 0) m1->x += width;
	m1->height += std::abs(height);
	if (height < 0) m1->y += height;
	//r is our return value.
	bool r = !sweep;
	if (sweep){
		//Sweeping, in short, just means that the rectangle moves.
		//left and right.
		if(x != 0){
			if (jeHitBox::collideBox(m1,m2,0,0,false,x,0)){
				r = true;
				m1->x = m2->x + ((x > 0) ? -m2->width : m2->width);
			}else{
				m1->x += x;
			}
		}
		//up and down
		if (y != 0){
			if(jeHitBox::collideBox(m1,m2,0,0,false,0,y)){
				r = true;
				m1->y = m2->y + ((y > 0) ? -m2->height : m2->height);
			}else{
				m1->y += y;
			}
		}
	}else{
		if(m1->bottom()+y <= m2->top()
		or m1->top()   +y >= m2->bottom()
		or m1->right() +x <= m2->left()
		or m1->left()  +x >= m2->right())
		{r = false;}
	}
	//Now reset the width and height
	m1->width -= std::abs(width);
	if (width < 0) m1->x -= width;
	m1->height -= std::abs(height);
	if (height < 0) m1->y -= height;
	//and return
	return r;
}

float jeHitBox::left(){return x;}
float jeHitBox::right(){return x + width;}
float jeHitBox::top(){return y;}
float jeHitBox::bottom(){return y+height;}
