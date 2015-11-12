#include "JE/jeEntity.h"
#include "JE/jeGroup.h"
#include "JE/UTIL/jeMath.h"
#include "JE/jeComponent.h"

namespace JE{

Entity::Entity(){
	this->_layer = 0;
	this->_mask_ptr.reset(nullptr);
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

const JE::MASK::Mask* Entity::getMask() const{
	return this->_mask_ptr.get();
}

JE::MASK::Mask* Entity::getMask(){
	return this->_mask_ptr.get();
}

void Entity::setLayer(int value){
	this->_layer = value;
	if (this->_group) this->_group->needUpdateEntityLayering = true;
}

JE::Component* Entity::getComponent(const std::string& name){
	if (this->_component_map.count(name) == 0) return nullptr;
	return this->_component_map[name].get();
}

void Entity::callComponent(const std::string& name){
	if (this->hasComponent(name)){
		this->_component_map[name]->call(*this);
	}
}

bool Entity::hasComponent(const std::string& name) const{
	return (this->_component_map.count(name) > 0);
}

int Entity::getX() const{
	if (this->hasMask()) return this->getMask()->getX();
	else return 0;
}

int Entity::getY() const{
	if (this->hasMask()) return this->getMask()->getY();
	else return 0;
}

int Entity::getCenterX() const{
	if (this->hasMask()) return this->getMask()->getCenterX();
	else return 0;
}

int Entity::getCenterY() const{
	if (this->hasMask()) return this->getMask()->getCenterY();
	else return 0;
}

bool Entity::hasMask() const{
	return (this->_mask_ptr != nullptr);
}

};
