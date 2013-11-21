#ifndef JEGROUP_H
#define JEGROUP_H

class jeWorld;
class jeEntity;
#include <vector>

class jeGroup
{
	public:
		jeGroup(int order, jeWorld* world = NULL);
		virtual ~jeGroup();

		int __INDEX__;
		int __PINDEX__;

		jeWorld* parent;/**< \brief jeWorld* world, the world this group is in. */
		bool inWorld;/**< \brief bool inWorld, Whether the group is actually in a world or not(Currently not in use) */

		std::vector<jeEntity*> entities;/**< \brief vector<jeEntity*> entities, a list of entities in the group. */
		std::vector<bool> __EREMOVED__;
		std::vector<unsigned int> __IREMOVED__;

		int order;/**< \brief JE_ORDER order, the entity order. */
		bool needOrder;/**< \brief bool needOrder, whether the group needs order or not. */

		void begin();/**< \brief Initiates the group. */
		void update(int group = -1);/**< \brief Updates all of the entities in the group. */
		void draw(int group = -1);/**< \brief Draws all of the entities in the group. */
		void end();/**< \brief Closes the group. */

        /** \brief Adds an entity to the specified Group.
         * \param jeEntity* entity, the entity to add.
         */
		void add(jeEntity* entity);
		//static inline void add(unsigned int group, jeEntity* entity){jeGroup::add(JE::world->groups[group], entity);}

        /** \brief Removes an entity from the specified group.
         * \param jeEntity* entity, the entity to remove.
         */
		void remove(jeEntity* entity);
		//static inline void remove(unsigned int group, jeEntity* entity){jeGroup::remove(JE::world->groups[group], entity);}

		/** \brief Changes the order of a group.
         * \param JE_ORDER order, the order to use.
		 */
		void changeOrder(int order);
		//static inline void changeOrder(unsigned int group, int order){jeGroup::changeOrder(JE::world->groups[group], order);};
	protected:
	private:
};

#endif // JEGROUP_H
