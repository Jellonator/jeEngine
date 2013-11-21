#include "JE.h"

jeGroup::jeGroup(int order, jeWorld* world){
	this->order = order;
	this->parent = world;
	this->inWorld = true;
	this->__PINDEX__ = -1;
	//jeAddGroup(this);
}

jeGroup::~jeGroup(){
	//dtor
}

void jeGroup::begin(){jeAddGroup(this);};

void jeGroup::update(int group){
	for (unsigned int i = 0; i < entities.size(); i ++){
		entities[i]->OnUpdate();
	}
};

void jeGroup::draw(int group){
	for (unsigned int i = 0; i < entities.size(); i ++){
		entities[i]->OnDraw();
	}
};

void jeGroup::end(){jeRemoveGroup(this);};

void jeGroup::add(jeEntity* entity){
	//Function that adds an entity.
	if (this->__IREMOVED__.size() > 0){//If there is free space
		//Set the entity's index
		entity->__INDEXES__[this->__INDEX__] = this->__IREMOVED__.back();
		//Add it to the empty spot
		this->entities[this->__IREMOVED__.back()] = entity;
		//Clean up the removal vectors
		this->__EREMOVED__[this->__IREMOVED__.back()] = false;
		this->__IREMOVED__.pop_back();
	}else{//otherwise make room
		entity->__INDEXES__[this->__INDEX__] = this->entities.size();
		//And push it to the back
		this->entities.push_back(entity);
		this->__EREMOVED__.push_back(false);
	}
	//entity->__GROUPS__[this->__INDEX__] = this;
	entity->__GCOUNT__ ++;
	//Tell the entity is was added
	//entity->add();
}

void jeGroup::remove(jeEntity* entity){
	if (this->order == JE_ORDER_FULL){
		this->entities.erase(this->entities.begin() + entity->__INDEXES__[this->__INDEX__]);
		for (unsigned int i = entity->__INDEXES__[this->__INDEX__]; i < this->entities.size(); i ++){
			if(this->__EREMOVED__[i] == false) this->entities[i]->__INDEXES__[this->__INDEX__] --;
		}
	}
	if (this->order == JE_ORDER_HALF){
	//If there is a half order
		//Tell the world that entity is long gone
		this->__EREMOVED__[entity->__INDEXES__[this->__INDEX__]] = true;
		this->__IREMOVED__.push_back(entity->__INDEXES__[this->__INDEX__]);
	}
	if (this->order == JE_ORDER_NONE){
	//If there is not an order
		//Just pop it, and place the entity at the back to it's position

		this->entities[entity->__INDEXES__[this->__INDEX__]] = this->entities[this->entities.size()-1];
		this->entities[entity->__INDEXES__[this->__INDEX__]]->__INDEXES__[this->__INDEX__] = entity->__INDEXES__[this->__INDEX__];
		this->entities.pop_back();
	}
	entity->__GCOUNT__ --;
	if (entity->__GCOUNT__ <= 0) delete entity;
	this->needOrder = true;
}

void jeGroup::changeOrder( int order){

	if (this->order == JE_ORDER_FULL && this->needOrder){
		//Check again.
		if (this->__IREMOVED__.size() > 0){
			//Loop through all of the missing entities
			for (unsigned int i = 0; i < this->__IREMOVED__.size(); i ++){
				//loop through all entities past this point and decrease their index
				for (unsigned int j = this->__IREMOVED__[i]+1; j < this->entities.size(); j ++){
					if (this->__EREMOVED__[j] == false) this->entities[j]->__INDEXES__[this->__INDEX__] --;
				}
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

