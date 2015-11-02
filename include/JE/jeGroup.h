#pragma once
#include "jeMain.h"
#include "jeUtil.h"
#include "jeMask.h"
#include <vector>
#include <memory>
#include <string>
#include <map>

namespace JE{

class World;
class Entity;

typedef Entity* entity_def;
typedef std::vector<entity_def> entity_vec;
typedef std::vector<entity_def>::size_type entity_vec_size;
typedef std::vector<entity_def>::iterator entity_vec_iter;
typedef std::map<std::string, entity_vec> group_map;

class Group
{
public:
	Group();
	virtual ~Group();
	
	void update(float dt);
	void draw();
	
	template <class EntityType, class... ArgType>
	EntityType& add(ArgType... args){
		EntityType* e = new EntityType(args...);
		this->entities_add.push_back(e);
		return *e;
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
	entity_vec::iterator getGroupBegin(const std::string& group);
	entity_vec::iterator getGroupEnd(const std::string& group);
	entity_vec::size_type getGroupSize(const std::string& group);
	
	void getCollideEntity(     JE::Entity& entity,  int move_x, int move_y, int* get_x, int* get_y);
	void getCollideMask(       JE::MASK::Mask& mask,int move_x, int move_y, int* get_x, int* get_y);
	void getCollideEntityGroup(JE::Entity& entity,  int move_x, int move_y, int* get_x, int* get_y, const std::string& group);
	void getCollideMaskGroup(  JE::MASK::Mask& mask,int move_x, int move_y, int* get_x, int* get_y, const std::string& group);
	template <class... Arg>
	void getCollideEntityGroups(JE::Entity& entity,  int move_x, int move_y, int* get_x, int* get_y, Arg... groups);
	template <class... Arg>
	void getCollideMaskGroups(JE::MASK::Mask& mask,  int move_x, int move_y, int* get_x, int* get_y, Arg... groups);
	
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
