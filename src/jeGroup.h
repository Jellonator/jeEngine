#pragma once
namespace JE{
class World;
class Entity;
#include <vector>

class Group
{
	public:
		Group(int order = JE_ORDER_NONE, int drawmode = JE_WORLD_MODE_ALL, int updatemode = JE_WORLD_MODE_ALL);
		virtual ~Group();
		std::vector<Group*> groups;
		std::vector<Entity*> entities;/**< \brief vector<Entity*> entities, a list of entities in the group. */

		int order;/**< \brief JE_ORDER order, the entity order. */
		bool needOrder;/**< \brief bool needOrder, whether the group needs order or not. */
		int drawMode;/**< \brief JE_WORLD_MODE drawMode, the drawing mode. */
		int updateMode;/**< \brief JE_WORLD_MODE updateMode, the update mode. */

		void begin();/**< \brief Initiates the group. */
		/** \brief Updates all entities in the group or sub-group.
         * \param int group, the group to update, if not specified it instead updates all of this group's entities.
         */
		void update(int group = -1);
		/** \brief Draws all entities in the group or sub-group.
         * \param int group, the group to draw, if not specified it instead draws all of this group's entities.
         */
		void draw(int group = -1);
		void end();/**< \brief Closes the group. */

        /** \brief Adds an entity to the specified Group.
         * \param Entity* entity, the entity to add.
         */
		void add(Entity* entity);

        /** \brief Removes an entity from the specified group.
         * \param Entity* entity, the entity to remove.
         */
		void remove(Entity* entity);
		void move(int from, int to);
		void clear();
		void clear(int group);
		void clearAll();
		void moveToBack(int from);
		void moveToFront(int from);
		void moveUp(int from);
		void moveDown(int from);
		int getID(Entity* entity);

		/** \brief Changes the order of a group.
         * \param JE_ORDER order, the order to use.
		 */
		void changeOrder(int order);

        /** \brief Adds an entity to a sub-group.
         * \param Entity* entity, the entity to add.
         * \param unsigned int group, the sub-group to add the entity to.
		 */
		void addToGroup(Entity* entity, unsigned int group);

        /** \brief Removes an entity from a sub-group.
         * \param Entity* entity, the entity to remove.
         * \param unsigned int group, the sub-group to remove from.
		 */
		void removeFromGroup(Entity* entity, unsigned int group);

        /** \brief Get a sub-group pointer from a group.
         * \param unsigned int index, the index of the sub-group to retrieve.
         * \return Group*, a pointer to a group.
         */
		Group* getGroup(unsigned int index);

		/** \brief Adds/resets a group to/in the world, automatically called by World::addToGroup()
		 * \param World* world, the world to add the group to.
		 * \param unsigned int group, the group to add.
		 * \param int order, the order to use.
		 */
		void addGroup(unsigned int group, int order = -1, int drawmode = -1, int updatemode = -1);

        /** \brief Removes a group form the world
         * \param unsigned int group, the group to remove.
		 */
		void removeGroup(unsigned int group);
        /** \brief Clears the world of all entities.
         * \param int level. 0 means entities in this group only. 1 means entities and sub-groups in this group only. 2 means all entities will be removed from their assosiated groups this group.  Sub-groups are also removed.
         */
		std::vector<bool> __EREMOVED__;
		std::vector<unsigned int> __IREMOVED__;
		//Overloaders
		Entity* operator[](unsigned int value);
};};
