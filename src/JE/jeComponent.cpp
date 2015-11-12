#include "JE/jeComponent.h"
#include "JE/jeEntity.h"

namespace JE{

Component::Component(){
	
}

Component::~Component(){
	
}

void Component::call(JE::Entity& entity){
	this->OnCall(entity);
}

void Component::OnCall(JE::Entity& entity){
	
}

}