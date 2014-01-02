#include "jeEntity.h"

jeEntity::jeEntity()
{
	x = 0;
	y = 0;
	this->mask = NULL;
	this->OnCreate();
}

jeEntity::~jeEntity()
{
	if(this->mask != NULL) delete this->mask;
}

void jeEntity::OnCreate(){};

void jeEntity::OnAdd(){};

void jeEntity::OnUpdate(){};

void jeEntity::OnDraw(){};

void jeEntity::OnRemove(){};

void jeEntity::destroy(){
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
