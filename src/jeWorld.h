#pragma once
#include "JE.h"
namespace JE{
class World : public Group
{
	public:
        /** \brief Exactly the same as JE::GROUP, but a little more abstracted.
         * \param order int, the ordering for entities. Defaults to no order(fastest).
         * \param drawmode int, the drawing mode. Defaults to all(renders all entities in order).
         * \param updatemode int, the update mode. Defaults to all(updates all entities in order).
         */
		World(int order = JE_ORDER_NONE, int drawmode = JE_WORLD_MODE_ALL, int updatemode = JE_WORLD_MODE_ALL);
		virtual ~World();

		virtual void OnBegin(){};/**< \brief Called when the world starts. */
		virtual void onUpdate(){};/**< \brief Called when the world is updated. */
		virtual void OnDraw(){};/**< \brief Called when the entity is drawn. */
		virtual void onEnd(){};/**< \brief Called when the world is ended. */

        /** \brief Initiates the world, DO NOT CALL EXPLICITLY, automatically called when using World::set().
         * \param World* world, the world to use.
         */
		void begin();

        /** \brief Updates the world.
         * \param World* world, the world to update.
         * \param int group, the group to update(if applicable).
         */
		void update(int group = -1);

        /** \brief draws the world
         * \param World* world, the world to draw.
         * \param int group, the group to draw(if applicable).
         */
		void draw(int group = -1);

        /** \brief Ends the world, DO NOT CALL EXPLICITLY, automatically called when using World::set().
         * \param World* world, the world to use.
         */
		void end();
};
/** \brief Sets the active world.
 * \param World* world, the world to use.
 */
void setWorld(World* world);
};
