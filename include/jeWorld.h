#pragma once
#include "JE.h"

class jeWorld
{
	public:
		jeWorld(int order = JE_ORDER_NONE, int drawmode = JE_WORLD_MODE_ALL, int updatemode = JE_WORLD_MODE_ALL);
		virtual ~jeWorld();

		std::vector<jeEntity*> entities;/**< \brief vector<jeEntity*> entities, the list of entities in the world. */
		std::vector<jeGroup*> groups;/**< \brief vector<jeGroup*> groups, the list of groups in the world. */
		int order;/**< \brief JE_ORDER order, the entity order. */
		bool needOrder;/**< \brief bool needOrder, whether the world needs order or not. */
		int drawMode;/**< \brief JE_WORLD_MODE drawMode, the drawing mode. */
		int updateMode;/**< \brief JE_WORLD_MODE updateMode, the update mode. */
		std::vector<bool> __EREMOVED__;
		std::vector<unsigned int> __IREMOVED__;

		virtual void OnBegin(){};/**< \brief Called when the world starts. */
		virtual void onUpdate(){};/**< \brief Called when the world is updated. */
		virtual void OnDraw(){};/**< \brief Called when the entity is drawn. */
		virtual void onEnd(){};/**< \brief Called when the world is ended. */

        /** \brief Initiates the world, DO NOT CALL EXPLICITLY, automatically called when using jeWorld::set().
         * \param jeWorld* world, the world to use.
         */
		static void begin(jeWorld* world = JE::world);

        /** \brief Updates the world.
         * \param jeWorld* world, the world to update.
         * \param int group, the group to update(if applicable).
         */
		static void update(jeWorld* world, int group = -1);

        /** \brief updates the world.
         * \param int group, the group to update(if applicable).
         */
		static inline void update(int group = -1){jeWorld::update(JE::world, group);}

        /** \brief draws the world
         * \param jeWorld* world, the world to draw.
         * \param int group, the group to draw(if applicable).
         */
		static void draw(jeWorld* world, int group = -1);

        /** \brief draws the world
         * \param jeWorld* world, the world to draw.
         * \param int group, the group to draw(if applicable).
         */
		static inline void draw(int group = -1){jeWorld::draw(JE::world, group);}

        /** \brief Ends the world, DO NOT CALL EXPLICITLY, automatically called when using jeWorld::set().
         * \param jeWorld* world, the world to use.
         */
		static void end(jeWorld* world = JE::world);

        /** \brief Adds an entity to the active world.
         * \param jeWorld* world, the world to add to.
         * \param jeEntity* entity, the entity to add.
         */
		static void add(jeWorld* world, jeEntity* entity);
        /** \brief Adds an entity to the specified world.
         * \param jeEntity* entity, the entity to add.
         */
		static inline void add(jeEntity* entity){jeWorld::add(JE::world, entity);}

        /** \brief Removes an entity from the world.
         * \param jeWorld* world, the world to remove from.
         * \param jeEntity* entity, the entity to remove.
         */
		static void remove(jeWorld* world, jeEntity* entity);
        /** \brief Removes an entity from the active world.
         * \param jeEntity* entity, the entity to remove.
         */
		static inline void remove(jeEntity* entity){jeWorld::remove(JE::world, entity);}

        /** \brief Sets the active world.
         * \param jeWorld* world, the world to use.
         */
		static void set(jeWorld* world);

		/** \brief Adds/resets a group to/in the world, automatically called by jeWorld::addToGroup()
		 * \param jeWorld* world, the world to add the group to.
		 * \param unsigned int group, the group to add.
		 * \param int order, the order to use.
		 */
		static void addGroup(jeWorld* world, unsigned int group, int order = -1);

		/** \brief Adds/resets a group to/in the active world, automatically called by jeWorld::addToGroup()
		 * \param unsigned int group, the group to add.
		 * \param int order, the order to use.
		 */
		static inline void addGroup(unsigned int group, int order = -1){jeWorld::addGroup(JE::world, group, order);}

        /** \brief Adds an entity to a group.
         * \param jeWorld* world, the world to add the entity to.
         * \param jeEntity* entity, the entity to add
         * \param unsigned int group, the group to add the entity to.
         */
		static void addToGroup(jeWorld* world, jeEntity* entity, unsigned int group);

        /** \brief Adds an entity to a group in the active world.
         * \param jeEntity* entity, the entity to add
         * \param unsigned int group, the group to add the entity to.
         */
		static inline void addToGroup(jeEntity* entity, unsigned int group){jeWorld::addToGroup(JE::world, entity, group);}

        /** \brief Removes an entity from a group.
         * \param jeWorld* world, the world to remove the entity from.
         * \param jeEntity* entity, the entity to remove.
         * \param unsigned int group, the group to remove from.
         */
		static void removeFromGroup(jeWorld* world, jeEntity* entity, unsigned int group);

        /** \brief Removes an entity from a group in the active world.
         * \param jeEntity* entity, the entity to remove.
         * \param unsigned int group, the group to remove from.
         */
		static inline void removeFromGroup(jeEntity* entity, unsigned int group){jeWorld::removeFromGroup(JE::world, entity, group);};

        /** \brief Changes the order mode of a world.
         * \param jeWorld* world, the world to change the order of.
         * \param JE_ORDER order, the order to use.
         */
		static void changeOrder(jeWorld* world, int order);

        /** \brief Changes the order mode of the active world.
         * \param JE_ORDER order, the order to use.
         */
		static inline void changeOrder(int order){jeWorld::changeOrder(JE::world, order);};
	protected:
	private:
};
