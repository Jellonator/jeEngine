#include "JE/jeEntity.h"
#include "JE/jeGroup.h"
#include "JE/UTIL/jeMath.h"

namespace JE{

Entity::Entity() : JE::Point(){
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

JE::MASK::Mask& Entity::getMask(){
	return *this->_mask_ptr;
}

};
