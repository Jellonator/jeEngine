#include "jeWorld.h"
namespace JE{
World::World(int order, int drawmode, int updatemode) : Group(order, drawmode, updatemode){
	//this->order = order;
	this->needOrder = false;
}

World::~World(){
	//dtor
}
void World::begin(){this->OnBegin();Group::begin();}
void World::end(){this->onEnd();Group::end();}

void World::update(int group){
	//Update all of the entities
	Group::update(group);
	this->onUpdate();
};

void World::draw(int group){
	//same as the update function
	Group::draw(group);
	this->OnDraw();
}

void setWorld(World* world){
	if(JE::world != NULL) JE::world->end();
	JE::world = world;
	JE::world->begin();
}
};
