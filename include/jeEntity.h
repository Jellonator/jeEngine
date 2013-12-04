#pragma once
#include "JE.h"

class jeEntity
{
	public:
		jeEntity();
		virtual ~jeEntity();
		float x = 0;/**< \brief float x, the entity's x position. */
		float y = 0;/**< \brief float y, he entity's y position. */
		jeMask* mask;/**< \brief jeMask* mask, he entity's mask. */

		virtual void OnCreate();/**< \brief Called when the entity is created. */
		virtual void OnAdd();/**< \brief Called when the entity is added to the world. */
		virtual void OnUpdate();/**< \brief Called when the entity is updated. */
		virtual void OnDraw();/**< \brief Called when the entity is drawn. */
		virtual void OnRemove();/**< \brief Called when the entity is removed from the world. */

		/** \brief Sets the specified entity's mask
		 * \param jeMask* mask, the mask to use
		 */
		inline void setMask(jeMask* mask){this->mask = mask;};
		void destroy();/**< \brief Use to destroy this entity, removes it from all existing worlds and deletes it. */
		std::vector<jeGroup*> __GROUPS__;
};
