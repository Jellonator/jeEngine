#pragma once
#include "jeMain.h"
#include "jeUtil.h"
#include <memory>
namespace JE{
class World;
class Entity;

class Group : public std::enable_shared_from_this<Group>
{
	public:
		/** \brief A group for containing entities.
		 * \param order int, the ordering for entities. Defaults to no order(fastest).
		 * \param drawmode int, the drawing mode. Defaults to all(renders all entities in order).
		 * \param updatemode int, the update mode. Defaults to all(updates all entities in order).
		 */
		Group(int drawmode = JE_WORLD_MODE_ALL, int updatemode = JE_WORLD_MODE_ALL);
		virtual ~Group();
		std::vector<std::shared_ptr<Group>> groups;
		std::vector<std::shared_ptr<Entity>> entities;/**< \brief vector<Entity*> entities, a list of entities in the group. */
		std::vector<std::shared_ptr<Entity>> entities_add;
		std::vector<std::shared_ptr<Entity>> entities_remove;

		int drawMode;/**< \brief JE_WORLD_MODE drawMode, the drawing mode. */
		int updateMode;/**< \brief JE_WORLD_MODE updateMode, the update mode. */
		bool needUpdateEntityLayering;

		bool do_sort;
		bool correct_remove;

		void begin();/**< \brief Initiates the group. */
		/** \brief Updates all entities in the group or sub-group.
		 * \param int group, the group to update, if not specified it instead updates all of this group's entities.
		 */
		void update(float dt, int group = -1);
		/** \brief Draws all entities in the group or sub-group.
		 * \param int group, the group to draw, if not specified it instead draws all of this group's entities.
		 */
		void draw(int group = -1);
		void end();/**< \brief Closes the group. */

		/** \brief Adds an entity to the specified Group.
		 * \param Entity* entity, the entity to add.
		 */
		virtual void add(std::shared_ptr<Entity> entity);

		/** \brief Removes an entity from the specified group.
		 * \param Entity* entity, the entity to remove.
		 */
		virtual void remove(std::shared_ptr<Entity> entity);
		void move(int from, int to);
		void clear();
		void clear(int group);
		void enableSort();
		void disableSort();
		void clearAll();
		//void moveToBack(int from);
		//void moveToFront(int from);
		//void moveUp(int from);
		//void moveDown(int from);
		//void swap(int a, int b);
		unsigned int size();
		int getID(std::shared_ptr<Entity> entity);

		/** \brief Changes the order of a group.
		 * \param JE_ORDER order, the order to use.
		 */
		//void changeOrder(int order);

		/** \brief Adds an entity to a sub-group.
		 * \param Entity* entity, the entity to add.
		 * \param unsigned int group, the sub-group to add the entity to.
		 */
		void addToGroup(std::shared_ptr<Entity> entity, unsigned int group);

		/** \brief Removes an entity from a sub-group.
		 * \param Entity* entity, the entity to remove.
		 * \param unsigned int group, the sub-group to remove from.
		 */
		void removeFromGroup(std::shared_ptr<Entity> entity, unsigned int group);

		/** \brief Get a sub-group pointer from a group.
		 * \param unsigned int index, the index of the sub-group to retrieve.
		 * \return Group*, a pointer to a group.
		 */
		std::shared_ptr<Group> getGroup(unsigned int index);
		const std::shared_ptr<Group>& getGroupConst(unsigned int index);

		/** \brief Adds/resets a group to/in the world, automatically called by World::addToGroup()
		 * \param World* world, the world to add the group to.
		 * \param unsigned int group, the group to add.
		 * \param int order, the order to use.
		 */
		void addGroup(unsigned int group, int drawmode = -1, int updatemode = -1);

		/** \brief Removes a group form the world
		 * \param unsigned int group, the group to remove.
		 */
		void removeGroup(unsigned int group);
		/** \brief Clears the world of all entities.
		 * \param int level. 0 means entities in this group only. 1 means entities and sub-groups in this group only. 2 means all entities will be removed from their assosiated groups this group.  Sub-groups are also removed.
		 */
		void deleteAll();
		
		void updateEntities();
		//Overloaders
		std::shared_ptr<Entity> getEntity(unsigned int value);
		const std::shared_ptr<Entity>& getEntityConst(unsigned int value);
		std::shared_ptr<Entity> operator[](unsigned int value);
	private:
		virtual void _add(std::shared_ptr<Entity> entity);
		virtual void _remove(std::shared_ptr<Entity> entity);
};};
