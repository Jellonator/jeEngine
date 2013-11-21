#include "jeEntity.h"
//Not commenting this file, should be easy enough to understand
jeEntity::jeEntity()
{
	x = 0;
	y = 0;
	this->OnCreate();
}

jeEntity::~jeEntity()
{
	//dtor
}

void jeEntity::OnCreate(){};

void jeEntity::OnAdd(){};

void jeEntity::OnUpdate(){};

void jeEntity::OnDraw(){};

void jeEntity::OnRemove(){};
