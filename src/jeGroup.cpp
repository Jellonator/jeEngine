#include "JE.h"

jeGroup::jeGroup(int order, int drawmode, int updatemode){
	this->order = order;
	this->drawMode = drawmode;
	this->updateMode = updatemode;
}

jeGroup::~jeGroup(){
	//dtor
}

void jeGroup::begin(){};
void jeGroup::update(int group){
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

void jeGroup::draw(int group){
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

void jeGroup::end(){};

void jeGroup::add(jeEntity* entity){
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
	//entity->add();
}

void jeGroup::remove(jeEntity* entity){
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
		//Tell the world that entity is long gon
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

void jeGroup::changeOrder( int order){

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

void jeGroup::addToGroup(jeEntity* entity, unsigned int group){
	//Test if group exists, if not then resize
	if (this->groups.size() < group+1) addGroup(group);
	//Then add to the group
	this->groups[group]->add(entity);
}

void jeGroup::removeFromGroup(jeEntity* entity, unsigned int group){
	this->groups[group]->remove(entity);
}

void jeGroup::addGroup(unsigned int group, int order, int drawmode, int updatemode){
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
		this->groups[i] = new jeGroup(this->order, drawmode, updatemode);
		//this->groups[i]->__PINDEX__ = a;
		this->groups[i]->begin();
	}
	//cout << this->groups[group] << endl;
}

jeGroup* jeGroup::getGroup(unsigned int index){
	if (this->groups.size() < index+1) addGroup(index);
	return groups[index];
}

void jeGroup::removeGroup(unsigned int group){
	this->groups.erase(this->groups.begin()+group);
	//jeRemoveGroup(this->groups[group]);
}

void jeGroup::clear(int level){
	if (level >= 2){
		int i = entities.size();
		while (i > 0){
			if (this->__EREMOVED__[0] == false) entities[0]->destroy();
			i = entities.size();
		}
	}
	if (level >= 1){
		for (unsigned int i = 0; i < groups.size(); i ++){
			groups[i]->clear(2);
			delete groups[i];
		}
	}
	if (level <= 1){
		for (unsigned int i = 0; i < entities.size(); i ++){
			if (this->__EREMOVED__[i] == false) entities[i]->OnRemove();
		}
		entities.clear();
	}
	entities.clear();
	__EREMOVED__.clear();
	__IREMOVED__.clear();
	needOrder = false;
}
