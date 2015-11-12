#pragma once
#include "jePoint.h"
#include "jeMask.h"
#include <vector>
#include <string>
#include <memory>
#include <map>

namespace JE{

class Component;
class Group;
class Entity
{
public:
friend Group;
	Entity();
	virtual ~Entity();

	//Callbacks
	virtual void OnCreate();/**< \brief Called when the entity is created. */
	virtual void OnDraw();/**< \brief Called when the entity is drawn. */
	virtual void OnAdd(JE::Group& group);/**< \brief Called when the entity is added to the world. */
	virtual void OnRemove(JE::Group& group);/**< \brief Called when the entity is removed from the world. */
	virtual void OnUpdate(JE::Group& group, float dt);/**< \brief Called when the entity is updated. */
	
	//Mask
	template <class MType, class... MArgs>
	MType& setMask(MArgs... arguments);
	
	JE::MASK::Mask* getMask();
	const JE::MASK::Mask* getMask() const;
	bool hasMask() const;
	
	//Component
	template <class CType, class... CArgs>
	CType& addComponent(const std::string& name, CArgs... arguments);
	
	template <class CType>
	CType* getComponent(const std::string& name);
	
	JE::Component* getComponent(const std::string& name);
	
	void callComponent(const std::string& name);
	bool hasComponent(const std::string& name) const;
	
	//Position getters
	int getX() const;
	int getY() const;
	int getCenterX() const;
	int getCenterY() const;
	
	//Layers
	void setLayer(int value);
	
	inline int getLayer() const{
		return this->_layer;
	}
	
private:
	std::vector<std::string> _groups_v;
	std::unique_ptr<JE::MASK::Mask> _mask_ptr;
	JE::Group* _group = nullptr;
	int _layer;
	std::map<std::string, std::unique_ptr<Component>> _component_map;
};

template <class MType, class... MArgs>
MType& Entity::setMask(MArgs... arguments){
	MType* ret = new MType(arguments...);
	this->_mask_ptr.reset(ret);
	return *ret;
}

template <class CType, class... CArgs>
CType& Entity::addComponent(const std::string& name, CArgs... arguments){
	CType* ret = new CType(arguments...);
	this->_component_map[name].reset(ret);
	return *ret;
}

template <class CType>
CType* Entity::getComponent(const std::string& name){
	JE::Component* component = this->getComponent(name);
	if (component == nullptr) return nullptr;
	CType* ret = dynamic_cast<CType>(component);
	return *ret;
}

};
