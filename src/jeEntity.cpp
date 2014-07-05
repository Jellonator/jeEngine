#include "jeEntity.h"
#include "JE.h"
namespace JE{
Entity::Entity(float x, float y) : JE::Point(x, y){
	this->mask = NULL;
	this->OnCreate();
}

Entity::~Entity(){
	//std::cout << "Entity delete" << std::endl;
	if(this->mask != NULL) {delete this->mask;this->mask = NULL;}
	//std::cout << "Entity delete" << std::endl;
}

void Entity::OnCreate(){};

void Entity::OnAdd(Group* group){};

void Entity::OnUpdate(){};

void Entity::OnDraw(){};

void Entity::OnRemove(Group* group){};

void Entity::destroy(){
	//tell the entity it is being removed
	this->OnRemove();
	//remove it from all groups
	//int j = 0;
	while (this->__GROUPS__.size() > 0){
		__GROUPS__[0]->remove(this);
	}
	//and delete
	delete this;
}
};
