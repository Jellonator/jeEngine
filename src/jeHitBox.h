#pragma once
#include "JE.h"
namespace JE{namespace MASK{
class HitBox : public Mask
{
	public:
		float width;/**< \brief float width, the width of the box. */
		float height;/**< \brief the float height, height of the box. */
        /** \brief A class for collision boxes.
         * \param x float, the x position.
         * \param y float, the y position.
         * \param width float, width.
         * \param height float, height.
         */
		HitBox(float x, float y, float width, float height);
        /** \brief A class for collision boxes.
         * \param width float, width.
         * \param height float, height.
         */
		HitBox(float width = 32, float height = 32);
		float left();/**< \return float, the left side of the box. */
		float right();/**< \return float, the right side of the box. */
		float top();/**< \return float, the top of the box. */
		float bottom();/**< \return float, the bottom of the box. */
		virtual ~HitBox();
	protected:
	private:
};

/** \brief Tests whether two hitboxes collided.
 * \param m1 HitBox*, the hitbox to use.
 * \param m2 Hitbox*, the hitbox to use.
 * \param x float, the x offset of the hitbox.
 * \param y float, the y offset of the hitbox.
 * \param sweep bool, whether the hitbox should move.
 * \return bool, If the masks collided.
 */
bool collideBox(HitBox* m1, HitBox* m2, float x = 0, float y = 0, bool sweep = false);
/** \brief Tests whether a hitbox and grid collided(via entities)
 * \param e1 Entity*, the hitbox to use.
 * \param e2 Entity*, the hitbox to use.
 * \param x float, the x offset of the hitbox.
 * \param y float, the y offset of the hitbox.
 * \param sweep bool, whether the hitbox should move.
 * \return bool, If the masks collided.
 */
bool collideBox(Entity* e1, Entity* e2, float x = 0, float y = 0, bool sweep = false);
};};
