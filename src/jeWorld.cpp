#include "jeWorld.h"

jeWorld::jeWorld(int order, int drawmode, int updatemode){
	this->order = order;
	this->drawMode = drawmode;
	this->updateMode = updatemode;
	this->needOrder = false;
}

jeWorld::~jeWorld(){
	//dtor
}

void jeWorld::begin(jeWorld* world){world->OnBegin();};

void jeWorld::update(jeWorld* world, int group){
	//Update all of the entities
	if (world->updateMode == JE_WORLD_MODE_ALL){
		for (unsigned int i = 0; i < world->entities.size(); i ++){
			if (world->__EREMOVED__[i] == false) world->entities[i]->OnUpdate();
		}
	} else if (world->updateMode == JE_WORLD_MODE_GROUP){
	//Update by group.
		if (group < 0){
			//update them all
			for (unsigned int i = 0; i < world->groups.size(); i ++){
				world->groups[i]->update();
			}
		}else{
			//update only one
			world->groups[group]->update();
		}
	}
	world->onUpdate();
};

void jeWorld::draw(jeWorld* world, int group){
	//same as the update function
	if (world->drawMode == JE_WORLD_MODE_ALL){
		for (unsigned int i = 0; i < world->entities.size(); i ++){
			if (world->__EREMOVED__[i] == false) world->entities[i]->OnDraw();
		}
	} else if (world->drawMode == JE_WORLD_MODE_GROUP){
		if (group < 0){
			for (unsigned int i = 0; i < world->groups.size(); i ++){
				world->groups[i]->draw();
			}
		}else{
			world->groups[group]->draw();
		}
	}
	world->OnDraw();
};

void jeWorld::end(jeWorld* world){};

void jeWorld::add(jeWorld* world, jeEntity* entity){
	//Function that adds an entity.
	if (world->__IREMOVED__.size() > 0){
	//If there is free space
		//Set the entity's index
		entity->__INDEX__ = world->__IREMOVED__.back();
		//Add it to the empty spot
		world->entities[world->__IREMOVED__.back()] = entity;
		//Clean up the removal vectors
		world->__EREMOVED__[world->__IREMOVED__.back()] = false;
		world->__IREMOVED__.pop_back();
	}else{
	//Otherwise push it to the back
		//set the entity's index to the back
		entity->__INDEX__ = world->entities.size();
		//And push it to the back
		world->entities.push_back(entity);
		world->__EREMOVED__.push_back(false);
	}
	//Tell the entity is was added
	entity->OnAdd();
}

void jeWorld::remove(jeWorld* world, jeEntity* entity){
	//Tell the entity that it is being removed
	entity->OnRemove();
	for (unsigned int i = 0; i < entity->__GROUPS__.size(); i ++){
		if (entity->__GROUPS__[i] >= 0) jeGroup::remove(JE::world->groups[i], entity);
	}
	if (world->order == JE_ORDER_FULL){
		world->entities.erase(world->entities.begin() + entity->__INDEX__);
		for (unsigned int i = entity->__INDEX__; i < world->entities.size(); i ++){
			if(world->__EREMOVED__[i] == false) world->entities[i]->__INDEX__ --;
		}
	}
	if (world->order == JE_ORDER_HALF){
	//If there is a half order
		//Tell the world that entity is long gone
		world->__EREMOVED__[entity->__INDEX__] = true;
		world->__IREMOVED__.push_back(entity->__INDEX__);
	}
	if (world->order == JE_ORDER_NONE){
	//If there is not an order
		//Just pop it, and place the entity at the back to it's position
		world->entities[entity->__INDEX__] = world->entities[world->entities.size()-1];
		world->entities[entity->__INDEX__]->__INDEX__ = entity->__INDEX__;
		world->entities.pop_back();
	}
	delete entity;
	world->needOrder = true;
}

void jeWorld::addGroup(jeWorld* world, unsigned int group, int order){
	//Adds a group
	//Add the entity to the world if it's not already there.
	if (entity->__INDEX__ < 0) jeWorld::add(entity);
	//If an order is unspecified, default to the world's order.
	if (order < 0) order = world->order;
	//Now calculate the difference in size before and after resizing
	int a = world->groups.size();
	world->groups.resize(std::max((unsigned int)world->groups.size(), group+1));
	//And fill up all of the new groups pointers with new groups
	for (unsigned int i = a; i < world->groups.size(); i ++){
		world->groups[i] = new jeGroup(world->order, world);
		world->groups[i]->__INDEX__ = a;
	}
	//Just incase(probably tired).
	if(world->groups[group] == NULL) world->groups[group] = new jeGroup(order, world);
	//And set his Index(still tired).
	world->groups[group]->__INDEX__ = group;
}

void jeWorld::addToGroup(jeWorld* world, jeEntity* entity, unsigned int group){
	//Test if group exists, if not then resize
	if (world->groups.size() < group+1) addGroup(group);
	jeGroup::add(world->groups[group], entity);
}

void jeWorld::removeFromGroup(jeWorld* world, jeEntity* entity, unsigned int group){
	jeGroup::remove(world->groups[group], entity);
}

void jeWorld::set(jeWorld* world){
	jeWorld::end();
	JE::world = world;
	jeWorld::begin();
}

void jeWorld::changeOrder(jeWorld* world, int order){

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
				world->entities.erase(world->entities.begin()+world->__IREMOVED__[i]);
				//and mark is as existent
				world->__EREMOVED__[i] = false;
			}
			//finalize, make sure to keep those arrays clean, boys!
			world->__EREMOVED__.resize(world->entities.size(), false);
			world->__IREMOVED__.clear();
		}
		//remove the need for order.
		world->needOrder = false;
	}

	world->order = order;
}
