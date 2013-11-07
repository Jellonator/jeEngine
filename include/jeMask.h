#pragma once
#include "JE.h"

class jeMask
{
	public:
		float x;/**< \brief float x, the Mask's x position. */
		float y;/**< \brief float y, the Mask's y position. */
		int type;/**< \brief JE_MASK_TYPE type, the Mask's type. */
		jeMask();
		virtual ~jeMask();

        /** \brief Checks for collision against two masks.
         * \param jeMask* m1, the first mask.
         * \param jeMask* m2, the second mask.
         * \param float x, the x offset.
         * \param float y, the y offset.
         * \param bool sweep, whether the collision should sweep.
         * \return bool, if the two masks collided or not.
         */
		bool collide(jeMask* m1, jeMask* m2, float x = 0, float y = 0, bool sweep = false);

        /** \brief Checks for collision against an entire group.
         * \param jeMask* mask, the mask.
         * \param jeGroup* group, the group.
         * \param float x, the x offset.
         * \param float y, the y offset.
         * \param bool sweep, whether the collision should sweep.
         * \return bool, if the mask collided with any entities in the group.
         */
		bool collideGroup(jeMask* mask, jeGroup* group, float x = 0, float y = 0, bool sweep = false);

        /** \brief Checks for collision against an entity.
         * \param jeMask* mask, the mask.
         * \param jeEntity* entity, the entity.
         * \param float x, the x offset.
         * \param float y, the y offset.
         * \param bool sweep, whether the collision should sweep.
         * \return bool, if the mask collided with the entity.
         */
		bool collideEntity(jeMask* mask, jeEntity* entity, float x = 0, float y = 0, bool sweep = false);
	protected:
	private:
};



#include "jeHitBox.h"
