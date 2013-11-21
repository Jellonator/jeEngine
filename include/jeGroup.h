#ifndef JEGROUP_H
#define JEGROUP_H

class jeWorld;
class jeEntity;
#include <vector>

class jeGroup
{
	public:
		friend class jeWorld;
		jeGroup(int order, jeWorld* world = NULL);
		virtual ~jeGroup();

		jeWorld* parent;/**< \brief jeWorld* world, the world this group is in. */
		bool inWorld;/**< \brief bool inWorld, Whether the group is actually in a world or not(Currently not in use) */

		std::vector<jeEntity*> entities;/**< \brief vector<jeEntity*> entities, a list of entities in the group. */

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

        /** \brief Removes an entity from the specified group.
         * \param jeEntity* entity, the entity to remove.
         */
		void remove(jeEntity* entity);

		/** \brief Changes the order of a group.
         * \param JE_ORDER order, the order to use.
		 */
		void changeOrder(int order);
		int __INDEX__;
		int __PINDEX__;
		std::vector<bool> __EREMOVED__;
		std::vector<unsigned int> __IREMOVED__;
};

#endif // JEGROUP_H
