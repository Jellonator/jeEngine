#pragma once
class jeGroup;
class jeEntity;
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
	protected:
	private:
};

/** \brief compares the collision of two entities.
 * \param e1 jeEntity*; the first entity.
 * \param e2 jeEntity*; the second entity.
 * \param float x; the offset-x.
 * \param float y; the offset-y.
 * \param bool sweep; whether to move the entity.
 * \return bool; whether the entities collided.
 */
bool jeCollide(jeEntity* e1, jeEntity* e2, float x = 0, float y = 0, bool sweep = false);

/** \brief compares the collision of two masks.
 * \param e1 jeMask*; the first mask.
 * \param e2 jeMask*; the second mask.
 * \param float x; the offset-x.
 * \param float y; the offset-y.
 * \param bool sweep; whether to move the mask.
 * \return bool; whether the masks collided.
 */
bool jeCollide(jeMask* e1, jeMask* e2, float x = 0, float y = 0, bool sweep = false);

/** \brief compares the collision of an entity and all of the entities in a group.
 * \param e jeEntity*; the enity.
 * \param group jeGroup*; the group. can also be jeWorld*.
 * \param float x; the offset-x.
 * \param float y; the offset-y.
 * \param bool sweep; whether to move the entity.
 * \return bool; whether the enity collided with another entity.
 */
bool jeCollideGroup(jeEntity* e, jeGroup* group, float x = 0, float y = 0, bool sweep = false);

/** \brief compares the collision of an entity and all of the entities in a group.
 * \param e jeEntity*; the enity.
 * \param group int; the group.
 * \param float x; the offset-x.
 * \param float y; the offset-y.
 * \param bool sweep; whether to move the entity.
 * \return bool; whether the enity collided with another entity.
 */
bool jeCollideGroup(jeEntity* e, int group, float x = 0, float y = 0, bool sweep = false);
#include "jeHitBox.h"
