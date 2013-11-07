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

		jeWorld* world;
		bool inWorld;

		std::vector<jeEntity*> entities;
		int order;
		bool needOrder;
		std::vector<bool> __EREMOVED__;
		std::vector<unsigned int> __IREMOVED__;

		void begin();
		void update();
		void draw();
		void end();

        /** \brief Adds an entity to the specified Group.
         * \param group jeGroup*
         * \param entity jeEntity*
         */
		static void add(jeGroup* group, jeEntity* entity);
		static inline void add(unsigned int group, jeEntity* entity){jeGroup::add(JE::world->groups[group], entity);}

        /** \brief Removes an entity from the specified group.
         * \param group jeGroup*, the group to remove from.
         * \param entity jeEntity*, the entity to remove.
         */
		static void remove(jeGroup* group, jeEntity* entity);
		static inline void remove(unsigned int group, jeEntity* entity){jeGroup::remove(JE::world->groups[group], entity);}

		static void changeOrder(jeGroup* group, int order);
		static inline void changeOrder(unsigned int group, int order){jeGroup::changeOrder(JE::world->groups[group], order);};
	protected:
	private:
};

#endif // JEGROUP_H
