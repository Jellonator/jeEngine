#pragma once

namespace JE{
	
class Entity;
class Group;

class Component{
public:
	Component();
	virtual ~Component();
	void update(JE::Entity& entity, JE::Group& group, float dt);
	void draw(JE::Entity& entity);
	void call(JE::Entity& entity);
	virtual void OnCall(JE::Entity& entity);
	virtual void OnUpdate(JE::Entity& entity, JE::Group& group, float dt);
	virtual void OnDraw(JE::Entity& entity);
	
	void enable();
	void disable();
	bool isEnabled() const;
private:
	bool _is_enabled;
};

}