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

void jeWorld::begin(){jeAddGroup(this);this->OnBegin();}
void jeWorld::end(){jeRemoveGroup(this);}

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
	entity->__INDEXES__.resize(JE::groups.size(), -1);
	//entity->__GROUPS__.resize(JE::groups.size(), NULL);
	//entity->__INDEXES__.reserve(JE::groups.size());
	//std::cout << "foo2" << std::endl;
	//std::cout << entity->__INDEXES__.max_size() << std::endl;
	//Function that adds an entity.
	jeGroup::add(entity);
	//Tell the entity is was added
	entity->OnAdd();
}

void jeWorld::remove(jeEntity* entity){
	//Tell the entity that it is being removed
	entity->OnRemove();
	//entity->__GROUPS__.resize(JE::groups.size(), NULL);
	entity->__INDEXES__.resize(JE::groups.size(), -1);
	for (unsigned int i = 0; i < entity->__INDEXES__.size(); i ++){
		if (entity->__INDEXES__[i] >= 0) jeWorld::removeFromGroup(entity, i);
	}
	jeGroup::remove(entity);
}

void jeWorld::addGroup(unsigned int group, int order){
	//Adds a group
	//If an order is unspecified, default to the world's order.
	if (order < 0) order = this->order;
	//Now calculate the difference in size before and after resizing
	int a = this->groups.size();
	this->groups.resize(std::max((unsigned int)this->groups.size(), group+1));
	//And fill up all of the new groups pointers with new groups
	for (unsigned int i = a; i < this->groups.size(); i ++){
		this->groups[i] = new jeGroup(this->order, this);
		this->groups[i]->__PINDEX__ = a;
		this->groups[i]->begin();
	}
}

void jeWorld::addToGroup(jeEntity* entity, unsigned int group){
	//Test if group exists, if not then resize
	if (this->groups.size() < group+1) addGroup(group);
	//Add the entity to the world if it's not already there.
	if (entity->__INDEXES__[this->__INDEX__] < 0) jeWorld::add(entity);
	//Then add to the group
	this->groups[group]->add(entity);
}

void jeWorld::removeFromGroup(jeEntity* entity, unsigned int group){
	this->groups[group]->remove(entity);
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

void jeWorld::removeGroup(unsigned int group){
	this->groups.erase(this->groups.begin()+group);
	jeRemoveGroup(this->groups[group]);
}
