#pragma once

namespace JE{
	
class Entity;

class Component{
public:
	Component();
	virtual ~Component();
	void call(JE::Entity& entity);
	virtual void OnCall(JE::Entity& entity);
private:
	
};

}