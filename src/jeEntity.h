#pragma once
#include "jePoint.h"
#include <cstddef>
#include <vector>
#include <memory>
namespace JE{
class Mask;
class Group;
class World;
class Entity : public Point, public std::enable_shared_from_this<Entity>
{
	friend Group;
	public:
		Entity(float x = 0, float y = 0);
		virtual ~Entity();
		std::shared_ptr<Mask> mask;/**< \brief jeMask* mask, he entity's mask. */
		int layer;

		virtual void OnCreate();/**< \brief Called when the entity is created. */
		virtual void OnAdd(Group* group);/**< \brief Called when the entity is added to the world. */
		virtual void OnAdd(World* world);/**< \brief Called when the entity is added to the world. */
		virtual void OnUpdate(float dt);/**< \brief Called when the entity is updated. */
		virtual void OnDraw();/**< \brief Called when the entity is drawn. */
		virtual void OnRemove(Group* group);/**< \brief Called when the entity is removed from the world. */
		virtual void OnRemove(World* world);/**< \brief Called when the entity is removed from the world. */
		
		void destroy();/**< \brief Use to destroy this entity, removes it from all existing worlds and deletes it. */
		virtual void moveBy(float move_x, float move_y);
		virtual void moveTo(float move_x, float move_y, bool force = false);
	private:
		std::vector<std::weak_ptr<Group>> __GROUPS__;
};
};
