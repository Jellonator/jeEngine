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

void Entity::OnUpdate(Group& group, float dt){
	for (auto& component : this->_component_update_list){
		this->_component_map[component]->update(*this, group, dt);
	}
}

void Entity::OnDraw(){
	for (auto& component : this->_component_update_list){
		this->_component_map[component]->draw(*this);
	}
}

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

void Entity::addUpdateComponent(const std::string& name){
	this->_component_update_list.push_back(name);
}

void Entity::addDrawComponent(const std::string& name){
	this->_component_draw_list.push_back(name);
}

void Entity::removeUpdateComponent(const std::string& name){
	this->_component_update_list.remove(name);
}

void Entity::removeDrawComponent(const std::string& name){
	this->_component_draw_list.remove(name);
}

void Entity::removeComponent(const std::string& name){
	std::map<std::string, std::shared_ptr<Component>>::iterator component_position = this->_component_map.find(name);
	if (component_position != this->_component_map.end()){
		this->_component_map.erase(component_position);
	}
}

bool Entity::isComponentEnabled(const std::string& name) const{
	if (!this->hasComponent(name)) return false;
	return this->_component_map.at(name)->isEnabled();
}

void Entity::enableComponent(const std::string& name){
	if (!this->hasComponent(name)) return;
	this->_component_map[name]->enable();
}

void Entity::disableComponent(const std::string& name){
	if (!this->hasComponent(name)) return;
	this->_component_map[name]->disable();
}

};
