#include "JE/jeComponent.h"
#include "JE/jeEntity.h"

namespace JE{

Component::Component(){
	this->_is_enabled = true;
}

Component::~Component(){
	
}

void Component::call(JE::Entity& entity){
	if (this->_is_enabled) this->OnCall(entity);
}

void Component::update(JE::Entity& entity, JE::Group& group, float dt){
	if (this->_is_enabled) this->OnUpdate(entity, group, dt);
}

void Component::draw(JE::Entity& entity){
	if (this->_is_enabled) this->OnDraw(entity);
}

void Component::OnCall(JE::Entity& entity){}

void Component::OnUpdate(JE::Entity& entity, JE::Group& group, float dt){}

void Component::OnDraw(JE::Entity& entity){}

void Component::enable(){
	this->_is_enabled = true;
}

void Component::disable(){
	this->_is_enabled = false;
}

bool Component::isEnabled() const{
	return this->_is_enabled;
}

}