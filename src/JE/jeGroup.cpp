#include "JE/jeGroup.h"
#include "JE/jeEntity.h"
#include <algorithm>
#include <iostream>
namespace JE{

Group::Group(){
	this->needUpdateEntityLayering = false;
	this->do_sort = true;
	this->correct_remove = true;
}

Group::~Group(){
	//this->deleteAll();
}

void Group::update(float dt){
	this->updateEntities();
	for (auto& entity : this->entities){
		entity->OnUpdate(*this, dt);
	}
}

void Group::draw(){
	this->updateEntities();
	for (auto& entity : this->entities){
		entity->OnDraw();
	}
}

void Group::remove(const Entity& entity){
	entity_vec_iter iter = this->entities.begin();
	while (iter != this->entities.end()){
		//dereference iterator -> dereference unique_ptr -> pointer
		if (iter->get() == &entity) this->remove(iter);
		++iter;
	}
}

void Group::remove(entity_vec_iter index){
	this->entities_remove.push_back(index);
}

struct sort_entity_by_layer
{
    inline bool operator() (const Entity& entity_a, const Entity& entity_b)
    {
        return (entity_a.getLayer() < entity_b.getLayer());
    }
};

void Group::updateEntities(){
	for (entity_vec_iter iter = this->entities_add.begin(); iter != this->entities_add.end(); ++iter){
		this->entities.push_back(nullptr);
		std::unique_ptr<Entity>& ptr = this->entities.back();
		ptr.swap(*iter);
	}
	this->entities_add.clear();
	
	for (entity_vec::size_type i = 0; i != this->entities_remove.size(); ++i){
		std::unique_ptr<Entity>& entity = this->entities.at(i);
		for (std::vector<std::string>::iterator iter = entity->_groups_v.begin(); iter != entity->_groups_v.end(); ++iter){
			this->removeFromGroup(*iter, *entity);
		}
		//delete entity;
		this->entities.erase(this->entities_remove.at(i));
	}
	this->entities_remove.clear();
	
	if (this->needUpdateEntityLayering && this->do_sort){
		std::sort(this->entities.begin(), this->entities.end(),  [ ]( const std::unique_ptr<Entity>& lhs, const std::unique_ptr<Entity>& rhs )
		{
		   return lhs->getLayer() < rhs->getLayer();
		});
		this->needUpdateEntityLayering = false;
	}
}

void Group::clear(){
	this->entities.clear();
	this->entities_add.clear();
	this->entities_remove.clear();
}

void Group::setSort(bool sort){
	this->do_sort = sort;
}

void Group::setCorrectRemove(bool do_correct_remove){
	this->correct_remove = do_correct_remove;
}

entity_vec::size_type Group::getSize() const{
	return this->entities.size();
}

entity_vec::iterator Group::getBegin(){
	return this->entities.begin();
}

entity_vec::iterator Group::getEnd(){
	return this->entities.end();
}

bool Group::getSort() const{
	return this->do_sort;
}

bool Group::getCorrectRemove() const{
	return this->correct_remove;
}

Entity& Group::getEntity(entity_vec_size value){
	return *this->entities.at(value);
}

Entity& Group::operator[](entity_vec_size value){
	return *this->entities.at(value);
}

const Entity& Group::getEntity(entity_vec_size value) const{
	return *this->entities.at(value);
}

const Entity& Group::operator[](entity_vec_size value) const{
	return *this->entities.at(value);
}

void Group::addToGroup(const std::string& group, Entity& entity){
	this->entity_groups[group].push_back(&entity);
	entity._groups_v.push_back(group);
}

void Group::removeFromGroup(const std::string& group, Entity& entity){
	for (std::vector<Entity*>::iterator iter = this->entity_groups[group].begin(); iter != this->entity_groups[group].end(); ++iter){
		if (*iter == &entity){
			iter = this->entity_groups[group].erase(iter);
		} else {
			++iter;
		}
	}
	
	for (std::vector<std::string>::iterator iter = entity._groups_v.begin(); iter != entity._groups_v.end(); ++iter){
		if (*iter == group){
			iter = entity._groups_v.erase(iter);
		} else {
			++iter;
		}
	}
}

std::vector<Entity*>::iterator Group::getGroupBegin(const std::string& group){
	return this->entity_groups[group].begin();
}

std::vector<Entity*>::iterator Group::getGroupEnd(const std::string& group){
	return this->entity_groups[group].end();
}

entity_vec::size_type Group::getGroupSize(const std::string& group){
	return this->entity_groups[group].size();
}

bool Group::getCollideEntity(JE::Entity& entity, int move_x, int move_y, int* get_x, int* get_y){
	JE::MASK::Mask* mask = entity.getMask();
	if (mask == nullptr) return false;
	return this->getCollideMask(*mask, move_x, move_y, get_x, get_y);
}

bool Group::getCollideMask(JE::MASK::Mask& mask, int move_x, int move_y, int* get_x, int* get_y){
	std::vector<JE::MASK::Mask*> mask_vec;
	
	for (auto& entity : this->entities){
		JE::MASK::Mask* other_mask = entity->getMask();
		if (other_mask == nullptr || other_mask == &mask) continue;
		
		mask_vec.push_back(other_mask);
	}
	
	return mask.callCollideGroup(mask_vec, move_x, move_y, get_x, get_y);
}

bool Group::getCollideEntityGroup(JE::Entity& entity,  int move_x, int move_y, int* get_x, int* get_y, const std::string& group){
	JE::MASK::Mask* mask = entity.getMask();
	if (mask == nullptr) return false;
	return this->getCollideMaskGroup(*mask, move_x, move_y, get_x, get_y, group);
}

bool Group::getCollideMaskGroup(JE::MASK::Mask& mask,int move_x, int move_y, int* get_x, int* get_y, const std::string& group){
	std::vector<JE::MASK::Mask*> mask_vec;
	
	for (JE::Entity* entity : this->entity_groups[group]){
		JE::MASK::Mask* other_mask = entity->getMask();
		if (other_mask == nullptr || other_mask == &mask) continue;
		
		mask_vec.push_back(other_mask);
	}
	
	return mask.callCollideGroup(mask_vec, move_x, move_y, get_x, get_y);
}

bool Group::getCollideEntityGroups(JE::Entity& entity,  int move_x, int move_y, int* get_x, int* get_y, const std::vector<std::string>& groups){
	JE::MASK::Mask* mask = entity.getMask();
	if (mask == nullptr) return false;
	return this->getCollideMaskGroups(*mask, move_x, move_y, get_x, get_y, groups);
}

bool Group::getCollideMaskGroups(JE::MASK::Mask& mask,int move_x, int move_y, int* get_x, int* get_y, const std::vector<std::string>& groups){
	std::vector<JE::MASK::Mask*> mask_vec;
	
	for (auto& entity : this->entities){
		JE::MASK::Mask* other_mask = entity->getMask();
		if (other_mask == nullptr || other_mask == &mask) continue;
		
		bool do_add = false;
		for (const std::string& entity_group_name : entity->_groups_v){
			for (const std::string& group_name : groups){
				if (entity_group_name == group_name){
					do_add = true;
				}
			}
		}
		
		if (!do_add) continue;
		
		mask_vec.push_back(other_mask);
	}
	
	/* Previous method, might be slower. Or it might be faster. I don't really know for sure.
	 * I guess it depends on how it is used.
	 */
	/*
	for (const std::string& group_name : groups){
		for (JE::Entity* entity : this->entity_groups[group_name]){
			JE::MASK::Mask* other_mask = entity->getMask();
			if (other_mask == nullptr || other_mask == &mask) continue;
			
			mask_vec.push_back(other_mask);
		}
	}
	*/
	return mask.callCollideGroup(mask_vec, move_x, move_y, get_x, get_y);
}

}