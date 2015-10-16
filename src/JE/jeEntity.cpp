#include "JE/jeEntity.h"
#include "JE/jeGroup.h"
#include "JE/jeWorld.h"
#include "JE/UTIL/jeMath.h"
namespace JE{
Entity::Entity(float x, float y) : JE::Point(x, y){
	this->layer = 0;
	this->OnCreate();
}

Entity::~Entity(){
	//std::cout << "Entity delete" << std::endl;
	//if(this->mask != NULL) {delete this->mask;this->mask = NULL;}
	//std::cout << "Entity delete" << std::endl;
}

void Entity::OnCreate(){};

void Entity::OnAdd(Group* group){};
void Entity::OnAdd(World* world){};

void Entity::OnUpdate(float dt){};

void Entity::OnDraw(){
};

void Entity::OnRemove(Group* group){};
void Entity::OnRemove(World* world){};

void Entity::destroy(){
	//tell the entity it is being removed
	for (unsigned int i = 0; i < this->__GROUPS__.size(); ++i){
		//if (group == nullptr) continue;
		if (this->__GROUPS__[i].expired()) continue;
		this->__GROUPS__[i].lock()->remove(shared_from_this());
	}
	this->__GROUPS__.clear();
}

void Entity::moveBy(float move_x, float move_y){
	this->x += move_x;
	this->y += move_y;
}
void Entity::moveTo(float move_x, float move_y, bool force){
	this->x = move_x;
	this->y = move_y;
}
};
