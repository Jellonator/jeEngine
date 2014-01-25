#include "jeData.h"

jeData::jeData(void* owner){
	this->owner = owner;
	this->independent = (owner == NULL);
}

jeData::~jeData(){
	//dtor
}

bool jeData::getKill(void* killer){
	if (killer == this->owner) return true;
	return false;
}
