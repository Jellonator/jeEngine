#include "JE.h"
namespace JE{
Group::Group(int order, int drawmode, int updatemode){
	this->order = order;
	this->drawMode = drawmode;
	this->updateMode = updatemode;
}

Group::~Group(){
	//dtor
}

void Group::begin(){};

void Group::update(int group){
	if (this->updateMode == JE_WORLD_MODE_ALL && group < 0){
		for (unsigned int i = 0; i < this->entities.size(); i ++){
			if (this->__EREMOVED__[i] == false) this->entities[i]->OnUpdate();
		}
	} else if (this->updateMode == JE_WORLD_MODE_GROUP || group >= 0){
	//Update by group.
		if (group < 0){
			//update them all
			for (unsigned int i = 0; i < this->groups.size(); i ++){
				this->groups[i]->update();
			}
		}else{
			//update only one
			this->groups[group]->update();
		}
	}
};

void Group::draw(int group){
	if (this->drawMode == JE_WORLD_MODE_ALL){
		for (unsigned int i = 0; i < this->entities.size(); i ++){
			if (this->__EREMOVED__[i] == false) this->entities[i]->OnDraw();
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

void Group::add(Entity* entity){
	//Function that adds an entity.
	if (this->__IREMOVED__.size() > 0){//If there is free space
		//Add it to the empty spot
		this->entities[this->__IREMOVED__.back()] = entity;
		//Clean up the removal vectors
		this->__EREMOVED__[this->__IREMOVED__.back()] = false;
		this->__IREMOVED__.pop_back();
	}else{
		//And push it to the back
		this->entities.push_back(entity);
		this->__EREMOVED__.push_back(false);
	}
	entity->__GROUPS__.push_back(this);
	//Tell the entity is was added
	entity->OnAdd(this);
}

void Group::remove(Entity* entity){
	entity->OnRemove(this);
	//If full order then 'erase' it
	if (this->order == JE_ORDER_FULL){
		unsigned int j = this->entities.size();
		for (unsigned int i = 0; i < j; i ++){
			if (entity == this->entities[i]) {
				this->entities.erase(this->entities.begin()+i);
				j --;
				i --;
			}
		}
	}
	else if (this->order == JE_ORDER_HALF){
	//If there is a half order
	//then remove it, leaving behind a hole for other entities
		for (unsigned int i = 0; i < this->entities.size(); i ++){
			if (entity == this->entities[i]) {
				this->__EREMOVED__[i] = true;
				this->__IREMOVED__.push_back(i);
			}
		}
	}
	else{
	//If there is not an order
		//Just pop it, and place the entity at the back to it's position
		for (unsigned int i = 0; i < this->entities.size(); i ++){
			if (entity == this->entities[i]) {
				if (i < this->entities.size()) this->entities[i] = this->entities[this->entities.size()-1];
				this->entities.pop_back();
				i = 0;
			}
		}
	}
	//now remove it from all groups
	/// TODO: Remove from world's groups, not the entity's.
	unsigned int j = entity->__GROUPS__.size();
	for (unsigned int i = 0; i < j; i ++){
		if (entity->__GROUPS__[i] == this){
			entity->__GROUPS__.erase(entity->__GROUPS__.begin()+i);
			i--;
			j--;
		}
	}
	this->needOrder = true;
}

void Group::clear(){
	this->entities.clear();
	this->__EREMOVED__.clear();
	this->__IREMOVED__.clear();
	this->needOrder = false;
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

int Group::getID(Entity* entity){
	for (unsigned int i = 0; i < this->entities.size(); ++i){
		if (this->entities[i] == entity) return i;
	}
	return -1;
}
void Group::move(int from, int to){
	if (from == -1) return;
	Entity* e = this->entities[from];
	this->entities.erase(this->entities.begin()+from);
	this->entities.insert(this->entities.begin()+to, e);
}
void Group::moveToBack(int from){
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
}

void Group::changeOrder( int order){

	if (this->order == JE_ORDER_FULL && this->needOrder){
		//Check again.
		if (this->__IREMOVED__.size() > 0){
			//Loop through all of the missing entities
			for (unsigned int i = 0; i < this->__IREMOVED__.size(); i ++){
				//erase that entity
				this->entities.erase(this->entities.begin()+this->__IREMOVED__[i]);
				//and mark is as existent
				this->__EREMOVED__[i] = false;
			}
			//finalize, make sure to keep those arrays clean, boys!
			this->__EREMOVED__.resize(this->entities.size(), false);
			this->__IREMOVED__.clear();
		}
		//remove the need for order.
		this->needOrder = false;
	}

	this->order = order;
}

void Group::addToGroup(Entity* entity, unsigned int group){
	//Test if group exists, if not then resize
	if (this->groups.size() < group+1) addGroup(group);
	//Then add to the group
	this->groups[group]->add(entity);
}

void Group::removeFromGroup(Entity* entity, unsigned int group){
	this->groups[group]->remove(entity);
}

void Group::addGroup(unsigned int group, int order, int drawmode, int updatemode){
	//Adds a group
	//If an order is unspecified, default to the world's order.
	if (order < 0) order = this->order;
	if (drawmode < 0) drawmode = this->drawMode;
	if (updatemode < 0) updatemode = this->updateMode;
	//Now calculate the difference in size before and after resizing
	int a = this->groups.size();
	this->groups.resize(std::max((unsigned int)this->groups.size(), group+1));
	//And fill up all of the new groups pointers with new groups
	for (unsigned int i = a; i < this->groups.size(); i ++){
		this->groups[i] = new Group(this->order, drawmode, updatemode);
		//this->groups[i]->__PINDEX__ = a;
		this->groups[i]->begin();
	}
}

Group* Group::getGroup(unsigned int index){
	if (this->groups.size() < index+1) addGroup(index);
	return groups[index];
}

void Group::removeGroup(unsigned int group){
	delete this->groups[group];
	this->groups.erase(this->groups.begin()+group);
	//RemoveGroup(this->groups[group]);
}

void Group::swap(int a, int b){
	if (a == -1 || b == -1) return;
	Entity* temp = this->entities[a];
	this->entities[a] = this->entities[b];
	this->entities[b] = temp;
}

Entity* Group::operator[](unsigned int value){
	return this->entities[value];
}
};
