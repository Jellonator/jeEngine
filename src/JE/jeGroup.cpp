#include "JE/jeGroup.h"
#include "JE/jeEntity.h"
#include <algorithm>
#include <iostream>
namespace JE{

Group::Group(){
	this->needUpdateEntityLayering = false;
	this->do_sort = true;
	this->correct_remove = true;
}

Group::~Group(){
	//this->deleteAll();
}

void Group::update(float dt){
	this->updateEntities();
	for (entity_def& entity : this->entities){
		entity->OnUpdate(*this, dt);
	}
}

void Group::draw(){
	this->updateEntities();
	for (entity_def& entity : this->entities){
		entity->OnDraw();
	}
}

void Group::remove(const Entity& entity){
	entity_vec_iter iter = this->entities.begin();
	while (iter != this->entities.end()){
		//dereference iterator -> dereference unique_ptr -> pointer
		if (*iter == &entity) this->remove(iter);
		++iter;
	}
}

void Group::remove(entity_vec_iter index){
	this->entities_remove.push_back(index);
}

bool sortEntity(const entity_def& a, const entity_def& b) { 
	return a->layer < b->layer; 
}

void Group::updateEntities(){
	for (entity_vec_iter iter = this->entities_add.begin(); iter != this->entities_add.end(); ++iter){
		this->entities.push_back(*iter);
	}
	this->entities_add.clear();
	
	for (entity_vec::size_type i = 0; i != this->entities_remove.size(); ++i){
		Entity* entity = this->entities.at(i);
		for (std::vector<std::string>::iterator iter = entity->_groups_v.begin(); iter != entity->_groups_v.end(); ++iter){
			this->removeFromGroup(*iter, *entity);
		}
		delete entity;
		this->entities.erase(this->entities_remove.at(i));
	}
	this->entities_remove.clear();
	
	if (this->needUpdateEntityLayering && this->do_sort){
		std::sort(this->entities.begin(), this->entities.end(), sortEntity);
		this->needUpdateEntityLayering = false;
	}
}

void Group::clear(){
	this->entities.clear();
	this->entities_add.clear();
	this->entities_remove.clear();
}

void Group::setSort(bool sort){
	this->do_sort = sort;
}

void Group::setCorrectRemove(bool do_correct_remove){
	this->correct_remove = do_correct_remove;
}

entity_vec::size_type Group::getSize() const{
	return this->entities.size();
}

entity_vec::iterator Group::getBegin(){
	return this->entities.begin();
}

entity_vec::iterator Group::getEnd(){
	return this->entities.end();
}

bool Group::getSort() const{
	return this->do_sort;
}

bool Group::getCorrectRemove() const{
	return this->correct_remove;
}

Entity& Group::getEntity(entity_vec_size value){
	return *this->entities.at(value);
}

Entity& Group::operator[](entity_vec_size value){
	return *this->entities.at(value);
}

const Entity& Group::getEntity(entity_vec_size value) const{
	return *this->entities.at(value);
}

const Entity& Group::operator[](entity_vec_size value) const{
	return *this->entities.at(value);
}

void Group::addToGroup(const std::string& group, Entity& entity){
	this->entity_groups[group].push_back(&entity);
	entity._groups_v.push_back(group);
}

void Group::removeFromGroup(const std::string& group, Entity& entity){
	for (entity_vec::iterator iter = this->entity_groups[group].begin(); iter != this->entity_groups[group].end(); ++iter){
		if (*iter == &entity){
			iter = this->entity_groups[group].erase(iter);
		} else {
			++iter;
		}
	}
	
	for (std::vector<std::string>::iterator iter = entity._groups_v.begin(); iter != entity._groups_v.end(); ++iter){
		if (*iter == group){
			iter = entity._groups_v.erase(iter);
		} else {
			++iter;
		}
	}
}

entity_vec::iterator Group::getGroupBegin(const std::string& group){
	return this->entity_groups[group].begin();
}

entity_vec::iterator Group::getGroupEnd(const std::string& group){
	return this->entity_groups[group].end();
}

entity_vec::size_type Group::getGroupSize(const std::string& group){
	return this->entity_groups[group].size();
}

void Group::getCollideEntity(JE::Entity& entity, int move_x, int move_y, int* get_x, int* get_y){
	this->getCollideMask(entity.getMask(), move_x, move_y, get_x, get_y);
}

void Group::getCollideMask(JE::MASK::Mask& mask, int move_x, int move_y, int* get_x, int* get_y){
	
}

void Group::getCollideEntityGroup(JE::Entity& entity,  int move_x, int move_y, int* get_x, int* get_y, const std::string& group){
	this->getCollideMaskGroup(entity.getMask(), move_x, move_y, get_x, get_y, group);
}

void Group::getCollideMaskGroup(JE::MASK::Mask& mask,int move_x, int move_y, int* get_x, int* get_y, const std::string& group){
	
}

}