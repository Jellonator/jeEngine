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

bool jeCollide(jeEntity* e1, jeEntity* e2, float x = 0, float y = 0, bool sweep = false);
bool jeCollide(jeMask* e1, jeMask* e2, float x = 0, float y = 0, bool sweep = false);
bool jeCollideGroup(jeEntity* e, jeGroup* group, float x = 0, float y = 0, bool sweep = false);
bool jeCollideGroup(jeEntity* e, int group, float x = 0, float y = 0, bool sweep = false);

#include "jeHitBox.h"
