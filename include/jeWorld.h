#pragma once
#include "JE.h"

class jeWorld
{
	public:
		jeWorld(int order = JE_ORDER_NONE, int drawmode = JE_WORLD_MODE_ALL, int updatemode = JE_WORLD_MODE_ALL);
		virtual ~jeWorld();

		std::vector<jeEntity*> entities;
		std::vector<jeGroup*> groups;
		int order;
		bool needOrder;
		int drawMode;
		int updateMode;
		std::vector<bool> __EREMOVED__;
		std::vector<unsigned int> __IREMOVED__;

		virtual void OnBegin(){};
		virtual void onUpdate(){};
		virtual void OnDraw(){};
		virtual void onEnd(){};

        /** \brief Initiates a world
         * \param world jeWorld*, the world to use.
         */
		static void begin(jeWorld* world = JE::world);
		static void update(jeWorld* world, int group = 0);
		static inline void update(int group = -1){jeWorld::update(JE::world, group);}
		static void draw(jeWorld* world, int group = 0);
		static inline void draw(int group = -1){jeWorld::draw(JE::world, group);}
		static void end(jeWorld* world = JE::world);

        /** \brief Adds an entity to the active world.
         * \param world jeWorld*
         * \param entity jeEntity*
         */
		static void add(jeWorld* world, jeEntity* entity);
        /** \brief Adds an entity to the specified world.
         * \param entity jeEntity*
         */
		static inline void add(jeEntity* entity){jeWorld::add(JE::world, entity);}

        /** \brief Removes an entity from the world.
         * \param world jeWorld*, the world to remove from.
         * \param entity jeEntity*, the entity to remove.
         */
		static void remove(jeWorld* world, jeEntity* entity);
        /** \brief Removes an entity from the active world.
         * \param entity jeEntity*, the entity to remove.
         */
		static inline void remove(jeEntity* entity){jeWorld::remove(JE::world, entity);}

        /** \brief Sets the active world.
         * \param world jeWorld*, the world to use.
         */
		static void set(jeWorld* world);


		static void addGroup(jeWorld* world, unsigned int group, int order = -1);
		static inline void addGroup(unsigned int group, int order = -1){jeWorld::addGroup(JE::world, group, order);}

		static void addToGroup(jeWorld* world, jeEntity* entity, unsigned int group);
		static inline void addToGroup(jeEntity* entity, unsigned int group){jeWorld::addToGroup(JE::world, entity, group);}

		static void removeFromGroup(jeWorld* world, jeEntity* entity, unsigned int group);
		static inline void removeFromGroup(jeEntity* entity, unsigned int group){jeWorld::removeFromGroup(JE::world, entity, group);};

		static void changeOrder(jeWorld* world, int order);
		static inline void changeOrder(int order){jeWorld::changeOrder(JE::world, order);};
	protected:
	private:
};
