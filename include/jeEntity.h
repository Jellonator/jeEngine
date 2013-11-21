#pragma once
#include "JE.h"

class jeEntity
{
	friend class jeGroup;
	friend class jeWorld;
	public:
		jeEntity();
		virtual ~jeEntity();
		float x = 0;/**< \brief float x, the entity's x position. */
		float y = 0;/**< \brief float y, he entity's y position. */
		jeMask* mask;/**< \brief jeMask* mask, he entity's mask. */

		//int __INDEX__;/**< \brief The entity's position in the world. */

		virtual void OnCreate();/**< \brief Called when the entity is created. */
		virtual void OnAdd();/**< \brief Called when the entity is added to the world. */
		virtual void OnUpdate();/**< \brief Called when the entity is updated. */
		virtual void OnDraw();/**< \brief Called when the entity is drawn. */
		virtual void OnRemove();/**< \brief Called when the entity is removed from the world. */

		/** \brief Sets the specified entity's mask
		 * \param jeEntity* entity, the entity to modify
		 * \param jeMask* mask, the mask to use
		 */
		static void setMask(jeEntity* entity, jeMask* mask);

		/** \brief Sets the specified entity's mask
		 * \param jeMask* mask, the mask to use
		 */
		inline void setMask(jeMask* mask){this->mask = mask;};
		std::vector<int> __INDEXES__;
		int __GCOUNT__ = 0;
};
