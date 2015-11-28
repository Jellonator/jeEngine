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
class Group;

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
	void draw(const JE::GRAPHICS::Camera& camera);
	
	template <class EntityType, class... ArgType>
	EntityType& add(ArgType... args);
	
	void remove(Entity& entity);
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
	
	//Component Callers
	void callComponents(const std::string& name);
	void callComponentsGroup(const std::string& group, const std::string& component);
	
private:
	entity_vec entities;
	entity_vec entities_add;
	std::vector<Entity*> entities_remove;
	group_map entity_groups;
	
	bool needUpdateEntityLayering;
	bool do_sort;
	bool correct_remove;
};

template <class EntityType, class... ArgType>
EntityType& Group::add(ArgType... args){
	EntityType* entity_ptr = new EntityType(args...);
	EntityType& entity_ref = *entity_ptr;
	
	this->entities_add.push_back(std::unique_ptr<Entity>(entity_ptr));
	
	this->needUpdateEntityLayering = true;
	
	entity_ref._group = this;
	entity_ref.OnAdd(*this);
	
	return entity_ref;
}

}
