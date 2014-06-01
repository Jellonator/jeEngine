#include "jeWorld.h"
namespace JE{
World::World(int order, int drawmode, int updatemode) : Group(order, drawmode, updatemode){
	//this->order = order;
	this->needOrder = false;
}

World::~World(){
	//dtor
}
void World::begin(){this->OnBegin();}
void World::end(){this->onEnd();}

void World::update(int group){
	//Update all of the entities
	Group::update(group);
	this->onUpdate();
};

void World::draw(int group){
	//same as the update function
	Group::draw(group);
	this->OnDraw();
};

void World::add(Entity* entity){
	//Function that adds an entity.
	Group::add(entity);
	//Tell the entity is was added
	entity->OnAdd(this);
}

void World::remove(Entity* entity){
	//Tell the entity that it is being removed
	entity->OnRemove(this);
	//entity->__GROUPS__.resize(JE::groups.size(), NULL);
	Group::remove(entity);
}

void World::set(World* world){
	if(JE::world != NULL) JE::world->end();
	JE::world = world;
	JE::world->begin();
}

void World::changeOrder(int order){
	this->changeOrder(order);
	this->order = order;
}
};
