#include "JE/jeWorld.h"
#include "JE/jeEntity.h"
namespace JE{
std::shared_ptr<World> world;/**< \brief jeWorld* world, the active world. */
World::World(int drawmode, int updatemode) : Group(drawmode, updatemode){
	//this->order = order;
	//this->needOrder = false;
}

World::~World(){
	//dtor
}
void World::begin(){Group::begin();this->OnBegin();}
void World::end(){this->OnEnd();Group::end();}

void World::update(float dt, int group){
	//Update all of the entities
	if (group < 0){
		this->OnUpdate(dt);
	} else Group::update(dt, group);
};

void World::draw(int group){
	//same as the update function
	if (group < 0){
		this->OnDraw();
	} else Group::update(group);
}
void setWorld(std::shared_ptr<World> world){
	if(JE::world != nullptr) JE::world->end();
	JE::world = world;
	JE::world->begin();
	JE::GRAPHICS::resize();
}
void World::OnUpdate(float dt){
	Group::update(dt);
}
void World::OnDraw(){
	Group::draw();
}
void World::OnBegin(){

}
void World::OnEnd(){

}
void World::add(std::shared_ptr<Entity> entity){
	Group::add(entity);
	entity->OnAdd(this);
}
void World::remove(std::shared_ptr<Entity> entity){
	Group::remove(entity);
	entity->OnRemove(this);
}
};
