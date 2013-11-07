#include "jeEntity.h"
//Not commenting this file, should be easy enough to understand
jeEntity::jeEntity()
{
	x = 0;
	y = 0;
	this->create();
}

jeEntity::~jeEntity()
{
	//dtor
}

void jeEntity::create(){};

void jeEntity::add(){};

void jeEntity::update(){};

void jeEntity::draw(){};

void jeEntity::remove(){};
