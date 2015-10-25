#include "JE/jeEntity.h"
#include "JE/jeGroup.h"
#include "JE/UTIL/jeMath.h"

namespace JE{

Entity::Entity(float x, float y) : JE::Point(x, y){
	this->layer = 0;
	this->OnCreate();
}

Entity::~Entity(){
	//std::cout << "Entity delete" << std::endl;
	//if(this->mask != NULL) {delete this->mask;this->mask = NULL;}
	//std::cout << "Entity delete" << std::endl;
}

void Entity::OnCreate(){}

void Entity::OnAdd(Group& group){}

void Entity::OnUpdate(Group& group, float dt){}

void Entity::OnDraw(){}

void Entity::OnRemove(Group& group){}

void Entity::moveBy(float move_x, float move_y){
	this->x += move_x;
	this->y += move_y;
}

void Entity::moveTo(float move_x, float move_y, bool force){
	this->x = move_x;
	this->y = move_y;
}

};
