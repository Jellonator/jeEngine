#include "JE/jeGroup.h"
#include "JE/jeEntity.h"
#include <algorithm>
#include <iostream>
namespace JE{
Group::Group(int drawmode, int updatemode) : groups(), entities(){
	//this->order = order;
	this->drawMode = drawmode;
	this->updateMode = updatemode;
	this->needUpdateEntityLayering = false;
	this->do_sort = true;
	this->correct_remove = true;
}

Group::~Group(){
	//this->deleteAll();
}

void Group::begin(){};
bool sortEntity(std::shared_ptr<Entity>a, std::shared_ptr<Entity>b) { return a->layer < b->layer; }
void Group::updateEntities(){
	// Add added entities
	for (auto e : this->entities_add){
		this->_add(e);
	}
	this->entities_add.clear();
	// Remove removed entities
	for (auto e : this->entities_remove){
		this->_remove(e);
	}
	this->entities_remove.clear();
	// Update entities in groups
	for (auto g : this->groups){
		g->updateEntities();
	}
}
void Group::update(float dt, int group){
	this->updateEntities();
	// Re-layer entities if needed
	if (this->needUpdateEntityLayering){
		if (this->do_sort) std::sort(this->entities.begin(), this->entities.end(), sortEntity);
		this->needUpdateEntityLayering = false;
		//std::cout << "Sorting group" << std::endl;
	}
	
	// Update
	if (this->updateMode == JE_WORLD_MODE_ALL && group < 0){
		for (unsigned int i = 0; i < this->entities.size(); i ++){
			if (this->entities[i] == NULL) continue;
			this->entities[i]->OnUpdate(dt);
		}
	} else if (this->updateMode == JE_WORLD_MODE_GROUP || group >= 0){
		//Update by group.
		if (group < 0){
			//update them all
			for (unsigned int i = 0; i < this->groups.size(); i ++){
				this->groups[i]->update(dt);
			}
		}else{
			//update only one
			this->groups[group]->update(dt);
		}
	}
};

void Group::draw(int group){
	if (this->needUpdateEntityLayering){
		if (this->do_sort) std::sort(this->entities.begin(), this->entities.end(), sortEntity);
		this->needUpdateEntityLayering = false;
		//std::cout << "Sorting group" << std::endl;
	}
	if (this->drawMode == JE_WORLD_MODE_ALL){
		for (unsigned int i = 0; i < this->entities.size(); i ++){
			this->entities[i]->OnDraw();
		}
	} else if (this->drawMode == JE_WORLD_MODE_GROUP){
		if (group < 0){
			for (unsigned int i = 0; i < this->groups.size(); i ++){
				this->groups[i]->draw();
			}
		}else{
			this->groups[group]->draw();
		}
	}
};

void Group::end(){};

void Group::add(std::shared_ptr<Entity> entity){
	this->entities_add.push_back(entity);
}
void Group::_add(std::shared_ptr<Entity> entity){
	if (entity == nullptr) return;
	//Function that adds an entity.
	this->entities.push_back(entity);
	std::weak_ptr<JE::Group> weak = shared_from_this();
	entity->__GROUPS__.push_back(weak);
	//Tell the entity is was added
	entity->OnAdd(*this);
	this->needUpdateEntityLayering = true;
}

void Group::remove(std::shared_ptr<Entity> entity){
	this->entities_remove.push_back(entity);
}
void Group::_remove(std::shared_ptr<Entity> entity){
	entity->OnRemove(*this);
	unsigned int i = 0;
	while (i < this->entities.size()){
		if (entity == this->entities[i]) {
			if (this->correct_remove){
				this->entities.erase(this->entities.begin()+i);
			}else{
				if (i < this->entities.size()-1) {
					this->entities[i] = this->entities.back();
				}
				this->entities.pop_back();
			}
		}else ++ i;
	}
	//if entities.erase() isn't used to remove entities, then sort entities.
	this->needUpdateEntityLayering = this->needUpdateEntityLayering || !this->correct_remove;
}

void Group::enableSort(){
	this->do_sort = true;
}

void Group::disableSort(){
	this->do_sort = false;
}

void Group::clear(){
	this->entities.clear();
	for (auto group : this->groups){
		group->clear();
	}
}

void Group::clear(int group){
	this->groups[group]->clear();
}

void Group::clearAll(){
	for (unsigned int i = 0; i < this->groups.size(); ++i){
		this->groups[i]->clearAll();
	}
	this->clear();
}

int Group::getID(std::shared_ptr<Entity> entity){
	for (unsigned int i = 0; i < this->entities.size(); ++i){
		if (this->entities[i] == entity) return i;
	}
	return -1;
}
/*void Group::move(int from, int to){
	if (from == to) return;
	if (from == -1) return;
	std::shared_ptr<Entity> e = this->entities[from];
	this->entities.erase(this->entities.begin()+from);
	this->entities.insert(this->entities.begin()+to, e);
}
void Group::moveToBack(int from){
	if (from == this->entities.size()-1) return;
	if (from == -1) return;
	Entity* e = this->entities[from];
	this->entities.erase(this->entities.begin()+from);
	this->entities.push_back(e);
}
void Group::moveToFront(int from){
	this->move(from, 0);
}
void Group::moveUp(int from){
	if (from >= this->entities.size()-1) return;
	this->move(from, from+1);
}
void Group::moveDown(int from){
	if (from <= 0) return;
	this->move(from, from-1);
}*/

void Group::addToGroup(std::shared_ptr<Entity> entity, unsigned int group){
	//Test if group exists, if not then resize
	if (this->groups.size() < group+1) addGroup(group);
	//Then add to the group
	this->groups[group]->add(entity);
}

void Group::removeFromGroup(std::shared_ptr<Entity> entity, unsigned int group){
	if (this->groups.size() < group+1) return;
	this->groups[group]->remove(entity);
}

void Group::addGroup(unsigned int group, int drawmode, int updatemode){
	//Adds a group
	//If an order is unspecified, default to the world's order.
	if (drawmode < 0) drawmode = JE_WORLD_MODE_ALL;
	if (updatemode < 0) updatemode = JE_WORLD_MODE_ALL;
	//Now calculate the difference in size before and after resizing
	//int a = this->groups.size();
	this->groups.resize(std::max((unsigned int)this->groups.size(), group+1), std::shared_ptr<Group>(new Group(drawmode, updatemode)));
	//And fill up all of the new groups pointers with new groups
	auto g = this->getGroup(group);
	g->drawMode = drawmode;
	g->updateMode = updatemode;
}

std::shared_ptr<Group> Group::getGroup(unsigned int index){
	if (this->groups.size() < index+1) addGroup(index);
	return this->groups[index];
}

const std::shared_ptr<Group>& Group::getGroupConst(unsigned int index){
	if (this->groups.size() < index+1) addGroup(index);
	return this->groups[index];
}

void Group::removeGroup(unsigned int group){
	//delete this->groups[group];
	this->groups.erase(this->groups.begin()+group);
	//RemoveGroup(this->groups[group]);
}

/*void Group::swap(int a, int b){
	if (a == -1 || b == -1) return;
	Entity* temp = this->entities[a];
	this->entities[a] = this->entities[b];
	this->entities[b] = temp;
}*/

void Group::deleteAll(){
	this->clearAll();
}

std::shared_ptr<Entity> Group::operator[](unsigned int value){
	return this->entities[value];
}

std::shared_ptr<Entity> Group::getEntity(unsigned int value){
	return this->entities[value];
}

const std::shared_ptr<Entity>& Group::getEntityConst(unsigned int value){
	return this->entities[value];
}

unsigned int Group::size(){
	return this->entities.size();
}
};
