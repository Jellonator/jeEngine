#pragma once
#include "JE.h"
#include "jeHitBox.h"

class jeHitBox : public jeMask
{
	public:
		float width;/**< \brief float width, the width of the box. */
		float height;/**< \brief the float height, height of the box. */
		jeHitBox(float x, float y, float width, float height);
		jeHitBox(float width = 32, float height = 32);
		float left();/**< \return float, the left side of the box. */
		float right();/**< \return float, the right side of the box. */
		float top();/**< \return float, the top of the box. */
		float bottom();/**< \return float, the bottom of the box. */
		virtual ~jeHitBox();

        /** \brief Checks for collision against two boxes
         * \param jeMask* b1, the first box.
         * \param jeMask* b2, the second box.
         * \param float x, the x offset.
         * \param float y, the y offset.
         * \param bool sweep, whether the collision should sweep.
         * \param float width, adds to the first box's width.
         * \param float height, adds to the first box's height.
         * \return bool, if the two boxes collided or not.
         */
		static bool collideBox(jeHitBox* b1, jeHitBox* b2, float x = 0, float y = 0, bool sweep = false, float width = 0, float height = 0);
	protected:
	private:
};
