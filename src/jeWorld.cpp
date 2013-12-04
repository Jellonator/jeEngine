#include "jeWorld.h"

jeWorld::jeWorld(int order, int drawmode, int updatemode) : jeGroup(order, drawmode, updatemode){
	//this->order = order;
	this->needOrder = false;
}

jeWorld::~jeWorld(){
	//dtor
}
void jeWorld::begin(){this->OnBegin();}
void jeWorld::end(){this->onEnd();}

void jeWorld::update(int group){
	//Update all of the entities
	jeGroup::update(group);
	this->onUpdate();
};

void jeWorld::draw(int group){
	//same as the update function
	jeGroup::update(group);
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
