#pragma once
#include "jeMain.h"
#include "jeUtil.h"
#include <memory>

namespace JE{
class World;
class Entity;

class Group
{
public:
	/** \brief A group for containing entities.
	 * \param order int, the ordering for entities. Defaults to no order(fastest).
	 * \param drawmode int, the drawing mode. Defaults to all(renders all entities in order).
	 * \param updatemode int, the update mode. Defaults to all(updates all entities in order).
	 */
	Group();
	virtual ~Group();
	
	void update(float dt);
	void draw();
	
	template <class EntityType, class... ArgType>
	void add(ArgType... args){
		std::unique_ptr<EntityType> entity_add(new EntityType(args...));
		this->entities_add.push_back(entity_add);
	}
	void remove(const Entity& entity);
	void remove(std::vector<std::unique_ptr<Entity>>::iterator);
	void updateEntities();
	
	void clear();
	void setSort(bool sort);
	void setCorrectRemove(bool do_correct_remove);
	
	unsigned int size() const;
	bool getSort() const;
	bool getCorrectRemove() const;
	
	//Overloaders
	Entity& getEntity(std::vector<std::unique_ptr<Entity>>::size_type value);
	Entity& operator[](std::vector<std::unique_ptr<Entity>>::size_type value);
	const Entity& getEntity(std::vector<std::unique_ptr<Entity>>::size_type value) const;
	const Entity& operator[](std::vector<std::unique_ptr<Entity>>::size_type value) const;
private:
	std::vector<std::unique_ptr<Entity>> entities;
	std::vector<std::unique_ptr<Entity>> entities_add;
	std::vector<std::vector<std::unique_ptr<Entity>>::iterator> entities_remove;
	
	bool needUpdateEntityLayering;
	bool do_sort;
	bool correct_remove;
};

}
