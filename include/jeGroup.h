#ifndef JEGROUP_H
#define JEGROUP_H
#include "JE.h"

class jeGroup
{
	public:
		jeGroup(int order = JE_ORDER_NONE, jeWorld* world = NULL);
		virtual ~jeGroup();

		int __INDEX__;
		bool __WORLD__;

		jeWorld* world;/**< \brief jeWorld* world, the world this group is in. */
		bool inWorld;/**< \brief bool inWorld, Whether the group is actually in a world or not(Currently not in use) */

		std::vector<jeEntity*> entities;/**< \brief vector<jeEntity*> entities, a list of entities in the group. */
		int order;/**< \brief JE_ORDER order, the entity order. */
		bool needOrder;/**< \brief bool needOrder, whether the group needs order or not. */
		std::vector<bool> __EREMOVED__;
		std::vector<unsigned int> __IREMOVED__;

		void begin();/**< \brief Initiates the group. */
		void update();/**< \brief Updates all of the entities in the group. */
		void draw();/**< \brief Draws all of the entities in the group. */
		void end();/**< \brief Closes the group. */

        /** \brief Adds an entity to the specified Group.
         * \param jeGroup* group, the group to add the entity to.
         * \param jeEntity* entity, the entity to add.
         */
		static void add(jeGroup* group, jeEntity* entity);
		//static inline void add(unsigned int group, jeEntity* entity){jeGroup::add(JE::world->groups[group], entity);}

        /** \brief Removes an entity from the specified group.
         * \param jeGroup* group, the group to remove from.
         * \param jeEntity* entity, the entity to remove.
         */
		static void remove(jeGroup* group, jeEntity* entity);
		//static inline void remove(unsigned int group, jeEntity* entity){jeGroup::remove(JE::world->groups[group], entity);}

		/** \brief Changes the order of a group.
		 * \param jeGroup* group, the group to change the order of.
         * \param JE_ORDER order, the order to use.
		 */
		static void changeOrder(jeGroup* group, int order);
		//static inline void changeOrder(unsigned int group, int order){jeGroup::changeOrder(JE::world->groups[group], order);};
	protected:
	private:
};

#endif // JEGROUP_H
