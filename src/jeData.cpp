#include "jeData.h"
namespace JE{
Data::Data(void* owner){
	this->owner = owner;
	this->independent = (owner == NULL);
}

Data::~Data(){
	//dtor
}

bool Data::kill(void* killer){
	if (killer == this->owner) {delete this;return true;}
	return false;
}

void Data::setOwner(void* owner){
	this->owner = owner;
}
};
