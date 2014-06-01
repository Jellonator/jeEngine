#pragma once
enum JE_MASK_TYPE{JE_MASK_NONE, JE_MASK_BOX, JE_MASK_GRID, JE_MASK_LIST};
namespace JE{
class Group;
class Entity;
class Mask
{
	public:
		float x;/**< \brief float x, the Mask's x position. */
		float y;/**< \brief float y, the Mask's y position. */
		int type;/**< \brief JE_MASK_TYPE type, the Mask's type. */
		Mask();
		virtual ~Mask();

        /** \brief Checks for collision against two masks.
         * \param Mask* m1, the first mask.
         * \param Mask* m2, the second mask.
         * \param float x, the x offset.
         * \param float y, the y offset.
         * \param bool sweep, whether the collision should sweep.
         * \return bool, if the two masks collided or not.
         */
	protected:
	private:
};
namespace MASK{
/** \brief compares the collision of two entities.
 * \param e1 Entity*; the first entity.
 * \param e2 Entity*; the second entity.
 * \param float x; the offset-x.
 * \param float y; the offset-y.
 * \param bool sweep; whether to move the entity.
 * \return bool; whether the entities collided.
 */
bool collide(Entity* e1, Entity* e2, float x = 0, float y = 0, bool sweep = false);

/** \brief compares the collision of two masks.
 * \param e1 Mask*; the first mask.
 * \param e2 Mask*; the second mask.
 * \param float x; the offset-x.
 * \param float y; the offset-y.
 * \param bool sweep; whether to move the mask.
 * \return bool; whether the masks collided.
 */
bool collide(Mask* e1, Mask* e2, float x = 0, float y = 0, bool sweep = false);

/** \brief compares the collision of an entity and all of the entities in a group.
 * \param e Entity*; the enity.
 * \param group Group*; the group. can also be World*.
 * \param float x; the offset-x.
 * \param float y; the offset-y.
 * \param bool sweep; whether to move the entity.
 * \return bool; whether the enity collided with another entity.
 */
bool collideGroup(Entity* e, Group* group, float x = 0, float y = 0, bool sweep = false);

/** \brief compares the collision of an entity and all of the entities in a group.
 * \param e Entity*; the enity.
 * \param group int; the group.
 * \param float x; the offset-x.
 * \param float y; the offset-y.
 * \param bool sweep; whether to move the entity.
 * \return bool; whether the enity collided with another entity.
 */
bool collideGroup(Entity* e, int group, float x = 0, float y = 0, bool sweep = false);
};};