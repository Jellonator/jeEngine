#include "jeData.h"
namespace JE{
Data::Data(void* owner){
	this->owner = owner;
	this->independent = (owner == NULL);
}

Data::~Data(){
	//dtor
}

bool Data::getKill(void* killer){
	if (killer == this->owner) return true;
	return false;
}
};
