#include "jeGroup.h"

jeGroup::jeGroup(int order, jeWorld* world){
	this->order = order;
	this->world = world;
	this->inWorld = true;
}

jeGroup::~jeGroup(){
	//dtor
}

void jeGroup::begin(){};

void jeGroup::update(){
	/*if (order == JE_ORDER_FULL && needOrder){
		if (this->__IREMOVED__.size() > 0){
			for (unsigned int i = 0; i < __IREMOVED__.size(); i ++){
				entities.erase(entities.begin()+i);
				__EREMOVED__[i] = false;
			}
			__EREMOVED__.resize(entities.size(), false);
			__IREMOVED__.clear();
		}
	}*/
	for (unsigned int i = 0; i < entities.size(); i ++){
		if (this->world->__EREMOVED__[i] == false) entities[i]->update();
	}
};

void jeGroup::draw(){
	for (unsigned int i = 0; i < entities.size(); i ++){
		entities[i]->draw();
	}
};

void jeGroup::end(){};

void jeGroup::add(jeGroup* group, jeEntity* entity){
	//Function that adds an entity.
	entity->__GROUPS__.resize(group->world->groups.size(), -1);
	if (group->__IREMOVED__.size() > 0){
	//If there is free space
		//Set the entity's index
		entity->__GROUPS__[group->__INDEX__] = group->__IREMOVED__.back();
		//Add it to the empty spot
		group->entities[group->__IREMOVED__.back()] = entity;
		//Clean up the removal vectors
		group->__EREMOVED__[group->__IREMOVED__.back()] = false;
		group->__IREMOVED__.pop_back();
	}else{
	//Otherwise push it to the back
		//set the entity's index to the back
		entity->__GROUPS__[group->__INDEX__] = group->entities.size();
		//And push it to the back
		group->entities.push_back(entity);
		group->__EREMOVED__.push_back(false);
	}
	//Tell the entity is was added
	//entity->add();
}

void jeGroup::remove(jeGroup* group, jeEntity* entity){
	//Tell the entity that it is being removed
	if (group->order == JE_ORDER_FULL){
		group->entities.erase(group->entities.begin() + entity->__GROUPS__[group->__INDEX__]);
		for (unsigned int i = entity->__INDEX__; i < group->entities.size(); i ++){
			if(group->__EREMOVED__[i] == false) group->entities[i]->__GROUPS__[group->__INDEX__] --;
		}
	}
	if (group->order == JE_ORDER_HALF){
	//If there is a half order
		//Tell the world that entity is long gone
		group->__EREMOVED__[entity->__GROUPS__[group->__INDEX__]] = true;
		group->__IREMOVED__.push_back(entity->__GROUPS__[group->__INDEX__]);
	}
	if (group->order == JE_ORDER_NONE){
	//If there is not an order
		//Just pop it, and place the entity at the back to it's position
		group->entities[entity->__GROUPS__[group->__INDEX__]] = group->entities[group->entities.size()-1];
		group->entities[entity->__GROUPS__[group->__INDEX__]]->__INDEX__ = entity->__GROUPS__[group->__INDEX__];
		group->entities.pop_back();
	}

	group->needOrder = true;
}

void jeGroup::changeOrder(jeGroup* group, int order){

	if (world->order == JE_ORDER_FULL && world->needOrder){
		//Check again.
		if (world->__IREMOVED__.size() > 0){
			//Loop through all of the missing entities
			for (unsigned int i = 0; i < world->__IREMOVED__.size(); i ++){
				//loop through all entities past this point and decrease their index
				for (unsigned int j = world->__IREMOVED__[i]+1; j < world->entities.size(); j ++){
					if (world->__EREMOVED__[j] == false) world->entities[j]->__INDEX__ --;
				}
				//erase that entity
				group->entities.erase(world->entities.begin()+world->__IREMOVED__[i]);
				//and mark is as existent
				group->__EREMOVED__[i] = false;
			}
			//finalize, make sure to keep those arrays clean, boys!
			group->__EREMOVED__.resize(group->entities.size(), false);
			group->__IREMOVED__.clear();
		}
		//remove the need for order.
		group->needOrder = false;
	}

	group->order = order;
}
