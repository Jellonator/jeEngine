#pragma once
#include "jeMain.h"
#include "jeUtil.h"
#include "jeMask.h"
#include "jeEntity.h"
#include <vector>
#include <memory>
#include <string>
#include <map>

namespace JE{

class Entity;

typedef std::vector<std::unique_ptr<Entity>> entity_vec;
typedef std::vector<std::unique_ptr<Entity>>::size_type entity_vec_size;
typedef std::vector<std::unique_ptr<Entity>>::iterator entity_vec_iter;
typedef std::map<std::string, std::vector<Entity*>> group_map;

class Group
{
friend Entity;
public:
	Group();
	virtual ~Group();
	
	void update(float dt);
	void draw();
	
	template <class EntityType, class... ArgType>
	EntityType& add(ArgType... args){
		EntityType* entity_ptr = new EntityType(args...);
		std::unique_ptr<Entity> entity_unique(entity_ptr);
		this->entities_add.emplace_back(std::move(entity_unique));
		
		EntityType& entity_ref = *entity_ptr;
		
		this->needUpdateEntityLayering = true;
		entity_ref.OnAdd(*this);
		entity_ref._group = this;
		return entity_ref;
	}
	void remove(const Entity& entity);
	void remove(entity_vec_iter index);
	void updateEntities();
	
	void clear();
	void setSort(bool sort);
	void setCorrectRemove(bool do_correct_remove);
	
	//regular getters
	bool getSort() const;
	bool getCorrectRemove() const;
	entity_vec::size_type getSize() const;
	entity_vec::iterator getBegin();
	entity_vec::iterator getEnd();
	
	//group functions
	void addToGroup(const std::string& group, Entity& entity);
	void removeFromGroup(const std::string& group, Entity& entity);
	std::vector<Entity*>::iterator getGroupBegin(const std::string& group);
	std::vector<Entity*>::iterator getGroupEnd(const std::string& group);
	entity_vec::size_type getGroupSize(const std::string& group);
	
	bool getCollideEntity(      JE::Entity& entity,  int move_x, int move_y, int* get_x, int* get_y);
	bool getCollideMask(        JE::MASK::Mask& mask,int move_x, int move_y, int* get_x, int* get_y);
	bool getCollideEntityGroup( JE::Entity& entity,  int move_x, int move_y, int* get_x, int* get_y, const std::string& group);
	bool getCollideMaskGroup(   JE::MASK::Mask& mask,int move_x, int move_y, int* get_x, int* get_y, const std::string& group);
	bool getCollideEntityGroups(JE::Entity& entity,  int move_x, int move_y, int* get_x, int* get_y, const std::vector<std::string>& groups);
	bool getCollideMaskGroups(  JE::MASK::Mask& mask,int move_x, int move_y, int* get_x, int* get_y, const std::vector<std::string>& groups);
	
	//entity getters
	Entity& getEntity(entity_vec_size value);
	Entity& operator[](entity_vec_size value);
	const Entity& getEntity(entity_vec_size value) const;
	const Entity& operator[](entity_vec_size value) const;
private:
	entity_vec entities;
	entity_vec entities_add;
	std::vector<entity_vec_iter> entities_remove;
	group_map entity_groups;
	
	bool needUpdateEntityLayering;
	bool do_sort;
	bool correct_remove;
};

}
