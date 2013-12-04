#include "jeWorld.h"

jeWorld::jeWorld(int order, int drawmode, int updatemode) : jeGroup(order){
	//this->order = order;
	this->drawMode = drawmode;
	this->updateMode = updatemode;
	this->needOrder = false;
}

jeWorld::~jeWorld(){
	//dtor
}
void jeWorld::begin(){this->OnBegin();}
void jeWorld::end(){}

void jeWorld::update(int group){
	//Update all of the entities
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
	this->onUpdate();
};

void jeWorld::draw(int group){
	//same as the update function
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
	this->OnDraw();
};

void jeWorld::add(jeEntity* entity){
	//Function that adds an entity.
	jeGroup::add(entity);
	//Tell the entity is was added
	entity->OnAdd();
}

void jeWorld::remove(jeEntity* entity){
	//Tell the entity that it is being removed
	entity->OnRemove();
	//entity->__GROUPS__.resize(JE::groups.size(), NULL);
	jeGroup::remove(entity);
}

void jeWorld::set(jeWorld* world){
	if(JE::world != NULL) JE::world->end();
	JE::world = world;
	JE::world->begin();
}

void jeWorld::changeOrder(int order){
	this->changeOrder(order);
	this->order = order;
}
