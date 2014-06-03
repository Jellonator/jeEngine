#pragma once
#include "JE.h"
#include "jePoint.h"
namespace JE{
class Entity : public Point
{
	public:
		Entity();
		virtual ~Entity();
		Mask* mask;/**< \brief jeMask* mask, he entity's mask. */

		virtual void OnCreate();/**< \brief Called when the entity is created. */
		virtual void OnAdd(Group* group = NULL);/**< \brief Called when the entity is added to the world. */
		virtual void OnUpdate();/**< \brief Called when the entity is updated. */
		virtual void OnDraw();/**< \brief Called when the entity is drawn. */
		virtual void OnRemove(Group* group = NULL);/**< \brief Called when the entity is removed from the world. */

		/** \brief Sets the specified entity's mask
		 * \param jeMask* mask, the mask to use
		 */
		inline void setMask(Mask* mask){this->mask = mask;};
		void destroy();/**< \brief Use to destroy this entity, removes it from all existing worlds and deletes it. */
		std::vector<Group*> __GROUPS__;
};
};
