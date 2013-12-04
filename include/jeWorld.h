#pragma once
#include "JE.h"

class jeWorld : public jeGroup
{
	public:
		jeWorld(int order = JE_ORDER_NONE, int drawmode = JE_WORLD_MODE_ALL, int updatemode = JE_WORLD_MODE_ALL);
		virtual ~jeWorld();
		int drawMode;/**< \brief JE_WORLD_MODE drawMode, the drawing mode. */
		int updateMode;/**< \brief JE_WORLD_MODE updateMode, the update mode. */

		virtual void OnBegin(){};/**< \brief Called when the world starts. */
		virtual void onUpdate(){};/**< \brief Called when the world is updated. */
		virtual void OnDraw(){};/**< \brief Called when the entity is drawn. */
		virtual void onEnd(){};/**< \brief Called when the world is ended. */

        /** \brief Initiates the world, DO NOT CALL EXPLICITLY, automatically called when using jeWorld::set().
         * \param jeWorld* world, the world to use.
         */
		void begin();

        /** \brief Updates the world.
         * \param jeWorld* world, the world to update.
         * \param int group, the group to update(if applicable).
         */
		void update(int group = -1);

        /** \brief draws the world
         * \param jeWorld* world, the world to draw.
         * \param int group, the group to draw(if applicable).
         */
		void draw(int group = -1);

        /** \brief Ends the world, DO NOT CALL EXPLICITLY, automatically called when using jeWorld::set().
         * \param jeWorld* world, the world to use.
         */
		void end();

        /** \brief Adds an entity to the active world.
         * \param jeWorld* world, the world to add to.
         * \param jeEntity* entity, the entity to add.
         */
		void add(jeEntity* entity);

        /** \brief Removes an entity from the world.
         * \param jeWorld* world, the world to remove from.
         * \param jeEntity* entity, the entity to remove.
         */
		void remove(jeEntity* entity);

        /** \brief Sets the active world.
         * \param jeWorld* world, the world to use.
         */
		static void set(jeWorld* world);

        /** \brief Changes the order mode of a world.
         * \param jeWorld* world, the world to change the order of.
         * \param JE_ORDER order, the order to use.
         */
		void changeOrder(int order);
};
