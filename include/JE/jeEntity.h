#pragma once
#include "jePoint.h"
#include "jeMask.h"
#include <vector>
#include <string>
#include <memory>

namespace JE{

class Group;
class World;
class Entity : public Point
{
friend Group;
public:
	Entity();
	virtual ~Entity();
	int layer;

	virtual void OnCreate();/**< \brief Called when the entity is created. */
	virtual void OnDraw();/**< \brief Called when the entity is drawn. */
	virtual void OnAdd(JE::Group& group);/**< \brief Called when the entity is added to the world. */
	virtual void OnRemove(JE::Group& group);/**< \brief Called when the entity is removed from the world. */
	virtual void OnUpdate(JE::Group& group, float dt);/**< \brief Called when the entity is updated. */
	
	//virtual void moveBy(float move_x, float move_y);
	//virtual void moveTo(float move_x, float move_y, bool force = false);
	
	template <class MType, class... MArgs>
	MType& setMask(MArgs... arguments);
	JE::MASK::Mask& getMask();
	
private:
	std::vector<std::string> _groups_v;
	std::unique_ptr<JE::MASK::Mask> _mask_ptr;
};

template <class MType, class... MArgs>
MType& Entity::setMask(MArgs... arguments){
	MType* ret = new MType(arguments...);
	this->_mask_ptr.reset(ret);
	return *ret;
}

};
