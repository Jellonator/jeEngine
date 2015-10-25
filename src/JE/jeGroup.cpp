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
	for (std::unique_ptr<Entity>& entity : this->entities){
		entity->OnUpdate(*this, dt);
	}
}

void Group::draw(){
	this->updateEntities();
	for (std::unique_ptr<Entity>& entity : this->entities){
		entity->OnDraw();
	}
}

void Group::remove(const Entity& entity){
	std::vector<std::unique_ptr<Entity>>::iterator iter = this->entities.begin();
	while (iter != this->entities.end()){
		//dereference iterator -> dereference unique_ptr -> pointer
		if (&**iter == &entity) this->remove(iter);
		++iter;
	}
}

void Group::remove(std::vector<std::unique_ptr<Entity>>::iterator index){
	this->entities_remove.push_back(index);
}

bool sortEntity(const std::unique_ptr<Entity>& a, const std::unique_ptr<Entity>& b) { return a->layer < b->layer; }
void Group::updateEntities(){
	for (std::vector<std::unique_ptr<Entity>>::size_type i = 0; i != this->entities_add.size(); ++i){
		this->entities.emplace_back();
		std::swap(this->entities.back(), this->entities_add.at(i));
	}
	this->entities_add.clear();
	
	//long type definition. Would use auto, but the verboseness is probably better
	for (std::vector<std::vector<std::unique_ptr<Entity>>::iterator>::size_type i = 0; i != this->entities_remove.size(); ++i){
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

unsigned int Group::size() const{
	return this->entities.size();
}

bool Group::getSort() const{
	return this->do_sort;
}

bool Group::getCorrectRemove() const{
	return this->correct_remove;
}

Entity& Group::getEntity(std::vector<std::unique_ptr<Entity>>::size_type value){
	return *this->entities.at(value);
}

Entity& Group::operator[](std::vector<std::unique_ptr<Entity>>::size_type value){
	return *this->entities.at(value);
}

const Entity& Group::getEntity(std::vector<std::unique_ptr<Entity>>::size_type value) const{
	return *this->entities.at(value);
}

const Entity& Group::operator[](std::vector<std::unique_ptr<Entity>>::size_type value) const{
	return *this->entities.at(value);
}

}