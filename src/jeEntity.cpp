#include "jeEntity.h"
namespace JE{
Entity::Entity()
{
	x = 0;
	y = 0;
	this->mask = NULL;
	this->OnCreate();
}

Entity::~Entity()
{
	if(this->mask != NULL) delete this->mask;
}

void Entity::OnCreate(){};

void Entity::OnAdd(World* world){};

void Entity::OnUpdate(){};

void Entity::OnDraw(){};

void Entity::OnRemove(World* world){};

void Entity::destroy(){
	//tell the entity it is being removed
	this->OnRemove();
	//remove it from all groups
	int j = __GROUPS__.size();
	while (j > 0){
		__GROUPS__[0]->remove(this);
		j = __GROUPS__.size();
	}
	//and delete
	delete this;
}
};
